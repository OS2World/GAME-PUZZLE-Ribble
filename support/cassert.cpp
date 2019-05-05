// -------------------------------
//  $Source: C:\logical\store\classes/RCS/CASSERT.CPP,v $
//  $Revision: 1.8 $
//  $Date: 1993/12/04 23:24:52 $
//  $Author: jason $
//  Language:       C++
//  Licence:        Public Domain
//  Purpose:        assert() replacement which knows about PM apps.
// -------------------------------

//static const char RCSid[] = "$Id: CASSERT.CPP,v 1.8 1993/12/04 23:24:52 jason Exp jason $";

#if defined(__OS2__)

#define INCL_PM
#define INCL_DOS
#include <stdio.h>
#include <stdlib.h>
#include <os2.h>

#include <CAssert.h>

void CSExport
CAssertHandler(const char* cond, const char* file, const int line)
{
  // If the calling application runs in a PM window, then
  // create a message box to display the problem.

  PTIB ptib;
  PPIB ppib;

  DosGetInfoBlocks(&ptib, &ppib);

  if ((ppib->pib_ultype & 7) == FAPPTYP_WINDOWAPI)
    {
      char buffer[1024];    // Can't use a CString since that
                            // uses CAssert.  Sigh.

      sprintf(buffer,
              "Assertion '%s' failed in '%s' at line %d.\n",
              cond, file, line);

      // Make sure that there's an adequate environment for
      // the message box to run in.  If WinCreateMsgQueue
      // fails, then there's probably a queue created for
      // the calling thread already...

      HAB hab = WinInitialize(0);
      HMQ hmq = 0;

      if (hab)
        {
          hmq = WinCreateMsgQueue(hab, 0);

          //if (hmq == 0)
          //  {
          //    APIRET rc = WinGetLastError(hab);
          //    if (rc != PMERR_MSG_QUEUE_ALREADY_EXISTS)
          //      abort();
          // }
        }

      // Pop up a message box

      WinMessageBox(HWND_DESKTOP,
                    HWND_DESKTOP,
                    (PSZ)buffer,
                    (PSZ)"Fatal Error:",
                    0,
                    MB_ERROR | MB_OK);

      // Tidy up.

      if (hmq)
        WinDestroyMsgQueue(hmq);
      if (hab)
        WinTerminate(hab);
    }
  else
    {
      // Boring text error on command line.
      fprintf(stderr,
              "Assertion '%s' failed in '%s' at line %d.\n",
              cond, file, line);
    }
  abort();
}

#endif
