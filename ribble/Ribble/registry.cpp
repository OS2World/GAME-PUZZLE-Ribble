//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//

#include "common.h"
#pragma hdrstop

#include "resources.h"
#include "ribble.h"
#include "registry.h"
#include "monster.h"
#include "mainwin.h"
#include "config.h"

// This table maps the ITEM_* items to their bitmaps in the
// resource file.

ULONG bmp_map[] =
{
/*  0*/  BMP_Empty,
/*  1*/  BMP_Boulder,
/*  2*/  BMP_BlueWall,
/*  3*/  BMP_Diamond,
/*  4*/  BMP_Earth,
/*  5*/  BMP_RedWall,
/*  6*/  BMP_RedWallN,
/*  7*/  BMP_RedWallNE,
/*  8*/  BMP_RedWallSE,
/*  9*/  BMP_RedWallSW,
/* 10*/  BMP_RedWallNW,
/* 11*/  BMP_Spirit,
/* 12*/  BMP_RibbleStatic,
/* 13*/  BMP_RedWallS,
/* 14*/  BMP_RedWallE,
/* 15*/  BMP_RedWallW,
/* 16*/  BMP_WalkRight1,
/* 17*/  BMP_WalkRight2,
/* 18*/  BMP_WalkRight3,
/* 19*/  BMP_WalkLeft1,
/* 20*/  BMP_WalkLeft2,
/* 21*/  BMP_WalkLeft3,
/* 22*/  BMP_Spirit1,
/* 23*/  BMP_Egg,
/* 24*/  BMP_CrackedEgg,
/* 25*/  BMP_SpiritMask,
/* 26*/  BMP_Spirit1Mask,
/* 27*/  BMP_Cage,
/* 28*/  BMP_Safe,
/* 29*/  BMP_Key,
/* 30*/  BMP_RibbleV1,
/* 31*/  BMP_RibbleV2,
/* 32*/  BMP_Edit,
/* 33*/  BMP_EditMask,
/* 34*/  BMP_Slither,
/* 35*/  BMP_Slither1,
/* 36*/  BMP_SlitherMask,
/* 37*/  BMP_SlitherMask1,
/* 38*/  BMP_Grave,
/* 39*/  BMP_Title,
/* 40*/  BMP_Teleport,
/* 41*/  BMP_Teleport1,
/* 42*/  BMP_Teleport2,
/* 43*/  BMP_Teleport3,
/* 44*/  BMP_Teleport4,
/* 45*/  BMP_Bomb,
/* 46*/  BMP_BombLive1,
/* 47*/  BMP_BombLive2,
/* 48*/  BMP_Flame1,
/* 49*/  BMP_Flame2,
/* 50*/  BMP_Flame3
};

Registry::Registry(MainWindow* _win, ULONG _lower, ULONG _upper)
{
  HWND _hwnd = _win->HWindow;
  win = _win;
  hps = WinGetPS(_hwnd);
  lower = _lower;
  size = _upper - _lower + 1;
  registry = new HBITMAP[size];
  CAssert(registry);
  registry2 = new HBITMAP[size];
  CAssert(registry2);
  reg2W = 0;
  reg2H = 0;

  for (ULONG wipe=0; wipe<size; wipe++)
    registry[wipe] = registry2[wipe] = 0;
}

Registry::~Registry()
{
  ClearRegistries();
  delete [] registry;
  delete [] registry2;
  WinReleasePS(hps);
}

void
Registry::ClearRegistries(void)
{
  for (ULONG free=0; free<size; free++)
    {
      if (registry[free])
        GpiDeleteBitmap(registry[free]);
      if (registry2[free])
        GpiDeleteBitmap(registry2[free]);
      registry[free] = registry2[free] = 0;
    }
}

void
Registry::ClearRegistry2(void)
{
  for (ULONG free=0; free<size; free++)
    if (registry2[free])
      {
        GpiDeleteBitmap(registry2[free]);
        registry2[free] = 0;
      }
}


HBITMAP
Registry::GetBitmap0(ULONG _id)
{
  return GetBitmap(bmp_map[_id]);
}

HBITMAP
Registry::GetBitmap(ULONG _id)
{
  HBITMAP bmp = registry[_id - lower];

  RibbleConfig* config = win->QueryConfig();

  if (bmp == 0)
    {
      bmp = GpiLoadBitmap(hps, 0, _id, config->QueryCellWidth(), config->QueryCellHeight());
      CAssert(bmp);
      registry[_id - lower] = bmp;
    }

  return bmp;
}

HBITMAP
Registry::GetBitmap0(ULONG _id, int _w, int _h)
{
  HBITMAP bmp;
  ULONG bid = bmp_map[_id];

  if (_w != reg2W || _h != reg2H)
    {
      ClearRegistry2();
      reg2W = _w;
      reg2H = _h;
      bmp = 0;
    }
  else
    bmp = registry2[bid - lower];

  if (bmp == 0)
    {
      registry2[bid - lower] = 
      bmp = GpiLoadBitmap(hps, 0, bid, _w, _h);
    }

  CAssert(bmp);
  return bmp;
}


ULONG
Registry::QueryLower(void)
{
  return lower;
}

