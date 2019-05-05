//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//

#ifndef _Hiscore_h
#define _Hiscore_h

class HiscoreDialog : public CDialog
{
public:

  HiscoreDialog(MainWindow* _win, HWND _owner, int _score);
  ~HiscoreDialog();
  MRESULT ProcessMsg(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
  void SetupWindow(void);
  MRESULT WMControl(MPARAM mp1, MPARAM mp2);
  MRESULT WMCommand(MPARAM mp1, MPARAM mp2);
  BOOL WorthyScore(void);
  void EnterName(void);


private:

  MainWindow* win;
  int score;
};


#endif

