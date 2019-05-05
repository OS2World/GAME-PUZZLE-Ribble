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
#include "edit.h"
#include "mainwin.h"
#include "spirit.h"
#include "slither.h"
#include "teleport.h"
#include "pal.h"
#include "about.h"
#include "help.h"
#include "level.h"
#include "save.h"
#include "options.h"
#include "config.h"
#include "hiscore.h"
#include "bomb.h"

#include <stdio.h>

void
MainWindow::UpdateScreen(void)
{
  HPS hps = WinGetPS(HWindow);

  switch (gamestate)
    {
    case ShowMap:
      RenderMap();
      break;
    case PlayGame:
    case Teleporting:
      RenderScreen();
      break;
    }

  screen->BlitScreen(hps, 0, 0);

  WinReleasePS(hps);
}

void
MainWindow::RenderScreen(void)
{
  int left = man->QueryXPos() - config->QueryCentreXoff() * config->QueryStepX();
  int btm = man->QueryYPos() - config->QueryCentreYoff() * config->QueryStepY();

  int mapX = left / config->QueryStepX();
  int ls = -(left % config->QueryStepX());
  int mapY = btm  / config->QueryStepY();
  int bs = -(btm  % config->QueryStepY());

  if (left < 0)
    {
      mapX--;
      ls += -config->QueryStepX();
    }
  if (btm < 0)
    {
      mapY--;
      bs += -config->QueryStepY();
    }

  int screenX = ls * (config->QueryCellWidth()  / config->QueryStepX());
  int screenY = bs * (config->QueryCellHeight() / config->QueryStepY());

  for (int w = 0; w < config->QueryVisWidth() + 1; w++)
    {
      for (int h = 0; h < config->QueryVisHeight() + 1; h++)
        {
          int sx = screenX + w * config->QueryCellWidth();
          int sy = screenY + h * config->QueryCellHeight();

          char item = map->QueryMap(mapX + w, mapY + h);

          if (item == ITEM_BOMBLIVE1 && (fizzleCnt & 2))
            item = ITEM_BOMBLIVE2;

          screen->DrawBitmap(item, sx, sy);
        }
    }

  RenderMonsters();
  RenderMan();
}

void
MainWindow::RenderMonsters(void)
{
  MonsterListIter it(monsters);
  while (it)
    {
      Monster* s = it++;

      int mx = s->QueryXPos();
      int my = s->QueryYPos();

      int left = man->QueryXPos() - config->QueryCentreXoff() * config->QueryStepX();
      int btm  = man->QueryYPos() - config->QueryCentreYoff() * config->QueryStepY();

      if (mx > left - config->QueryStepX() && mx < left + (config->QueryVisWidth() * config->QueryStepX()) + config->QueryStepX() &&
          my > btm - config->QueryStepY() && my < btm + (config->QueryVisHeight() * config->QueryStepY()) + config->QueryStepY())
        {
          int screenX = (mx - left) * (config->QueryCellWidth()  / config->QueryStepX());
          int screenY = (my - btm)  * (config->QueryCellHeight() / config->QueryStepY());
          ULONG id = s->QueryItemID();
          ULONG mid = s->QueryItemMskID();

          if (mid == 0)
            screen->DrawBitmap(id, screenX, screenY);
          else
            screen->DrawBitmap(id, mid, screenX, screenY);

          if (man->IsMan() == FALSE && s->QueryName() == ITEM_TELEPORT)
            {
              Teleport* tele = (Teleport*)s;

              RECTL rct;
              rct.xLeft = screenX;
              rct.xRight = screenX + config->QueryCellWidth();
              rct.yBottom = screenY;
              rct.yTop = screenY + config->QueryCellHeight();

              char buffer[16];
              sprintf(buffer, "%d", tele->QueryTeleNum());

              screen->RenderText(buffer, rct, CLR_WHITE, CLR_RED);
            }
        }

      if (man->IsMan() == FALSE && s->QueryName() == ITEM_TELEPORT)
        {
          Teleport* tele = (Teleport*)s;

          int mx = tele->QueryDestX() * config->QueryStepX();
          int my = tele->QueryDestY() * config->QueryStepY();

          if (mx > left - config->QueryStepX() && mx < left + (config->QueryVisWidth() * config->QueryStepX()) + config->QueryStepX() &&
              my > btm - config->QueryStepY() && my < btm + (config->QueryVisHeight() * config->QueryStepY()) + config->QueryStepY())
            {
              int screenX = (mx - left) * (config->QueryCellWidth()  / config->QueryStepX());
              int screenY = (my - btm)  * (config->QueryCellHeight() / config->QueryStepY());

              RECTL rct;
              rct.xLeft = screenX;
              rct.xRight = screenX + config->QueryCellWidth();
              rct.yBottom = screenY;
              rct.yTop = screenY + config->QueryCellHeight();

              char buffer[16];
              sprintf(buffer, "%d", tele->QueryTeleNum());

              screen->RenderText(buffer, rct, CLR_WHITE, CLR_BLUE);
            }
        }
    }
}

