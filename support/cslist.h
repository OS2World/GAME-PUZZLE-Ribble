// -------------------------------
//  $Source: C:\logical\store\classes/RCS/CSLIST.H,v $
//  $Revision: 1.8 $
//  $Date: 1994/01/22 14:47:12 $
//  $Author: jason $
//  J.R.Shannon (jrs@larch.demon.co.uk)
//  Language:       C++ (BC3.1, BC4.0, BCOS2 1.0, CSET++, WATCOM10.0)
//  Licence:        Public Domain
//  Purpose:        Singly linked list & iterator classes
// -------------------------------

#ifndef _CSList_h
#define _CSList_h

// Forward declaration of list and iterator

template <class T> class CSList;
template <class T> class CSListIterator;

template <class T>
class CSListNode
{
public:
  CSListNode(const T& _item);

private:
  CSListNode<T>* next;
  T     item;
  friend class CSList<T>;
  friend class CSListIterator<T>;
};

// -------------------------------------------------------------
// The CSList class.  Assumes meaningful copy characteristics
// for the item type to be stored, and a meaningful default
// constructor.
// -------------------------------------------------------------

template <class T>
class CSList
{
  friend class CSListIterator<T>;

public:
  CSListNode<T>* tail;

public:
  CSList();
  CSList(const CSList<T>& from);
  ~CSList();
  CSList<T>& operator=(const CSList<T>& from);
  CSList<T>& operator+=(const T item);
  T& getHead(void) const;
  T& getTail(void) const;
  void addTail(const T item);
  void addHead(const T item);
  T remHead(void);
  int detach(const T item);
  void destroy(void);
  int isEmpty(void) const;
  operator int() const;
  int count(void) const;
};

// -------------------------------------------------------------
// The CSListIterator class.  Allows sequential perusal
// of a CSList class's contents.
// -------------------------------------------------------------

template <class T>
class CSListIterator
{
protected:
  CSListNode<T>*   cur;
  const CSList<T>* list;

public:
  CSListIterator(const CSList<T>& _list);
  CSListIterator(const CSListIterator<T>& _it);
  T& current(void) const;
  void rewind(void);
  operator int();
  T& operator++(int);
  T& operator++();
  CSListIterator<T>& operator=(const CSListIterator<T>& _it);
};

#ifndef _CSET2
#include <CSList.c>
#endif

#endif

