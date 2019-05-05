//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//

#include "common.h"
#pragma hdrstop

#include "resources.h"
#include "ribble.h"
#include "registry.h"
#include "map.h"
#include "screen.h"
#include "monster.h"
#include "man.h"
#include "mainwin.h"
#include "config.h"


Screen::Screen(MainWindow* _owner)
{
  owner = _owner;
  registry = new Registry(owner, BMP_LowestID, BMP_HighestID);

  device = DevOpenDC(owner->QueryHAB(), OD_MEMORY, (PSZ)"*", 0, 0, 0);
  CAssert(device);
  SIZEL sizl = { 0, 0 };
  canvas = GpiCreatePS(owner->QueryHAB(), device, &sizl, PU_PELS | GPIF_DEFAULT | GPIT_MICRO | GPIA_ASSOC);
  CAssert(canvas);

  GpiSetColor(canvas, CLR_WHITE);
  GpiSetBackColor(canvas, CLR_BLACK);
  GpiSetBackMix(canvas,  BM_OVERPAINT);

  CreateBitmap();
}

void
Screen::CreateBitmap(void)
{
  RibbleConfig* config = owner->QueryConfig();

  BITMAPINFOHEADER hdr;
  memset(&hdr, 0, sizeof(hdr));
  hdr.cbFix = sizeof(BITMAPINFOHEADER);
  hdr.cx = (USHORT)(config->QueryVisWidth() * config->QueryCellWidth());
  hdr.cy = (USHORT)(config->QueryVisHeight() * config->QueryCellHeight());
  hdr.cPlanes = 1;
  hdr.cBitCount = 8;

  HPS ps = WinGetPS(owner->HWindow);
  canvbmp = GpiCreateBitmap(ps, (PBITMAPINFOHEADER2)&hdr, 0, 0, 0);
  CAssert(canvbmp);
  GpiSetBitmap(canvas, canvbmp);
  WinReleasePS(ps);
}

Screen::~Screen()
{
  if (canvbmp)
    GpiDeleteBitmap(canvbmp);
  if (canvas)
    GpiDestroyPS(canvas);
  if (device)
    DevCloseDC(device);
  if (registry)
    delete registry;
}

void
Screen::BlitScreen(HPS _hps, int _xoff, int _yoff)
{
  RibbleConfig* config = owner->QueryConfig();

  POINTL p[3];
  p[0].x = _xoff;
  p[0].y = _yoff;
  p[1].x = p[0].x + config->QueryVisWidth()  * config->QueryCellWidth();
  p[1].y = p[0].y + config->QueryVisHeight() * config->QueryCellHeight();
  p[2].x = 0;
  p[2].y = 0;

  GpiBitBlt(_hps, canvas, 3, p, ROP_SRCCOPY, BBO_IGNORE);
}

void
Screen::DrawBitmap(ULONG _item, int _x, int _y)
{
  RibbleConfig* config = owner->QueryConfig();

  HBITMAP bmp = registry->GetBitmap0(_item);

  POINTL p[3];
  p[0].x = _x;
  p[0].y = _y;
  p[1].x = p[0].x + config->QueryCellWidth();
  p[1].y = p[0].y + config->QueryCellHeight();
  p[2].x = 0;
  p[2].y = 0;
  GpiWCBitBlt(canvas, bmp, 3, p, ROP_SRCCOPY, 0);
}

void
Screen::DrawBitmap(ULONG _item, int _x, int _y, int _w,  int _h)
{
  HBITMAP bmp = registry->GetBitmap0(_item, _w, _h);

  POINTL p[3];
  p[0].x = _x;
  p[0].y = _y;
  p[1].x = p[0].x + _w;
  p[1].y = p[0].y + _h;
  p[2].x = 0;
  p[2].y = 0;
  GpiWCBitBlt(canvas, bmp, 3, p, ROP_SRCCOPY, 0);
}

void
Screen::DrawBitmap(ULONG _item, ULONG _mask, int _x, int _y)
{
  RibbleConfig* config = owner->QueryConfig();

  POINTL p[3];
  p[0].x = _x;
  p[0].y = _y;
  p[1].x = p[0].x + config->QueryCellWidth();
  p[1].y = p[0].y + config->QueryCellHeight();
  p[2].x = 0;
  p[2].y = 0;

  HBITMAP bmp = registry->GetBitmap0(_mask);
  GpiWCBitBlt(canvas, bmp, 3, p, 0x22, 0);
  bmp = registry->GetBitmap0(_item);
  GpiWCBitBlt(canvas, bmp, 3, p, ROP_SRCPAINT, 0);
}

HBITMAP
Screen::QueryBitmap(ULONG _id)
{
  return registry->GetBitmap(_id);
}

void
Screen::RenderText(char* _text, RECTL& _pos, ULONG _fgnd, ULONG _bgnd, ULONG _flags)
{
  GpiSetBackMix(canvas, BM_OVERPAINT);

  WinDrawText(canvas,
              -1,
              (PSZ)_text,
              &_pos,
              _fgnd,
              _bgnd,
              _flags);

  GpiSetBackMix(canvas,  BM_OVERPAINT);
}

void
Screen::ClearBitmaps(void)
{
  registry->ClearRegistries();

  if (canvbmp)
    GpiDeleteBitmap(canvbmp);
  if (canvas)
    GpiDestroyPS(canvas);

  CreateBitmap();
}

