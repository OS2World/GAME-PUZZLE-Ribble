//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//

#include "common.h"

#include "resources.h"
#include "about.h"

const int TRIBBLE_TIMER_DELAY = 50;
const int TribbleWidth  = 48;
const int TribbleHeight = 48;
const int ButtonWidth  = TribbleWidth  + 10;
const int ButtonHeight = TribbleHeight + 7;

static ULONG   ptDormant[] =
{
  DORMANT_BASE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, TABLE_END
  };

static ULONG   ptRolling[] =
{
  ROLLING_BASE, 0, 1, 2, 3, 4, 5, 6, 7, 8, TABLE_END
  };

static ULONG   ptJump[] =
{
  JUMPING_BASE, 0, 1, 2, 3, 4, 5, 6, 7, TABLE_END
  };

static ULONG   ptRolling2[] =
{
  ROLLING_BASE, 8, 7, 6, 5, 4, 3, 2, 1, 0, TABLE_END
  };

static ULONG   ptBlinking[] =
{
  BLINKING_BASE, 0, 1, 2, 3, 4, 4, 3, 2, 1, 0, TABLE_END
  };

static ULONG   ptAntennae[] =
{
  ANTENNAE_BASE, 0, 1, 2, 3, 4, 5, 6, 5, 4, 6, 5, 4, 3, 2, 1, 0, TABLE_END
  };

static ULONG   ptSide[] =
{
  SIDE_BASE, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, TABLE_END
  };

static ULONG   ptSide2[] =
{
  SIDE_BASE, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, TABLE_END
  };

static ULONG*  actionTable[] =
{
  ptDormant,
  ptDormant,
  ptBlinking,
  ptDormant,
  ptBlinking,
  ptDormant,    // <----- after first loop, reset to here (offset 5)
  ptBlinking,
  ptDormant,
  ptRolling,
  ptRolling,
  ptRolling,
  ptDormant,
  ptBlinking,
  ptJump,
  ptDormant,
  ptBlinking,
  ptRolling2,
  ptRolling2,
  ptRolling2,
  ptDormant,
  ptBlinking,
  ptRolling,
  ptRolling,
  ptBlinking,
  ptDormant,
  ptJump,
  ptJump,
  ptJump,
  ptJump,
  ptDormant,
  ptBlinking,
  ptSide,
  ptDormant,
  ptBlinking,
  ptDormant,
  ptAntennae,
  ptBlinking,
  ptDormant,
  ptSide2,
  ptBlinking,
  0
  };


ProductInfoDlg::ProductInfoDlg(HWND hwnd)
: CDialog(hwnd, DLG_ProductInfo, FALSE)
{
  anim = action = 0;
  button = 0;
  timerID = TID_USERMAX - 1;
}

ProductInfoDlg::~ProductInfoDlg()
{
  if (button)
    WinDestroyWindow(button);
  button = 0;
}

void
ProductInfoDlg::SetupWindow(void)
{
  RECTL rect;

  HWND hwndBox  = WinWindowFromID(HWindow, DID_AboutButtonGroup);

  WinQueryWindowRect(hwndBox, &rect);

  POINTL ptl = {0, 0};

  WinMapWindowPoints(hwndBox, HWindow, &ptl, 1);

  long y = ptl.y + 4;
  long x = ptl.x + 4;

  button = WinCreateWindow(HWindow,
                           WC_BUTTON,
                           (PSZ)"",
                           WS_VISIBLE | BS_PUSHBUTTON | WS_GROUP | WS_TABSTOP | BS_USERBUTTON,
                           x, y, ButtonWidth, ButtonHeight,
                           HWindow,
                           HWND_TOP,
                           BMP_Tribble,
                           0,
                           0);

  WinStartTimer(QueryHAB(), HWindow, timerID, TRIBBLE_TIMER_DELAY);    // reward those who read credits dialogs!
}

