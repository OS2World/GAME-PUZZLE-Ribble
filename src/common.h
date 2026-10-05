//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//

#ifndef _Common_h
#define _Common_h

#define INCL_WIN
#define INCL_GPI
#define INCL_DOS
#include <os2.h>

#include <cassert.h>
#include <cstrng.h>
#include <cslist.h>
#include <cdlist.h>
#include <cwindow.h>
#include <cdialog.h>
#include <cthread.h>

//extern "C" int pmPrintf(const char*, ...);

template <class T>
T Min(T a, T b)
{
  return a < b ? a : b;
}

template <class T>
T Max(T a, T b)
{
  return a > b ? a : b;
}

#endif
