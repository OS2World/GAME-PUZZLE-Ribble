//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//

#include "common.h"
#pragma hdrstop

#include <fcntl.h>
#include <io.h>
#include <ctype.h>
#include <fstream.h>
#include <stdio.h>
#include <direct.h>

#include "resources.h"
#include "ribble.h"
#include "map.h"
#include "monster.h"
#include "mainwin.h"
#include "options.h"
#include "config.h"


GameOptions::GameOptions(MainWindow* _win, HWND _owner)
: CDialog(_owner, DLG_GameOptions),
  win(_win)
{
}

GameOptions::~GameOptions()
{
}

MRESULT
GameOptions::ProcessMsg(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  switch (msg)
    {
    case WM_INITDLG:
      return (MRESULT)TRUE;
    case WM_CONTROL:
      return WMControl(mp1, mp2);
    case WM_COMMAND:
      return WMCommand(mp1, mp2);
    }
  return CDialog::ProcessMsg(hwnd, msg, mp1, mp2);
}

void
GameOptions::SetupWindow(void)
{
  RibbleConfig* config = win->QueryConfig();

  WinCheckButton(HWindow, DID_OptionsSave, config->QuerySaveConfig() ? TRUE : FALSE);

  switch (config->QueryControlType())
    {
    case RibbleConfig::Arrow:
      WinCheckButton(HWindow, DID_KeysArrow, TRUE);
      WinSetFocus(HWND_DESKTOP, WinWindowFromID(HWindow, DID_KeysArrow));
      break;
    case RibbleConfig::Classic:
      WinCheckButton(HWindow, DID_KeysClassic, TRUE);
      WinSetFocus(HWND_DESKTOP, WinWindowFromID(HWindow, DID_KeysClassic));
      break;
    case RibbleConfig::Other:
      WinCheckButton(HWindow, DID_KeysOther, TRUE);
      WinSetFocus(HWND_DESKTOP, WinWindowFromID(HWindow, DID_KeysOther));
      break;
    }

  HandleKeyEnable();

  char buffer[] = "n";

  buffer[0] = config->QueryLeftKey();
  WinSetDlgItemText(HWindow, DID_LeftKey, (PSZ)buffer);
  buffer[0] = config->QueryRightKey();
  WinSetDlgItemText(HWindow, DID_RightKey, (PSZ)buffer);
  buffer[0] = config->QueryUpKey();
  WinSetDlgItemText(HWindow, DID_UpKey, (PSZ)buffer);
  buffer[0] = config->QueryDownKey();
  WinSetDlgItemText(HWindow, DID_DownKey, (PSZ)buffer);

  int ref = config->QueryRefreshRate();

  WinSendDlgItemMsg(HWindow, DID_RefreshRate, SPBM_SETLIMITS, MPFROMLONG(500), MPFROMLONG(0));
  WinSendDlgItemMsg(HWindow, DID_RefreshRate, SPBM_SETCURRENTVALUE, MPFROMLONG(ref), MPVOID);

  char* cellWidthValues[] = { "16x16",
                              "32x32",
                              "48x48",
                              "64x64"
			      };
  char* visWidthValues[] =  { "5x5",
                              "7x7",
                              "9x9",
                              "11x11",
                              "13x13",
                              "15x15",
                              "17x17",
                              "19x19",
                              "21x21",
                              "23x23",
                              "25x25",
                            };

  WinSendDlgItemMsg(HWindow, DID_CellSize, SPBM_SETARRAY, MPFROMP(cellWidthValues), MPFROMLONG(4));
  WinSendDlgItemMsg(HWindow, DID_VisibleSize, SPBM_SETARRAY, MPFROMP(visWidthValues), MPFROMLONG(11));

  int cellIndex = config->QueryCellWidth() / 16 - 1;
  WinSendDlgItemMsg(HWindow, DID_CellSize, SPBM_SETCURRENTVALUE, MPFROMLONG(cellIndex), MPVOID);

  int visIndex = config->QueryVisWidth() / 2 - 2;
  WinSendDlgItemMsg(HWindow, DID_VisibleSize, SPBM_SETCURRENTVALUE, MPFROMLONG(visIndex), MPVOID);
}

MRESULT
GameOptions::WMCommand(MPARAM mp1, MPARAM mp2)
{
  mp2;

  switch (SHORT1FROMMP(mp1))
    {
    case DID_OK:
      {
        RibbleConfig* config = win->QueryConfig();

        config->SetSaveConfig((int)WinQueryButtonCheckstate(HWindow, DID_OptionsSave));

        // Pull in changes made and store in config.

        StoreKeySettings(config);
        StoreRefreshRate(config);
        StoreSizes(config);
        config->SaveConfig();
      }
      // Purposely drop through to DID_CANCEL code
    case DID_CANCEL:
      WinPostMsg(HWindow, WM_CLOSE, MPVOID, MPVOID);
      break;
    }
  return 0;
}

