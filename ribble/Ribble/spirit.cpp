//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//

#include "common.h"

#include "resources.h"
#include "ribble.h"
#include "map.h"
#include "screen.h"
#include "monster.h"
#include "man.h"
#include "mainwin.h"
#include "spirit.h"
#include "config.h"

#include <stdio.h>
#include <ctype.h>

inline
BOOL
SpiritPossMove(char m)
{
  return (m == ITEM_EMPTY || m == ITEM_EARTH || m == ITEM_CAGE) ? TRUE : FALSE;
}

// Spirits are little fluffy creatures which try to follow
// walls.  When they come into contact with a cage, they
// disappear, and the cage becomes a diamond.
//
// Spirits become dazed (circle endlessly) if they lose
// their wall.  They can move through earth, and empty
// space.
//
// Spirits kill Ribbles.
//

Spirit::Spirit(MainWindow* _win, int x, int y, const char* data)
: Monster(_win,
          x * _win->QueryConfig()->QueryStepX(),
          y * _win->QueryConfig()->QueryStepY(),
          ITEM_SPIRIT)
{
  if (data)
    {
      dir = (MoveDir)atoi(data);
      const char* a = data;
      while (*a && isdigit(*a)) a++;
      while (*a && isspace(*a)) a++;
      if (*a)
        {
          posX = atoi(a);

          while (*a && isdigit(*a)) a++;
          while (*a && isspace(*a)) a++;
          if (*a)
            {
              posY = atoi(a);
            }
        }
    }
  else
    dir = DirLeft;
  trapped = FALSE;
}

void
Spirit::Move(void)
{
  // offsets to map cell in current direction
  static int dxo[4]    = { -1,  0,  1,  0 };
  static int dyo[4]    = {  0,  1,  0, -1 };
  // offsets to map cell to left of current posn.
  static int lxo[4]    = {  0, -1,  0,  1 };
  static int lyo[4]    = { -1,  0,  1,  0 };
  // direction rotated clockwise
  static MoveDir rr[4] = { DirUp, DirRight, DirDown, DirLeft };
  // direction rotated anti-clockwise
  static MoveDir rl[4] = { DirDown, DirLeft, DirUp, DirRight };

  Map* map = win->QueryMap();
  RibbleConfig* config = win->QueryConfig();

  // On a cell boundary?
  if ((posX % config->QueryStepX()) == 0 && (posY % config->QueryStepY()) == 0)
    {
      trapped = TRUE;

      char& c = map->QueryMap(posX / config->QueryStepX(), posY / config->QueryStepY());
      if (c == ITEM_CAGE)
        {
          c = ITEM_DIAMOND;
          dead = TRUE;
          win->Scored(25);
          return;
        }

      // Finding a wall to its left can take a Spirit
      // four direction changes.

      for (int esc=0; esc<4; esc++)
        {
          // Has wall to left vanished?

          char m = map->QueryMap(posX / config->QueryStepX() + lxo[dir], posY / config->QueryStepY() + lyo[dir]);
          if (SpiritPossMove(m) == TRUE)
            {
              // Yup, rotate direction anti-clockwise to try to pick it
              // up again.

              dir = rl[dir];
              trapped = FALSE;
              break;
            }

          // Can Spirit continue in current direction?
          m = map->QueryMap(posX / config->QueryStepX() + dxo[dir], posY / config->QueryStepY() + dyo[dir]);
          if (SpiritPossMove(m) == FALSE)
            {
              // Nope, so rotate direction clockwise so obstacle
              // is on the Spirit's left.
              dir = rr[dir];
            }
          else
            {
              trapped = FALSE;
              break;
            }
        }
    }
  if (trapped == FALSE) // If not trapped, then move in current dirn.
    {
      posX += dxo[dir];
      posY += dyo[dir];
    }
}

ULONG
Spirit::QueryItemID(void)
{
  // Change bitmap when trapped maybe?  Sulking spirit?  Change to a diamond?
  return (posX & 0x01) | (posY & 0x01) ? ITEM_SPIRIT1 : ITEM_SPIRIT;
}

ULONG
Spirit::QueryItemMskID(void)
{
  // Change bitmap when trapped maybe?  Sulking spirit?  Change to a diamond?
  return (posX & 0x01) | (posY & 0x01) ? ITEM_SPIRIT1MASK : ITEM_SPIRITMASK;
}

const char*
Spirit::QueryData(void)
{
  sprintf(dataBuffer, "%d %d %d", dir, posX, posY);
  return dataBuffer;
}


