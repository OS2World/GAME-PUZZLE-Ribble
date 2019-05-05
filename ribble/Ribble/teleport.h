//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//

#ifndef _Teleport_h
#define _Teleport_h


class Teleport : public Monster
{
public:

  Teleport(MainWindow* _win, int x, int y, const char* data = 0);
  ULONG QueryItemID(void);
  void Move(void);
  const char* QueryData(void);

  BOOL QuerySaveable(void) { return TRUE;          }
  char* QueryTitle(void)   { return "Teleport";  }
  BOOL MonstersOverlap(int _x1, int _y1, int _x2, int _y2);

  int QueryDestX(void) { return destX; }
  int QueryDestY(void) { return destY; }
  void SetDestX(int _dx) { destX = _dx; }
  void SetDestY(int _dy) { destY = _dy; }
  int QueryTeleNum(void) { return teleNum; }
  void SetTeleNum(int _tnum)  { teleNum = _tnum; }

private:

  char        dataBuffer[16];
  int         destX;
  int         destY;
  int         teleNum;
  int         anim;
};


#endif

