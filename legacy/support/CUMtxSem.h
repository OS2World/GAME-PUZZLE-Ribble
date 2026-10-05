// -------------------------------
//  Name:           CUMtxSem.h
//  Author:         J.R.Shannon
//  Language:       C++
//  Date:           7/11/92
//  Revison:        2.0
//  Last revision:  16/6/93
//  Licence:        Public Domain
//  Purpose:        Unnamed Mutex semaphore
// -------------------------------
//

#include <CSupport.h>
#include <CAssert.h>

#ifndef _CUMtxSem_h
#define _CUMtxSem_h

  #if defined(__OS2__)
    #define INCL_DOSSEMAPHORES
    #define INCL_NOPMAPI
    #include <os2.h>
    typedef APIRET CUMtxSemRet;
    typedef HMTX CUMtxSemHMTX;
    #define CUMtxSemWait SEM_INDEFINITE_WAIT
  #else
    typedef int CUMtxSemRet;
    typedef int CUMtxSemHMTX;
    typedef unsigned long ULONG;
    #define CUMtxSemWait 0
  #endif

class CSExport CUMtxSem
{
public:
  CUMtxSem(void);
  ~CUMtxSem();
  CUMtxSemRet request(ULONG timeout = CUMtxSemWait) const;
  void obtain(void) const;
  void release(void) const;

private:
  CUMtxSemHMTX  lock;
};

#endif

