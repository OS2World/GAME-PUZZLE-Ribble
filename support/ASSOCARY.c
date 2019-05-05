#include <AssocAry.h>


template <class T>
AssocAry<T>::AssocAry(void)
: stackIter(stack)
{
  bucket = new AssocEl*[AssocTableSize];

  for (int i = AssocTableSize; --i >= 0; )
    bucket[i] = 0;
}

template <class T>
AssocAry<T>::~AssocAry(void)
{
  delete [] bucket;

  while (stackIter)
    delete stackIter++;
}

template <class T>
void
AssocAry<T>::Destroy(void)
{
  for (int i = AssocTableSize; --i >= 0; )
    bucket[i] = 0;

  stackIter.rewind();

  while (stackIter)
    stackIter++->used = 0;

  stackIter.rewind();
}

template <class T>
void
AssocAry<T>::insert(const T _a, const T _b)
{
  unsigned int index = (unsigned int)_a % AssocTableSize;

  AssocEl* element = bucket[index];
  if (element == 0)
    {
      AssocEl* newElement = GetElement();
      newElement->a = _a;
      newElement->b = _b;
      newElement->next = 0;
      newElement->used = 1;
      bucket[index] = newElement;
    }
  else
    {
      while (element)
        {
          if (element->a == _a)
            {
              element->b = _b;
              break;
            }

          AssocEl* next = element->next;
          if (next == 0)
            {
              AssocEl* newElement = GetElement();
              newElement->a = _a;
              newElement->b = _b;
              newElement->next = 0;
              newElement->used = 1;
              element->next = newElement;
              break;
            }
          else
            element = next;
        }
    }
}

template <class T>
int
AssocAry<T>::findA(const T _b, T& _a) const 
{
  AssocElStackIter it(stack);

  while (it)
    {
      AssocEl* element = it++;
      if (element->used == 1 && element->b == _b)
        {
          _a = element->a;
          return 1;
        }
    }
  return 0;
}

template <class T>
int
AssocAry<T>::findB(const T _a, T& _b) const 
{
  unsigned int index = (unsigned int)_a % AssocTableSize;

  AssocEl* element = bucket[index];

  while (element)
    {
      if (element->a == _a)
        {
          _b = element->b;
          return 1;
        }
      element = element->next;
    }
  return 0;
}

template <class T>
int
AssocAry<T>::remove(const T _a)
{
  for (int i=0; i<AssocTableSize; i++)
    {
      AssocEl** prev = &bucket[i];
      AssocEl* element = *prev;
      while (element)
        {
          if (element->a == _a)
            {
              element->used = 0;
              *prev = element->next;
              return 1;
            }

          prev = &element->next;
          element = *prev;
        }
    }
  return 0;
}


template <class T, class U>
AssocAry2<T, U>::AssocAry2(void)
: stackIter(stack)
{
  bucket = new AssocEl*[AssocTableSize];

  for (int i = AssocTableSize; --i >= 0; )
    bucket[i] = 0;
}

template <class T, class U>
AssocAry2<T, U>::~AssocAry2(void)
{
  delete [] bucket;

  while (stackIter)
    delete stackIter++;
}

template <class T, class U>
void
AssocAry2<T, U>::Destroy(void)
{
  for (int i = AssocTableSize; --i >= 0; )
    bucket[i] = 0;

  stackIter.rewind();

  while (stackIter)
    stackIter++->used = 0;

  stackIter.rewind();
}

template <class T, class U>
void
AssocAry2<T, U>::insert(const T _a, const U _b)
{
  unsigned int index = (unsigned int)_a % AssocTableSize;

  AssocEl* element = bucket[index];
  if (element == 0)
    {
      AssocEl* newElement = GetElement();
      newElement->a = _a;
      newElement->b = _b;
      newElement->next = 0;
      newElement->used = 1;
      bucket[index] = newElement;
    }
  else
    {
      while (element)
        {
          if (element->a == _a)
            {
              element->b = _b;
              break;
            }

          AssocEl* next = element->next;
          if (next == 0)
            {
              AssocEl* newElement = GetElement();
              newElement->a = _a;
              newElement->b = _b;
              newElement->next = 0;
              newElement->used = 1;
              element->next = newElement;
              break;
            }
          else
            element = next;
        }
    }
}

template <class T, class U>
int
AssocAry2<T, U>::findA(const U _b, T& _a) const 
{
  AssocElStackIter it(stack);

  while (it)
    {
      AssocEl* element = it++;
      if (element->used == 1 && element->b == _b)
        {
          _a = element->a;
          return 1;
        }
    }
  return 0;
}

template <class T, class U>
int
AssocAry2<T, U>::findB(const T _a, U& _b) const 
{
  unsigned int index = (unsigned int)_a % AssocTableSize;

  AssocEl* element = bucket[index];

  while (element)
    {
      if (element->a == _a)
        {
          _b = element->b;
          return 1;
        }
      element = element->next;
    }
  return 0;
}

template <class T, class U>
int
AssocAry2<T, U>::remove(const T _a)
{
  for (int i=0; i<AssocTableSize; i++)
    {
      AssocEl** prev = &bucket[i];
      AssocEl* element = *prev;
      while (element)
        {
          if (element->a == _a)
            {
              element->used = 0;
              *prev = element->next;
              return 1;
            }

          prev = &element->next;
          element = *prev;
        }
    }
  return 0;
}

template <class T, class U>
int
AssocAry2<T, U>::remove(const U _b)
{
  for (int i=0; i<AssocTableSize; i++)
    {
      AssocEl** prev = &bucket[i];
      AssocEl* element = *prev;
      while (element)
        {
          if (element->b == _b)
            {
              element->used = 0;
              *prev = element->next;
              return 1;
            }

          prev = &element->next;
          element = *prev;
        }
    }
  return 0;
}
