#include <CSupport.h>
#include <CStrng.h>

#if defined(__WIN__) || defined(WIN31)
  #if defined(__WATCOMC__)
    #include <stdio.h>
  #else
    #include <dir.h>
  #endif
#endif


#ifndef _Cff_h
#define _Cff_h

class CSExport CFindFile
{
public:

  enum CFindAttrib
  {
    InclFiles,
    InclFilesAndDirs
  };

  CFindFile(char* _pattern, CFindAttrib _attrib);
  ~CFindFile();
  int Find(CString& _result);

private:

  int           first;
  CFindAttrib   attr;
  CString       pattern;

#if defined(__OS2__)
  HDIR  hdir;
#else
  ffblk ff;
#endif
};

#endif
