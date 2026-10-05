#include <CSupport.h>

#ifndef _CThread_h
#define _CThread_h

class CSExport CThread
{
#if defined(__BORLANDC__) || defined(__WATCOMC__)
        friend void CThreadMain(PVOID arg);
#else
        friend void _Optlink CThreadMain(PVOID arg);
#endif

public:
        CThread(void);
        virtual ~CThread();
        void Run(void);
        TID QueryTID(void);
        virtual void ThreadProc(void) = 0;
        void Wait(void);
        void Kill(void);

private:
        CThread(const CThread&)             {}
        CThread& operator=(const CThread&)  { return *this; }
        int threadID;
        HAB hab;
        HMQ hmq;
};

#endif
