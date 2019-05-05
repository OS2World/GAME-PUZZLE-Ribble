// -------------------------------
//  Name:           CString.cpp
//  Author:         J.R.Shannon
//  Language:       C++
//  Date:           6/11/92
//  Revison:        2.1
//  Last revision:  9/7/93
//  Licence:        Public Domain
//  Purpose:        String handling package
// -------------------------------

#include <CStrng.h>
#include <stdio.h>
#include <ctype.h>

// Make a CString from nothing.

CString::CString()
{
  length = 0;
  chunk = chunkRound(length + 1);
  data = new char[chunk];
  CAssert(data);
  data[0] = '\0';
}

// Make a CString from another CString.

CString::CString(const CString& from)
{
  length = from.length;
  chunk = from.chunk;
  data = new char[chunk];
  CAssert(data);
  memcpy(data, from.data, length + 1);
}

// Make a CString from a '\0' terminated char* string.

CString::CString(const char* from)
{
  length = strlen(from);
  chunk = chunkRound(length + 1);
  data = new char[chunk];
  CAssert(data);
  memcpy(data, from, length + 1);
}

// Make a CString from a character.

CString::CString(const char from)
{
  length = sizeof(from);
  chunk = chunkRound(length + 1);
  data = new char[chunk];
  CAssert(data);
  data[0] = from;
  data[1] = '\0';
}

// Make a CString from a decimal number.

CString::CString(const unsigned int from)
{
  length = 16;
  chunk = chunkRound(length + 1);
  data = new char[chunk];
  CAssert(data);
  sprintf(data, "%u", from);
  length = strlen(data);
}

// Append another CString.

CString& CString::operator+=(const CString& from)
{
  if (chunk < length + from.length + 1)
    {
      chunk = chunkRound(length + from.length + 1);
      char* newdata = new char[chunk];
      CAssert(newdata);
      memcpy(newdata, data, length);
      memcpy(newdata+length, from.data, from.length+1);
      delete [] data;
      data = newdata;
    }
  else
    memcpy(data+length, from.data, from.length + 1);

  length += from.length;
  return *this;
}

// Append a char* '\0' terminated string.

CString& CString::operator+=(const char* from)
{
  const size_t fromLen = strlen(from);

  if (chunk < length + fromLen + 1)
    {
      chunk = chunkRound(length + fromLen + 1);
      char* newdata = new char[chunk];
      CAssert(newdata);
      memcpy(newdata, data, length);
      memcpy(newdata+length, from, fromLen+1);
      delete [] data;
      data = newdata;
    }
  else
    memcpy(data+length, from, fromLen + 1);

  length += fromLen;
  return *this;
}

// Append a character to the end of the CString.

CString& CString::operator+=(const char from)
{
  const size_t fromLen = sizeof(from);

  if (chunk < length + fromLen + 1)
    {
      chunk = chunkRound(length + fromLen + 1);
      char* newdata = new char[chunk];
      CAssert(newdata);
      memcpy(newdata, data, length);
      newdata[length] = from;
      newdata[length+1] = '\0';
      delete [] data;
      data = newdata;
    }
  else
    {
      data[length] = from;
      data[length+1] = '\0';
    }
  length += fromLen;

  return *this;
}

// Assignment from a CString.

CString& CString::operator=(const CString& from)
{
  if (this != &from)
    {
      if (from.length+1 > chunk)
        {
          delete [] data;
          chunk = from.chunk;
          data = new char[chunk];
          CAssert(data);
        }
      length = from.length;
      memcpy(data, from.data, length + 1);
    }
  return *this;
}

// Assignment from a '\0' char* string.

CString& CString::operator=(const char* from)
{
  delete [] data;
  length = strlen(from);
  chunk = chunkRound(length + 1);
  data = new char[chunk];
  CAssert(data);
  memcpy(data, from, length + 1);
  return *this;
}

// Assignment from a character.

CString& CString::operator=(const char from)
{
  delete [] data;
  length = sizeof(from);
  chunk = chunkRound(length + 1);
  data = new char[chunk];
  CAssert(data);
  data[0] = from;
  data[1] = '\0';
  return *this;
}

// Convert the CString to upper case.

void CString::makeUpper(void)
{
  size_t ind = length;

  while (ind--)
    data[ind] = (char)toupper(data[ind]);
}

// Convert the CString to lower case.

void CString::makeLower(void)
{
  size_t ind = length;

  while (ind--)
    data[ind] = (char)tolower(data[ind]);
}

void
CString::stripTrailing(char _ch)
{
  size_t l = length;
  while (l && data[l - 1] == _ch)
    l--;
  data[l] = '\0';
  length = l;
}

//
// IMPLEMENTATION (see CString.cpp as well)
//

// Round a string length up to the next highest chunk boundary


size_t CString::chunkRound(size_t from) const
{
  return ((from / chunk_size) + 1) * chunk_size;
}

// Destroy a CString


CString::~CString()
{
  delete [] data;
}

// Add two CString/s together and return the result.


CString CString::operator+(const CString& from) const
{
  CString temp = *this;
  temp += from;
  return temp;
}


// Return a char* representation to the data in the CString.
// CAVEAT: trashing the contents is not wise....


CString::operator char*() const
{
  return data;
}

//
//CString::operator size_t() const
//{
//  return length;
//}

// Return the length of the CString (NOT including
// the terminal '\0').


size_t CString::len() const
{
  return strlen(data);
}

// Compare two CString/s for equality etc.  Returns same
// values as strcmp.


int CString::operator==(const CString& other) const
{
  return strcmp(data, other.data) == 0;
}


int CString::operator!=(const CString& other) const
{
  return strcmp(data, other.data) != 0;
}


int CString::operator<=(const CString& other) const
{
  return strcmp(data, other.data) <= 0;
}


int CString::operator>=(const CString& other) const
{
  return strcmp(data, other.data) >= 0;
}


int CString::operator<(const CString& other) const
{
  return strcmp(data, other.data) < 0;
}


int CString::operator>(const CString& other) const
{
  return strcmp(data, other.data) > 0;
}


int CString::operator==(const char* other) const
{
  return strcmp(data, other) == 0;
}


int CString::operator!=(const char* other) const
{
  return strcmp(data, other) != 0;
}


int CString::operator<=(const char* other) const
{
  return strcmp(data, other) <= 0;
}


int CString::operator>=(const char* other) const
{
  return strcmp(data, other) >= 0;
}


int CString::operator<(const char* other) const
{
  return strcmp(data, other) < 0;
}


int CString::operator>(const char* other) const
{
  return strcmp(data, other) > 0;
}

// Return a reference to the character at the specified
// index in the CString.
// CAVEAT:  Trashing the referred character is not advised.
//          No bounds checking is performed.


const char& CString::operator[](size_t ind)
{
  return data[ind];
}

// strchr and strrchr facilities.


char* CString::index(const int ch)
{
  return strchr(data, ch);
}


char* CString::rindex(const int ch)
{
  return strrchr(data, ch);
}

