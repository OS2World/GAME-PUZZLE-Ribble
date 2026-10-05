//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//

#include "common.h"
#pragma hdrstop

#include "resources.h"
#include "ribble.h"
#include "map.h"
#include "screen.h"
#include "monster.h"
#include "man.h"
#include "edit.h"
#include "mainwin.h"
#include "spirit.h"
#include "slither.h"
#include "teleport.h"
#include "pal.h"
#include "about.h"
#include "help.h"
#include "level.h"
#include "save.h"
#include "options.h"
#include "config.h"
#include "hiscore.h"
#include "bomb.h"
#include "lang.h"

#include <stdio.h>

// BLDLEVEL string (plan.txt section 4): <Vendor>:<Version> signature followed
// by build date, platform tag and description.
const char BldLevel[] =
  "@#J.R.Shannon & D.J.Neades:1.1#@##1## 04 Oct 2026 00:00:00      "
  "ARCAOS:::0::::@@Ribble - Boulder Dash style puzzle game for OS/2\r\n\x1a";

int current_lang = LANG_ENGLISH;

static HWND langMenuHwnd = 0;

struct LangMenuItem
{
  SHORT itemId;      // command id on the popup
  SHORT popupId;     // containing top-level popup (menu bar id)
  int   string;      // STR_ index into LanguageStrings
};

static const LangMenuItem LocalizedItems[] =
{
  { IDM_GameStart,    IDM_GameMenu,      STR_MENU_NEW      },
  { IDM_GameAbandon,  IDM_GameMenu,      STR_MENU_END      },
  { IDM_GameOpen,     IDM_GameMenu,      STR_MENU_OPEN     },
  { IDM_GameSave,     IDM_GameMenu,      STR_MENU_SAVE     },
  { IDM_GameExit,     IDM_GameMenu,      STR_MENU_EXIT     },
  { IDM_EditLevel,    IDM_EditMenu,      STR_MENU_LEVEL    },
  { IDM_EditOptions,  IDM_EditMenu,      STR_MENU_OPTIONSDLG },
  { IDM_ViewMap,      IDM_GameMenu,      STR_MENU_VIEWMAP  },
  { IDM_ViewStatus,   IDM_GameMenu,      STR_MENU_VIEWSTATUS },
  { IDM_Settings,     IDM_OptionsMenu,   STR_MENU_SETTINGS },
  { IDM_FrameControl, IDM_OptionsMenu,   STR_MENU_FRAME   },
  { IDM_SaveOptions,  IDM_OptionsMenu,   STR_MENU_SAVEONEXIT },
  { IDM_About,        IDM_HelpMenu,      STR_MENU_ABOUT    }
};



MainWindow::MainWindow(HAB hab)
: CWinFramedClient(HWND_DESKTOP,
                   HWND_DESKTOP,
                   hab,
                   FCF_TITLEBAR | FCF_TASKLIST | FCF_SYSMENU | FCF_MINBUTTON | FCF_BORDER,
                   FALSE,
                   CS_SIZEREDRAW,
                   0, 0, 0, 0, 0,
                   FID_CLIENT,
                   IDW_MAIN)
{
  SetStyle(CS_CLIPCHILDREN | CS_CLIPSIBLINGS | CS_SIZEREDRAW);
  screen = 0;
  man = 0;
  map = 0;
  itemPalette = 0;
  eggHatchCnt = 0;
  fizzleCnt = 0;
  inGame = FALSE;
  teleporting = -1;
  gamestate = ShowTitle;
  hwndHelp = 0;
  restartLevel = FALSE;
  config = new RibbleConfig();
  config->LoadConfig();
  hwndTitleBar = hwndSysMenu = hwndMinMax = hwndMenuBar = hwndObject = 0;
  frameHidden = FALSE;
}


MainWindow::~MainWindow()
{
  WinStopTimer(QueryHAB(), HWindow, TimerID);
  WinStopTimer(QueryHAB(), HWindow, TitleID);

  HACCEL accel = WinQueryAccelTable(QueryHAB(), hwndFrame());
  if (accel)
    WinDestroyAccelTable(accel);

  RemoveMonsters();

  if (itemPalette)
    delete itemPalette;
  if (man)
    delete man;
  if (screen)
    delete screen;
  if (map)
    delete map;

  // Restore hidden frame controls before the frame and parking window go away
  if (frameHidden && hwndObject)
    {
      WinSetParent(hwndTitleBar, hwndFrame(), FALSE);
      WinSetParent(hwndSysMenu, hwndFrame(), FALSE);
      WinSetParent(hwndMinMax, hwndFrame(), FALSE);
      WinSetParent(hwndMenuBar, hwndFrame(), FALSE);
    }
  if (hwndObject)
    WinDestroyWindow(hwndObject);

  // "Save settings on exit" (plan.txt 6.9)
  if (config->QuerySaveConfig())
    config->SaveConfig();

  delete config;
}

