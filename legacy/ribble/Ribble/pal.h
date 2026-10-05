//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//

#ifndef _Pal_h
#define _Pal_h

class ItemPalette : public CWinClient
{
public:

  ItemPalette(MainWindow* _win);
  ~ItemPalette();
  MRESULT ProcessMsg(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
  void ProcessCmd(MPARAM mp1, MPARAM mp2);
  MRESULT ProcessCtl(MPARAM mp1, MPARAM mp2);
  void SetupWindow(void);
  void Paint(void);
  void CreateButtons(void);
  int CalcXwid(int _num);
  int CalcYhgt(int _num);
  int QueryCurrentChoice(void) { return currentChoice; }
  BOOL SetCurrentChoice(int x, int y);

private:

  MainWindow* win;
  int         currentChoice;
  HWND        valueset;
};

#endif
