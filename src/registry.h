//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//

#ifndef _Registry_h
#define _Registry_h

class MainWindow;

class Registry
{
public:
  Registry(MainWindow* win, ULONG lower, ULONG upper);
  ~Registry();
  void ClearRegistries(void);
  void ClearRegistry2(void);
  HBITMAP GetBitmap(ULONG id);
  HBITMAP GetBitmap0(ULONG id);
  HBITMAP GetBitmap0(ULONG id, int _w, int _h);
  ULONG QueryLower(void);

private:
  HPS       hps;
  HBITMAP*  registry;
  HBITMAP*  registry2;
  ULONG     size;
  ULONG     lower;
  int       reg2W;
  int       reg2H;
  MainWindow* win;
};

#endif

