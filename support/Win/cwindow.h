#ifndef _cwindow_h
#define _cwindow_h

#include <stdlib.h>
#include <cstrng.h>

class CApplication
{
public:
  CApplication(void);
  virtual ~CApplication();
  void Run(void);
  HAB QueryHAB(void) { return hab; }
  HMQ QueryHMQ(void) { return hmq; }

private:
  HAB hab;
  HMQ hmq;
};

#define CWINDOWCLIENTCLASS "CWindowClientClass"
#define CWINDOWDEFFCFLAGS  (FCF_TITLEBAR | FCF_SYSMENU | FCF_MINMAX | FCF_SIZEBORDER | FCF_TASKLIST)

class CWinBase
{
};

class CWinFrame : private CWinBase
{
public:
  CWinFrame(HWND  _parent  = HWND_DESKTOP,
            HWND  _owner   = HWND_DESKTOP,
            HAB   _hab     = 0,
            ULONG _flags   = CWINDOWDEFFCFLAGS,
            BOOL  _visible = FALSE,
            ULONG _fid     = 1,
            LONG  _x       = 0,
            LONG  _y       = 0,
            LONG  _w       = 0,
            LONG  _h       = 0);
  virtual ~CWinFrame();
  void Destroy(void);

  void title(const char* _title);
  void move(LONG _x, LONG _y);
  void move(LONG _x, LONG _y, LONG _w, LONG _h);
  void size(LONG _w, LONG _h);
  void show(BOOL _visible = TRUE);
  void front(void);
  void back(void);

protected:
  HWND      parent;
  HWND      owner;
  ULONG     flags;
  HAB       hab;
  BOOL      visible;
  LONG      x, y, w, h;
  ULONG     fid;

public:
  HWND      hwnd;

private:
  void Create(void);
};

class CWinClient : private CWinBase
{
  friend MRESULT EXPENTRY CWinClientWindowProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);

public:
  CWinClient(HWND  _parent  = HWND_DESKTOP,
             HWND  _owner   = HWND_DESKTOP,
             HAB   _hab     = 0,
             ULONG _clStyle = CS_SIZEREDRAW,
             ULONG _wnStyle = 0,
             ULONG _id      = FID_CLIENT,
             const char* _class = CWINDOWCLIENTCLASS);
  virtual ~CWinClient();
  void Destroy(void);
  void Create(void);

  virtual MRESULT ProcessMsg(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
  virtual void SetupWindow(void);

  void move(LONG _x, LONG _y);
  void move(LONG _x, LONG _y, LONG _w, LONG _h);
  void size(LONG _w, LONG _h);
  void show(BOOL _visible = TRUE);
  void front(void);
  void back(void);
  void SetStyle(ULONG _style);
  void SetSize(LONG x, LONG y, LONG w, LONG h);

  HAB QueryHAB(void);

protected:
  HWND        parent;
  HWND        owner;
  PVOID       MsgSpec;

private:
  ULONG     clStyle;
  ULONG     wnStyle;
  ULONG     winID;
  HAB       hab;
  CString   className;
  LONG      x, y, w, h;

public:
  HWND      HWindow;
};

class CWinFramedClient : private CWinFrame, public CWinClient
{
public:
  CWinFramedClient(HWND  _parent  = HWND_DESKTOP,
                   HWND  _owner   = HWND_DESKTOP,
                   HAB   _hab     = 0,
                   ULONG _fcFlags = CWINDOWDEFFCFLAGS,
                   BOOL  _visible = FALSE,
                   ULONG _clStyle = CS_SIZEREDRAW,
                   ULONG _wnStyle = 0,
                   LONG  _x       = 0,
                   LONG  _y       = 0,
                   LONG  _w       = 0,
                   LONG  _h       = 0,
                   ULONG _id      = FID_CLIENT,
                   ULONG _fid     = 1,
                   const char* _class = CWINDOWCLIENTCLASS);
  virtual ~CWinFramedClient();
  void Destroy(void);
  void Create(void);
  void title(const char* _title);

  virtual MRESULT ProcessMsg(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
  virtual void SetupWindow(void);

  void move(LONG _x, LONG _y);
  void move(LONG _x, LONG _y, LONG _w, LONG _h);
  void size(LONG _w, LONG _h);
  void show(BOOL _visible = TRUE);
  void front(void);
  void back(void);

  HWND hwndFrame(void);
  HWND hwndClient(void);

public:
};



#endif

