//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//

#include "common.h"
#pragma hdrstop

#include <fcntl.h>
#include <io.h>
#include <ctype.h>
#include <fstream.h>

#include "resources.h"
#include "ribble.h"
#include "map.h"
#include "screen.h"
#include "monster.h"
#include "man.h"
#include "mainwin.h"
#include "spirit.h"
#include "slither.h"
#include "teleport.h"
#include "config.h"

extern char* fpgetline(int fd);

char temp_table[16] =
{
  ITEM_EMPTY,     ITEM_EMPTY,   ITEM_EMPTY,      ITEM_BOULDER,
  ITEM_EARTH,     ITEM_REDWALL, ITEM_REDWALLNW,  ITEM_EMPTY,
  ITEM_REDWALLNE, ITEM_DIAMOND, ITEM_EMPTY,      ITEM_EARTH,
  ITEM_BOULDER,   ITEM_EARTH,   ITEM_REDWALL,    ITEM_EARTH
  };

inline
BOOL
PotentialDiamond(int c)
{
  return c == ITEM_DIAMOND ||
    c == ITEM_SAFE    ||
      c == ITEM_CAGE;
}


Map::Map(MainWindow* _win)
: win(_win)
{
  ClearMap();
}

Map::~Map()
{
  delete [] map;
}

void
Map::ClearMap(void)
{
  startX = startY = 0;
  mapWidth = 4;
  mapHeight = 4;
  numDiamonds = numMonsters = numTeleporters = 0;
  mapTime = 1000;
  compDiamonds = TRUE;
  compEarth = compMonsters = FALSE;
  offMapItem = ITEM_REDWALL;
  map = new char[mapWidth * mapHeight];
  memset(map, ITEM_EARTH, mapWidth * mapHeight);
  title = "Prison";
  author = "J.R.Wibble";
  comment = "";
}

Map::KeyInfo KeyData[] = {
  { "Title:",       Map::KEY_TITLE   },
  { "Author:",      Map::KEY_AUTHOR  },
  { "Collect:",     Map::KEY_COLLECT },
  { "Locate:",      Map::KEY_LOCATE  },
  { "Data:",        Map::KEY_DATA    },
  { "OffMapItem:",  Map::KEY_OFFMAP  },
  { "End:",         Map::KEY_END     },
  { "Time:",        Map::KEY_TIME    },
  { "Spirit:",      Map::KEY_SPIRIT  },
  { "Slither:",     Map::KEY_SLITHER },
  { "Teleport:",    Map::KEY_TELEPORT },
  { "Comment:",     Map::KEY_COMMENT },
  { 0,              Map::KEY_UNKNOWN }
};

Map::KeyToken
Map::GetKey(char* line, char*& data)
{
  KeyInfo* test = KeyData;

  while (test->keyText)
    {
      int len = strlen(test->keyText);
      if (strnicmp(test->keyText, line, len) == 0)
        {
          while (isspace(line[len]))
            len++;
          data = line + len;
          break;
        }
      test++;
    }
  return test->token;
}

BOOL
Map::ParseCollect(char* _data)
{
  _data;
  compDiamonds = TRUE;
  return TRUE;
}

BOOL
Map::ParseLocate(char* _data)
{
  startX = atoi(_data);
  char* a = _data;
  while (*a && isdigit(*a)) a++;
  while (*a && isspace(*a)) a++;
  startY = atoi(a);
  return TRUE;
}

BOOL
Map::ParseOffMap(char* _data)
{
  offMapItem = atoi(_data);
  if (offMapItem == 0)
    offMapItem = ITEM_REDWALL;
  return TRUE;
}

BOOL
Map::ParseTime(char* _data)
{
  mapTime = atoi(_data);
  if (mapTime == 0)
    mapTime = 1000;
  return TRUE;
}

BOOL
Map::ParseSpirit(char* _data)
{
  int sx = 0;
  int sy = 0;

  sx = atoi(_data);
  char* a = _data;
  while (*a && isdigit(*a)) a++;
  while (*a && isspace(*a)) a++;
  sy = atoi(a);
  while (*a && isdigit(*a)) a++;
  while (*a && isspace(*a)) a++;

  if (win)
    win->QueryMonsters()->addTail(new Spirit(win, sx, sy, a));

  numMonsters++;

  return TRUE;
}

