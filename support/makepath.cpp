#include <CSupport.h>
#include <Makepath.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#if defined(__OS2__) || defined(__WATCOMC__)
#include <direct.h>
#else
#include <dir.h>
#endif

// Returns 1 if path found
// Returns 2 if path created
// Returns 0 if failed

int CSExport
makePath(const char* newPath)
{
  if (isValidPath(newPath) == 0)
    return 0;

  char*   path = new char[strlen(newPath)+1];
  char*   p = path;
	int     success = 1;

  if (path == 0)
    return 0;
  else
    strcpy(path, newPath);

  if (*p == '\\' || *p == '/')  // skip leading root spec.
    p++;

  if (*p == 0)
    return 1;

  while (success)
    {
      if ((*p == '\\' || *p == '/' || *p == '\0') && (p - path > 0 && p[-1] != ':'))
        {
          char oldCh = *p;
          *p = '\0';

					struct stat info;

          if (stat(path, &info) == -1)
            if (errno == ENOENT)
              if (mkdir(path) == -1)
                success = 0;
              else
                success = 2;    // worked & dir made

          *p = oldCh;

          if (*p == 0)
            break;
        }
      p++;
		}
	return success;
}

int CSExport
isValidPath(const char* _path)
{
  // Check that dir being made is <= 8 chars in length

  const char* pch = _path + strlen(_path) - 1;
  int len = 0;

  while (pch != _path)
    {
      char ch = *pch--;
      if (ch == ':' || ch == '\\' || ch == '/' || ch == '.')
        len = 0;
      else if (ch == '\0')
        break;
      else
        len++;

      if (len > 8)
        return 0;
    }

  return 1;
}


