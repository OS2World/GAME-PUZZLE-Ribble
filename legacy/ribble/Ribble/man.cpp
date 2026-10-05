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
#include "mainwin.h"
#include "config.h"

#define sgn(a) (((a)<0)?-1:((a==0)?0:1))

static
ULONG
manAnimRight[4] =
{
  ITEM_WALKRIGHT1,
  ITEM_WALKRIGHT2,
  ITEM_WALKRIGHT1,
  ITEM_WALKRIGHT3
  };

static
ULONG
manAnimLeft[4] =
{
  ITEM_WALKLEFT1,
  ITEM_WALKLEFT2,
  ITEM_WALKLEFT1,
  ITEM_WALKLEFT3
  };

static
ULONG
manAnimVert[4] =
{
  ITEM_RIBBLEV1,
  ITEM_RIBBLEV1,
  ITEM_RIBBLEV2,
  ITEM_RIBBLEV2,
};

ULONG
Man::QueryItemID(void)
{
  ULONG id;

  if (IsDead())
    return ITEM_GRAVE;
  else if (cxd > 0)
    id = manAnimRight[abs(cxd) - 1];
  else if (cxd < 0)
    id = manAnimLeft[abs(cxd) - 1];
  else if (cyd)
    id = manAnimVert[abs(cyd) - 1];
  else
    id = ITEM_RIBBLESTATIC;
  return id;
}

static
BOOL
IsEdible(char c)
{
  return c == ITEM_EMPTY   ||
    c == ITEM_EARTH   ||
      c == ITEM_DIAMOND ||
	c == ITEM_KEY;
}

#define CanPush(x)        \
x == ITEM_BOULDER   ||   \
x == ITEM_BOMB      ||   \
x == ITEM_BOMBLIVE1 ||   \
map->QueryEgg(x)

     void
     Man::Move(void)
{
  if (IsDead())
    {
      return;
    }

  // If we're just starting a new movement, then check in
  // the direction we're about to move for boulders which
  // can be pushed out of the way etc.
  // Once this has been done, we can stick an ITEM_REPTONSTATIC
  // in the destination location to prevent anything falling onto
  // us, and to prevent boulders above displaced ones from falling
  // into the newly unoccupied slot.
  // If it's not possible to move in the required direction,
  // then clear cxd and cyd.

  Map* map = win->QueryMap();
  RibbleConfig* config = win->QueryConfig();

  if (abs(cxd) == config->QueryStepX() || abs(cyd) == config->QueryStepY())
    {
      oldcx = posX;
      oldcy = posY;

      char item;

      BOOL canMove = FALSE;
      if (cxd)
        {
          char& adj1 = map->QueryMap(posX / config->QueryStepX() + sgn(cxd), posY / config->QueryStepY());
          item = adj1;

          if (IsEdible(item))
            {
              canMove = TRUE;
            }
          else if (CanPush(adj1))
            {
              int xx = posX / config->QueryStepX() + sgn(cxd) * 2;
              int yy = posY / config->QueryStepY();

              char& adj2 = map->QueryMap(xx, yy);
              if (adj2 == ITEM_EMPTY)
                {
                  adj2 = adj1;
                  adj1 = ITEM_EMPTY;
                  canMove = TRUE;
                  win->CheckMonsterCrushed(xx, yy);
                }
            }
        }
      else
        {
          char& adj1 = map->QueryMap(posX / config->QueryStepX(), posY / config->QueryStepY() + sgn(cyd));
          item = adj1;
          if (IsEdible(item))
            {
              canMove = TRUE;
            }
        }
      if (canMove == FALSE)
        {
          oldcxd = cxd = oldcyd = cyd = 0;
        }
      else
        {
          switch (item)
            {
	    case ITEM_EARTH:
	      win->EatEarth();
	      break;
	    case ITEM_DIAMOND:
	      win->EatDiamond();
	      break;
	    case ITEM_KEY:
	      win->GotKey();
	      break;
            }
        }
    }

  // Handle current motion
  if (cxd < 0)       { posX--; cxd++; }
  else if (cxd > 0)  { posX++; cxd--; }
  if (cyd < 0)       { posY--; cyd++; }
  else if (cyd > 0)  { posY++; cyd--; }

  if (cxd == 0 && cyd == 0)   // If motion complete, consider future...
    {
      if (IsDead() == FALSE)
        {
          char& m = map->QueryMap(posX / config->QueryStepX(), posY / config->QueryStepY());
          m = ITEM_EMPTY;
        }

      // Now see about moving off this newly reached position.
      // Favour the previous movement direction if possible...
      if (oldcxd > 0 && keys[RightKey])
        cxd = config->QueryStepX();
      else if (oldcxd < 0 && keys[LeftKey])
        cxd = -config->QueryStepX();
      else if (oldcyd < 0 && keys[DownKey])
        cyd = -config->QueryStepY();
      else if (oldcyd > 0 && keys[UpKey])
        cyd = config->QueryStepY();
      else if (keys[LeftKey])     // No favoured direction, pick anything
        cxd = -config->QueryStepX();
      else if (keys[RightKey])
        cxd = config->QueryStepX();
      else if (keys[UpKey])
        cyd = config->QueryStepY();
      else if (keys[DownKey])
        cyd = -config->QueryStepY();
      oldcxd = cxd;
      oldcyd = cyd;
    }
}

void
Man::KeySet(int _key, ULONG _state)
{
  keys[_key] = (_state & KC_KEYUP) ? 0 : 1;
}

void
Man::Revive(void)
{
  Monster::Revive();

  posX = oldcx;
  posY = oldcy;
  cxd = oldcxd = cyd = oldcyd = 0;
}

Man::Man(MainWindow* _win, int _x, int _y)
: Monster(_win, _x, _y, ITEM_RIBBLESTATIC)
{
  cxd = 0;
  cyd = 0;
  oldcx = posX;
  oldcy = posY;
  oldcxd = cxd;
  oldcyd = cyd;
  keys[LeftKey] = keys[RightKey] =
    keys[UpKey]   = keys[DownKey]  = 0;
}


