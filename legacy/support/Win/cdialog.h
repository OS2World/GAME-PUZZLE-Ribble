#ifdef __OS2__

// -------------------------------
//  Name:           CDialog.h
//  Author:         J.R.Shannon
//  Language:       C++
//  Date:           6/11/92
//  Revison:        2.1
//  Last revision:  9/7/93
//  Licence:        Public Domain
//  Purpose:        Basic dialog window handling.
// -------------------------------
//
// Remarks:
//      The header file <os2.h> must have been included
//   prior to this one, with at least INCL_WIN defined.
//
//
// Using this CDialog class:
//
//      Construction of the dialog window does not actually
//   take place until the open() method is called.  It
//   should be called after (or during) the constructor
//   of the derived class which contains the overridden
//   version of ProcessMsg.
//      The reason for this is that
//   if the dialog window is opened in the CDialog
//   constructor then the virtual function jump tables
//   will contain a pointer to the wrong ProcessMsg
//   and some of the early messages will be lost
//   to CDialog::ProcessMsg rather than the derived
//   class's ProcessMsg.
//
//      If the dialog window is created modeless, then
//   the user is responsible for running of the calling
//   thread's message queue.  A modal dialog window
//   runs the queue for the window's life-time.
//
//  Warning:
//
//   The ULONG at QWL_USER in the dialog's window words
//   is *NOT* available for use by the user.  Use
//   storage inside your derived CDialog object instead.
//

#ifndef _CDialog_h
#define _CDialog_h


// Class for a dialog window

class CDialog
{
public:
  // _owner    = the window which is to own the dialog window
  // _resID    = id of dialog template in .exe resource section
  // _modeless = TRUE: create a modeless dialog window - control returns after creation
  // _parent   = parent window for dialog window. (Window is clipped to the parent)
  CDialog(HWND _owner, ULONG _resID, BOOL _modeless = FALSE, HWND _parent = HWND_DESKTOP, HMODULE _module = 0);

  virtual ~CDialog();

  HWND hwnd(void);          // Get handle on window.
  virtual void Create(void);  // Open the dialog window.  Returns after creation if
                            // it is modeless, and after the window has closed if it
                            // is modal.
  virtual void Destroy(void); // Force the window to close.
  virtual void SetupWindow(void);
  virtual void show(BOOL _show = TRUE);
  HAB QueryHAB(void);

protected:
  friend MRESULT EXPENTRY CDialogInitialDialogWindowProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
  friend MRESULT EXPENTRY CDialogDialogWindowProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
  virtual MRESULT ProcessMsg(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);

  PVOID       MsgSpec;

public:
  union
    {
      HWND    hwndDialog;
      HWND    HWindow;
    };

private:
  HWND    owner;
  HWND    parent;
  ULONG   resID;
  HMODULE module;
  BOOL    modeless;
};


#endif

#else

// $Source: C:\logical\store\classes/RCS/CDIALOG.H,v $
// $Revision: 1.5 $
// $Date: 1994/01/22 14:47:12 $
//

#ifndef _cdialog_h
#define _cdialog_h

class CDialog
{
public:
       CDialog(HWND _owner, HINSTANCE _hInst, char* _resID, BOOL _modal = FALSE);
       ~CDialog();
       void Close(void);
       void Create(void);
       void Show(void);
       void Hide(void);
       void Move(int _x, int _y);
       void BringToTop(void);
       HWND handle(void) { return hwnd; }
       //--
       virtual LRESULT RealProc(HWND, UINT, WPARAM, LPARAM);

       union
         {
           HWND hwnd;
           HWND HWindow;
         };
private:
        HWND      owner;
        HINSTANCE hInst;
        CString   resID;
        DLGPROC   proc;
        BOOL      modal;
        //--
        static LRESULT CALLBACK DialogProc(HWND, UINT, WPARAM, LPARAM);
};

#endif

#endif

