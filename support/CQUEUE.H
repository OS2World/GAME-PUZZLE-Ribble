//  $Source: C:\logical\store\classes/RCS/CQUEUE.H,v $
//  $Revision: 1.1 $
//  $Date: 1993/08/25 16:31:01 $
//  $Author: jason $

#include <CSupport.h>
#include <CSList.h>

#ifndef _CQueue_h
#define _CQueue_h

template <class T>
class CSExport CQueue
{
public:
  CQueue()            {  }
  ~CQueue()           {  }
  int isEmpty()       { return !queue; }
  operator int()      { return !isEmpty(); }
  T remove(void)      { return queue.remHead(); }
  void push(T& item)  { queue.addTail(item); }

private:
  CSList<T> queue;
};

#endif

