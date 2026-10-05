#define INCL_DOS
#define INCL_DOSSEMAPHORES
#include <os2.h>
#include <process.h>

#include <cthread.h>

CThread::CThread(void)
{
  hab = 0;
  hmq = 0;
  threadID = -1;
}

CThread::~CThread()
{
  if (hmq)
    {
      WinDestroyMsgQueue(hmq);
      hmq = 0;
    }

  if (hab)
    {
      WinTerminate(hab);
      hab = 0;
    }

  Kill();
}

void
CThread::Run(void)
{
  if (threadID == -1)
    {
#if defined(__BORLANDC__)
      threadID = _beginthread(CThreadMain, 64 * 1024, (PVOID)this);
#else
      threadID = _beginthread(CThreadMain, 0, 64 * 1024, (PVOID)this);
#endif
    }
}

TID
CThread::QueryTID(void)
{
  return (TID)threadID;
}

void
#if defined(__BORLANDC__) || defined(__WATCOMC__)
#else
_Optlink
#endif
CThreadMain(PVOID arg)
{
  CThread* obj = (CThread*)arg;

  obj->hab = WinInitialize(0);
  obj->hmq = WinCreateMsgQueue(obj->hab, 0);
  obj->ThreadProc();
}

void
CThread::Wait(void)
{
  if (threadID != -1)
    {
      DosWaitThread((PTID)&threadID, DCWW_WAIT);
    }
}

void
CThread::Kill(void)
{
  if (threadID != -1)
    {
      DosKillThread((TID)threadID);
      Wait();
      threadID = -1;
    }
}

