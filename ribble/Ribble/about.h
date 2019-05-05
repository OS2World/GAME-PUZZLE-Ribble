//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//

#ifndef _About_h
#define _About_h

class ProductInfoDlg : public CDialog
{
public:
  ProductInfoDlg(HWND hwnd);
  ~ProductInfoDlg();

  void SetupWindow(void);
  MRESULT ProcessMsg(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);

private:

  HWND button;
  ULONG anim;
  ULONG action;
  ULONG timerID;
};


#define DORMANT_BASE    BMP_TribbleNormal
#define BLINKING_BASE   BMP_TribbleBlink1
#define ROLLING_BASE    BMP_TribbleEyeRoll1
#define ANTENNAE_BASE   BMP_TribbleAntennae1
#define SIDE_BASE       BMP_TribbleSide1
#define JUMPING_BASE    BMP_TribbleJump1
#define TABLE_END       ((ULONG)-1)


#endif
