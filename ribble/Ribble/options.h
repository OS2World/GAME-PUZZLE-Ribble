//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//

#ifndef _Options_h
#define _Options_h

class GameOptions : public CDialog
{
public:

  GameOptions(MainWindow* _win, HWND _owner);
  ~GameOptions();
  MRESULT ProcessMsg(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
  void SetupWindow(void);
  MRESULT WMControl(MPARAM mp1, MPARAM mp2);
  MRESULT WMCommand(MPARAM mp1, MPARAM mp2);
  void HandleKeyEnable(void);
  void StoreKeySettings(RibbleConfig* config);
  void StoreRefreshRate(RibbleConfig* config);
  void StoreSizes(RibbleConfig* config);

private:

  MainWindow* win;
};

#endif

