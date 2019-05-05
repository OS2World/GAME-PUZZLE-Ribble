//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//

#include "common.h"
#pragma hdrstop

#include "resources.h"
#include "ribble.h"
#include "map.h"
#include "screen.h"
#include "monster.h"
#include "man.h"
#include "edit.h"
#include "mainwin.h"
#include "spirit.h"
#include "pal.h"

#include <stdio.h>
#include <iostream.h>
#include <fstream.h>


const int buttonWid = 38;
const int buttonHgt = 38;
const int butSep = 2;
const int palWid = 4;
const topHgt = 36;
const ULONG valueID = 1000;


extern ULONG bmp_map[];

int VisItems[] =
{
  ITEM_EMPTY,
  ITEM_BOULDER,
  ITEM_REDWALL,
  ITEM_REDWALLN,
  ITEM_REDWALLNE,
  ITEM_REDWALLE,
  ITEM_REDWALLSE,
  ITEM_REDWALLS,
  ITEM_REDWALLSW,
  ITEM_REDWALLW,
  ITEM_REDWALLNW,
  ITEM_BLUEWALL,
  ITEM_EARTH,
  ITEM_DIAMOND,
  ITEM_KEY,
  ITEM_SAFE,
  ITEM_SPIRIT,
  ITEM_CAGE,
  ITEM_EGG,
  ITEM_TELEPORT,
  ITEM_BOMB,
};

const int NUM_ITEMS = sizeof(VisItems) / sizeof(int);


ItemPalette::ItemPalette(MainWindow* _win)
: CWinClient(_win->HWindow,
             _win->HWindow,
             0,
             0,
             0,
             3,
             "ItemPal")
{
  SetStyle(CS_CLIPCHILDREN | CS_CLIPSIBLINGS | CS_SIZEREDRAW);
  win = _win;
  currentChoice = ITEM_EMPTY;
  valueset = 0;
}

ItemPalette::~ItemPalette()
{
  if (valueset)
    {
      WinDestroyWindow(valueset);
      valueset = 0;
    }
}

void
ItemPalette::SetupWindow(void)
{
  CreateButtons();

  RECTL palSize;
  WinQueryWindowRect(valueset, &palSize);

  size(palSize.xRight - palSize.xLeft,
       palSize.yTop - palSize.yBottom + topHgt);

  WinSetWindowPos(valueset, HWND_TOP, 0, 0, 0, 0, SWP_ZORDER | SWP_MOVE);
}

MRESULT
ItemPalette::ProcessMsg(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  switch (msg)
    {
    case WM_PAINT:
      Paint();
      return 0;
    case WM_COMMAND:
      ProcessCmd(mp1, mp2);
      return 0;
    case WM_CONTROL:
      return ProcessCtl(mp1, mp2);
    }
  return CWinClient::ProcessMsg(hwnd, msg, mp1, mp2);
}

BOOL
ItemPalette::SetCurrentChoice(int x, int y)
{
  int item = (x-1) + (y-1) * palWid;
  if (item >= 0 && item < NUM_ITEMS &&
      x >= 1 && x <= palWid &&
      y >= 1 && y <= CalcYhgt(NUM_ITEMS))
    {
      currentChoice = VisItems[item];
      WinInvalidateRect(HWindow, 0, FALSE);
      return TRUE;
    }
  return FALSE;
}

MRESULT
ItemPalette::ProcessCtl(MPARAM mp1, MPARAM mp2)
{
  switch (SHORT1FROMMP(mp1))
    {
    case valueID:
      {
        switch (SHORT2FROMMP(mp1))
          {
          case VN_SETFOCUS:
            {
              WinPostMsg(win->HWindow, WM_GiveFocus, MPVOID, MPVOID);
              break;
            }
          case VN_SELECT:
            {
              int x = SHORT2FROMMP(mp2);
              int y = SHORT1FROMMP(mp2);
              SetCurrentChoice(x, y);
              break;
            }
          case VN_ENTER:
            {
              int x = SHORT2FROMMP(mp2);
              int y = SHORT1FROMMP(mp2);
              if (SetCurrentChoice(x, y) == TRUE)
                win->SetMapItem(currentChoice);
              break;
            }
          }
      }
    }
  return 0;
}



