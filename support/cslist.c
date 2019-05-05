#include <CSList.h>

template <class T>
CSListNode<T>::CSListNode(const T& _item) 
: item(_item) 
{ 
}

template <class T>
CSList<T>::CSList(const CSList<T>& from)
{
  tail = 0;

  CSListIterator<T> it(from);

  while (it)
    addTail(it++);
}

template <class T>
CSList<T>::CSList()                                             
{ 
  tail = 0;  
}

template <class T>
CSList<T>::~CSList()                                    
{ 
  destroy();  
}

template <class T>
CSList<T>& 
CSList<T>::operator+=(const T item)
{
  addTail(item);
  return *this;
}

template <class T>
T& 
CSList<T>::getHead(void) const                       
{ 
  return tail->next->item;  
}

template <class T>
T& 
CSList<T>::getTail(void) const                       
{ 
  return tail->item;  
}

template <class T>
int 
CSList<T>::isEmpty(void) const                      
{ 
  return (tail == 0);  
}

template <class T>
CSList<T>::operator int() const                         
{ 
  return !isEmpty();  
}

template <class T>
CSList<T>& 
CSList<T>::operator=(const CSList<T>& from)
{
  if (this != &from)
    {
      destroy();
      tail = 0;

      CSListIterator<T> it(from);

      while (it)
        addTail(it++);
    }
  return *this;
}

template <class T>
void 
CSList<T>::destroy(void)
{
  CSListNode<T>* walk = tail;

  if (walk)
    {
      do
        {
          CSListNode<T>* n = walk->next;
          delete walk;
          walk = n;
        } while (walk != tail);
    }
  tail = 0;
}

template <class T>
void 
CSList<T>::addTail(const T item)
{
  CSListNode<T>* newNode = new CSListNode<T>(item);
  if (tail)
    {
      newNode->next = tail->next;
      tail = tail->next = newNode;
    }
  else
    tail = newNode->next = newNode;
}

template <class T>
void 
CSList<T>::addHead(const T item)
{
  CSListNode<T>* newNode = new CSListNode<T>(item);
  if (tail)
    {
      newNode->next = tail->next;
      tail->next = newNode;
    }
  else
    tail = newNode->next = newNode;
}

template <class T>
T 
CSList<T>::remHead(void)
{
  CSListNode<T>* n = tail->next;
  if (n == tail)
    tail = 0;
  else
    tail->next = n->next;

  T result = n->item;
  delete n;
  return result;
}

template <class T>
int 
CSList<T>::count(void) const
{
  int c = 0;
  if (tail)
    {
      CSListNode<T>* n = tail->next;
      do
        {
          c++;
          n = n->next;
        }
      while (n != tail->next);
    }
  return c;
}

template <class T>
CSListIterator<T>::CSListIterator(const CSList<T>& _list) 
: list(&_list)         
{ 
  cur = list->tail ? list->tail->next : 0; 
}

template <class T>
CSListIterator<T>::CSListIterator(const CSListIterator<T>& _it) 
: list(_it.list) 
{ 
  cur = _it.cur; 
}

template <class T>
T& 
CSListIterator<T>::current(void) const                                
{ 
  return cur->item;  
}

template <class T>
void 
CSListIterator<T>::rewind(void)                                     
{ 
  cur = list->tail ? list->tail->next : 0;  
}

template <class T>
CSListIterator<T>::operator int()                                        
{ 
  return cur != 0;  
}

template <class T>
T& 
CSListIterator<T>::operator++(int)
{
  CSListNode<T>* n = cur;
  if (cur == list->tail)
    cur = 0;
  else
    cur = cur->next;
  return n->item;
}

template <class T>
T& 
CSListIterator<T>::operator++()
{
  if (cur == list->tail)
    cur = 0;
  else
    cur = cur->next;
  return cur->item;
}

template <class T>
CSListIterator<T>& 
CSListIterator<T>::operator=(const CSListIterator<T>& _it)
{
  if (this != &_it)
    {
      list = _it.list;
      cur = _it.cur;
    }
  return *this;
}