void
MainWindow::SetupWindow(void)
{
  title("Ribble - Game view");

  HPOINTER ptr = WinLoadPointer(HWND_DESKTOP, 0, IDW_MAIN);
  if (ptr)
    WinSendMsg(hwndFrame(), WM_SETICON, (MPARAM)ptr, MPVOID);

  HACCEL accel = WinLoadAccelTable(QueryHAB(), 0, IDW_MAIN);
  if (accel)
    WinSetAccelTable(QueryHAB(), accel, hwndFrame());

  hwndMenu = WinLoadMenu(hwndFrame(), 0, IDM_MainMenu);

  langMenuHwnd = hwndMenu;

  // Frame Controls (plan.txt 16.10): capture frame children AFTER the frame
  // exists and create the parking window used to hide them.
  hwndTitleBar = WinWindowFromID(hwndFrame(), FID_TITLEBAR);
  hwndSysMenu  = WinWindowFromID(hwndFrame(), FID_SYSMENU);
  hwndMinMax   = WinWindowFromID(hwndFrame(), FID_MINMAX);
  hwndMenuBar  = WinWindowFromID(hwndFrame(), FID_MENU);
  hwndObject   = WinCreateWindow(HWND_OBJECT, WC_FRAME, "",
                                 0L, 0, 0, 0, 0,
                                 NULLHANDLE, HWND_TOP, 0, NULL, NULL);

  // Apply persisted language (plan.txt 8.4) and Settings checkmark
  SetLanguage(config->QueryLang());
  WinCheckMenuItem(hwndMenu, IDM_SaveOptions, config->QuerySaveConfig() ? TRUE : FALSE);
  WinCheckMenuItem(hwndMenu, IDM_FrameControl, FALSE);

  InitHelp();

  EnableMenuItems(FALSE); // set states when not playing

  char* font = "12.Helv";
  WinSetPresParam(HWindow, PP_FONTNAMESIZE, strlen(font)+1, (PVOID)font);

  screen = new Screen(this);

  int wid = config->QueryVisWidth() * config->QueryCellWidth();
  int hgt = config->QueryVisHeight() * config->QueryCellHeight() + resHgt;

  RECTL req;
  req.xLeft = 0;
  req.xRight = wid;
  req.yBottom = 0;
  req.yTop = hgt;

  WinCalcFrameRect(hwndFrame(), &req, FALSE);

  memset(&border, 0, sizeof(RECTL));

  move(64, 64,
       req.xRight - req.xLeft,
       req.yTop - req.yBottom);

  WinSetFocus(HWND_DESKTOP, HWindow);
  show();

  WinStartTimer(QueryHAB(), HWindow, TitleID, titleTimeInterval);
}

MRESULT
MainWindow::ProcessMsg(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  switch (msg)
    {
    case WM_ResetSize:
      ResetSize();
      return 0;

    case WM_GiveFocus:
      WinSetFocus(HWND_DESKTOP, HWindow);
      return 0;

    case WM_COMMAND:
      return ProcessCmd(mp1, mp2);

    case WM_BUTTON1DOWN:
      WinSetFocus(HWND_DESKTOP, HWindow);
      return 0;

    case WM_SETFOCUS:
      {
        if (inGame == TRUE)
          {
            if (SHORT1FROMMP(mp2) == TRUE)
              {
                if (man->IsMan())
                  WinStartTimer(QueryHAB(), HWindow, TimerID, config->QueryRefreshRate());
              }
            else
              WinStopTimer(QueryHAB(), HWindow, TimerID);
          }
        return 0;
      }

    case WM_PAINT:
      Paint();
      return 0;

    case WM_CHAR:
      return WMChar();

    case WM_SIZE:
      WinQueryWindowRect(HWindow, &border);
      return 0;

    case WM_TIMER:
      {
        switch (SHORT1FROMMP(mp1))
          {
          case TimerID:
            WinStartTimer(QueryHAB(), HWindow, TimerID, config->QueryRefreshRate());
            WMTimer();
            return 0;
          case TitleID:
            WinStartTimer(QueryHAB(), HWindow, TitleID, titleTimeInterval);
            HandleTitle();
            return 0;
          }
        break;
      }

    case HM_QUERY_KEYS_HELP:    /* Keys Help selected in Help manager window - give it ID of my keys help page */
      {
        return (MRESULT)pKEYS;   /* return id of key help panel */
      }
    }
  return CWinFramedClient::ProcessMsg(hwnd, msg, mp1, mp2);
}


void
MainWindow::Paint(void)
{
  HPS hps = WinBeginPaint(HWindow, 0, 0);

  if (inGame == TRUE)
    {
      switch (gamestate)
        {
        case ShowStatus:
          RenderStatus(hps);
          break;
        case ShowMap:
          RenderPanel(hps);
          RenderMap();
          screen->BlitScreen(hps, 0, 0);
          break;
        case PlayGame:
        case Teleporting:
          RenderPanel(hps);
          RenderScreen();
          screen->BlitScreen(hps, 0, 0);
          break;
        }
    }
  else
    {
      switch (gamestate)
        {
        case ShowHiscores:
          ShowScores(hps);
          break;
        case ShowTitle:
          ShowTitleBitmap(hps);
          break;
        }
    }

  RECTL palSpace;
  palSpace.xLeft = config->QueryCellWidth() * config->QueryVisWidth();
  palSpace.xRight = border.xRight;
  palSpace.yTop = border.yTop;
  palSpace.yBottom = border.yBottom;

  WinFillRect(hps, &palSpace, CLR_BLACK);

  WinEndPaint(hps);
}

void
MainWindow::WMTimer(void)
{
  if (inGame == TRUE)
    HandleThings();
}