void
ItemPalette::ProcessCmd(MPARAM mp1, MPARAM mp2)
{
  mp1;
  mp2;
}

void
ItemPalette::Paint(void)
{
  RECTL rct;
  WinQueryWindowRect(HWindow, &rct);

  HPS hps = WinBeginPaint(HWindow, 0, 0);
  WinFillRect(hps, &rct, CLR_BLACK);

  RECTL textRct;
  textRct.xLeft = 4;
  textRct.xRight = rct.xRight / 2;
  textRct.yTop = rct.yTop - 4;
  textRct.yBottom = rct.yTop - topHgt;

  char* text = "Current >> ";

  WinDrawText(hps,
              -1,
              (PSZ)text,
              &textRct,
              CLR_GREEN,
              CLR_BLACK,
              DT_RIGHT | DT_VCENTER);

  textRct.xLeft = textRct.xRight + 4;
  textRct.xRight = textRct.xLeft + 32;

  GpiSetColor(hps, CLR_WHITE);
  GpiSetBackColor(hps, CLR_BLACK);
  GpiSetBackMix(hps,  BM_OVERPAINT);

  HBITMAP bmp = GpiLoadBitmap(hps, 0, bmp_map[currentChoice], 32, 32);
  if (bmp)
    {
      POINTL p[3];
      p[0].x = textRct.xLeft;
      p[0].y = textRct.yBottom;
      p[1].x = p[0].x + 32;
      p[1].y = p[0].y + 32;
      p[2].x = 0;
      p[2].y = 0;
      GpiWCBitBlt(hps, bmp, 3, p, ROP_SRCCOPY, 0);
      GpiDeleteBitmap(bmp);
    }

  WinEndPaint(hps);
}

int
ItemPalette::CalcXwid(int _num)
{
  if (_num >= palWid)
    return palWid;
  else
    return _num;
}

int
ItemPalette::CalcYhgt(int _num)
{
  return (_num / palWid) + 1;
}

void
ItemPalette::CreateButtons(void)
{
  VSCDATA ctldata;
  ctldata.cbSize = sizeof(ctldata);
  ctldata.usRowCount = (USHORT)CalcYhgt(NUM_ITEMS);
  ctldata.usColumnCount = (USHORT)CalcXwid(NUM_ITEMS);

  valueset = WinCreateWindow(HWindow,
                             WC_VALUESET,
                             (PSZ)0,
                             VS_BITMAP | /*VS_BORDER | */WS_VISIBLE,
                             0, 0,
                             butSep + (buttonWid + butSep) * CalcXwid(NUM_ITEMS),
                             butSep + (buttonHgt + butSep) * CalcYhgt(NUM_ITEMS),
                             HWindow,
                             HWND_TOP,
                             valueID,
                             (PVOID)&ctldata,
                             0);
  CAssert(valueset);

  RGB rgb;
  rgb.bBlue  = 0x80;
  rgb.bGreen = 0x00;
  rgb.bRed   = 0x00;

  WinSetPresParam(valueset, PP_BACKGROUNDCOLOR, sizeof(RGB), &rgb);

  int x = 0;
  int y = 0;

  for (int item = 0; item < NUM_ITEMS; item++)
    {
      ULONG id = bmp_map[VisItems[item]];
      HBITMAP bmp = win->QueryScreen()->QueryBitmap(id);
      WinSendMsg(valueset, VM_SETITEM,
		 MPFROM2SHORT(y+1, x+1), (MPARAM)bmp);
      if (++x >= palWid)
        {
          x = 0;
          y++;
        }
    }
}


