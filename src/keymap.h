//
// keymap.h -- keyboard and joystick mapping of Ribble (Options - Key Mapping...)
//

#ifndef _KeyMap_h
#define _KeyMap_h

// actions; the values are the same as LeftKey, RightKey, UpKey, DownKey of man.h
#define KM_LEFT    0
#define KM_RIGHT   1
#define KM_UP      2
#define KM_DOWN    3
#define KM_NACT    4

void KmInit(void);                  // open GAME$, read the saved mapping
void KmDone(void);
int  KmKeyAction(ULONG fs, USHORT vkey, UCHAR scan);   // action of a WM_CHAR key, or -1
BOOL KmJoyEnabled(void);
void KmJoyPoll(void);               // read the stick once per game timer tick
BOOL KmJoyDown(int act);            // is that action held on the joystick?
void KmDialog(HWND hwndOwner);      // the dialog; saves the result when OK is chosen

#endif
