#define INCL_WIN
#define INCL_DOS
#include <os2.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <direct.h>
#include <io.h>
#include <sys/stat.h>
#include <errno.h>
#include <dos.h>

#include <cwindow.h>
#include <cdialog.h>
#include <cthread.h>
#include "Install.h"
#include <MakePath.h>

const int MaxStringLen = 256;
const ULONG WM_InstallThreadComplete = WM_USER;
const char* RibbleObjectClass  = "WPProgram";
const char* RibbleObjectTitle  = "<WP_RibbleObject>";
const char* RibbleWPStitle     = "Ribble";
const char* RibbleLocation     = "<WP_DESKTOP>";
char pszSrcDirectory[512];

// ---------------------------------------------------------

class InstallThread : public CThread
{
public:
  InstallThread(HWND _notify);
  void ThreadProc(void);
  int CopyFile(HWND hwnd, ULONG id, CString file, char* extraPath = 0);
  int CreateObject(void);
  void RemoveObject(void);
  void SetEA(char* src, char* dst);
  void StatusLine(char* text, BOOL _noScroll = FALSE);

private:
  HWND notify;
};


class InstallDialog : public CDialog
{
public:
  InstallDialog(void);
  ~InstallDialog();
  void SetupWindow(void);
  MRESULT ProcessMsg(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
  void DoInstall(void);
  void EnableControls(BOOL enable = TRUE);
  void StopThread(void);

private:
  InstallThread* instThread;
  HSWITCH        switchEntry;
};


InstallThread::InstallThread(HWND _notify)
{
  notify = _notify;
}

int
InstallThread::CopyFile(HWND hwnd, ULONG id, CString file, char* extraPath)
{
  int res = 0;

  char buffer[MaxStringLen];
  WinQueryDlgItemText(hwnd, id, MaxStringLen, (PSZ)buffer);

  int l = strlen(buffer) - 1;
  while (l > 0 && buffer[l] == '\\' || buffer[l] == '/')
    buffer[l--] = '\0';

  if (extraPath)
    strcat(buffer, extraPath);

  int made = makePath(buffer);

  if (made)
    {
      CString message;

      if (made == 2)
        {
          message  = "Created directory ";
	  message += buffer;
	  message += "...";
          StatusLine(message);
	}

      CString path  = buffer;
      path += '\\';
      path += file;

      message  = "Copying ";
      message += file;
      message += " to ";
      message += path;
      message += "...";

      StatusLine(message);

      CString dist = "dist\\";
      dist += file;

      CString eadist = "dist\\ea";
      eadist += file;

  //printf("source: %s\n", (char*)dist);

      int source = open(dist, O_RDONLY | O_BINARY);
      if (source != -1)
	{
//printf("dest: %s\n", (char*)path);

	  int dest = open(path, O_WRONLY | O_BINARY | O_CREAT, S_IREAD | S_IWRITE);
	  if (dest != -1)
	    {
	      struct stat size;
	      if (fstat(source, &size) != -1)
		{
		  char* data = new char[size.st_size];
		  if (data)
		    {
		      int r = read(source, data, size.st_size);
		      if (r == size.st_size)
			{
			  int w = write(dest, data, r);
			  if (w == r)
                            {
			      res = 1;
                            }
			}
		      delete data;
		    }
		}
	      close(dest);
	    }
	  else
	    {
	      CString message = "ERROR: Failed to open target file.";
              StatusLine(message);
	    }
	  close(source);
	}
      else
	{
	  CString message = "ERROR: Failed to open source file.";
          StatusLine(message);
	}

      if (res == 1)
        if (access(eadist, 0) == 0)
          {
            SetEA(eadist, path);
          }

    }
  else
    {
      CString message = "ERROR: Directory creation failed.";
      StatusLine(message);
    }
  return res;
}

void
InstallThread::RemoveObject(void)
{
  CString message = "Searching for Ribble objects...";
  StatusLine(message);

  // Remove any old Ribble object instances

  HOBJECT existing;

  do
    {
      existing = WinQueryObject((PSZ)(char*)RibbleObjectTitle);
      if (existing)
	{
	  message = "Removing an old Ribble object...";
          StatusLine(message);
	  WinDestroyObject(existing);
	}
    }
  while (existing);
}

int
InstallThread::CreateObject(void)
{
  char buffer[MaxStringLen];
  WinQueryDlgItemText(notify, DID_ExePath, MaxStringLen, (PSZ)buffer);

  int l = strlen(buffer) - 1;
  while (l > 0 && buffer[l] == '\\' || buffer[l] == '/')
    buffer[l--] = '\0';

  CString RibbleSetupString = "NOPRINT=YES;MINWIN=DESKTOP;PROGTYPE=PM;OBJECTID=";
  RibbleSetupString += RibbleObjectTitle;
  RibbleSetupString += ";STARTUPDIR=";
  RibbleSetupString += buffer;
  RibbleSetupString += ";EXENAME=";
  strcat(buffer, "\\Ribble.exe");
  RibbleSetupString += buffer;

  CString message = "Creating a Ribble object on the desktop...";
  StatusLine(message);

  HOBJECT obj = WinCreateObject((PSZ)RibbleObjectClass,
                                (PSZ)RibbleWPStitle,
                                (PSZ)(char*)RibbleSetupString,
                                (PSZ)RibbleLocation,
                                CO_REPLACEIFEXISTS);
  if (obj)
    return 1;

  return 0;
}

void
InstallThread::ThreadProc(void)
{
  WinSendDlgItemMsg(notify, DID_ProgressText, LM_DELETEALL, MPVOID, MPVOID);

  BOOL failed = TRUE;

  RemoveObject();

  int a = CopyFile(notify, DID_ExePath, "Ribble.exe");
  int b = CopyFile(notify, DID_HlpPath, "Ribble.hlp");
  int c = CopyFile(notify, DID_ExePath, "level.1", "\\levels");
  if (c) c = CopyFile(notify, DID_ExePath, "level.2", "\\levels");
  if (c) c = CopyFile(notify, DID_ExePath, "level.3", "\\levels");
  if (c) c = CopyFile(notify, DID_ExePath, "level.4", "\\levels");
  if (c) c = CopyFile(notify, DID_ExePath, "level.5", "\\levels");
  if (c) c = CopyFile(notify, DID_ExePath, "level.6", "\\levels");
  if (c) c = CopyFile(notify, DID_ExePath, "level.7", "\\levels");
  if (c) c = CopyFile(notify, DID_ExePath, "level.8", "\\levels");
  if (c) c = CopyFile(notify, DID_ExePath, "level.9", "\\levels");
  if (c) c = CopyFile(notify, DID_ExePath, "level.10", "\\levels");

  if (a && b && c)
    {
      failed = FALSE;

      USHORT createObj = (USHORT)(ULONG)WinSendDlgItemMsg(notify, DID_CreateObject, BM_QUERYCHECK, MPVOID, MPVOID);

      if (createObj)
        {
          if (CreateObject() == 0)
            failed = TRUE;
        }
    }

  if (failed == FALSE)
    {
      CString message = "All done!";
      StatusLine(message);

      char buffer[MaxStringLen];
      WinQueryDlgItemText(notify, DID_ExePath, MaxStringLen, (PSZ)buffer);

      // Set the Exe path in OS2.INI

      int l = strlen(buffer) - 1;
      while (l > 0 && buffer[l] == '\\' || buffer[l] == '/')
	buffer[l--] = '\0';

      CString buffer2 = buffer;
      buffer2 += "\\Ribble.exe";

      PrfWriteProfileString(HINI_PROFILE,
			    (PSZ)"Ribble/2",
			    (PSZ)"Executable_Path",
			    (PSZ)(char*)buffer2);

      message  = "Ribble has been successfully installed.\n\n"
	"If you intend to run Ribble from the command-line,\n"
	  "then you should ensure that the PATH variable in\n"
	    "your CONFIG.SYS file contains the following path:\n\n\"";
      message += buffer;
      message += "\"\n\nFor example:\n";
      message += "SET PATH=C:\\;C:\\OS2;";
      message += buffer;
      message += ";\n\n";
      message += "Next, ensure that your HELP variable contains the following\npath:\n\n\"";

      WinQueryDlgItemText(notify, DID_HlpPath, MaxStringLen, (PSZ)buffer);

      message += buffer;
      message += "\"\n\nFor example:\n";
      message += "SET HELP=C:\\OS2\\HELP;";
      message += buffer;
      message += ";\n\nFinally, if you have made changes to your CONFIG.SYS\n"
	"file, then you should reboot your system so that the\n"
	  "changes can take effect.";

      char linebuffer[1024];
      char* a = linebuffer;
      char* b = message;

      WinSendDlgItemMsg(notify, DID_ProgressText, LM_DELETEALL, MPVOID, MPVOID);

      do
	{
	  if (*b == '\0' || *b == '\n')
	    {
	      *a = 0;
              StatusLine(linebuffer, TRUE);
	      a = linebuffer;
	      b++;
	    }
	  else
	    *a++ = *b++;
	}
      while (b[-1]);
    }
  else
    {
      WinMessageBox(HWND_DESKTOP,
		    notify,
		    (PSZ)"An error occured during installation.\n\n"
		    "The reason for the failure should be displayed "
		    "in the last few items of the progress window.",
		    (PSZ)"Ribble installation error",
		    0,
		    MB_OK | MB_ERROR);

    }

  WinEnableWindow(WinWindowFromID(notify, DID_Dismiss), TRUE);
  WinPostMsg(notify, WM_InstallThreadComplete, MPVOID, MPVOID);
}

// ---------------------------------------------------------

InstallDialog::InstallDialog(void)
: CDialog(HWND_DESKTOP, DLG_Install, FALSE)
{
  instThread = 0;
  switchEntry = 0;
}

InstallDialog::~InstallDialog()
{
  StopThread();

  if (switchEntry)
    WinRemoveSwitchEntry(switchEntry);
}

void
InstallDialog::StopThread(void)
{
  if (instThread)
    {
      delete instThread;
      instThread = 0;
    }
}

void
InstallDialog::EnableControls(BOOL enable)
{
  if (enable == TRUE)
    {
      WinShowWindow(WinWindowFromID(HWindow, DID_ProgressBox), !enable);
      WinShowWindow(WinWindowFromID(HWindow, DID_ProgressText), !enable);
      WinShowWindow(WinWindowFromID(HWindow, DID_Dismiss), !enable);
    }
  WinEnableWindow(WinWindowFromID(HWindow, DID_Dismiss), FALSE);
  WinEnableWindow(WinWindowFromID(HWindow, DID_OK), enable);
  WinEnableWindow(WinWindowFromID(HWindow, DID_CANCEL), enable);
  WinEnableWindow(WinWindowFromID(HWindow, DID_Defaults), enable);
  WinShowWindow(WinWindowFromID(HWindow, DID_ExePath), enable);
  WinShowWindow(WinWindowFromID(HWindow, DID_HlpPath), enable);
  WinShowWindow(WinWindowFromID(HWindow, DID_ExeTitle), enable);
  WinShowWindow(WinWindowFromID(HWindow, DID_HlpTitle), enable);
  WinShowWindow(WinWindowFromID(HWindow, DID_ExeName), enable);
  WinShowWindow(WinWindowFromID(HWindow, DID_HlpName), enable);
  WinShowWindow(WinWindowFromID(HWindow, DID_CreateObject), enable);
  WinShowWindow(WinWindowFromID(HWindow, DID_InstallPaths), enable);
  WinShowWindow(WinWindowFromID(HWindow, DID_InstallOptions), enable);
  WinShowWindow(WinWindowFromID(HWindow, DID_OK), enable);
  WinShowWindow(WinWindowFromID(HWindow, DID_CANCEL), enable);
  WinShowWindow(WinWindowFromID(HWindow, DID_Defaults), enable);
  if (enable == FALSE)
    {
      WinShowWindow(WinWindowFromID(HWindow, DID_ProgressBox), !enable);
      WinShowWindow(WinWindowFromID(HWindow, DID_ProgressText), !enable);
      WinShowWindow(WinWindowFromID(HWindow, DID_Dismiss), !enable);
    }
}

void
InstallDialog::DoInstall(void)
{
  EnableControls(FALSE);

  instThread = new InstallThread(HWindow);
  instThread->Run();
}

void
InstallDialog::SetupWindow(void)
{
  /* Provide an icon for the application (load it from the resource section) */
  {
    HPOINTER appIcon = WinLoadPointer(HWND_DESKTOP, 0, 1);  /* ICON ID = 1 */

    if (appIcon)
      WinSendMsg(HWindow,
		 WM_SETICON,
		 MPFROMP(appIcon),
		 MPVOID);
  }

  /* Add application to the Switch List */

  {
    SWCNTRL sw;

    sw.hwnd = HWindow;
    sw.hwndIcon = 0;
    sw.hprog = 0;
    sw.idProcess = 0;
    sw.idSession = 0;
    sw.uchVisibility = SWL_VISIBLE;
    sw.fbJump = SWL_JUMPABLE;
    strcpy(sw.szSwtitle, "Ribble installation");
    sw.bProgType = PROG_PM;
    switchEntry = WinAddSwitchEntry(&sw);
  }

  EnableControls(TRUE);

  WinSendDlgItemMsg(HWindow, DID_ExePath, EM_SETTEXTLIMIT, MPFROMLONG(MaxStringLen), MPVOID);
  WinSendDlgItemMsg(HWindow, DID_HlpPath, EM_SETTEXTLIMIT, MPFROMLONG(MaxStringLen), MPVOID);

  ULONG drive;

  APIRET rc = DosQuerySysInfo(QSV_BOOT_DRIVE,
			      QSV_BOOT_DRIVE,
			      (PVOID)&drive,
			      sizeof(drive));

  CString InstPath  = "X:\\RIBBLE";
  *(char*)InstPath = (rc == 0) ? 'A' + drive - 1
    : 'C';

  WinSetDlgItemText(HWindow, DID_ExePath, (PSZ)(char*)InstPath);
  WinSetDlgItemText(HWindow, DID_HlpPath, (PSZ)(char*)InstPath);

  WinCheckButton(HWindow, DID_CreateObject, TRUE);
}

MRESULT
InstallDialog::ProcessMsg(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  switch (msg)
    {
    case WM_CLOSE:
      {
	if (instThread)
	  return 0;
	break;
      }
    case WM_COMMAND:
      {
	CMDMSG* cmdmsg = (PCMDMSG)MsgSpec;
	switch (cmdmsg->cmd)
	  {
	  case DID_CANCEL:
	    WinSendMsg(hwnd, WM_CLOSE, MPVOID, MPVOID);
	    break;
	  case DID_OK:
	    DoInstall();
	    break;
	  case DID_Defaults:
	    SetupWindow();
	    break;
	  case DID_Dismiss:
	    WinSendMsg(hwnd, WM_CLOSE, MPVOID, MPVOID);
	    break;
	  }
	return 0;
      }
    case WM_InstallThreadComplete:
      {
	StopThread();
	return 0;
      }
    }
  return WinDefDlgProc(hwnd, msg, mp1, mp2);
}

// ---------------------------------------------------------

int
main(int argc, unsigned char* argv[])
{
  HMODULE hmod;
  char szSavDir[512];
  DosQueryModuleHandle((PSZ)argv[0], &hmod);
  DosQueryModuleName(hmod, sizeof(pszSrcDirectory), pszSrcDirectory);

  int iSavDisk = _getdrive();
  if (getcwd(szSavDir, 512) == 0)
    return 0;

  //printf("cd: %s\n", szSavDir);
  //printf("sd: %s\n", pszSrcDirectory);

#if defined(__WATCOMC__)
  unsigned total;
  _dos_setdrive(pszSrcDirectory[0] - 'A' + 1, &total);
#else
  _chdrive(pszSrcDirectory[0] - 'A' + 1);
#endif

  // lose install.exe from the end
  pszSrcDirectory[strrchr(pszSrcDirectory, '\\') - pszSrcDirectory] = 0;

  CApplication app;
  InstallDialog dialog;
  dialog.Create();

#if defined(__WATCOMC__)
  _dos_setdrive(iSavDisk, &total);
#else
  _chdrive(iSavDisk);
#endif
  chdir(szSavDir);

  argc;

  return 0;
}

void
InstallThread::SetEA(char* src, char* dst)
{
  StatusLine("Setting Extended Attributes for RIBBLE.EXE");

  STARTDATA   StartData;
  ULONG       session;
  PID         cPID;
  UCHAR       ObjBuf[100];
  HFILE       queue;
  const char* queueName = "\\QUEUES\\RIBBLE.QUE";

  APIRET rc = DosCreateQueue(&queue, QUE_FIFO, (PSZ)queueName);

  if (rc == 0)
    {
      const char* TITLE = "Ribble EAUTIL session";
      const char* PROGRAM = "EAUTIL.EXE";
      CString args = dst;
      args += ' ';
      args += src;
      args += " /O /J /P";

      StartData.Length        = sizeof(STARTDATA);
      StartData.Related       = SSF_RELATED_CHILD; /* I get notified of the session\'s demise & can kill it */
      StartData.FgBg          = SSF_FGBG_BACK;     /* Runs in background (not of much importance) */
      StartData.TraceOpt      = SSF_TRACEOPT_NONE; /* No debugging traces or anything */
      StartData.PgmTitle      = (PSZ)TITLE;        /* Title for session window (hidden, but in WPS windowlist) */
      StartData.PgmName       = (PSZ)PROGRAM;      /* Program to execute */
      StartData.PgmInputs     = (PSZ)(char*)args;  /* Arguments for program */
      StartData.TermQ         = (PSZ)queueName;    /* Queue on which death is notified */
      StartData.Environment   = 0;                 /* No special environment vars */
      StartData.InheritOpt    = SSF_INHERTOPT_PARENT; /* Inherit file handles from me */
      StartData.SessionType   = SSF_TYPE_DEFAULT;     /* Work out session type (Windowed AVIO in this case) */
      StartData.IconFile      = 0;
      StartData.PgmHandle     = 0;
      StartData.PgmControl    = SSF_CONTROL_INVISIBLE; /* Don\'t want window cluttering up desktop, so hide it */
      StartData.InitXPos      = 0;                 /* no initial positioning */
      StartData.InitYPos      = 0;
      StartData.InitXSize     = 0;
      StartData.InitYSize     = 0;
      StartData.Reserved      = 0;
      StartData.ObjectBuffer  = (PSZ)ObjBuf; /* errors in starting are plonked here (for wot it\'s worth) */
      StartData.ObjectBuffLen = 100;

      APIRET rc = DosStartSession(&StartData, &session, &cPID);

      if (rc == 0)
        {
          REQUESTDATA req;
          ULONG dataLen = sizeof(SHORT) * 2;
          PVOID data;
          BYTE pri;

          rc = DosReadQueue(queue,
                            &req,
                            &dataLen,
                            &data,
                            0,
                            DCWW_WAIT,
                            &pri,
                            0);
          if (rc == 0)
            {
              DosFreeMem(data);

              StatusLine("Extended Attributes set okay");
            }
        }

      DosCloseQueue(queue);
    }
}

void
InstallThread::StatusLine(char* text, BOOL _noScroll)
{
  SHORT item = (SHORT)
    WinInsertLboxItem(WinWindowFromID(notify, DID_ProgressText),
		      LIT_END,
		      (PSZ)text);
  if (_noScroll == FALSE)
    WinSendDlgItemMsg(notify,
                      DID_ProgressText,
                      LM_SETTOPINDEX,
                      MPFROMSHORT(item),
                      MPVOID);
}