void
MainWindow::RenderMan(void)
{
  int screenX = config->QueryCentreXoff() * config->QueryCellWidth();
  int screenY = config->QueryCentreYoff() * config->QueryCellHeight();

  ULONG id = man->QueryItemID();
  ULONG mid = man->QueryItemMskID();
  if (mid == 0)
    screen->DrawBitmap(id, screenX, screenY);
  else
    screen->DrawBitmap(id, mid, screenX, screenY);

  if (man->IsMan() == FALSE)
    {
      Edit* edit = (Edit*)man;
      if (edit->QueryHoldNum())
        {
          char buffer[8];
          sprintf(buffer, "%d", edit->QueryHoldNum());

          RECTL rct;
          rct.xLeft   = config->QueryCellWidth()  * config->QueryCentreXoff();
          rct.xRight  = rct.xLeft + config->QueryCellWidth();
          rct.yBottom = config->QueryCellHeight() * config->QueryCentreYoff();
          rct.yTop    = rct.yBottom + config->QueryCellHeight();

          screen->RenderText(buffer, rct, CLR_WHITE, CLR_BLUE);
        }
    }
}

void
MainWindow::RenderMap(void)
{
  int cellWidth  = mapCellWid;
  int cellHeight = mapCellHgt;
  int centreXoff = config->QueryCentreXoff() * (config->QueryCellWidth()  / cellWidth);
  int centreYoff = config->QueryCentreYoff() * (config->QueryCellHeight() / cellHeight);
  int visWidth  = config->QueryVisWidth()  * (config->QueryCellWidth()  / cellWidth);
  int visHeight = config->QueryVisHeight() * (config->QueryCellHeight() / cellHeight);

  int left = man->QueryXPos() - centreXoff * config->QueryStepX();
  int btm = man->QueryYPos() - centreYoff * config->QueryStepY();

  int mapX = left / config->QueryStepX();
  int ls = -(left % config->QueryStepX());
  int mapY = btm  / config->QueryStepY();
  int bs = -(btm  % config->QueryStepY());

  if (left < 0)
    {
      mapX--;
      ls += -config->QueryStepX();
    }
  if (btm < 0)
    {
      mapY--;
      bs += -config->QueryStepY();
    }

  int screenX = ls * (cellWidth  / config->QueryStepX());
  int screenY = bs * (cellHeight / config->QueryStepY());

  for (int w = 0; w < visWidth + 1; w++)
    {
      for (int h = 0; h < visHeight + 1; h++)
        {
          int sx = screenX + w * cellWidth;
          int sy = screenY + h * cellHeight;

          char item = map->QueryMap(mapX + w, mapY + h);

          screen->DrawBitmap(item, sx, sy, cellWidth, cellHeight);
        }
    }
}

void
MainWindow::HandleThings(void)
{
  if (gamestate == Teleporting)
    {
      HandleTeleport();
      return;
    }

  if (gamestate == PlayGame)
    {
      man->Move();

      if (man->IsDead() && man->Weaken() == 0)
        {
          lives--;
          RenderLives();
          if (lives == 0)
            {
              oldScore = score;
              EndGame();
              HandleHiscores();
              return;
            }
          else
            {
              if (restartLevel == TRUE)
                RestartCurrentLevel();
              else
                { // Set man position to initial location on map
                  // not any more - this only happens on Escape.
                  //man->SetXPos(map->QueryInitialX() * config->QueryStepX());
                  //man->SetYPos(map->QueryInitialY() * config->QueryStepY());
                }
            }
          man->Revive();
        }
    }

  HPS hps = WinGetPS(HWindow);

  if (gamestate != ShowStatus)
    {
      time--;
      if ((time % TimeScale) == 0)
        RenderTime(hps);
      if (time == 0)
        {
          man->Die(manDeathCount);
        }
    }

  if (gamestate == PlayGame || gamestate == Teleporting)
    {
      if (man->IsMan())
        {
          MoveMonsters();
          DropBoulders();
          RenderScreen();
          screen->BlitScreen(hps, 0, 0);
        }
    }

  WinReleasePS(hps);
}