MRESULT
MainWindow::ProcessCmd(MPARAM mp1, MPARAM mp2)
{
  PCMDMSG cmdmsg = (PCMDMSG)MsgSpec;
  switch (cmdmsg->cmd)
    {
    case IDM_GameStart:
      EndGame();
      InitGame();
      break;
    case IDM_GameAbandon:
      if (inGame == TRUE)
        {
          oldScore = score;
          EndGame();
          HandleHiscores();
          break;
        }
    case IDM_GameOpen:
      ChooseLevel();
      break;
    case IDM_GameExit:
      WinPostMsg(HWindow, WM_CLOSE, MPVOID, MPVOID);
      break;
    case IDM_EditLevel:
      SwapEdit();
      break;
    case IDM_EditOptions:
      OptionsDialog();
      break;
    case IDM_ViewMap:
      ToggleMap();
      break;
    case IDM_ViewStatus:
      WinStartTimer(QueryHAB(), HWindow, TitleID, titleTimeInterval);
      gamestate = ShowStatus;
      WinInvalidateRect(HWindow, 0, FALSE);
      break;
    case IDM_GameSave:
      if (inGame)
        HandleLevelSave();
      break;
    case IDM_HelpGeneral:
      if (hwndMenu)
        WinSendMsg(hwndHelp, HM_DISPLAY_HELP, MPFROMLONG(pMAINPANEL), MPFROMLONG(HM_RESOURCEID));
      break;
    case IDM_HelpIndex:
      if (hwndMenu)
        WinSendMsg(hwndHelp, HM_HELP_INDEX, MPVOID, MPVOID);
      break;
    case IDM_HelpKeys:
      if (hwndMenu)
        WinSendMsg(hwndHelp, HM_DISPLAY_HELP, MPFROMLONG(pKEYS), MPFROMLONG(HM_RESOURCEID));
      break;
    case IDM_HelpUsing:
      if (hwndMenu)
        WinSendMsg(hwndHelp, HM_DISPLAY_HELP, MPVOID, MPVOID);
      break;
    case IDM_Settings:
      OptionsDialog();
      break;
    case IDM_SaveOptions:
      config->SetSaveConfig(config->QuerySaveConfig() ? 0 : 1);
      WinCheckMenuItem(hwndMenu, IDM_SaveOptions, config->QuerySaveConfig() ? TRUE : FALSE);
      break;
    case IDM_FrameControl:
      ToggleFrameControls();
      break;
    case IDM_LANG_EN:
    case IDM_LANG_ES:
    case IDM_LANG_NL:
    case IDM_LANG_DE:
    case IDM_LANG_FR:
    case IDM_LANG_IT:
      SetLanguage(cmdmsg->cmd - IDM_LANG_BASE);
      config->SetLang(current_lang);
      TermHelp();
      InitHelp();
      break;
    case IDM_About:
      {
        ProductInfoDlg info(HWindow);
        info.Create();
        break;
      }
    }
  mp1; mp2;
  return (MRESULT)0;
}


MRESULT
MainWindow::WMChar(void)
{
  PCHRMSG charmsg = (PCHRMSG)MsgSpec;
  USHORT fs = charmsg->fs;
  BOOL fProcessed = FALSE;

  if (fs & KC_INVALIDCHAR)
    {
    }
  else if (man)
    {
      if (fs & KC_VIRTUALKEY)
        {
          fProcessed = TRUE;

          // Space bar toggles map on/off

          if (!(fs & KC_KEYUP) && charmsg->vkey == VK_SPACE)
            {
              ToggleMap();
            }

          switch (charmsg->vkey)
            {
            case VK_LEFT:
              {
                man->KeySet(LeftKey, fs);
                break;
              }
            case VK_RIGHT:
              {
                man->KeySet(RightKey, fs);
                break;
              }
            case VK_UP:
              {
                man->KeySet(UpKey, fs);
                break;
              }
            case VK_DOWN:
              {
                man->KeySet(DownKey, fs);
                break;
              }
            }

          switch (charmsg->vkey)
            {
            case VK_NEWLINE:
            case VK_ENTER:
              {
                if (!(fs & KC_KEYUP) && itemPalette)
                  {
                    if (man->IsMan() == FALSE)
                      {
                        Edit* edit = (Edit*)man;
                        if (edit->QueryHoldNum())
                          {
                            Teleport* tele = LocateTeleport(edit->QueryHoldNum());
                            if (tele)
                              {
                                tele->SetDestX(edit->QueryXPos() / config->QueryStepX());
                                tele->SetDestY(edit->QueryYPos() / config->QueryStepY());
                              }
                            edit->SetHoldNum(0);
                            break;
                          }
                      }
                    int item = itemPalette->QueryCurrentChoice();
                    SetMapItem(item);
                  }
                break;
              }
            case VK_INSERT:
              {
                HandleInsert();
                break;
              }
            case VK_DELETE:
              {
                HandleDelete();
                break;
              }
            case VK_ESC:
              {
                if (!(fs & KC_KEYUP))
                  HandleEscape();
                break;
              }
            }
        }

      if (man->IsMan() == FALSE)
        {
          man->Move();
          UpdateScreen();
        }
    }
  return (MRESULT)fProcessed;
}


void
MainWindow::ShowTitleBitmap(HPS hps)
{
  HBITMAP bmp = GpiLoadBitmap(hps,
                              0,
                              BMP_Title,
                              config->QueryCellWidth() * config->QueryVisWidth(),
                              config->QueryCellHeight() * config->QueryVisHeight());
  if (bmp)
    {
      POINTL pts[3];
      pts[0].x = 0;
      pts[0].y = 0;
      pts[1].x = config->QueryCellWidth() * config->QueryVisWidth();
      pts[1].y = config->QueryCellHeight() * config->QueryVisHeight();
      pts[2].x = 0;
      pts[2].y = 0;
      GpiWCBitBlt(hps, bmp, 3, pts, ROP_SRCCOPY, 0);
      GpiDeleteBitmap(bmp);

      RECTL rct;
      rct.xLeft = 0;
      rct.xRight = border.xRight;
      rct.yTop = border.yTop;
      rct.yBottom = rct.yTop - resHgt;

      WinDrawText(hps,
                  -1,
                  (PSZ)"(c) 1994 D.J.Neades and J.R.Shannon",
                  &rct,
                  CLR_GREEN,
                  CLR_BLACK,
                  DT_CENTER | DT_VCENTER | DT_ERASERECT
		  );
    }
  else
    {
      WinFillRect(hps, &border, CLR_RED);
    }
}

