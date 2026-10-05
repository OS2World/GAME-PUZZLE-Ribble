//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//

#ifndef _Save_h
#define _Save_h

class SaveLevel : public CDialog
{
public:

  SaveLevel(MainWindow* _win, HWND _owner);
  ~SaveLevel();
  MRESULT ProcessMsg(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
  void SetupWindow(void);
  MRESULT WMControl(MPARAM mp1, MPARAM mp2);
  MRESULT WMCommand(MPARAM mp1, MPARAM mp2);
  void SaveCurrentLevel(void);

private:

  MainWindow* win;
};


#endif

