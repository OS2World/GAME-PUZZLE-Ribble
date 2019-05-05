//  $Source: C:\logical\store\classes/RCS/CSTACK.H,v $
//  $Revision: 1.2 $
//  $Date: 1993/10/20 21:42:13 $
//  $Author: jason $

#include <CSupport.h>
#include <CSList.h>

#ifndef _CStack_h
#define _CStack_h


template <class T>
class CSExport CStack
{
public:
  CStack()            {  }
  ~CStack()           {  }
  CStack(const CStack<T>& _stk) : stack(_stk.stack) { }
  int isEmpty()       { return !stack; }
  operator int()      { return !isEmpty(); }
  T pop(void)         { return stack.remHead(); }
  void push(const T& item)  { stack.addHead(item); }

private:
  CSList<T> stack;
};

#endif

