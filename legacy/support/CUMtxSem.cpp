#include <CUMtxSem.h>

CUMtxSem::CUMtxSem(void)
{
#if defined(__OS2__)
  CAssert(DosCreateMutexSem(0, &lock, 0, 0) == 0);
#else
#endif
}

CUMtxSem::~CUMtxSem()
{
#if defined(__OS2__)
  CAssert(DosCloseMutexSem(lock) == 0);
#else
#endif
}

CUMtxSemRet
CUMtxSem::request(ULONG timeout) const
{
#if defined(__OS2__)
  return DosRequestMutexSem(lock, timeout);
#else
  return 0;
#endif
}

void
CUMtxSem::obtain(void) const
{
  CAssert(request() == 0);
}

void
CUMtxSem::release(void) const
{
#if defined(__OS2__)
  CAssert(DosReleaseMutexSem(lock) == 0);
#else
#endif
}

