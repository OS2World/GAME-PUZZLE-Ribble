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
#include "man.h"
#include "edit.h"
#include "mainwin.h"
#include "config.h"

void
Edit::Move(void)
{
}

void
Edit::KeySet(int _key, ULONG _state)
{
  Man::KeySet(_key, _state);

  Map* map = win->QueryMap();
  RibbleConfig* config = win->QueryConfig();

  int wid = (map->Width() - 1) * config->QueryStepX();
  int hgt = (map->Height() - 1) * config->QueryStepY();

  if (keys[LeftKey] && posX > 0)
    posX -= config->QueryStepX();
  else if (keys[RightKey] && posX < wid)
    posX += config->QueryStepX();
  if (keys[DownKey] && posY > 0)
    posY -= config->QueryStepY();
  else if (keys[UpKey] && posY < hgt)
    posY += config->QueryStepY();

  keys[LeftKey] = keys[RightKey] = keys[UpKey] = keys[DownKey] = 0;
}

Edit::Edit(MainWindow* _win, int _x, int _y)
: Man(_win, _x, _y)
{
  holdNum = 0;
}




