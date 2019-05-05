#include "CDList.h"

template <class T>
CDListNode<T>::CDListNode(const T& _item)
: item(_item) 
{
}

template <class T>
CDListNode<T>::CDListNode(void)
{
}

template <class T>
CDList<T>::CDList(void)
{
  head.prev = 0;
  head.next = &tail;
  tail.prev = &head;
  tail.next = 0;
}

template <class T>
CDList<T>::~CDList()                              
{ 
  destroy(); 
}

template <class T>
int 
CDList<T>::isEmpty(void) const                
{ 
  return head.next == &tail; 
}

template <class T>
CDList<T>::operator int() const                   
{ 
  return !isEmpty(); 
}

template <class T>
T& 
CDList<T>::getHead(void) const                 
{ 
  return head.next->item; 
}

template <class T>
T& 
CDList<T>::getTail(void) const                 
{ 
  return tail.prev->item; 
}

template <class T>
CDList<T>& CDList<T>::operator+=(const T item)
{
  addTail(item);
  return *this;
}


template <class T>
CDList<T>::CDList(const CDList<T>& _list)
{
  head.prev = 0;
  head.next = &tail;
  tail.prev = &head;
  tail.next = 0;

  CDListIterator<T> it(_list);
  while (it)
    addTail(it++);
}

template <class T>
CDList<T>& CDList<T>::operator=(const CDList<T>& _list)
{
  if (this != &_list)
    {
      destroy();
      CDListIterator<T> it(_list);
      while (it)
        addTail(it++);
    }
  return *this;
}

template <class T>
void CDList<T>::addHead(const T item)
{
  CDListNode<T>* newNode = new CDListNode<T>(item);
  newNode->next = head.next;
  newNode->prev = &head;
  head.next->prev = newNode;
  head.next = newNode;
}

template <class T>
void CDList<T>::addTail(const T item)
{
  CDListNode<T>* newNode = new CDListNode<T>(item);
  newNode->next = &tail;
  newNode->prev = tail.prev;
  tail.prev->next = newNode;
  tail.prev = newNode;
}

template <class T>
T CDList<T>::remHead(void)
{
  CDListNode<T>* n = head.next;
  head.next = n->next;
  n->next->prev = &head;
  T result = n->item;
  delete n;
  return result;
}

template <class T>
T CDList<T>::remTail(void)
{
  CDListNode<T>* n = tail.prev;
  tail.prev = n->prev;
  n->prev->next = &tail;
  T result = n->item;
  delete n;
  return result;
}

template <class T>
void CDList<T>::destroy(void)
{
  CDListNode<T>* n = head.next;
  while (n != &tail)
    {
      CDListNode<T>* w = n->next;
      delete n;
      n = w;
    }
  head.next = &tail;
  tail.prev = &head;
}

template <class T>
int CDList<T>::count(void) const
{
  int c = 0;
  CDListNode<T>* n = head.next;
  while (n != &tail)
    {
      c++;
      n = n->next;
    }
  return c;
}

template <class T>
CDListIterator<T>::CDListIterator(const CDList<T>& _list) 
: list(&_list)          
{ 
  cur = list->head.next; 
}

template <class T>
CDListIterator<T>::CDListIterator(const CDListIterator<T>& _it) 
: list(_it.list)  
{ 
  cur = _it.cur; 
}

template <class T>
CDListIterator<T>& 
CDListIterator<T>::operator=(const CDListIterator<T>& _it)
{
  if (this != &_it)
    {
      list = _it.list;
      cur = _it.cur;
    }
  return *this;
}

template <class T>
T& 
CDListIterator<T>::current(void) const                                 
{ 
  return cur->item; 
}

template <class T>
void 
CDListIterator<T>::rewind(void)                                      
{ 
  cur = list->head.next; 
}

template <class T>
void 
CDListIterator<T>::fastforward(void)                                 
{ 
  cur = list->tail.prev; 
}

template <class T>
CDListIterator<T>::operator int()                                         
{ 
  return cur != &list->tail && cur != &list->head; 
}

template <class T>
T& 
CDListIterator<T>::operator++(int)
{
  CDListNode<T>* n = cur;
  cur = cur->next;
  return n->item;
}

template <class T>
T& 
CDListIterator<T>::operator++()
{
  cur = cur->next;
  return cur->item;
}

template <class T>
T& 
CDListIterator<T>::operator--(int)
{
  CDListNode<T>* n = cur;
  cur = cur->prev;
  return n->item;
}

template <class T>
T& 
CDListIterator<T>::operator--()
{
  cur = cur->prev;
  return cur->item;
}

template <class T>
void 
CDListIterator<T>::insertAfter(const T item)
{
  CDListNode<T>* newNode = new CDListNode<T>(item);
  newNode->next = cur->next;
  newNode->prev = cur;
  cur->next->prev = newNode;
  cur->next = newNode;
  cur = newNode;
}

template <class T>
void 
CDListIterator<T>::insertBefore(const T item)
{
  CDListNode<T>* newNode = new CDListNode<T>(item);
  newNode->next = cur;
  newNode->prev = cur->prev;
  cur->prev->next = newNode;
  cur->prev = newNode;
  cur = newNode;
}

template <class T>
void 
CDListIterator<T>::remove(void)
{
  cur->next->prev = cur->prev;
  cur->prev->next = cur->next;

  CDListNode<T>* next = cur->next;
  delete cur;
  cur = next;
}


