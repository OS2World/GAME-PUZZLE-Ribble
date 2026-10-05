// -------------------------------
//  $Source: C:\logical\store\classes/RCS/CASSERT.H,v $
//  $Revision: 1.6 $
//  $Date: 1993/11/27 21:36:00 $
//  $Author: jason $
//  Language:       C/C++
//  Licence:        Public Domain
//  Purpose:        assert() replacement which knows about PM apps.
// -------------------------------

#include <CSupport.h>

#ifndef _CAssert_h
#define _CAssert_h

  #ifdef __OS2__
     void CSExport CAssertHandler(const char* cond, const char* file, const int line);

    #define CAssert(condition)                                              \
             ((condition) ? (void)0                                         \
                          : CAssertHandler(#condition, __FILE__, __LINE__))

  #else
    #include <assert.h>
    #define CAssert(condition) assert(condition)
  #endif

#endif
