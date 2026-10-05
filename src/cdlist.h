// -------------------------------
//  $Source: C:\logical\store\classes/RCS/CDLIST.H,v $
//  $Revision: 1.10 $
//  $Date: 1994/02/18 11:35:43 $
//  $Author: jason $
//  J.R.Shannon (jrs@larch.demon.co.uk)
//  Language:       C++ (BC3.1, BC4.0, BCOS2 1.0, CSET++, WATCOM10.0)
//  Licence:        Public Domain
//  Purpose:        Doubly linked list & iterator classes
// -------------------------------

#ifndef _CDList_h
#define _CDList_h

// Forward declaration of list iterator

template <class T> class CDListIterator;
template <class T> class CDList;


template <class T>
class CDListNode
{
  friend class CDList<T>;
  friend class CDListIterator<T>;

public:
  CDListNode(const T& _item);
  CDListNode(void);

private:
  T               item;
  CDListNode<T>*  next;
  CDListNode<T>*  prev;
};


// -------------------------------------------------------------
// The CDList class.  Assumes meaningful copy characteristics
// for the item type to be stored, and a meaningful default
// constructor.
// -------------------------------------------------------------

template <class T>
class CDList
{
  friend class CDListIterator<T>;

private:
  CDListNode<T>  head;
  CDListNode<T>  tail;

public:
  CDList(void);
  CDList(const CDList<T>& _list);
  CDList<T>& operator=(const CDList<T>& _list);
  ~CDList();
  int isEmpty(void) const;
  operator int() const;
  T& getHead(void) const;
  T& getTail(void) const;
  void destroy(void);
  void addHead(const T item);
  void addTail(const T item);
  T remHead(void);
  T remTail(void);
  int detach(const T item);
  int count(void) const;
  CDList<T>& operator+=(const T item);
};

// -------------------------------------------------------------
// The CDListIterator class.  Allows sequential preusal
// of a CDList class's contents.
// -------------------------------------------------------------

template <class T>
class CDListIterator
{
public:
  CDListIterator(const CDList<T>& _list); 
  CDListIterator(const CDListIterator<T>& _it);
  CDListIterator<T>& operator=(const CDListIterator<T>& _it);
  T& current(void) const;                                 
  void rewind(void);                                      
  void fastforward(void);                                 
  operator int();                                         
  T& operator++(int);
  T& operator++();
  T& operator--(int);
  T& operator--();
  void insertAfter(const T item);
  void insertBefore(const T item);
  void remove(void);

private:
  const CDList<T>* list;
  CDListNode<T>*   cur;
};

#ifndef _CSET2
#include "CDList.c"
#endif


#endif

