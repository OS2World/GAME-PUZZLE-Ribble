// -------------------------------
//  $Source: C:\logical\store\classes/RCS/cvector.h,v $
//  $Revision: 1.10 $
//  $Date: 1993/11/09 17:45:41 $
//  $Author: jason $
//  Language:       C++
//  Licence:        Public Domain
//  Purpose:        Dynamically sized vectors
// -------------------------------

#ifndef _CVector_h
#define _CVector_h

#include "CAssert.h"

#ifndef C_NO_IOSTREAM
#include <iostream.h>
#endif

const int DEF_CHUNK_SIZE = 8;

template <class T>
class CVector
{
public:
  CVector();
  CVector(const CVector<T>&);
  CVector(const T);
  CVector(const T huge*, unsigned long);
  ~CVector();

  CVector<T>& operator=(const CVector<T>&);
  CVector<T>& operator=(const T);
  CVector<T>& operator+=(const CVector<T>&);
  CVector<T>& operator+=(const T);
  CVector<T>  operator+(const CVector<T>&) const;
  int operator==(const CVector<T>&) const;
  int operator!=(const CVector<T>&) const;
  T& operator[](long index);

  unsigned long size() const       { return set ? (unsigned long)(upper - lower + 1L) : 0; }
  unsigned long len() const        { return size(); }

  long   getLower(void) const { return set ? lower : 0; }
  long   getUpper(void) const { return set ? upper : 0; }

  void setRange(long from, long to, T value);

private:
  T huge*          data;   // array contents
  short            set;    // data in array?
  long             lower;  // effective lower bound
  long             upper;  // effective upper bound
  long             clb;    // real lower bound
  long             cub;    // real upper bound;
  long             chunk_size;

  long roundUp(long) const;
  long roundDown(long) const;
};

#ifndef _CSET2
#include "CVector.c"
#endif

#endif