MRESULT
GameOptions::WMControl(MPARAM mp1, MPARAM mp2)
{
  mp2;

  RibbleConfig* config = win->QueryConfig();

  /*  if (SHORT2FROMMP(mp1) == BN_CLICKED)
      {
      switch (SHORT1FROMMP(mp1))
      {
      case DID_KeysArrow:
      pmPrintf("arrow click\n");
      break;
      case DID_KeysOther:
      pmPrintf("other click\n");
      break;
      case DID_KeysClassic:
      pmPrintf("classic click\n");
      break;
      }
      }
      */

  switch (SHORT1FROMMP(mp1))
    {
    case DID_KeysArrow:
      if (SHORT2FROMMP(mp1) == BN_CLICKED)
        {
          WinCheckButton(HWindow, DID_KeysArrow,   TRUE );
          WinCheckButton(HWindow, DID_KeysClassic, FALSE);
          WinCheckButton(HWindow, DID_KeysOther,   FALSE);

          config->SetControlType(RibbleConfig::Arrow);
          HandleKeyEnable();
        }
      break;
    case DID_KeysClassic:
      if (SHORT2FROMMP(mp1) == BN_CLICKED)
        {
          WinCheckButton(HWindow, DID_KeysArrow,   FALSE);
          WinCheckButton(HWindow, DID_KeysClassic, TRUE );
          WinCheckButton(HWindow, DID_KeysOther,   FALSE);

          config->SetControlType(RibbleConfig::Classic);
          HandleKeyEnable();
        }
      break;
    case DID_KeysOther:
      if (SHORT2FROMMP(mp1) == BN_CLICKED)
        {
          WinCheckButton(HWindow, DID_KeysArrow,   FALSE);
          WinCheckButton(HWindow, DID_KeysClassic, FALSE);
          WinCheckButton(HWindow, DID_KeysOther,   TRUE );

          config->SetControlType(RibbleConfig::Other);
          HandleKeyEnable();
        }
      break;
    default:
      break;
    }

  return 0;
}

void
GameOptions::HandleKeyEnable(void)
{
  RibbleConfig* config = win->QueryConfig();

  BOOL enable = TRUE;

  if (config->QueryControlType() != RibbleConfig::Other)
    enable = FALSE;

  enable = FALSE;

  WinEnableWindow(WinWindowFromID(HWindow, DID_LeftKey), enable);
  WinEnableWindow(WinWindowFromID(HWindow, DID_RightKey), enable);
  WinEnableWindow(WinWindowFromID(HWindow, DID_UpKey), enable);
  WinEnableWindow(WinWindowFromID(HWindow, DID_DownKey), enable);
  WinEnableWindow(WinWindowFromID(HWindow, DID_LeftText), enable);
  WinEnableWindow(WinWindowFromID(HWindow, DID_RightText), enable);
  WinEnableWindow(WinWindowFromID(HWindow, DID_UpText), enable);
  WinEnableWindow(WinWindowFromID(HWindow, DID_DownText), enable);
}

void
GameOptions::StoreKeySettings(RibbleConfig* config)
{
  RibbleConfig::ControlType ct = RibbleConfig::Unset;

  ULONG state;

  state = WinQueryButtonCheckstate(HWindow, DID_KeysClassic);
  if (state)
    ct = RibbleConfig::Classic;

  state = WinQueryButtonCheckstate(HWindow, DID_KeysArrow);
  if (state)
    ct = RibbleConfig::Arrow;

  state = WinQueryButtonCheckstate(HWindow, DID_KeysOther);
  if (state)
    ct = RibbleConfig::Other;

  if (ct != RibbleConfig::Unset)
    config->SetControlType(ct);
}

void
GameOptions::StoreRefreshRate(RibbleConfig* config)
{
  LONG value;

  BOOL ret = (BOOL)WinSendDlgItemMsg(HWindow,
                                     DID_RefreshRate,
                                     SPBM_QUERYVALUE,
                                     MPFROMP(&value),
                                     MPFROM2SHORT(0, SPBQ_DONOTUPDATE));

  if (ret == TRUE)
    {
      config->SetRefreshRate((int)value);
    }
}

void
GameOptions::StoreSizes(RibbleConfig* config)
{
  int oldCellWid = config->QueryCellWidth();
  int oldVisWid = config->QueryVisWidth();

  LONG value;

  BOOL ret = (BOOL)WinSendDlgItemMsg(HWindow,
                                     DID_CellSize,
                                     SPBM_QUERYVALUE,
                                     MPFROMP(&value),
                                     MPFROM2SHORT(0, SPBQ_DONOTUPDATE));
  if (ret == TRUE)
    {
      int newWid = 16 + value * 16;
      config->SetCellWidth(newWid);
    }

  ret = (BOOL)WinSendDlgItemMsg(HWindow,
                                DID_VisibleSize,
                                SPBM_QUERYVALUE,
                                MPFROMP(&value),
                                MPFROM2SHORT(0, SPBQ_DONOTUPDATE));
  if (ret == TRUE)
    {
      int newWid = 5 + value * 2;
      config->SetVisWidth(newWid);
      config->SetCentreXoff(newWid >> 1);
    }

  if (oldCellWid != config->QueryCellWidth() ||
      oldVisWid  != config->QueryVisWidth())
    {
      WinShowWindow(HWindow, FALSE);
      WinPostMsg(win->HWindow, WM_ResetSize, MPVOID, MPVOID);
    }
}



