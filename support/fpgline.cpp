//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//

#include <CSupport.h>
#include <CAssert.h>
#include <string.h>
#include <fcntl.h>
#include <io.h>

char* CSExport
fpreadline(int _fd)
{
  static char* line;
  static int len = 0;

  if (len == 0)
    {
      len = 64;
      line = new char[len];
      CAssert(line);
    }

  *line = '\0';

  int eof = 0;

  for (int got = 0; !eof;)
    {
      char ch;
      if (read(_fd, &ch, sizeof(ch)) == sizeof(ch))
        {
          if (ch == '\n')
            {
              line[got] = '\0';
              break;
            }
          line[got++] = ch;
          if (got >= len)
            {
              len <<= 1;
              char* ext = new char[len];
              memcpy(ext, line, got);
              delete [] line;
              line = ext;
            }
        }
      else
        eof = 1;
    }
  return !got && eof ? 0 : line;
}

char* CSExport
fpgetline(int _fd)
{
  char* line;
  while ((line = fpreadline(_fd)) != 0)
    {
      char* a = line;
      char* b = line;
      while ((*a = *b) != 0)
        {
          if (*b == '#')
            {
              *a = '\0';
              break;
            }
          a++;
          b++;
        }
      if (*line)
        break;
    }
  return line;
}


