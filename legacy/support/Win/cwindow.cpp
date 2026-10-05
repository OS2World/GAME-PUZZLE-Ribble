#define INCL_WIN
#include <os2.h>

#include "win\cwindow.h"

// **********************************************

CApplication::CApplication(void)
{
  hab = WinInitialize(0);
  if (hab)
    hmq = WinCreateMsgQueue(hab, 0);
  else
    hmq = 0;

  if (hab == 0 || hmq == 0)
    exit(EXIT_FAILURE);
}

CApplication::~CApplication()
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
}

void
CApplication::Run(void)
{
 QMSG qmsg;

 while (WinGetMsg(hab, &qmsg, 0, 0, 0))
   WinDispatchMsg(hab, &qmsg);
}

// **********************************************

void
CWinFrame::Create(void)
{
  FRAMECDATA fcdata;
  fcdata.cb            = sizeof(fcdata);
  fcdata.flCreateFlags = flags;
  fcdata.hmodResources = 0;
  fcdata.idResources   = 0;

  hwnd = WinCreateWindow(parent,
                         WC_FRAME,
                         0,
                         visible == TRUE ? WS_VISIBLE : 0,
                         x, y, w, h,
                         owner,
                         HWND_TOP,
                         fid,
                         &fcdata,
                         0);
}

// **********************************************

void
CWinClient::Create(void)
{
  if (hab == 0)
    hab = WinQueryAnchorBlock(owner);

  if (hab)
    {
      BOOL success = WinRegisterClass(hab,
                                      (PSZ)(char*)className,
                                      (PFNWP)CWinClientWindowProc,
                                      clStyle,
                                      sizeof(CWinClient*));

      if (success == FALSE)
        exit(EXIT_FAILURE);
    }



  HWindow = WinCreateWindow(parent,
                            (PSZ)(char*)className,
                            (PSZ)"",
                            wnStyle,
                            x, y, w, h,
                            owner,
                            HWND_TOP,
                            winID,
                            (PVOID)this,
                            0);
  if (HWindow == 0)
    exit(EXIT_FAILURE);
}

MRESULT EXPENTRY
CWinClientWindowProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  CWinClient* object = 0;

  if (msg == WM_CREATE)
    {
      object = (CWinClient*)mp1;
      WinSetWindowPtr(hwnd, QWL_USER, (PVOID)object);
      object->HWindow = hwnd;
      object->SetupWindow();
    }
  else
    object = (CWinClient*)WinQueryWindowPtr(hwnd, QWL_USER);

  object->MsgSpec = (PVOID)((PBYTE)&msg + sizeof(MPARAM));

  return object->ProcessMsg(hwnd, msg, mp1, mp2);
}


CWinFrame::CWinFrame(HWND  _parent,
                     HWND  _owner,
                     HAB   _hab,
                     ULONG _flags,
                     BOOL  _visible,
                     ULONG _fid,
                     LONG  _x,
                     LONG  _y,
                     LONG  _w,
                     LONG  _h)
: parent(_parent),
  owner(_owner),
  hab(_hab),
  flags(_flags),
  visible(_visible),
  fid(_fid),
  x(_x),
  y(_y),
  w(_w),
  h(_h),
  hwnd(0)
{
  Create();
}


CWinFrame::~CWinFrame()
{
  Destroy();
}


void
CWinFrame::Destroy(void)
{
  if (hwnd)
    {
      WinDestroyWindow(hwnd);
      hwnd = 0;
    }
}


void
CWinFrame::title(const char* _title)
{
  WinSetWindowText(hwnd, (PSZ)_title);
}


void
CWinFrame::move(LONG _x, LONG _y)
{
  WinSetWindowPos(hwnd, 0, _x, _y, 0, 0, SWP_MOVE);
}


void
CWinFrame::move(LONG _x, LONG _y, LONG _w, LONG _h)
{
  WinSetWindowPos(hwnd, 0, _x, _y, _w, _h, SWP_MOVE | SWP_SIZE);
}


void
CWinFrame::size(LONG _w, LONG _h)
{
  WinSetWindowPos(hwnd, 0, 0, 0, _w, _h, SWP_SIZE);
}


void
CWinFrame::show(BOOL _visible)
{
  WinShowWindow(hwnd, _visible);
}


void
CWinFrame::front(void)
{
  WinSetWindowPos(hwnd, HWND_TOP, 0, 0, 0, 0, SWP_ZORDER);
}


void
CWinFrame::back(void)
{
  WinSetWindowPos(hwnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_ZORDER);
}

// **********************************************


