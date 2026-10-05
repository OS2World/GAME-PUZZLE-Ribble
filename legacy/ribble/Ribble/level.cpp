//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//

#include "common.h"

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
#include "level.h"


SelectLevel::SelectLevel(MainWindow* _win, HWND _owner)
: CDialog(_owner, DLG_SelectLevel),
  win(_win)
{
  levelThread = 0;
}

SelectLevel::~SelectLevel()
{
  if (levelThread)
    {
      levelThread->Kill();
      delete levelThread;
      levelThread = 0;
    }

  MapListIter it(maps);
  while (it)
    delete it++;
}

MRESULT
SelectLevel::ProcessMsg(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  switch (msg)
    {
    case WM_CONTROL:
      return WMControl(mp1, mp2);
    case WM_COMMAND:
      return WMCommand(mp1, mp2);
    }
  return CDialog::ProcessMsg(hwnd, msg, mp1, mp2);
}

void
SelectLevel::SetupWindow(void)
{
  levelThread = new LevelThread(HWindow, maps);
  levelThread->Run();
}

MRESULT
SelectLevel::WMCommand(MPARAM mp1, MPARAM mp2)
{
  mp2;

  switch (SHORT1FROMMP(mp1))
    {
    case DID_OK:
      LoadCurrentLevel();
      break;
    case DID_CANCEL:
      WinPostMsg(HWindow, WM_CLOSE, MPVOID, MPVOID);
      break;
    }
  return 0;
}

MRESULT
SelectLevel::WMControl(MPARAM mp1, MPARAM mp2)
{
  switch (SHORT1FROMMP(mp1))
    {
    case DID_LevelList:
      {
        switch (SHORT2FROMMP(mp1))
          {
          case LN_SELECT:
            {
              SHORT index = (SHORT)(ULONG)WinSendMsg((HWND)mp2,
                                                     LM_QUERYSELECTION,
                                                     MPVOID, MPVOID);
              MapListIter it(maps);
              while (index && it)
                {
                  index--;
                  it++;
                }
              if (it)
                ShowLevelInfo(it.current());
              break;
            }
          case LN_ENTER:
            {
              LoadCurrentLevel();
            }
          }
      }
    }
  return 0;
}

void
SelectLevel::ShowLevelInfo(Map* map)
{
  char buffer[256];
  WinSetDlgItemText(HWindow, DID_AuthorText,      (PSZ)(char*)map->QueryAuthor());
  WinSetDlgItemText(HWindow, DID_CommentText,     (PSZ)(char*)map->QueryComment());
  WinSetDlgItemText(HWindow, DID_CollectText,     (PSZ)"diamonds");
  itoa(map->QueryMapTime(), buffer, 10);
  WinSetDlgItemText(HWindow, DID_TimeText,        (PSZ)buffer);
  itoa(map->QueryNumMonsters(), buffer, 10);
  WinSetDlgItemText(HWindow, DID_MonstersText,    (PSZ)buffer);
  itoa(map->QueryNumDiamonds(), buffer, 10);
  WinSetDlgItemText(HWindow, DID_DiamondsText,    (PSZ)buffer);
  itoa(map->QueryNumTeleporters(), buffer, 10);
  WinSetDlgItemText(HWindow, DID_TeleportersText, (PSZ)buffer);
}

void
SelectLevel::LoadCurrentLevel(void)
{
  SHORT index = (SHORT)(ULONG)WinSendDlgItemMsg(HWindow, DID_LevelList,
                                                LM_QUERYSELECTION,
                                                MPVOID, MPVOID);
  MapListIter it(maps);
  while (index && it)
    {
      index--;
      it++;
    }
  if (it)
    {
      Map* map = it.current();

      int levelNum = map->QueryLevelNum();

      win->InitGame(levelNum);
      WinPostMsg(HWindow, WM_CLOSE, MPVOID, MPVOID);
    }
}


void
LevelThread::ThreadProc(void)
{
  HWND listBox = WinWindowFromID(HWindow, DID_LevelList);
  BOOL setHigh = FALSE;

  for (int level = 1; ; level++)
    {
      char num[34];
      itoa(level, num, 10);

      char buffer[260];
      sprintf(buffer, "levels/level.%s", num);

      Map* map = new Map(0, buffer);
      if (map->UserMap())
        {
          CString text  = num;
	  text += " ... ";
	  text += map->QueryTitle();

          WinSendMsg(listBox,
                     LM_INSERTITEM,
                     MPFROMSHORT(LIT_END),
                     MPFROMP((char*)text));

          maps += map;

          if (setHigh == FALSE)
            {
              WinSendMsg(listBox,
                         LM_SELECTITEM,
                         MPFROMSHORT(0),
                         MPFROMSHORT(TRUE));
              setHigh = TRUE;
            }
        }
      else
        {
          delete map;
          break;
        }
    }
}


