//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//

#ifndef _Spirit_h
#define _Spirit_h

class Spirit : public Monster
{
  enum MoveDir { DirLeft = 0, DirUp, DirRight, DirDown };

public:

  Spirit(MainWindow* _win, int x, int y, const char* data = 0);
  ULONG QueryItemID(void);
  ULONG QueryItemMskID(void);
  void Move(void);
  const char* QueryData(void);

  BOOL QuerySaveable(void) { return TRUE;     }
  char* QueryTitle(void)   { return "Spirit"; }

private:

  MoveDir     dir;
  BOOL        trapped;
  char        dataBuffer[16];
};



#endif

