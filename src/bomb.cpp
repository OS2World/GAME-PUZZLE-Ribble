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
#include "bomb.h"
#include "config.h"

#include <stdio.h>
#include <ctype.h>


Bomb::Bomb(MainWindow* _win, int x, int y, const char* data)
: Monster(_win,
          x * _win->QueryConfig()->QueryStepX(),
          y * _win->QueryConfig()->QueryStepY(),
          ITEM_BOMB)
{
  data;
  fizzleCnt = 20;
}

void
Bomb::Move(void)
{
  // Having a bomb chase Ribble around the map could
  // be amusing.

  if (--fizzleCnt == 0)
    {
      dead = TRUE;

      RibbleConfig* config = win->QueryConfig();
      Map* map = win->QueryMap();

      int mapX = posX / config->QueryStepX();
      int mapY = posY / config->QueryStepY();

      if (map->OnMap(mapX, mapY))
        map->QueryMap(mapX, mapY) = ITEM_EMPTY;
    }
}

static
ULONG
itemTable[3] =
{
  ITEM_FLAME1,
  ITEM_FLAME2,
  ITEM_FLAME3
  };


ULONG
Bomb::QueryItemID(void)
{
  return itemTable[fizzleCnt % 3];
}


