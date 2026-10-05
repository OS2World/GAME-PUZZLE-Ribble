// -------------------------------
//  Name:           CString.h
//  Author:         J.R.Shannon
//  Language:       C++
//  Date:           6/11/92
//  Revison:        2.1
//  Last revision:  9/7/93
//  Licence:        Public Domain
//  Purpose:        String handling package
// -------------------------------
//

#include <CSupport.h>
#include <CAssert.h>

#ifndef _CString_h
#define _CString_h

#include <string.h>
#include <sys/types.h>

//
// INTERFACE
//

class CSExport CString
{
public:
  CString();
  CString(const CString&);
  CString(const char*);
  CString(const char);
  CString(const unsigned int);
  ~CString();

  CString& operator=(const CString&);
  CString& operator=(const char*);
  CString& operator=(const char);
  CString& operator+=(const CString&);
  CString& operator+=(const char*);
  CString& operator+=(const char);
  CString  operator+(const CString&) const;
  int operator==(const CString&) const;
  int operator!=(const CString&) const;
  int operator<=(const CString&) const;
  int operator>=(const CString&) const;
  int operator<(const CString&) const;
  int operator>(const CString&) const;
  int operator==(const char*) const;
  int operator!=(const char*) const;
  int operator<=(const char*) const;
  int operator>=(const char*) const;
  int operator<(const char*) const;
  int operator>(const char*) const;
  const char& operator[](size_t index);

  void Resync(void) { length = strlen(data); }
  operator char*() const;   // Get a pointer to a char* representation of the CString
  size_t len() const;

  char* index(const int);   // strchr and strrchr facilities
  char* rindex(const int);

  void makeUpper(void);     // conver to upper case
  void makeLower(void);     //           lower
  void stripTrailing(char _ch);

private:
  char*               data;
  size_t              length;
  size_t              chunk;

  enum { chunk_size = 16 };

  size_t  chunkRound(size_t) const;
};


#endif

