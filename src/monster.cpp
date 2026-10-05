//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//

#include "common.h"
#pragma hdrstop

#include "resources.h"
#include "ribble.h"
#include "map.h"
#include "screen.h"
#include "monster.h"
#include "man.h"
#include "mainwin.h"
#include "config.h"


Monster::Monster(MainWindow* _win, int _posX, int _posY, ULONG _name)
: win(_win), posX(_posX), posY(_posY),
  name(_name)
{
  dead = -1;
}

Monster::~Monster()
{
}

BOOL
Monster::OverlapsMapLocn(int _x, int _y)
{
  RibbleConfig* config = win->QueryConfig();

  if (IsDead() == FALSE)
    {
      int x1 = _x * config->QueryStepX();
      int y1 = _y * config->QueryStepY();
      if (posX > x1 - config->QueryStepX() && posX < x1 + config->QueryStepX() &&
          posY > y1 - config->QueryStepY() && posY < y1 + config->QueryStepY())
        return TRUE;
    }
  return FALSE;
}

BOOL
Monster::MonstersOverlap(int _x1, int _y1, int _x2, int _y2)
{
  RibbleConfig* config = win->QueryConfig();

  RECTL rct1, rct2, dst;

  rct1.xLeft = _x1;
  rct1.xRight = _x1 + config->QueryStepX();
  rct1.yBottom = _y1;
  rct1.yTop = _y1 + config->QueryStepY();
  rct2.xLeft = _x2;
  rct2.xRight = _x2 + config->QueryStepX();
  rct2.yBottom = _y2;
  rct2.yTop = _y2 + config->QueryStepY();

  return WinIntersectRect(win->QueryHAB(), &dst, &rct1, &rct2);
}



