//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//

#ifndef _Screen_h
#define _Screen_h

class MainWindow;
class Registry;

class Screen
{
public:

  Screen(MainWindow* _owner);
  ~Screen();
  void ClearBitmaps(void);
  void BlitScreen(HPS _hps, int _xoff, int _yoff);
  void DrawBitmap(ULONG _item, int _x, int _y);
  void DrawBitmap(ULONG _item, int _x, int _y, int _w, int _h);
  void DrawBitmap(ULONG _item, ULONG _mask, int _x, int _y);
  HBITMAP QueryBitmap(ULONG _id);
  void RenderText(char* text, RECTL& pos, ULONG _fgnd, ULONG _bgnd, ULONG _flags = DT_LEFT | DT_TOP);
  void CreateBitmap(void);

private:

  MainWindow*     owner;
  HDC             device;
  HPS             canvas;
  HBITMAP         canvbmp;
  Registry*       registry;

};

#endif