#define DroppableObject(x)     \
((x) == ITEM_BOULDER ||       \
 (x) == ITEM_BOMB ||          \
 (x) == ITEM_BOMBLIVE1 ||     \
 map->QueryEgg(x))            \

 void
 MainWindow::DropBoulders(void)
{
  if (man->IsMan() == FALSE)// || man->IsDead())
    return;

  BOOL checkEggs = FALSE;
  BOOL checkBombs = FALSE;

  if (eggHatchCnt && --eggHatchCnt == 0)
    checkEggs = TRUE;
  if (fizzleCnt == 0)
    checkBombs = TRUE;
  else
    fizzleCnt--;

  for (int y=-1; y<map->Height(); y++)
    {
      for (int x=0; x<map->Width(); x++)
        {
          BOOL drop = FALSE;
          int dropX, dropY;

          char& b = map->QueryMap(x, y);

          if (b == ITEM_SPIRIT)
            {
              b = ITEM_EMPTY;
              monsters += new Spirit(this, x, y);
            }
          else if (b == ITEM_TELEPORT)
            {
              b = ITEM_EARTH; // so that boulders rest on top
              Teleport* tele = new Teleport(this, x, y);
              tele->SetTeleNum(QueryHighestTeleNum() + 1);
              monsters += tele;
            }
          else
            {
              char& a = map->QueryMap(x, y+1);

              if (checkEggs && a == ITEM_CRACKEDEGG)
                {
                  a = ITEM_EMPTY;
                  monsters.addTail(new Slither(this, x, y+1));
                }

              if (checkBombs && a == ITEM_BOMBLIVE1)
                {
                  a = ITEM_EMPTY;
                  monsters += new Bomb(this, x-1, y);
                  monsters += new Bomb(this, x,   y);
                  monsters += new Bomb(this, x+1, y);
                  monsters += new Bomb(this, x-1, y+1);
                  monsters += new Bomb(this, x,   y+1);
                  monsters += new Bomb(this, x+1, y+1);
                  monsters += new Bomb(this, x-1, y+2);
                  monsters += new Bomb(this, x,   y+2);
                  monsters += new Bomb(this, x+1, y+2);
                }

              if (DroppableObject(a))
                {
                  if (b == ITEM_EMPTY && RibbleBelow(x, y) == FALSE)
                    {
                      if (CheckManCrushed(x, y) == TRUE)
                        {
                          man->Die(manDeathCount);
                        }
                      else
                        {
                          do
                            {
                              char& f = map->QueryMap(x, y-1);
                              if (f != ITEM_EMPTY)
                                if (a == ITEM_EGG)
                                  {
                                    b = ITEM_CRACKEDEGG;
                                    eggHatchCnt = HatchDelayCnt;
                                    break;
                                  }
                                else if (f != ITEM_EARTH && a == ITEM_BOMB)
                                  {
                                    b = ITEM_BOMBLIVE1;
                                    fizzleCnt = FizzleDelayCnt;
                                    break;
                                  }
                                else if (f == ITEM_BOMB && a == ITEM_BOULDER)
                                  {
                                    f = ITEM_BOMBLIVE1;
                                    break;
                                  }
                              b = a;
                            }
                          while (0);

                          a = ITEM_EMPTY;
                          drop = TRUE; dropX = x; dropY = y;
                        }
                    }
                  else if (map->IsCurved(b) == TRUE)
                    {
                      char& c = map->QueryMap(x-1, y);
                      char& d = map->QueryMap(x-1, y+1);
                      if (c == ITEM_EMPTY &&
                          d == ITEM_EMPTY &&
                          RibbleMap(x-1, y) == FALSE &&
                          RibbleMap(x-1, y+1) == FALSE)
                        {
                          d = a;
                          a = ITEM_EMPTY;
                          drop = TRUE; dropX = x-1; dropY = y+1;
                        }
                      else
                        {
                          char& c = map->QueryMap(x+1, y);
                          char& d = map->QueryMap(x+1, y+1);
                          if (c == ITEM_EMPTY && d == ITEM_EMPTY &&
                              RibbleMap(x+1, y) == FALSE &&
                              RibbleMap(x+1, y+1) == FALSE)
                            {
                              d = a;
                              a = ITEM_EMPTY;
                              drop = TRUE; dropX = x+1; dropY = y+1;
                            }
                        }
                    }
                  else if (map->IsCurvedNW(b))
                    {
                      char& c = map->QueryMap(x-1, y);
                      char& d = map->QueryMap(x-1, y+1);
                      if (c == ITEM_EMPTY && d == ITEM_EMPTY &&
                          RibbleMap(x-1, y) == FALSE &&
                          RibbleMap(x-1, y+1) == FALSE)
                        {
                          d = a;
                          a = ITEM_EMPTY;
                          drop = TRUE; dropX = x-1; dropY = y+1;
                        }
                    }
                  else if (map->IsCurvedNE(b))
                    {
                      char& c = map->QueryMap(x+1, y);
                      char& d = map->QueryMap(x+1, y+1);
                      if (c == ITEM_EMPTY && d == ITEM_EMPTY &&
                          RibbleMap(x+1, y) == FALSE &&
                          RibbleMap(x+1, y+1) == FALSE)
                        {
                          d = a;
                          a = ITEM_EMPTY;
                          drop = TRUE; dropX = x+1; dropY = y+1;
                        }
                    }
                }
            }

          if (drop == TRUE)
            {
              CheckMonsterCrushed(dropX, dropY);
            }
        }
    }
}

