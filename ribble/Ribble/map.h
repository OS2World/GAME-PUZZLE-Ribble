//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//

#ifndef _Map_h
#define _Map_h

class MainWindow;

class Map
{
public:
  enum KeyToken {
    KEY_TITLE,
    KEY_AUTHOR,
    KEY_COMMENT,
    KEY_COLLECT,
    KEY_LOCATE,
    KEY_DATA,
    KEY_END,
    KEY_OFFMAP,
    KEY_TIME,
    KEY_SPIRIT,
    KEY_SLITHER,
    KEY_TELEPORT,
    KEY_UNKNOWN
    };

  struct KeyInfo {
    char*         keyText;
    Map::KeyToken token;
  };

  Map(MainWindow* _win);
  Map(MainWindow* _win, char* _mapfile);
  ~Map();
  char& QueryMap(int _x, int _y);
  BOOL QueryEgg(char _item);
  int Height(void) { return mapHeight; }
  int Width(void) { return mapWidth; }
  void ClearMap(void);

  KeyToken GetKey(char* _line, char*& _data);
  BOOL ParseCollect(char* _data);
  BOOL ParseLocate(char* _data);
  BOOL ParseOffMap(char* _data);
  BOOL ParseTime(char* _data);
  BOOL ParseSpirit(char* _data);
  BOOL ParseSlither(char* _data);
  BOOL ParseTeleport(char* _data);
  BOOL ParseData(char* _data, int _fd);

  int QueryInitialX(void) { return startX; }
  int QueryInitialY(void) { return startY; }

  int QueryNumMonsters(void)    { return numMonsters; }
  int QueryNumTeleporters(void) { return numTeleporters; }
  int QueryNumDiamonds(void)    { return numDiamonds; }
  int QueryMapTime(void)        { return mapTime; }

  void SaveMap(void);
  void MergeSave(void);
  void StraightSave(void);

  void SetFilename(int _level);
  CString& QueryFilename(void) { return filename; }
  CString& QueryTitle(void) { return title; }
  CString& QueryAuthor(void) { return author; }
  CString& QueryComment(void) { return comment; }
  BOOL UserMap(void) { return title != "Prison"; }

  void SetTitle(char* _text)    { title = _text; }
  void SetAuthor(char* _text)   { author = _text; }
  void SetComment(char* _text)  { comment = _text; }
  void SetMapTime(int _time)    { mapTime = _time; }

  int QueryLevelNum(void);

  BOOL IsCurved(char _item);
  BOOL IsCurvedNE(char _item);
  BOOL IsCurvedNW(char _item);

  BOOL OnMap(int x, int y);

private:

  MainWindow* win;
  char* map;
  char offMapItem;
  CString filename;
  CString title;
  CString comment;
  CString author;
  BOOL compDiamonds;
  BOOL compEarth;
  BOOL compMonsters;
  int mapWidth;
  int mapHeight;
  int startX;
  int startY;

  int numMonsters;
  int numTeleporters;
  int numDiamonds;
  int mapTime;
};

inline
char&
Map::QueryMap(int x, int y)
{
  if (x < 0 || x >= mapWidth || y < 0 || y >= mapHeight)
    return offMapItem;
  return *(map + x + y * mapWidth);
}

inline
BOOL
Map::QueryEgg(char _a)
{
  return _a == ITEM_EGG || _a == ITEM_CRACKEDEGG;
}





#endif

