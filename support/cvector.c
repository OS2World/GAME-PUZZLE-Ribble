#include "CVector.h"


template <class T>
inline CVector<T>::CVector(void)
{
  set = 0;
  chunk_size = DEF_CHUNK_SIZE;
}

template <class T>
inline CVector<T>::~CVector()
{
  if (set)
    delete [] data;
}

template <class T>
inline CVector<T>& CVector<T>::operator+=(const T from)
{
  operator[](upper + 1) = from;
  return *this;
}

template <class T>
inline CVector<T> CVector<T>::operator+(const CVector<T>& from) const
{
  CVector<T> temp = *this;
  temp += from;
  return temp;
}

template <class T>
inline int CVector<T>::operator!=(const CVector<T>& from) const
{
  return !operator==(from);
}

template <class T>
void CVector<T>::setRange(long from, long to, T value)
{
  // Fill from outer edge of vector to the
  // inner so that a maximum of one chunk allocation
  // is performed.

  if (to >= from)
    for (long ind = to; ind >= from; ind--)
      operator[](ind) = value;
  else
    for (long ind = from; ind >= to; ind--)
      operator[](ind) = value;
}

template <class T>
long CVector<T>::roundUp(long from) const
{
  return ((from / chunk_size) + 1) * chunk_size;
}

template <class T>
long CVector<T>::roundDown(long from) const
{
  return ((from / chunk_size) - 1) * chunk_size;
}

template <class T>
CVector<T>::CVector(const CVector<T>& from)
{
  chunk_size = DEF_CHUNK_SIZE;
  if ((set = from.set) != 0)
    {
      lower = from.lower;
      upper = from.upper;
      clb = from.clb;
      cub = from.cub;
      data = new CSHuge T[(unsigned long)(cub - clb + 1)];
      CAssert(data);
      unsigned long len = size();
      for (unsigned long ind = 0; ind < len; ind++)
        data[(unsigned long)(ind + lower - clb)] = from.data[(unsigned long)(ind + lower - clb)];
    }
}

template <class T>
CVector<T>::CVector(const T from)
{
  chunk_size = DEF_CHUNK_SIZE;
  set = 1;
  lower = upper = 0;
  clb = roundDown(lower);
  cub = roundUp(upper);
  data = new CSHuge T[(unsigned long)(cub - clb + 1)];
  CAssert(data);
  data[(unsigned long)(0 + lower - clb)] = from;
}

template <class T>
CVector<T>::CVector(const T CSHuge* from, unsigned long frlen)
{
  chunk_size = DEF_CHUNK_SIZE;
  set = 1;
  lower = 0;
  upper = frlen - 1;
  clb = roundDown(lower);
  cub = roundUp(upper);
  data = new CSHuge T[(unsigned long)(cub - clb + 1)];
  CAssert(data);
  for (unsigned long ind = 0; ind < frlen; ind++)
    data[(unsigned long)(ind + lower - clb)] = from[ind];
}

template <class T>
CVector<T>& CVector<T>::operator=(const CVector<T>& from)
{
  if (this != &from)
    {
      if (set)
        delete [] data;
      if ((set = from.set) != 0)
        {
          lower = from.lower;
          upper = from.upper;
          clb = from.clb;
          cub = from.cub;
          data = new CSHuge T[(unsigned long)(cub - clb + 1)];
          CAssert(data);
          unsigned long len = size();
          for (unsigned long ind = 0; ind < len; ind++)
            data[(unsigned long)(ind + lower - clb)] = from.data[(unsigned long)(ind + lower - clb)];
        }
    }
  return *this;
}

template <class T>
CVector<T>& CVector<T>::operator=(const T from)
{
  if (set)
    delete [] data;
  else
    set = 1;
  lower = upper = 0;
  clb = roundDown(lower);
  cub = roundUp(upper);
  data = new CSHuge T[(unsigned long)(cub - clb + 1)];
  CAssert(data);
  data[(unsigned long)(0 - clb)] = from;
  return *this;
}

template <class T>
CVector<T>& CVector<T>::operator+=(const CVector<T>& from)
{
  unsigned long len = from.size();
  for (unsigned long ind = 0; ind < len; ind++)
    operator[](upper + 1) = from.data[(unsigned long)(ind + from.lower - from.clb)];
  return *this;
}

template <class T>
int CVector<T>::operator==(const CVector<T>& from) const
{
  if (this == &from)
    return 1;
  
  if (size() != from.size())
    return 0;
  unsigned long len = size();
  for (unsigned long ind = 0; ind < len; ind++)
    if (data[(unsigned long)(ind + lower - clb)] != from.data[(unsigned long)(ind + from.lower - from.clb)])
      return 0;
  return 1;
}

template <class T>
T& CVector<T>::operator[](long index)
{
  if (!set)
    {
      set = 1;
      lower = upper = index;
      clb = roundDown(lower);
      cub = roundUp(upper);
      data = new CSHuge T[(unsigned long)(cub - clb + 1)];
      CAssert(data);
    }
  else if (index < clb)
    {
      long newclb = roundDown(index);
      long newlower = index;
      T CSHuge* newdata = new CSHuge T[(unsigned long)(cub - newclb + 1)];
      CAssert(newdata);
      for (unsigned long ind = 0; ind < upper - lower + 1; ind++)
        newdata[(unsigned long)(ind + lower - newclb)] = data[(unsigned long)(ind + lower - clb)];
      delete [] data;
      clb = newclb;
      lower = newlower;
      data = newdata;
    }
  else if (index > cub)
    {
      long newcub = roundUp(index);
      long newupper = index;
      T CSHuge* newdata = new CSHuge T[(unsigned long)(newcub - clb + 1)];
      CAssert(newdata);
      for (unsigned long ind = 0; ind < upper - lower + 1; ind++) //was newupper
        newdata[(unsigned long)(ind + lower - clb)] = data[(unsigned long)(ind + lower - clb)];
      delete [] data;
      cub = newcub;
      upper = newupper;
      data = newdata;
    }
  else if (index < lower)
    {
      lower = index;
    }
  else if (index > upper)
    {
      upper = index;
    }
  
  return data[(unsigned long)(index - clb)];
}


