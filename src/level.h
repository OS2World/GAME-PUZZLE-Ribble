//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//

#ifndef _Level_h
#define _Level_h

class LevelThread;

class SelectLevel : public CDialog
{
public:

  SelectLevel(MainWindow* _win, HWND _owner);
  ~SelectLevel();
  MRESULT ProcessMsg(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
  void SetupWindow(void);
  MRESULT WMControl(MPARAM mp1, MPARAM mp2);
  MRESULT WMCommand(MPARAM mp1, MPARAM mp2);
  void ShowLevelInfo(Map* map);
  void LoadCurrentLevel(void);

  typedef CDList<Map*>          MapList;
  typedef CDListIterator<Map*>  MapListIter;

private:

  MapList       maps;
  MainWindow*   win;
  LevelThread*  levelThread;
};

class
LevelThread : public CThread
{
public:
  LevelThread(HWND _HWindow, SelectLevel::MapList& _maps)
    : HWindow(_HWindow),
  maps(_maps)
    {
    }
  void ThreadProc(void);

private:
  HWND                  HWindow;
  SelectLevel::MapList& maps;
};


#endif