BOOL
MainWindow::RibbleMap(int _x, int _y)
{
  if (man->IsMan() == FALSE)
    return FALSE;

  return man->OverlapsMapLocn(_x, _y);
}

BOOL
MainWindow::RibbleBelow(int _x, int _y)
{
  if (man->IsMan() == FALSE)
    return FALSE;

  return man->OverlapsMapLocn(_x, _y) &&
    (man->QueryYPos() % config->QueryStepY()) == 0;
}

void
MainWindow::MoveMonsters(void)
{
  MonsterListIter it(monsters);
  while (it)
    {
      Monster* s = it.current();

      s->Move();

      if (s->IsDead() && s->Weaken() == 0)
        {
          delete it.current();
          it.remove();
        }
      else
        {
          if (s->Deadly() == TRUE && man->IsDead() == FALSE)
            {
              if (s->MonstersOverlap(s->QueryXPos(),
                                     s->QueryYPos(),
                                     man->QueryXPos(),
                                     man->QueryYPos()) == TRUE)
                {
                  man->Die(manDeathCount);
                }
            }

          it++;
        }
    }
}

void
MainWindow::RemoveMonsters(void)
{
  MonsterListIter it(monsters);
  while (it)
    {
      Monster* s = it++;
      delete s;
    }
  monsters.destroy();
}


void
MainWindow::CheckMonsterCrushed(int _x, int _y)
{
  // Check for monsters under this boulder...
  // This is rather inefficient.

  MonsterListIter it(monsters);
  while (it)
    {
      Monster* s = it.current();

      if (s->QueryName() == ITEM_SLITHER && s->OverlapsMapLocn(_x, _y))
        {
          Scored(50);
          delete it.current();
          it.remove();
        }
      else
        it++;
    }
}

void
MainWindow::Scored(int _amount)
{
  score += _amount;
  RenderScore();
}

void
MainWindow::GotKey(void)
{
  Scored(10);
  for (int y=0; y<map->Height(); y++)
    {
      for (int x=0; x<map->Width(); x++)
        {
          char& b = map->QueryMap(x, y);

          if (b == ITEM_SAFE)
            b = ITEM_DIAMOND;
        }
    }
}

void
MainWindow::EatDiamond(void)
{
  Scored(10);
  diamonds--;
  RenderDiamonds();
  RenderScore();

  if (diamonds == 0)
    {
      StartTeleporting(-1, -1);
    }
}

void
MainWindow::EatEarth(void)
{
  Scored(1);
  RenderScore();
}

BOOL
MainWindow::CheckManCrushed(int _x, int _y)
{
  //if (man->IsDead() == FALSE)
  {
    if (man->OverlapsMapLocn(_x, _y-1))
      return TRUE;
  }
  return FALSE;
}

void
MainWindow::SetMapItem(int _item)
{
  if (man)
    {
      int x = man->QueryXPos() / config->QueryStepX();
      int y = man->QueryYPos() / config->QueryStepY();

      map->QueryMap(x, y) = _item;

      UpdateScreen();
    }
}

Monster*
MainWindow::LocateMonster(int _mx, int _my)
{
  MonsterListIter it(monsters);
  while (it)
    {
      Monster* m = it++;
      if (m->OverlapsMapLocn(_mx, _my))
        return m;
    }
  return 0;
}

