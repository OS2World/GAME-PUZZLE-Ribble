//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//

#include "common.h"
#include "resources.h"

#ifndef _Monster_h
#define _Monster_h

class MainWindow;

class Monster
{
public:

  Monster(MainWindow* _win, int _posX, int _posY, ULONG _name = ITEM_EMPTY);
  virtual ~Monster();
  virtual int QueryXPos(void) { return posX; }
  virtual int QueryYPos(void) { return posY; }
  virtual void SetXPos(int _x) { posX = _x; }
  virtual void SetYPos(int _y) { posY = _y; }
  virtual ULONG QueryItemID(void) = 0;
  virtual ULONG QueryItemMskID(void) { return 0; }
  virtual void Move(void) = 0;
  virtual BOOL OverlapsMapLocn(int _x, int _y);
  virtual const char* QueryData(void) { return ""; }
  virtual void Die(int _dead = 0) { dead = _dead; }
  virtual BOOL IsDead(void) { return dead != -1 ? TRUE : FALSE; }
  virtual int DeathCnt(void) { return dead; }
  virtual int Weaken(void) { return dead > 0 ? --dead : 0; }
  virtual void Revive(void) { dead = -1; }
  virtual BOOL Deadly(void) { return TRUE; }
  virtual BOOL MonstersOverlap(int _x1, int _y1, int _x2, int _y2);

  virtual ULONG QueryName(void) { return name; }
  virtual char* QueryTitle(void) { return "Monster"; }
  virtual BOOL QuerySaveable(void) { return FALSE; }

protected:

  int             dead;
  int             posX;
  int             posY;
  MainWindow*     win;
  ULONG           name;
};

typedef CDList<Monster*>          MonsterList;
typedef CDListIterator<Monster*>  MonsterListIter;

#endif

