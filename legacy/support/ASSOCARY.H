// -------------------------------
//  Name:           AssocAry.h
//  Author:         J.R.Shannon
//  Language:       C++
//  Date:           6/11/92
//  Revison:        2.1
//  Last revision:  9/7/93
//  Licence:        Public Domain
//  Purpose:        Associative array
// -------------------------------

#include <CSupport.h>
#include <CDList.h>

#ifndef _AssocAry_h
#define _AssocAry_h

template <class T>
class CSExport AssocAry
{
  enum Constants
  {
    AssocTableSize = 1024
  };

public:

  struct AssocEl
  {
    T         a;
    T         b;
    AssocEl*  next;
    int      used;
  };

public:
  AssocAry(void);
  ~AssocAry();
  void Destroy(void);
  void insert(const T a, const T b);
  int findB(const T a, T& b) const;
  int findA(const T b, T& a) const;
  int remove(const T a);

private:
  AssocEl* GetElement(void)
  {
    if (!stackIter)
      {
        AssocEl* newElement = new AssocEl;
        stack.addTail(newElement);
        stackIter.fastforward();
      }
    return stackIter++;
  }


  typedef CDList<AssocEl*>         AssocElStack;
  typedef CDListIterator<AssocEl*> AssocElStackIter;

  AssocEl**         bucket;
  AssocElStack      stack;
  AssocElStackIter  stackIter;
};

template <class T, class U>
class CSExport AssocAry2
{
  enum Constants
  {
    AssocTableSize = 1024
  };

public:

  struct AssocEl
  {
    T         a;
    U         b;
    AssocEl*  next;
    int      used;
  };

public:
  AssocAry2(void);
  ~AssocAry2();
  void Destroy(void);
  void insert(const T a, const U b);
  int findB(const T a, U& b) const;
  int findA(const U b, T& a) const;
  int remove(const T a);
  int remove(const U b);

private:
  AssocEl* GetElement(void)
  {
    if (!stackIter)
      {
        AssocEl* newElement = new AssocEl;
        stack.addTail(newElement);
        stackIter.fastforward();
      }
    return stackIter++;
  }


  typedef CDList<AssocEl*>         AssocElStack;
  typedef CDListIterator<AssocEl*> AssocElStackIter;

  AssocEl**         bucket;
  AssocElStack      stack;
  AssocElStackIter  stackIter;
};


#ifndef _CSET2
#include <AssocAry.c>
#endif

#endif