void
MainWindow::RenderPanel(HPS hps)
{
  RenderScore(hps);
  RenderTime(hps);
  RenderLives(hps);
  RenderDiamonds(hps);

  RECTL rct;
  rct.xLeft = RemainingX;
  rct.xRight = border.xRight;
  rct.yTop = border.yTop;
  rct.yBottom = config->QueryCellHeight() * config->QueryVisHeight(); //rct.yTop - resHgt;

  HPS usePS = hps ? hps : WinGetPS(HWindow);
  WinFillRect(usePS, &rct, CLR_BLACK);
  if (hps == 0)
    WinReleasePS(usePS);
}

void
MainWindow::RenderItem(HPS hps, int _off, int _wid, char* title, char* fmt, int val)
{
  HPS usePS = hps ? hps : WinGetPS(HWindow);

  char buffer[64];
  strcpy(buffer, title);

  RECTL rct = border;
  rct.xLeft = _off;
  rct.xRight = rct.xLeft + _wid;
  rct.yBottom = config->QueryCellHeight() * config->QueryVisHeight(); //rct.yTop - resHgt;

  WinDrawText(usePS,
              -1,
              (PSZ)buffer,
              &rct,
              CLR_GREEN,
              CLR_BLACK,
              DT_CENTER | DT_TOP | DT_ERASERECT);

  sprintf(buffer, fmt, val);

  WinDrawText(usePS,
              -1,
              (PSZ)buffer,
              &rct,
              CLR_GREEN,
              CLR_BLACK,
              DT_CENTER | DT_BOTTOM);

  if (hps == 0)
    WinReleasePS(usePS);
}


void
MainWindow::RenderScore(HPS hps)
{
  RenderItem(hps, ScoreX, ItemW1, "Score", "%05d", score);
}

void
MainWindow::RenderTime(HPS hps)
{
  RenderItem(hps, TimeX, ItemW1, "Time", "%04d", time / TimeScale);
}

void
MainWindow::RenderLives(HPS hps)
{
  RenderItem(hps, LivesX, ItemW1, "Lives", "%d", lives);
}

void
MainWindow::RenderDiamonds(HPS hps)
{
  RenderItem(hps, DiamondsX, ItemW2, "Diamonds", "%d", diamonds);
}

void
MainWindow::SwapEdit(void)
{
  if (inGame == TRUE)
    {
      if (man == 0)
        {
          man = new Edit(this);
          WinCheckMenuItem(hwndMenu, IDM_EditLevel, TRUE);
        }
      else
        {
          Man* old = man;
          int x = man->QueryXPos();
          int y = man->QueryYPos();
          if (man->IsMan() == TRUE)
            {
              CreateItemPalette();
              man = new Edit(this, x - (x % config->QueryStepX()), y - (y % config->QueryStepY()));
            }
          else
            {
              RemoveItemPalette();
              man = new Man(this, x, y);
            }
          delete old;
        }
    }
}


void
MainWindow::RestartCurrentLevel(void)
{
  restartLevel = FALSE;
  int mapNum = map->QueryLevelNum();
  delete man; man = 0;
  delete map; map = 0;
  InitGame(mapNum, FALSE);
}

// Returns TRUE if there are no more levels

BOOL
MainWindow::InitGame(int _level, BOOL _realStart)
{
  if (_realStart == TRUE)
    {
      score = 0;
      lives = 3;
    }

  RemoveItemPalette();

  teleporting = -1;
  gamestate = PlayGame;
  RemoveMonsters();

  char buffer[StringLimit];
  sprintf(buffer, "levels/level.%d", _level);

  map = new Map(this, buffer);

  if (_level != 1 && !map->UserMap())
    {
      // All levels completed...  No more!
      if (_realStart == TRUE)
        EndGame();
      return TRUE;
    }

  diamonds = map->QueryNumDiamonds();
  time = map->QueryMapTime() * TimeScale;
  man = new Man(this,
                map->QueryInitialX() * config->QueryStepX(),
                map->QueryInitialY() * config->QueryStepY());
  RenderPanel();

  EnableMenuItems();

  CString text  = "Ribble - ";
  text += map->QueryTitle();
  title(text);

  // ------------------------------
  inGame = TRUE;
  WinStartTimer(QueryHAB(), HWindow, TimerID, config->QueryRefreshRate());

  return FALSE;
}

void
MainWindow::EndGame(GameState _newstate)
{
  if (inGame == TRUE)
    {
      WinStopTimer(QueryHAB(), HWindow, TimerID);
      inGame = FALSE;
      gamestate = _newstate;

      RemoveItemPalette();

      delete man;
      man = 0;
      delete map;
      map = 0;

      WinInvalidateRect(HWindow, 0, FALSE);

      EnableMenuItems(FALSE);
      WinStartTimer(QueryHAB(), HWindow, TitleID, titleTimeInterval);

      title("Ribble - Game view");
    }
}

void
MainWindow::StartNextLevel(void)
{
  int nextNum = map->QueryLevelNum() + 1;

  delete man;
  man = 0;
  delete map;
  map = 0;

  oldScore = score;

  BOOL completed = InitGame(nextNum, FALSE);

  if (completed == TRUE)
    {
      EndGame();
      HandleHiscores();
    }
}