CWinClient::CWinClient(HWND  _parent,
                       HWND  _owner,
                       HAB   _hab,
                       ULONG _clStyle,
                       ULONG _wnStyle,
                       ULONG _id,
                       const char* _class)
: parent(_parent),
  owner(_owner),
  hab(_hab),
  clStyle(_clStyle),
  wnStyle(_wnStyle),
  winID(_id),
  className(_class),
  HWindow(0),
  x(0), y(0), w(0), h(0)
{
}



CWinClient::~CWinClient()
{
  Destroy();
}


void
CWinClient::Destroy(void)
{
  if (HWindow)
    {
      WinDestroyWindow(HWindow);
      HWindow = 0;
    }
}


MRESULT
CWinClient::ProcessMsg(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  return WinDefWindowProc(hwnd, msg, mp1, mp2);
}


void
CWinClient::SetupWindow(void)
{
}


void
CWinClient::move(LONG _x, LONG _y)
{
  WinSetWindowPos(HWindow, 0, _x, _y, 0, 0, SWP_MOVE);
}


void
CWinClient::move(LONG _x, LONG _y, LONG _w, LONG _h)
{
  WinSetWindowPos(HWindow, 0, _x, _y, _w, _h, SWP_MOVE | SWP_SIZE);
}


void
CWinClient::size(LONG _w, LONG _h)
{
  WinSetWindowPos(HWindow, 0, 0, 0, _w, _h, SWP_SIZE);
}


void
CWinClient::show(BOOL _visible)
{
  WinShowWindow(HWindow, _visible);
}


void
CWinClient::front(void)
{
  WinSetWindowPos(HWindow, HWND_TOP, 0, 0, 0, 0, SWP_ZORDER);
}


void
CWinClient::back(void)
{
  WinSetWindowPos(HWindow, HWND_BOTTOM, 0, 0, 0, 0, SWP_ZORDER);
}


void
CWinClient::SetStyle(ULONG _style)
{
  wnStyle = _style;
}


void
CWinClient::SetSize(LONG _x, LONG _y, LONG _w, LONG _h)
{
  x = _x;
  y = _y;
  w = _w;
  h = _h;
}


HAB
CWinClient::QueryHAB(void)
{
  return hab;
}

// **********************************************


CWinFramedClient::CWinFramedClient(HWND  _parent,
                                   HWND  _owner,
                                   HAB   _hab,
                                   ULONG _fcFlags,
                                   BOOL  _visible,
                                   ULONG _clStyle,
                                   ULONG _wnStyle,
                                   LONG  _x,
                                   LONG  _y,
                                   LONG  _w,
                                   LONG  _h,
                                   ULONG _id,
                                   ULONG _fid,
                                   const char* _class)
: CWinFrame(_parent, _owner, _hab, _fcFlags, _visible, _fid, _x, _y, _w, _h),
  CWinClient(hwndFrame(), hwndFrame(), _hab, _clStyle, _wnStyle, _id, _class)
{
}


CWinFramedClient::~CWinFramedClient()
{
  Destroy();
}


void
CWinFramedClient::Destroy(void)
{
  CWinClient::Destroy();
  CWinFrame::Destroy();
}


void
CWinFramedClient::Create(void)
{
  CWinClient::Create();
}


MRESULT
CWinFramedClient::ProcessMsg(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  return CWinClient::ProcessMsg(hwnd, msg, mp1, mp2);
}


void
CWinFramedClient::SetupWindow(void)
{
  CWinClient::SetupWindow();
}


void
CWinFramedClient::move(LONG _x, LONG _y)
{
  CWinFrame::move(_x, _y);
}


void
CWinFramedClient::move(LONG _x, LONG _y, LONG _w, LONG _h)
{
  CWinFrame::move(_x, _y, _w, _h);
}


void
CWinFramedClient::size(LONG _w, LONG _h)
{
  CWinFrame::size(_w, _h);
}


void
CWinFramedClient::show(BOOL _visible)
{
  CWinFrame::show(_visible);
}


void
CWinFramedClient::front(void)
{
  CWinFrame::front();
}


void
CWinFramedClient::back(void)
{
  CWinFrame::back();
}


HWND
CWinFramedClient::hwndClient(void)
{
  return CWinClient::HWindow;
}


HWND
CWinFramedClient::hwndFrame(void)
{
  return CWinFrame::hwnd;
}


void
CWinFramedClient::title(const char* _title)
{
  CWinFrame::title(_title);
}

// **************************************************

#ifdef RECT_DEFINED


void
GetClientRect(HWND hwnd, RECT* _rect)
{
  WinQueryWindowRect(hwnd, (PRECTL)_rect);
}

#endif