Teleport*
MainWindow::LocateTeleport(int _teleNum)
{
  MonsterListIter it(monsters);
  while (it)
    {
      Monster* m = it++;
      if (m->QueryName() == ITEM_TELEPORT)
        {
          Teleport* tele = (Teleport*)m;
          if (tele->QueryTeleNum() == _teleNum)
            return tele;
        }
    }
  return 0;
}

Teleport*
MainWindow::LocateTeleDest(int _tx, int _ty)
{
  MonsterListIter it(monsters);
  while (it)
    {
      Monster* m = it++;
      if (m->QueryName() == ITEM_TELEPORT)
        {
          Teleport* tele = (Teleport*)m;
          if (tele->QueryDestX() == _tx &&
              tele->QueryDestY() == _ty)
            return tele;
        }
    }
  return 0;
}

int
MainWindow::QueryHighestTeleNum(void)
{
  int res = 0;

  MonsterListIter it(monsters);
  while (it)
    {
      Monster* m = it++;
      if (m->QueryName() == ITEM_TELEPORT)
        {
          Teleport* tele = (Teleport*)m;
          if (tele->QueryTeleNum() > res)
            res = tele->QueryTeleNum();
        }
    }
  return res;
}

void
MainWindow::StartTeleporting(int _tx, int _ty)
{
  teleDestX = _tx;
  teleDestY = _ty;
  teleporting = (config->QueryVisWidth() + 1) / 2;
  gamestate = Teleporting;
}

void
MainWindow::HandleTeleport(void)
{
  HPS hps = WinGetPS(HWindow);

  int off = (config->QueryVisWidth() + 1) / 2 - teleporting;
  int sx;
  int sy;
  int fadeItem = teleDestX == -1 ? ITEM_DIAMOND : ITEM_TELEPORT;

  for (int a = off; a <= config->QueryVisWidth() - off - 1; a++)
    {
      sx = a * config->QueryCellWidth();
      sy = off * config->QueryCellHeight();
      screen->DrawBitmap(fadeItem, sx, sy);

      sy = config->QueryCellHeight() * config->QueryVisHeight() - sy - config->QueryCellHeight();
      screen->DrawBitmap(fadeItem, sx, sy);
    }

  for (a = off + 1; a <= config->QueryVisHeight() - off - 2; a++)
    {
      sx = off * config->QueryCellWidth();
      sy = a * config->QueryCellHeight();
      screen->DrawBitmap(fadeItem, sx, sy);

      sx = config->QueryCellWidth() * config->QueryVisWidth() - sx - config->QueryCellWidth();
      screen->DrawBitmap(fadeItem, sx, sy);
    }

  if (teleDestX == -1)
    {
      RECTL pos;
      pos.xLeft = 0;
      pos.xRight = config->QueryCellWidth() * config->QueryVisWidth();
      pos.yBottom = 0;
      pos.yTop = config->QueryCellHeight() * config->QueryVisHeight();

      screen->RenderText("** Next Level! **",
			 pos,
			 CLR_YELLOW,
			 CLR_BLUE,
			 DT_CENTER | DT_VCENTER);
    }

  screen->BlitScreen(hps, 0, 0);

  WinReleasePS(hps);

  if (--teleporting == -1)
    {
      gamestate = PlayGame;

      if (teleDestX == -1 && teleDestY == -1)
        {
          StartNextLevel();
        }
      else
        {
          man->SetXPos(teleDestX);
          man->SetYPos(teleDestY);
        }
    }
}

int
MainWindow::QueryNumEarth(void)
{
  return QueryNumItems(ITEM_EARTH);
}

int
MainWindow::QueryNumSpirits(void)
{
  return QueryNumItems(ITEM_SPIRIT) + QueryNumMonsters(ITEM_SPIRIT);
}

int
MainWindow::QueryNumTeleporters(void)
{
  return QueryNumItems(ITEM_TELEPORT) + QueryNumMonsters(ITEM_TELEPORT);
}

int
MainWindow::QueryNumMonsters(ULONG _name)
{
  int count = 0;

  MonsterListIter it(monsters);
  while (it)
    if (it++->QueryName() == _name)
      count++;
  return count;
}

int
MainWindow::QueryNumItems(ULONG _name)
{
  int count = 0;

  for (int x=0; x<map->Width(); x++)
    for (int y=0; y<map->Height(); y++)
      if (map->QueryMap(x, y) == _name)
        count++;
  return count;
}

