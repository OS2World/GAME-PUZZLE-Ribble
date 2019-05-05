//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//

#ifndef _Bomb_h
#define _Bomb_h

class Bomb : public Monster
{
public:

  Bomb(MainWindow* _win, int x, int y, const char* data = 0);
  ULONG QueryItemID(void);
  void Move(void);

private:

  int fizzleCnt;
};



#endif

