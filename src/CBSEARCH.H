// -------------------------------
//  $Source: C:\logical\store\classes/RCS/CBSEARCH.H,v $
//  $Revision: 1.4 $
//  $Date: 1994/02/15 11:14:41 $
//  $Author: jason $
//  Language:       C++
//  Licence:        Public Domain
//  Purpose:        Binary searches
// -------------------------------

#include <CSupport.h>

#ifndef _CBSearch_h
#define _CBSearch_h

template <class T> 
long CSExport
CBSearch(T huge* _elems, long _lower, long _upper, T _target)
{
  while (_upper >= _lower)
    {
      long middle = (_upper + _lower) >> 1;

      if (_elems[middle] == _target)
        return 1;
      else
        if (_elems[middle] < _target)
          _lower = middle + 1;
        else
          _upper = middle - 1;
    }
  return 0;
}

template <class T> 
long CSExport
CBSearchP(T huge* huge* _elems, long _lower, long _upper, T* _target)
{
  while (_upper >= _lower)
    {
      long middle = (_upper + _lower) >> 1;

      if (*_elems[middle] == *_target)
        return 1;
      else
        if (*_elems[middle] < *_target)
          _lower = middle + 1;
        else
          _upper = middle - 1;
    }
  return 0;
}

template <class T> 
T huge* huge* CSExport
CBSearchPp(T huge* huge* _elems, long _lower, long _upper, T* _target)
{
  while (_upper >= _lower)
    {
      long middle = (_upper + _lower) >> 1;

      if (*_elems[middle] == *_target)
        return &_elems[middle];
      else
        if (*_elems[middle] < *_target)
          _lower = middle + 1;
        else
          _upper = middle - 1;
    }
  return 0;
}

template <class T> 
long CSExport
CBSearchP2(T huge* huge* _elems, long _lower, long _upper, T _target)
{
  while (_upper >= _lower)
    {
      long middle = (_upper + _lower) >> 1;

      if (*_elems[middle] == _target)
        return 1;
      else
        if (*_elems[middle] < _target)
          _lower = middle + 1;
        else
          _upper = middle - 1;
    }
  return 0;
}

template <class T> 
long CSExport
CBSearch(CVector<T>& _elems, long _lower, long _upper, T& _target)
{
  while (_upper >= _lower)
    {
      long middle = (_upper + _lower) >> 1;

      if (_elems[middle] == _target)
        return 1;
      else
        if (_elems[middle] < _target)
          _lower = middle + 1;
        else
          _upper = middle - 1;
    }
  return 0;
}

template <class T> 
long CSExport
CBSearchP(CVector<T*>& _elems, long _lower, long _upper, T* _target)
{
  while (_upper >= _lower)
    {
      long middle = (_upper + _lower) >> 1;

      if (*_elems[middle] == *_target)
        return 1;
      else
        if (*_elems[middle] < *_target)
          _lower = middle + 1;
        else
          _upper = middle - 1;
    }
  return 0;
}

template <class T> 
long CSExport
CBSearchP2(CVector<T*>& _elems, long _lower, long _upper, T& _target)
{
  while (_upper >= _lower)
    {
      long middle = (_upper + _lower) >> 1;

      if (*_elems[middle] == _target)
        return 1;
      else
        if (*_elems[middle] < _target)
          _lower = middle + 1;
        else
          _upper = middle - 1;
    }
  return 0;
}

#endif
