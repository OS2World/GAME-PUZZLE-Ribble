//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//

#include "common.h"
#pragma hdrstop

#include "resources.h"
#include "ribble.h"
#include "map.h"
#include "monster.h"
#include "mainwin.h"
#include "config.h"
#include "hiscore.h"

HiscoreDialog::HiscoreDialog(MainWindow* _win, HWND _owner, int _score)
: CDialog(_owner, DLG_HiscoreDialog),
  win(_win),
  score(_score)
{
}

HiscoreDialog::~HiscoreDialog()
{
}

MRESULT
HiscoreDialog::ProcessMsg(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
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
HiscoreDialog::SetupWindow(void)
{
  // See whether this score is worthy...

  if (WorthyScore())
    {
      show();
    }
  else
    {
      WinShowWindow(WinWindowFromID(HWindow, DID_QualifyText), FALSE);
      WinShowWindow(WinWindowFromID(HWindow, DID_ScoreName), FALSE);
      WinShowWindow(WinWindowFromID(HWindow, DID_BerateText), TRUE);
      WinSetDlgItemText(HWindow, DID_OK, (PSZ)"~Sorry");
    }
  //WinPostMsg(HWindow, WM_CLOSE, MPVOID, MPVOID);
}

MRESULT
HiscoreDialog::WMCommand(MPARAM mp1, MPARAM mp2)
{
  mp2;

  switch (SHORT1FROMMP(mp1))
    {
    case DID_OK:
      EnterName();
    case DID_CANCEL:
      WinPostMsg(HWindow, WM_CLOSE, MPVOID, MPVOID);
      break;
    }
  return 0;
}

MRESULT
HiscoreDialog::WMControl(MPARAM mp1, MPARAM mp2)
{
  mp1;
  mp2;

  return 0;
}


void
HiscoreDialog::EnterName(void)
{
  RibbleConfig* config = win->QueryConfig();

  RibbleConfig::ScoreItem scoreItem;

  for (int i=0; i<ScoreTableLen; i++)
    {
      config->LoadScoreItem(i, &scoreItem);

      if (score > scoreItem.score)
        {
          RibbleConfig::ScoreItem newItem;
          newItem.score = score;
          WinQueryDlgItemText(HWindow, DID_ScoreName, 64, (PSZ)newItem.text);
          config->SaveScoreItem(i, &newItem);

          for (i++; i<ScoreTableLen; i++)
            {
              config->LoadScoreItem(i, &newItem);
              config->SaveScoreItem(i, &scoreItem);
              scoreItem = newItem;
            }
          break;
        }
    }
}


BOOL
HiscoreDialog::WorthyScore(void)
{
  RibbleConfig* config = win->QueryConfig();

  RibbleConfig::ScoreItem scoreItem;

  for (int i=0; i<ScoreTableLen; i++)
    {
      config->LoadScoreItem(i, &scoreItem);

      if (score > scoreItem.score)
        return TRUE;
    }
  return FALSE;
}