void
MainWindow::HandleInsert(void)
{
  // See if we're above a teleporter.

  if (man->IsMan() == FALSE)
    {
      Edit* edit = (Edit*)man;

      int x = man->QueryXPos();
      int y = man->QueryYPos();

      int mx = x / config->QueryStepX();
      int my = y / config->QueryStepY();

      Teleport* teleport = LocateTeleDest(mx, my);

      if (teleport)
        {
          edit->SetHoldNum(teleport->QueryTeleNum());
          UpdateScreen();
        }
    }
}

void
MainWindow::HandleDelete(void)
{
  if (man->IsMan() == FALSE)
    {
      int x = man->QueryXPos();
      int y = man->QueryYPos();
      int mx = x / config->QueryStepX();
      int my = y / config->QueryStepY();

      MonsterListIter it(monsters);
      while (it)
        {
          Monster* m = it.current();
          if (m->OverlapsMapLocn(mx, my))
            it.remove();
          else
            it++;
        }
      UpdateScreen();
    }
}


int
main(void)
{
  volatile const char* probe = BldLevel;   // keep BLDLEVEL string in the image
  (void)probe;

  CApplication app;
  MainWindow win(app.QueryHAB());
  win.Create();
  app.Run();
  return 0;
}


// Per-language on-line help libraries (translated IPF files, same panel ids)
static const char* helpLibs[NUM_LANGUAGES] =
  {
    "help/ribble-en.hlp",  // LANG_ENGLISH
    "help/ribble-es.hlp",  // LANG_SPANISH
    "help/ribble-nl.hlp",  // LANG_DUTCH
    "help/ribble-de.hlp",  // LANG_GERMAN
    "help/ribble-fr.hlp",  // LANG_FRENCH
    "help/ribble-it.hlp"   // LANG_ITALIAN
  };

void
MainWindow::InitHelp(void)
{
  HELPINIT init;
  memset(&init, 0, sizeof(init));

  init.cb = sizeof(init);
  init.phtHelpTable = (PHELPTABLE)MAKEULONG(ID_HELPTABLE, 0xffff);
  init.pszHelpWindowTitle = (PSZ)"Ribble Information";
  init.fShowPanelId = CMIC_HIDE_PANEL_ID;
  init.pszHelpLibraryName = (PSZ)helpLibs[current_lang];

  BOOL success = TRUE;

  hwndHelp = WinCreateHelpInstance(QueryHAB(), &init);

  if (hwndHelp == 0)
    {
      success = FALSE;
    }
  else
    {
      success = WinAssociateHelpInstance(hwndHelp, hwndFrame());
    }
  if (success == FALSE)
    {
      WinMessageBox(HWND_DESKTOP, HWindow,
                    (PSZ)"Couldn't find Ribble on-line help. Help will be disabled.",
                    (PSZ)"Ribble help error",
                    1,
                    MB_OK | MB_INFORMATION | MB_MOVEABLE);

      WinEnableMenuItem(hwndMenu, IDM_HelpIndex, FALSE);
      WinEnableMenuItem(hwndMenu, IDM_HelpGeneral, FALSE);
      WinEnableMenuItem(hwndMenu, IDM_HelpUsing, FALSE);
      WinEnableMenuItem(hwndMenu, IDM_HelpKeys, FALSE);

      TermHelp();
    }
}

void
MainWindow::ChooseLevel(void)
{
  SelectLevel select(this, HWindow);
  select.Create();
}


void
MainWindow::TermHelp(void)
{
  if (hwndHelp)
    {
      WinAssociateHelpInstance(0, hwndFrame());
      WinDestroyHelpInstance(hwndHelp);
      hwndHelp = 0;
    }
}

void
SetLanguage(int lang)
{
  if (lang < 0 || lang >= NUM_LANGUAGES)
    return;
  current_lang = lang;
  ApplyLanguageMenu();
}