BOOL
Map::ParseSlither(char* _data)
{
  int sx = 0;
  int sy = 0;

  sx = atoi(_data);
  char* a = _data;
  while (*a && isdigit(*a)) a++;
  while (*a && isspace(*a)) a++;
  sy = atoi(a);
  while (*a && isdigit(*a)) a++;
  while (*a && isspace(*a)) a++;

  if (win)
    win->QueryMonsters()->addTail(new Slither(win, sx, sy, a));

  numMonsters++;

  return TRUE;
}

BOOL
Map::ParseTeleport(char* _data)
{
  int sx = 0;
  int sy = 0;

  sx = atoi(_data);
  char* a = _data;
  while (*a && isdigit(*a)) a++;
  while (*a && isspace(*a)) a++;
  sy = atoi(a);
  while (*a && isdigit(*a)) a++;
  while (*a && isspace(*a)) a++;

  if (win)
    {
      Teleport* tele = new Teleport(win, sx, sy, a);
      tele->SetTeleNum(win->QueryHighestTeleNum() + 1);
      win->QueryMonsters()->addTail(tele);
      QueryMap(sx, sy) = ITEM_EARTH;
    }

  numTeleporters++;

  return TRUE;
}


BOOL
Map::ParseData(char* _data, int _fd)
{
  if (map)
    delete [] map;

  mapWidth = mapHeight = 0;   // defaults
  mapWidth = atoi(_data);
  char* a = _data;
  while (*a && isdigit(*a)) a++;
  while (*a && isspace(*a)) a++;
  mapHeight = atoi(a);

  if (mapWidth == 0 || mapHeight == 0)
    return FALSE;

  map = new char[mapWidth * mapHeight];
  memset(map, 0, mapWidth * mapHeight);

  for (int lineNum = 0; lineNum < mapHeight; lineNum++)
    {
      char* line = fpgetline(_fd);

      if (line == 0)
        break;

      char* a = line;
      char* e = line + strlen(line);

      for (int mapNum = 0; a < e && mapNum < mapWidth; mapNum++)
        {
          while (*a && isspace(*a)) a++;
          if (!isdigit(*a))
            break;

          char* b = a;
          while (*a && isdigit(*a)) a++;
          *a++ = '\0';

          int item = atoi(b);
          QueryMap(mapNum, mapHeight - lineNum - 1) = (char)item;

          if (QueryEgg(item)       ||
              item == ITEM_SLITHER ||
              item == ITEM_SPIRIT)
            numMonsters++;
          else if (item == ITEM_TELEPORT)
            numTeleporters++;

          if (PotentialDiamond(item))
            numDiamonds++;
        }

      if (mapNum < mapWidth)
        break;
    }

  if (lineNum == mapHeight)
    return TRUE;
  else
    return FALSE;
}

Map::Map(MainWindow* _win, char* _mapfile)
: win(_win), 
  filename(_mapfile)
{
  BOOL success = TRUE;

  ClearMap();

  int fd = open(_mapfile, O_RDONLY);
  if (fd != -1)
    {
      char* line;
      char* data;
      BOOL end = FALSE;
      while (end == FALSE && success == TRUE && (line = fpgetline(fd)) != 0)
        {
          switch (GetKey(line, data))
            {
            case KEY_TITLE:
              title = data;
              break;
            case KEY_AUTHOR:
              author = data;
              break;
            case KEY_COMMENT:
              comment = data;
              break;
            case KEY_SPIRIT:
              success = ParseSpirit(data);
              break;
            case KEY_SLITHER:
              success = ParseSlither(data);
              break;
            case KEY_TELEPORT:
              success = ParseTeleport(data);
              break;
            case KEY_TIME:
              success = ParseTime(data);
              break;
            case KEY_COLLECT:
              success = ParseCollect(data);
              break;
            case KEY_LOCATE:
              success = ParseLocate(data);
              break;
            case KEY_DATA:
              success = ParseData(data, fd);
              break;
            case KEY_OFFMAP:
              success = ParseOffMap(data);
              break;
            case KEY_END:
              end = TRUE;
              break;
            case KEY_UNKNOWN:
              if (win)
                {
                  CString msg  = "Unknown directive: '";
		  msg += line;
		  msg += "'.";
                  WinMessageBox(HWND_DESKTOP, win->HWindow,
                                (PSZ)(char*)msg,
                                (PSZ)"Ribble map error",
                                0,
                                MB_OK | MB_ERROR);
                }
              success = FALSE;
              break;
            }
        }
      close(fd);
    }
  if (success == FALSE)
    {
      ClearMap();
    }
}

