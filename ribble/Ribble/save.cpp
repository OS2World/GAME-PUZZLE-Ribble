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
#include "level.h"
#include "save.h"


SaveLevel::SaveLevel(MainWindow* _win, HWND _owner)
: CDialog(_owner, DLG_SaveLevel),
  win(_win)
{
}

SaveLevel::~SaveLevel()
{
}

MRESULT
SaveLevel::ProcessMsg(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
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
SaveLevel::SetupWindow(void)
{
  Map* map = win->QueryMap();
  CAssert(map);

  int spin = map->QueryLevelNum();

  WinSendDlgItemMsg(HWindow, DID_SaveLevelFile, SPBM_SETLIMITS, MPFROMLONG(256), MPFROMLONG(1));
  WinSendDlgItemMsg(HWindow, DID_SaveLevelFile, SPBM_SETCURRENTVALUE, MPFROMLONG(spin), MPVOID);

  WinSendDlgItemMsg(HWindow, DID_SaveAuthorText, EM_SETTEXTLIMIT, MPFROMSHORT(StringLimit), MPVOID);
  WinSendDlgItemMsg(HWindow, DID_SaveTitleText, EM_SETTEXTLIMIT, MPFROMSHORT(StringLimit), MPVOID);
  WinSendDlgItemMsg(HWindow, DID_SaveCommentText, EM_SETTEXTLIMIT, MPFROMSHORT(StringLimit), MPVOID);
  WinSendDlgItemMsg(HWindow, DID_SaveTime, EM_SETTEXTLIMIT, MPFROMSHORT(StringLimit), MPVOID);

  WinSetDlgItemText(HWindow, DID_SaveAuthorText, (PSZ)(char*)map->QueryAuthor());
  WinSetDlgItemText(HWindow, DID_SaveTitleText, (PSZ)(char*)map->QueryTitle());
  WinSetDlgItemText(HWindow, DID_SaveCommentText, (PSZ)(char*)map->QueryComment());

  char buffer[StringLimit];
  itoa(map->QueryMapTime(), buffer, 10);
  WinSetDlgItemText(HWindow, DID_SaveTime, (PSZ)buffer);
}

MRESULT
SaveLevel::WMCommand(MPARAM mp1, MPARAM mp2)
{
  mp2;

  switch (SHORT1FROMMP(mp1))
    {
    case DID_OK:
      SaveCurrentLevel();
      break;
    case DID_CANCEL:
      WinPostMsg(HWindow, WM_CLOSE, MPVOID, MPVOID);
      break;
    }
  return 0;
}

MRESULT
SaveLevel::WMControl(MPARAM mp1, MPARAM mp2)
{
  mp2;

  switch (SHORT1FROMMP(mp1))
    {
    default:
      break;
    }
  return 0;
}

void
SaveLevel::SaveCurrentLevel(void)
{
  Map* map = win->QueryMap();
  CAssert(map);

  LONG value;

  BOOL ret = (BOOL)WinSendDlgItemMsg(HWindow,
                                     DID_SaveLevelFile,
                                     SPBM_QUERYVALUE,
                                     MPFROMP(&value),
                                     MPFROM2SHORT(0, SPBQ_DONOTUPDATE));

  if (ret == TRUE)
    {
      int oldLevelNum = map->QueryLevelNum();

      map->SetFilename((int)value);

      CString text  = "Level will be saved to the file\n\n\"";
      text += map->QueryFilename();
      text += "\"\n\nProceed?";

      ULONG ok  = WinMessageBox(HWND_DESKTOP,
                                HWindow,
                                (PSZ)(char*)text,
                                (PSZ)"Ribble save level",
                                1,
                                MB_YESNO | MB_INFORMATION | MB_MOVEABLE);



      if (ok != MBID_YES)
        {
          map->SetFilename((int)oldLevelNum);
          return;
        }

      char buffer[StringLimit];
      WinQueryDlgItemText(HWindow, DID_SaveAuthorText, StringLimit, (PSZ)buffer);
      map->SetAuthor(buffer);

      WinQueryDlgItemText(HWindow, DID_SaveCommentText, StringLimit, (PSZ)buffer);
      map->SetComment(buffer);

      WinQueryDlgItemText(HWindow, DID_SaveTitleText, StringLimit, (PSZ)buffer);
      map->SetTitle(buffer);

      WinQueryDlgItemText(HWindow, DID_SaveTime, StringLimit, (PSZ)buffer);
      map->SetMapTime(atoi(buffer));

      map->SaveMap();

      WinPostMsg(HWindow, WM_CLOSE, MPVOID, MPVOID);
    }
  else
    WinAlarm(HWND_DESKTOP, WA_ERROR);
}