void
ApplyLanguageMenu(void)
{
  if (langMenuHwnd == 0)
    return;

  // Top-level popup titles (Game, Edit, Options, Language, Help).
  // The Map Editor submenu is NESTED inside Options, so it cannot be
  // resolved directly from the menu bar - it is handled separately below.
  static const struct { SHORT popupId; int string; } topMenus[] =
    {
      { IDM_GameMenu,    STR_MENU_GAME    },
      { IDM_OptionsMenu, STR_MENU_OPTIONS },
      { IDM_LangMenu,    STR_MENU_LANGUAGE},
      { IDM_HelpMenu,    STR_MENU_HELP    },
    };

  for (int i = 0; i < sizeof(topMenus)/sizeof(topMenus[0]); i++)
    WinSendMsg(langMenuHwnd, MM_SETITEMTEXT,
               MPFROMSHORT(topMenus[i].popupId),
               MPFROMP((PSZ)LanguageStrings[current_lang][topMenus[i].string]));

  // Resolve the popup handles: top-level popups live on the menu bar
  // itself, but the Map Editor submenu lives inside the Options popup.
  MENUITEM mi;
  HWND hwndPopup = 0;
  HWND optionsPopup = 0;
  HWND editPopup = 0;

  memset(&mi, 0, sizeof(mi));
  mi.iPosition = -1;
  if (WinSendMsg(langMenuHwnd, MM_QUERYITEM,
                 MPFROMSHORT(IDM_OptionsMenu), MPARAM(&mi)))
    optionsPopup = mi.hwndSubMenu;

  if (optionsPopup)
    {
      memset(&mi, 0, sizeof(mi));
      mi.iPosition = -1;
      if (WinSendMsg(optionsPopup, MM_QUERYITEM,
                     MPFROMSHORT(IDM_EditMenu), MPARAM(&mi)))
        editPopup = mi.hwndSubMenu;
    }

  // Localize the Map Editor submenu title inside the Options popup
  if (optionsPopup)
    WinSendMsg(optionsPopup, MM_SETITEMTEXT,
               MPFROMSHORT(IDM_EditMenu),
               MPFROMP((PSZ)LanguageStrings[current_lang][STR_MENU_MAPEDITOR]));

  // Items inside popups
  for (int n = 0; n < sizeof(LocalizedItems)/sizeof(LocalizedItems[0]); n++)
    {
      memset(&mi, 0, sizeof(mi));
      mi.iPosition = -1;

      // resolve the popup handle first (the Map Editor items live in a
      // nested popup, not directly on the menu bar)
      hwndPopup = 0;
      if (LocalizedItems[n].popupId == IDM_EditMenu)
        hwndPopup = editPopup;
      else if (WinSendMsg(langMenuHwnd, MM_QUERYITEM,
                          MPFROMSHORT(LocalizedItems[n].popupId), MPARAM(&mi)))
        hwndPopup = mi.hwndSubMenu;

      if (hwndPopup)
        WinSendMsg(hwndPopup, MM_SETITEMTEXT,
                   MPFROMSHORT(LocalizedItems[n].itemId),
                   MPFROMP((PSZ)LanguageStrings[current_lang][LocalizedItems[n].string]));
    }

  // Language names never change (plan 8.3); just check the active one
  for (int i = 0; i < NUM_LANGUAGES; i++)
    WinCheckMenuItem(langMenuHwnd, IDM_LANG_BASE + i, current_lang == i);
}

void
MainWindow::ToggleFrameControls(void)
{
  if (hwndObject == 0)
    return;

  frameHidden = frameHidden ? FALSE : TRUE;

  HWND hwnds[4];
  hwnds[0] = hwndTitleBar;
  hwnds[1] = hwndSysMenu;
  hwnds[2] = hwndMinMax;
  hwnds[3] = hwndMenuBar;

  for (int i = 0; i < 4; i++)
    WinSetParent(hwnds[i], frameHidden ? hwndObject : hwndFrame(), FALSE);

  WinSendMsg(hwndFrame(), WM_UPDATEFRAME,
             MPFROMLONG(FCF_TITLEBAR | FCF_SYSMENU | FCF_MINBUTTON | FCF_MENU),
             MPVOID);
  WinInvalidateRect(hwndFrame(), 0, TRUE);
  WinUpdateWindow(hwndFrame());

  // Recompute the frame size for the new decoration layout (plan 16.10)
  int wid = config->QueryVisWidth() * config->QueryCellWidth();
  int hgt = config->QueryVisHeight() * config->QueryCellHeight() + resHgt;

  RECTL req;
  req.xLeft = 0;
  req.xRight = wid;
  req.yBottom = 0;
  req.yTop = hgt;
  WinCalcFrameRect(hwndFrame(), &req, FALSE);

  WinSetWindowPos(hwndFrame(), HWND_TOP, 0, 0,
                  req.xRight - req.xLeft,
                  req.yTop - req.yBottom,
                  SWP_SIZE);

  WinCheckMenuItem(hwndMenu, IDM_FrameControl, frameHidden ? TRUE : FALSE);
}

void
MainWindow::EnableMenuItems(BOOL _inGame)
{
  WinEnableMenuItem(hwndMenu, IDM_ViewMap, _inGame);
  WinEnableMenuItem(hwndMenu, IDM_ViewStatus, _inGame);
  WinEnableMenuItem(hwndMenu, IDM_GameAbandon, _inGame);
  WinEnableMenuItem(hwndMenu, IDM_EditLevel, _inGame);
  WinEnableMenuItem(hwndMenu, IDM_GameSave, _inGame);
  WinEnableMenuItem(hwndMenu, IDM_GameSaveAs, _inGame);
}

void
MainWindow::ToggleMap(void)
{
  if (gamestate != ShowMap)
    {
      gamestate = ShowMap;
      RenderMap();
      WinInvalidateRect(HWindow, 0, FALSE);
    }
  else
    gamestate = PlayGame;

  WinCheckMenuItem(hwndMenu, IDM_ViewMap, gamestate == ShowMap);
}

void
MainWindow::HandleLevelSave(void)
{
  SaveLevel save(this, HWindow);
  save.Create();

}

void
MainWindow::OptionsDialog(void)
{
  GameOptions options(this, HWindow);
  options.Create();
}

void
MainWindow::ResetSize(void)
{
  int wid = config->QueryVisWidth() * config->QueryCellWidth();
  int hgt = config->QueryVisHeight() * config->QueryCellHeight() + resHgt;

  RECTL req;
  req.xLeft = 0;
  req.xRight = wid;
  req.yBottom = 0;
  req.yTop = hgt;

  WinCalcFrameRect(hwndFrame(), &req, FALSE);

  memset(&border, 0, sizeof(RECTL));

  screen->ClearBitmaps();

  if (itemPalette)
    {
      RemoveItemPalette();
      CreateItemPalette();
    }
  else
    size(req.xRight - req.xLeft, req.yTop - req.yBottom);
}

