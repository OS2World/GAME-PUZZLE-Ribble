//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//

#include "common.h"

#include <stdio.h>
#include <ctype.h>

#include "resources.h"
#include "ribble.h"
#include "map.h"
#include "screen.h"
#include "monster.h"
#include "man.h"
#include "mainwin.h"
#include "teleport.h"
#include "config.h"


// Teleporters allow Ribble to jump from one area of the map
// to another.   Once used, they disappear....
//

Teleport::Teleport(MainWindow* _win, int x, int y, const char* data)
: Monster(_win,
          x * _win->QueryConfig()->QueryStepX(),
          y * _win->QueryConfig()->QueryStepY(),
          ITEM_TELEPORT)
{
  if (data)
    {
      destX = atoi(data);
      const char* a = data;
      while (*a && isdigit(*a)) a++;
      while (*a && isspace(*a)) a++;
      destY = atoi(a);
    }
  else
    {
      destX = x;
      destY = y;
    }
  teleNum = 0;
  anim = 0;
}

static ULONG
teleTable[4] =
{
  ITEM_TELEPORT1,
  ITEM_TELEPORT3,
  ITEM_TELEPORT2,
  ITEM_TELEPORT4
  };

ULONG
Teleport::QueryItemID(void)
{
  if (IsDead())
    return ITEM_EMPTY;
  return teleTable[(anim >> 2) & 0x03];
}

void
Teleport::Move(void)
{
  anim = anim + 1;
}

const char*
Teleport::QueryData(void)
{
  sprintf(dataBuffer, "%d %d", destX, destY);
  return dataBuffer;
}


BOOL 
Teleport::MonstersOverlap(int _x1, int _y1, int _x2, int _y2)
{
  RibbleConfig* config = win->QueryConfig();

  if (Monster::MonstersOverlap(_x1, _y1, _x2, _y2) == TRUE &&
      (_x2 % config->QueryStepX() == 0) &&
      (_y2 % config->QueryStepY() == 0) )
    {
      Man* man = win->QueryMan();
      if (man && man->IsDead() == FALSE && man->IsMan() == TRUE)
        {
          win->StartTeleporting(destX * config->QueryStepX(), destY * config->QueryStepY());
          //man->SetXPos(destX * config->QueryStepX());
          //man->SetYPos(destY * config->QueryStepY());
          Die();
        }
    }
  return FALSE;
}




