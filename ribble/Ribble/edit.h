//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//

#ifndef _Edit_h
#define _Edit_h

class Edit : public Man
{
public:

  Edit(MainWindow* _win, int _x = 0, int _y = 0);
  ULONG QueryItemID(void)    { return ITEM_EDIT;     }
  ULONG QueryItemMskID(void) { return ITEM_EDITMASK; }
  void Move(void);
  void KeySet(int _key, ULONG _state);
  virtual BOOL IsMan(void) { return FALSE; }

  void SetHoldNum(int _num) { holdNum = _num; }
  int QueryHoldNum(void) { return holdNum; }

private:

  int holdNum;

};

#endif