MRESULT
ProductInfoDlg::ProcessMsg(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  switch (msg)
    {
    case WM_TIMER:
      {
	if (SHORT1FROMMP(mp1) == timerID)
	  {
	    ULONG oldBmp = actionTable[action][0] + actionTable[action][1 + anim];
	    anim++;
	    if (actionTable[action][1 + anim] == TABLE_END)
	      {
		anim = 0;
		action++;
		if (actionTable[action] == 0)
		  action = 5;
	      }
	    ULONG newBmp = actionTable[action][0] + actionTable[action][1 + anim];
	    if (oldBmp != newBmp)
	      WinInvalidateRect(button, 0, FALSE);
	    WinStartTimer(QueryHAB(), HWindow, timerID, TRIBBLE_TIMER_DELAY);
	    return 0;
	  }
	break;
      }
    case WM_CONTROL:
      {
	if (SHORT1FROMMP(mp1) == BMP_Tribble && SHORT2FROMMP(mp1) == BN_PAINT)
	  {
	    if (button)
              {
                USERBUTTON& ub = *(USERBUTTON*)mp2;

                BOOL buttonUp = (ub.fsState != BDS_HILITED) ? TRUE : FALSE;

                ULONG newBmp = actionTable[action][0] + actionTable[action][1 + anim];
                HBITMAP newBitmap = GpiLoadBitmap(ub.hps, 0, newBmp, 48, 48);

		RECTL rect;
		WinQueryWindowRect(button, &rect);

		POINTL poly[3];
		poly[0].x = rect.xLeft  + 1;          poly[0].y = rect.yBottom + 1;
		poly[1].x = rect.xLeft  + 1;          poly[1].y = rect.yTop    - 2;
                poly[2].x = rect.xRight - 2;          poly[2].y = rect.yTop    - 2;
                GpiSetColor(ub.hps, SYSCLR_BUTTONDARK);
                GpiMove(ub.hps, &poly[0]);
                GpiPolyLine(ub.hps, 2, poly + 1);

                poly[0].x = rect.xLeft  + 2;          poly[0].y = rect.yBottom + 2;
                poly[1].x = rect.xLeft  + 2;          poly[1].y = rect.yTop    - 3;
                poly[2].x = rect.xRight - 3;          poly[2].y = rect.yTop    - 3;
                GpiSetColor(ub.hps, buttonUp ? SYSCLR_BUTTONLIGHT : SYSCLR_BUTTONDARK);
                GpiMove(ub.hps, &poly[0]);
                GpiPolyLine(ub.hps, 2, poly + 1);

		poly[0].x = rect.xLeft  + 2;          poly[0].y = rect.yBottom + 1;
		poly[1].x = rect.xRight - 2;          poly[1].y = rect.yBottom + 1;
                poly[2].x = rect.xRight - 2;          poly[2].y = rect.yTop    - 3;
                GpiSetColor(ub.hps, SYSCLR_BUTTONDARK);
                GpiMove(ub.hps, &poly[0]);
                GpiPolyLine(ub.hps, 2, poly + 1);

                poly[0].x = rect.xLeft  + 3;          poly[0].y = rect.yBottom + 2;
                poly[1].x = rect.xRight - 3;          poly[1].y = rect.yBottom + 2;
                poly[2].x = rect.xRight - 3;          poly[2].y = rect.yTop    - 4;
                GpiSetColor(ub.hps, buttonUp ? SYSCLR_BUTTONDARK : SYSCLR_BUTTONLIGHT);
                GpiMove(ub.hps, &poly[0]);
                GpiPolyLine(ub.hps, 2, poly + 1);

                if (newBitmap)
                  {
                    POINTL p;
		    p.x = buttonUp ? 6 : 7;
		    p.y = buttonUp ? 4 : 3;
		    WinDrawBitmap(ub.hps, newBitmap, 0, &p, 0, 0, DBM_NORMAL);
		    GpiDeleteBitmap(newBitmap);
                  }
              }
          }
	return 0;
      }
    case WM_COMMAND:
      {
        break;
      }
    case WM_DESTROY:
      {
        WinStopTimer(QueryHAB(), HWindow, timerID);
        break;
      }
    }

  return CDialog::ProcessMsg(hwnd, msg, mp1, mp2);
}


