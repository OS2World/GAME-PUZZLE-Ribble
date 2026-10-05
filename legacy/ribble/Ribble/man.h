//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//

#ifndef _Man_h
#define _Man_h

enum {
  LeftKey = 0,
  RightKey,
  UpKey,
  DownKey
  };

class Man : public Monster
{
public:

  Man(MainWindow* _win, int _x = 0, int _y = 0);
  virtual ULONG QueryItemID(void);
  virtual void Move(void);
  virtual void KeySet(int _key, ULONG _state);
  virtual BOOL IsMan(void) { return TRUE; }
  virtual void Revive(void);

private:

  int             cxd;          // Movement flag. <0 == moving left, >0 == moving right
  int             cyd;          // ditto for up/down
  int             oldcx;        // old position
  int             oldcy;
  int             oldcxd;       // old move dirn.
  int             oldcyd;

public:

  int keys[4];

};

#endif

