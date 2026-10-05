//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//

#ifndef _Slither_h
#define _Slither_h

class Slither : public Monster
{
public:

  Slither(MainWindow* _win, int x, int y, char* _data = 0);
  ULONG QueryItemID(void);
  ULONG QueryItemMskID(void);
  void Move(void);
  BOOL QuerySaveable(void) { return TRUE; }
  virtual char* QueryTitle(void) { return "Slither"; }


private:

  int xd;
  int yd;
  int oldxd;
  int oldyd;
  int anim;
};



#endif

