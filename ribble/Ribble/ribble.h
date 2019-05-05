//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//

#ifndef _Ribble_h
#define _Ribble_h

const ULONG WM_GiveFocus = WM_USER;
const ULONG WM_ResetSize = WM_USER + 1;
const ULONG StringLimit = 256;
const int ScoreTableLen = 8;

const int resHgt = 24;
const ULONG TimerID = TID_USERMAX - 1;
const ULONG TitleID = TID_USERMAX - 2;
const ULONG titleTimeInterval = 5000;
const int HatchDelayCnt = 50;
const int FizzleDelayCnt = 40;
const int TimeScale = 4;
const int ItemW1 = 40;
const int ItemW2 = 48;
const int ScoreX = 0;
const int TimeX = ScoreX + ItemW1;
const int LivesX = TimeX + ItemW1;
const int DiamondsX = LivesX + ItemW1;
const int RemainingX = DiamondsX + ItemW2;
const int manDeathCount = 20;
const int mapCellWid = 16;
const int mapCellHgt = mapCellWid;

#endif