void
MainWindow::CreateItemPalette(void)
{
  if (itemPalette == 0)
    {
      WinStopTimer(QueryHAB(), HWindow, TimerID);

      itemPalette = new ItemPalette(this);
      itemPalette->Create();

      RECTL itemRct;
      WinQueryWindowRect(itemPalette->HWindow, &itemRct);

      int vWid = config->QueryCellWidth() * config->QueryVisWidth();
      int vHgt = config->QueryCellHeight() * config->QueryVisHeight() + resHgt;

      int itemWid = itemRct.xRight - itemRct.xLeft;
      int wid = vWid + itemWid;
      int hgt = Max(vHgt, (int)(itemRct.yTop - itemRct.yBottom));

      RECTL winRct;
      winRct.xLeft = winRct.yBottom = 0;
      winRct.xRight = wid; winRct.yTop = hgt;
      WinCalcFrameRect(hwndFrame(), &winRct, FALSE);
      wid = winRct.xRight - winRct.xLeft;
      hgt = winRct.yTop - winRct.yBottom;

      WinSetWindowPos(hwndFrame(), 0, 0, 0, wid, hgt, SWP_SIZE);
      WinSetWindowPos(itemPalette->HWindow, 0, winRct.xRight - itemWid, 0, 0, 0, SWP_MOVE);
      itemPalette->show();

      WinCheckMenuItem(hwndMenu, IDM_EditLevel, TRUE);
    }
}

void
MainWindow::RemoveItemPalette(void)
{
  if (itemPalette)
    {
      delete itemPalette;
      itemPalette = 0;
    }
  int wid = config->QueryCellWidth() * config->QueryVisWidth();
  int hgt = config->QueryCellHeight() * config->QueryVisHeight() + resHgt;

  RECTL winRct;
  winRct.xLeft = winRct.yBottom = 0;
  winRct.xRight = wid; winRct.yTop = hgt;
  WinCalcFrameRect(hwndFrame(), &winRct, FALSE);
  wid = winRct.xRight - winRct.xLeft;
  hgt = winRct.yTop - winRct.yBottom;

  WinSetWindowPos(hwndFrame(), 0, 0, 0, wid, hgt, SWP_SIZE);

  WinStartTimer(QueryHAB(), HWindow, TimerID, config->QueryRefreshRate());
  WinCheckMenuItem(hwndMenu, IDM_EditLevel, FALSE);
}

void
MainWindow::HandleTitle(void)
{
  if (inGame == FALSE)
    {
      if (gamestate == ShowHiscores)
        gamestate = ShowTitle;
      else if (gamestate == ShowTitle)
        gamestate = ShowHiscores;

      WinInvalidateRect(HWindow, 0, FALSE);
    }
  else
    {
      if (gamestate == ShowStatus)
        {
          gamestate = PlayGame;
          WinInvalidateRect(HWindow, 0, FALSE);
        }
    }
}

void
MainWindow::HandleHiscores(void)
{
  HiscoreDialog hiScore(this, HWindow, oldScore);
  hiScore.Create();
  WinStartTimer(QueryHAB(), HWindow, TitleID, titleTimeInterval);
  gamestate = ShowHiscores;
  WinInvalidateRect(HWindow, 0, FALSE);
}

const int numScoreVerdicts = 11;

char* scoreVerdicts[] = {
  "Cabbage",            // 0000
  "Hopeless",           // 0400
  "Miserable",          // 0800
  "Pathetic",           // 1200
  "Promising",          // 1600
  "Satisfactory",       // 2000
  "Good",               // 2400
  "Excellent",          // 2800
  "Amazing",            // 3200
  "Incredible",         // 3600
  "Suspicious"          // 4000
  };

void
MainWindow::ShowScores(HPS _hps)
{
  WinFillRect(_hps, &border, CLR_BLACK);

  // Centre the title text in the top 32 pixels of the window.

  RECTL rct = border;
  rct.yBottom = rct.yTop - 31;

  WinDrawText(_hps, -1, (PSZ)"- Ribble Addicts -", &rct, CLR_CYAN, CLR_BLACK, DT_CENTER | DT_VCENTER | DT_MNEMONIC);

  int scoreWidth = 72;
  int nameWidth = 162;
  int verdictWidth = 84;

  int totalWidth = scoreWidth + nameWidth + verdictWidth;
  int totalHeight = ScoreTableLen * 27;

  int scrWid = border.xRight;
  int scrHgt = border.yTop - 32;

  int xOff = 0;
  int yOff = 0;

  if (scrWid < totalWidth)
    totalWidth = scrWid;
  if (scrHgt < totalHeight)
    totalHeight = scrHgt;

  xOff = (scrWid - totalWidth)  / 2;
  yOff = (scrHgt - totalHeight) / 2;

  rct.xLeft = xOff;
  rct.xRight = border.xRight - xOff;
  rct.yTop = border.yTop - 32 - yOff;
  rct.yBottom = rct.yTop - 27;

  for (int i = 0; i < ScoreTableLen; i++)
    {
      char text[StringLimit];
      RibbleConfig::ScoreItem score;

      config->LoadScoreItem(i, &score);

      rct.xLeft = xOff;
      rct.xRight = rct.xLeft + scoreWidth;

      sprintf(text, "%06d", score.score);
      WinDrawText(_hps, -1, (PSZ)text, &rct, CLR_YELLOW, CLR_BLACK, DT_LEFT | DT_VCENTER | DT_MNEMONIC);

      rct.xLeft = rct.xRight;
      rct.xRight = rct.xLeft + nameWidth;
      WinDrawText(_hps, -1, (PSZ)score.text, &rct, CLR_GREEN, CLR_BLACK, DT_LEFT | DT_VCENTER | DT_MNEMONIC);

      if (score.score)
        {
          rct.xLeft = rct.xRight;
          rct.xRight = rct.xLeft + verdictWidth;

          int verdict = score.score / 400;

          if (verdict >= numScoreVerdicts)
            verdict = numScoreVerdicts - 1;

          WinDrawText(_hps, -1, (PSZ)scoreVerdicts[verdict], &rct, CLR_PINK, CLR_BLACK, DT_LEFT | DT_VCENTER | DT_MNEMONIC);
        }

      rct.yTop -= 27;
      rct.yBottom -= 27;
    }
}

