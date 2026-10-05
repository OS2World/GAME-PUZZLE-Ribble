// -------------------------------
//  Name:           CDialog.cpp
//  Author:         J.R.Shannon
//  Language:       C++
//  Date:           6/11/92
//  Revison:        2.1
//  Last revision:  9/7/93
//  Licence:        Public Domain
//  Purpose:        Basic dialog window handling.
// -------------------------------

#ifdef __OS2__

#define INCL_WIN
#include <os2.h>

#include "CAssert.h"
#include "win\CDialog.h"


// This dialog window procedure discards window
// messages until WM_INITDLG is received.  This
// message contains information about the object
// which is to supply the ProcessMsg method for
// future message processing.

MRESULT EXPENTRY CDialogInitialDialogWindowProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  switch (msg)
    {
    case WM_INITDLG:
      {
        // Ensure valid object pointer passed
        CAssert(mp2);
        // Set user area in window words.
        WinSetWindowULong(hwnd, QWL_USER, (ULONG)mp2);
        // Set new window procedure to one that knows
        // about objects.
        WinSubclassWindow(hwnd, (PFNWP)CDialogDialogWindowProc);
        // Call the object's ProcessMsg for the
        // WM_INITDLG message.
        CDialog* real = (CDialog*)mp2;
        real->HWindow = hwnd;
        real->MsgSpec = (PVOID)((PBYTE)&msg + sizeof(MPARAM));
        real->SetupWindow();
        return real->ProcessMsg(hwnd, msg, mp1, mp2);
      }
    }
  return WinDefDlgProc(hwnd, msg, mp1, mp2);
}

// This dialog window procedure dispatches received
// messages to the object's ProcessMsg method.

MRESULT EXPENTRY CDialogDialogWindowProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  CDialog* real = (CDialog*)WinQueryWindowULong(hwnd, QWL_USER);
  real->MsgSpec = (PVOID)((PBYTE)&msg + sizeof(MPARAM));
  return real->ProcessMsg(hwnd, msg, mp1, mp2);
}

// Override this virtual method to provide your own
// message processing.

MRESULT CDialog::ProcessMsg(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  return WinDefDlgProc(hwnd, msg, mp1, mp2);
}

// Set up CDialog ready for the open().

CDialog::CDialog(HWND _owner, ULONG _resID,
                 BOOL _modeless, HWND _parent,
                 HMODULE _module)
  : owner(_owner), resID(_resID), modeless(_modeless),
    parent(_parent), hwndDialog(0), module(_module)
{
}

// Open the dialog window, and run it if it's modal.

void CDialog::Create(void)
{
  if (modeless == TRUE)
    {
      hwndDialog = WinLoadDlg(parent,
                              owner,
                              (PFNWP)CDialogInitialDialogWindowProc,
                              module,
                              resID,
                              (PVOID)this);
      CAssert(hwndDialog);
    }
  else
    {
      WinDlgBox(parent,
                owner,
                (PFNWP)CDialogInitialDialogWindowProc,
                module,
                resID,
                (PVOID)this);
    }
}

void
CDialog::SetupWindow(void)
{
}

HAB
CDialog::QueryHAB(void)
{
  return WinQueryAnchorBlock(HWindow);
}

CDialog::~CDialog()
{
  Destroy();
}

HWND CDialog::hwnd(void)
{
  return hwndDialog;
}

void CDialog::show(BOOL _show)
{
  WinShowWindow(hwndDialog, _show);
}

void CDialog::Destroy(void)
{
  if (hwndDialog)
    {
      WinDestroyWindow(hwndDialog);
      hwndDialog = 0;
    }
}


#else

// $Source: C:\logical\store\classes/RCS/CDIALOG.CPP,v $
// $Revision: 1.7 $
// $Date: 1994/02/15 11:14:41 $
//
// Information window implementation file - J.R.Shannon
// (c) 1993 Logical Water.

#include <windows.h>

#define C_NO_IOSTREAM
#include <CDList.h>
#include <CStrng.h>

#include "cdialog.h"

// ---------------------------------------------------------------------------------------

CDialog::CDialog(HWND _owner, HINSTANCE _hInst, char* _resID, BOOL _modal)
: owner(_owner),
  hInst(_hInst),
  resID(_resID),
  modal(_modal)
{
  hwnd = 0;
  proc = (DLGPROC)MakeProcInstance((FARPROC)DialogProc, hInst);
}

CDialog::~CDialog()
{
  Close();
  if (proc)
    {
      FreeProcInstance((FARPROC)DialogProc);
      proc = 0;
    }
}

void
CDialog::Create(void)
{
  if (modal == TRUE)
    DialogBoxParam(hInst, (LPCSTR)resID, owner, proc, (LPARAM)this);
  else
    CreateDialogParam(hInst, (LPCSTR)resID, owner, proc, (LPARAM)this);
}

void
CDialog::Show(void)
{
  if (hwnd)
    ShowWindow(hwnd, SW_SHOW);
}

void
CDialog::Hide(void)
{
  if (hwnd)
    ShowWindow(hwnd, SW_HIDE);
}

void
CDialog::BringToTop(void)
{
  if (hwnd)
    BringWindowToTop(hwnd);
}

void
CDialog::Move(int _x, int _y)
{
  SetWindowPos(hwnd, 0, _x, _y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
}

void
CDialog::Close(void)
{
  if (hwnd)
    {
      if (modal)
        EndDialog(hwnd, 1);
      else
        DestroyWindow(hwnd);

      hwnd = 0;
    }
}

LRESULT CALLBACK
CDialog::DialogProc(HWND hwnd, UINT msg, WPARAM mp1, LPARAM mp2)
{
  if (msg == WM_INITDIALOG)
    {
      ((CDialog*)mp2)->HWindow = hwnd;
      SetWindowLong(hwnd, DWL_USER, mp2);
      return ((CDialog*)mp2)->RealProc(hwnd, msg, mp1, mp2);
    }
  else
    {
      CDialog* dialog = (CDialog*)GetWindowLong(hwnd, DWL_USER);
      if (dialog)
        return dialog->RealProc(hwnd, msg, mp1, mp2);
    }
  return 0;
}

LRESULT
CDialog::RealProc(HWND hwnd, UINT msg, WPARAM mp1, LPARAM mp2)
{
  hwnd;
  msg;
  mp1;
  mp2;
  return 0;
}

#endif