void
Map::SaveMap(void)
{
  /*
     BOOL doMerge = FALSE;

     if (access(filename, 0) == 0)
     {
     CString title = "Saving level [";
     title += filename;
     title += "]";

     ULONG response = WinMessageBox(HWND_DESKTOP,
     win->HWindow,
     (PSZ)"Use the same layout as the previous "
     "version of this level file?",
     (PSZ)(char*)title,
     0,
     MB_YESNOCANCEL | MB_ICONQUESTION | MB_APPLMODAL | MB_MOVEABLE);
     if (response == MBID_YES)
     doMerge = TRUE;
     else if (response == MBID_CANCEL)
     {
     WinMessageBox(HWND_DESKTOP,
     win->HWindow,
     (PSZ)"The level has not been saved.",
     (PSZ)(char*)title,
     0,
     MB_OK | MB_INFORMATION | MB_APPLMODAL | MB_MOVEABLE);
     return;
     }
     }
     */

  //if (doMerge == TRUE)
  //  {
  //    MergeSave();
  //  }
  //else
  //  {
  StraightSave();
  //  }
}

void
Map::StraightSave(void)
{
  ofstream tmpfile(filename);

  int manX = 0;
  int manY = 0;

  Man* man = win->QueryMan();
  RibbleConfig* config = win->QueryConfig();

  if (man)
    {
      manX = man->QueryXPos() / config->QueryStepX();
      manY = man->QueryYPos() / config->QueryStepY();
    }

  tmpfile << "# Ribble v1.00 level file.\n#\n"
    << "Title: " << (char*)title << endl
      << "Comment: " << (char*)comment << endl
	<< "Author: " << (char*)author << endl
          << "Locate: " << manX << ' ' << manY << endl
	    << "Time: " << mapTime << endl
	      << "Data: " << Width() << ' ' << Height();

  for (int y = Height(); --y >= 0; )
    {
      tmpfile << endl;
      for (int x = 0; x < Width(); x++)
        {
          tmpfile << (int)QueryMap(x, y) << ' ';
        }
    }

  tmpfile << endl << "#" << endl;

  MonsterListIter it(*win->QueryMonsters());
  while (it)
    {
      Monster* m = it++;
      if (m->QuerySaveable())
        {
          tmpfile << m->QueryTitle() << ": "
	    << m->QueryXPos() / config->QueryStepX() << ' '
	      << m->QueryYPos() / config->QueryStepX() << ' '
		<< m->QueryData() << endl;
        }
    }
  tmpfile << "End:" << endl;
}

void
Map::SetFilename(int _level)
{
  char buffer[33];
  itoa(_level, buffer, 10);
  filename = "Levels/level.";
  filename += buffer;
}

int
Map::QueryLevelNum(void)
{
  char* filename = QueryFilename();
  char* num = strrchr(filename, '.') + 1;
  int res = atoi(num);
  CAssert(res);
  return res;
}

BOOL
Map::IsCurved(char _item)
{
  return _item == ITEM_BOULDER ||
    _item == ITEM_BOMB ||
      QueryEgg(_item)     ||
	_item == ITEM_DIAMOND;
}

BOOL
Map::IsCurvedNE(char _item)
{
  return IsCurved(_item)         ||
    _item == ITEM_REDWALLNE;
}

BOOL
Map::IsCurvedNW(char _item)
{
  return IsCurved(_item)         ||
    _item == ITEM_REDWALLNW;
}

BOOL
Map::OnMap(int x, int y)
{
  return (x >= 0 && x < mapWidth  &&
          y >= 0 && y < mapHeight) ? TRUE : FALSE;
}