void
MainWindow::RenderStatus(HPS _hps)
{
  WinFillRect(_hps, &border, CLR_BLACK);

  char buffer[128];

  int statusWidth = 140;
  int statusHeight = 10 * 24;

  int scrWid = config->QueryCellWidth()  * config->QueryVisWidth();
  int scrHgt = config->QueryCellHeight() * config->QueryVisHeight();

  int xOff = 0;
  int yOff = 0;

  if (scrWid < statusWidth)
    statusWidth = scrWid;
  if (scrHgt < statusHeight)
    statusHeight = scrHgt;

  xOff = (scrWid - statusWidth)  / 2;
  yOff = (scrHgt - statusHeight) / 2;

  RECTL rct;

  rct.xLeft = xOff;
  rct.xRight = scrWid - xOff;
  rct.yTop = scrHgt - yOff;
  rct.yBottom = rct.yTop - 24;

  WinDrawText(_hps, -1, (PSZ)(char*)map->QueryTitle(), &rct, CLR_YELLOW, CLR_BLACK, DT_CENTER | DT_VCENTER | DT_MNEMONIC);

  rct.yTop -= 24;
  rct.yBottom -= 24;
  WinDrawText(_hps, -1, (PSZ)(char*)map->QueryAuthor(), &rct, CLR_GREEN, CLR_BLACK, DT_CENTER | DT_VCENTER | DT_MNEMONIC);

  rct.yTop -= 24;
  rct.yBottom -= 24;
  WinDrawText(_hps, -1, (PSZ)(char*)map->QueryComment(), &rct, CLR_PINK, CLR_BLACK, DT_CENTER | DT_VCENTER | DT_MNEMONIC);

  rct.yTop -= 16 * 3;
  rct.yBottom -= 16 * 3;
  WinDrawText(_hps, -1, (PSZ)"Score", &rct, CLR_CYAN, CLR_BLACK, DT_LEFT | DT_VCENTER | DT_MNEMONIC);
  itoa(score, buffer, 10);
  WinDrawText(_hps, -1, (PSZ)buffer, &rct, CLR_YELLOW, CLR_BLACK, DT_RIGHT | DT_VCENTER | DT_MNEMONIC);

  rct.yTop -= 24;
  rct.yBottom -= 24;
  WinDrawText(_hps, -1, (PSZ)"Lives", &rct, CLR_CYAN, CLR_BLACK, DT_LEFT | DT_VCENTER | DT_MNEMONIC);
  itoa(lives, buffer, 10);
  WinDrawText(_hps, -1, (PSZ)buffer, &rct, CLR_YELLOW, CLR_BLACK, DT_RIGHT | DT_VCENTER | DT_MNEMONIC);

  rct.yTop -= 24;
  rct.yBottom -= 24;
  WinDrawText(_hps, -1, (PSZ)"Diamonds", &rct, CLR_CYAN, CLR_BLACK, DT_LEFT | DT_VCENTER | DT_MNEMONIC);
  itoa(diamonds, buffer, 10);
  WinDrawText(_hps, -1, (PSZ)buffer, &rct, CLR_YELLOW, CLR_BLACK, DT_RIGHT | DT_VCENTER | DT_MNEMONIC);

  rct.yTop -= 24;
  rct.yBottom -= 24;
  WinDrawText(_hps, -1, (PSZ)"Earth", &rct, CLR_CYAN, CLR_BLACK, DT_LEFT | DT_VCENTER | DT_MNEMONIC);
  itoa(QueryNumEarth(), buffer, 10);
  WinDrawText(_hps, -1, (PSZ)buffer, &rct, CLR_YELLOW, CLR_BLACK, DT_RIGHT | DT_VCENTER | DT_MNEMONIC);

  rct.yTop -= 24;
  rct.yBottom -= 24;
  WinDrawText(_hps, -1, (PSZ)"Spirits", &rct, CLR_CYAN, CLR_BLACK, DT_LEFT | DT_VCENTER | DT_MNEMONIC);
  itoa(QueryNumSpirits(), buffer, 10);
  WinDrawText(_hps, -1, (PSZ)buffer, &rct, CLR_YELLOW, CLR_BLACK, DT_RIGHT | DT_VCENTER | DT_MNEMONIC);

  rct.yTop -= 24;
  rct.yBottom -= 24;
  WinDrawText(_hps, -1, (PSZ)"Teleporters", &rct, CLR_CYAN, CLR_BLACK, DT_LEFT | DT_VCENTER | DT_MNEMONIC);
  itoa(QueryNumTeleporters(), buffer, 10);
  WinDrawText(_hps, -1, (PSZ)buffer, &rct, CLR_YELLOW, CLR_BLACK, DT_RIGHT | DT_VCENTER | DT_MNEMONIC);
}

void
MainWindow::HandleEscape(void)
{
  if (inGame == TRUE)
    {
      restartLevel = TRUE;
      if (man->IsDead() == FALSE)
        man->Die(manDeathCount);
    }
}






