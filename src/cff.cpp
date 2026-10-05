#if defined(__OS2__)
#define INCL_DOS
#include <os2.h>
#else
#include <dos.h>
#endif

#include <Cff.h>

CFindFile::CFindFile(char* _pattern, CFindAttrib _attrib)
: pattern(_pattern),
  first(1),
  attr(_attrib)
{
}


CFindFile::~CFindFile()
{
#if defined(__OS2__)
  if (first == 0)
    DosFindClose(hdir);
#else
#endif
}

int
CFindFile::Find(CString& _foundfile)
{
#if defined(__OS2__)
  FILEFINDBUF3 ffb3;
  ULONG count = 1;

  if (first)
    {
      first = 0;
      hdir = HDIR_CREATE;

      ULONG attrib = attr == InclFiles ? 0 :
                     attr == InclFilesAndDirs ? FILE_DIRECTORY : 0;

      APIRET rc = DosFindFirst((PSZ)(char*)pattern, &hdir, attrib,
                               &ffb3, sizeof(ffb3), &count, FIL_STANDARD);

      if (rc == 0 && count == 1)
        {
          _foundfile = ffb3.achName;
          return 1;
        }
    }
  else
    {
      APIRET rc = DosFindNext(hdir, &ffb3, sizeof(ffb3), &count);

      if (rc == 0 && count == 1)
        {
          _foundfile = ffb3.achName;
          return 1;
        }
    }
#else
  if (first)
    {
      int attrib = attr == InclFiles ? 0 :
                   attr == InclFilesAndDirs ? FA_DIREC : 0;
      int ret = findfirst(pattern, &ff, attrib);
      if (ret == 0)
        {
          _foundfile = ff.ff_name;
          return 1;
        }
    }
  else
    {
      int ret = findnext(&ff);
      if (ret == 0)
        {
          _foundfile = ff.ff_name;
          return 1;
        }
    }
#endif
  return 0;
}




