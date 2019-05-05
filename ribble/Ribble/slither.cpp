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
#include "slither.h"
#include "config.h"

#define sgn(a) (((a)<0)?-1:((a)!=0))

// Slither monsters are nasty evil creatures which follow
// Ribble around the arena, and kill him when they touch him.
// Slithers hatch out of eggs (handled elsewhere).  The die
// when ever a boulder occupies their current location
// (dropped or pushed into them)

Slither::Slither(MainWindow* _win, int x, int y, char* _data)
: Monster(_win,
          x * _win->QueryConfig()->QueryStepX(),
          y * _win->QueryConfig()->QueryStepY(),
          ITEM_SLITHER)
{
  _data;

  xd = 0;
  yd = 0;
  oldxd = 0;
  oldyd = 0;
}

inline
BOOL
SlitherPossMove(char m)
{
  return (m == ITEM_EMPTY || m == ITEM_EARTH || m == ITEM_KEY) ? TRUE : FALSE;
}

void
Slither::Move(void)
{
  anim++;

  Man* man = win->QueryMan();
  Map* map = win->QueryMap();
  RibbleConfig* config = win->QueryConfig();

  if (abs(xd) == config->QueryStepX() || abs(yd) == config->QueryStepY())
    {
      if (xd)
        {
          char& a = map->QueryMap(posX / config->QueryStepX() + sgn(xd), posY / config->QueryStepY());
          if (!SlitherPossMove(a))
            {
              xd = 0;
              if (posY <= man->QueryYPos() && SlitherPossMove(map->QueryMap(posX /  config->QueryStepX(), posY / config->QueryStepY() + 1)))
                yd = config->QueryStepY();
              else if (posY >= man->QueryYPos() && SlitherPossMove(map->QueryMap(posX /  config->QueryStepX(), posY / config->QueryStepY() - 1)))
                yd = -config->QueryStepY();
              else if (SlitherPossMove(map->QueryMap(posX / config->QueryStepX() - sgn(xd), posY / config->QueryStepY())))
                xd = -xd;
            }
        }

      if (yd)
        {
          char& a = map->QueryMap(posX / config->QueryStepX(), posY / config->QueryStepY() + sgn(yd));
          if (!SlitherPossMove(a))
            {
              yd = 0;
              if (posX <= man->QueryXPos() && SlitherPossMove(map->QueryMap(posX /  config->QueryStepX() + 1, posY / config->QueryStepY())))
                xd = config->QueryStepX();
              else if (posX >= man->QueryXPos() && SlitherPossMove(map->QueryMap(posX /  config->QueryStepX() -  1, posY / config->QueryStepY())))
                xd = -config->QueryStepX();
              else if (SlitherPossMove(map->QueryMap(posX / config->QueryStepX(), posY / config->QueryStepY() - sgn(yd))))
                yd = -yd;
            }
        }
    }

  if (xd > 0)      { posX++; xd--; }
  else if (xd < 0) { posX--; xd++; }
  if (yd > 0)      { posY++; yd--; }
  else if (yd < 0) { posY--; yd++; }

  if (xd == 0 && yd == 0)
    {
      if (man)
        {
          int x = man->QueryXPos();
          int y = man->QueryYPos();

          if (posX > x)
            xd = -config->QueryStepX();
          else if (posX < x)
            xd = config->QueryStepX();
          else if (posY > y)
            yd = -config->QueryStepY();
          else if (posY < y)
            yd = config->QueryStepY();
        }
      oldxd = xd;
      oldyd = yd;
    }
}

ULONG
Slither::QueryItemID(void)
{
  return ((anim & 0x04) ? 0 : 1) + ITEM_SLITHER;
}

ULONG
Slither::QueryItemMskID(void)
{
  return ((anim & 0x04) ? 0 : 1) + ITEM_SLITHERMASK;
}


