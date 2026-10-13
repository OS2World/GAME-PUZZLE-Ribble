/*
 * keymap.cpp -- keyboard and joystick mapping of Ribble and the "Key Mapping..."
 *               dialog (notebook: Keyboard, Joystick).
 *
 * Keyboard: each of the four moves (left, right, up, down) is a key.  A key is stored
 *           as a code: 0x100 + virtual key (arrows, Home, End, PgUp, PgDn) or
 *           0x200 + scan code (every other key).
 * Joystick: through the GAME$ driver, stick A or B.  Every move is a joystick
 *           button or a stick direction.
 * The mapping is saved in the user profile (application "Ribble_V1.1", key "KeyMap").
 */
#define INCL_WIN
#define INCL_DOS
#define INCL_DOSERRORS
#define INCL_WINSTDBOOK
#define INCL_WINENTRYFIELDS
#define INCL_WININPUT
#define INCL_WINSHELLDATA
#include <os2.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "keymap.h"
#include "resources.h"
#include "joyos2.h"

extern int current_lang;            /* mainwin.cpp: 0 EN, 1 ES, 2 NL, 3 DE, 4 FR, 5 IT */

static const char *KM_APP = "Ribble_V1.1";

/* ------------------------------------------------------------------ texts */

enum {
   KMS_TITLE = 0, KMS_TAB_KBD, KMS_TAB_JOY, KMS_JOY_EN, KMS_JOY_A, KMS_JOY_B,
   KMS_CAL_A, KMS_CAL_B, KMS_OK, KMS_CANCEL, KMS_CAL_MSG, KMS_CAL_TITLE,
   KMS_NONE, KMS_AXL, KMS_AXR, KMS_AXU, KMS_AXD, KMS_BTN,
   KMS_LEFT, KMS_RIGHT, KMS_UP, KMS_DOWN, KMS_PRESS,
   KMS_KBD_H, KMS_JOY_H1, KMS_JOY_H2, KMS_DEFAULT,
   KMS_COUNT
};

static const char *km_txt[6][KMS_COUNT] = {
   /* EN */ {
      "Key Mapping", "Keyboard", "Joystick", "~Enable Joystick",
      "Joystick ~A", "Joystick ~B", "Calibrate A", "Calibrate B",
      "OK", "Cancel", "Center Joystick %c, then click OK.", "Calibrate Joystick %c",
      "None", "Axis L", "Axis R", "Axis Up",
      "Axis Down", "Btn %d", "Left", "Right",
      "Up", "Down", "Press key...",
      "Click a box, then press the key.", "Click a box, then press a joystick button", "or move the stick (Delete clears).", "Default"
   },
   /* ES */ {
      "Asignacion de teclas", "Teclado", "Joystick", "~Activar joystick",
      "Joystick ~A", "Joystick ~B", "Calibrar A", "Calibrar B",
      "Aceptar", "Cancelar", "Centre el joystick %c y pulse Aceptar.", "Calibrar joystick %c",
      "Ninguno", "Eje izq.", "Eje der.", "Eje arriba",
      "Eje abajo", "Boton %d", "Izquierda", "Derecha",
      "Arriba", "Abajo", "Pulse una tecla...",
      "Haga clic en un cuadro y pulse la tecla.", "Haga clic en un cuadro y pulse un boton", "del joystick o mueva la palanca (Supr borra).", "Por defecto"
   },
   /* NL */ {
      "Toetsen toewijzen", "Toetsenbord", "Joystick", "Joystick ~gebruiken",
      "Joystick ~A", "Joystick ~B", "Kalibreer A", "Kalibreer B",
      "OK", "Annuleren", "Centreer joystick %c en klik op OK.", "Joystick %c kalibreren",
      "Geen", "As links", "As rechts", "As omhoog",
      "As omlaag", "Knop %d", "Links", "Rechts",
      "Omhoog", "Omlaag", "Druk op een toets...",
      "Klik op een vak en druk op de toets.", "Klik op een vak en druk op een joystickknop", "of beweeg de stick (Delete wist).", "Standaard"
   },
   /* DE */ {
      "Tastenzuordnung", "Tastatur", "Joystick", "Joystick ~aktivieren",
      "Joystick ~A", "Joystick ~B", "A kalibrieren", "B kalibrieren",
      "OK", "Abbrechen", "Joystick %c zentrieren, dann OK klicken.", "Joystick %c kalibrieren",
      "Keine", "Achse links", "Achse rechts", "Achse oben",
      "Achse unten", "Taste %d", "Links", "Rechts",
      "Hoch", "Runter", "Taste druecken...",
      "Klicke auf ein Feld und druecke die Taste.", "Klicke auf ein Feld und druecke eine Joystick-Taste", "oder bewege den Stick (Entf loescht).", "Standard"
   },
   /* FR */ {
      "Affectation des touches", "Clavier", "Joystick", "~Activer le joystick",
      "Joystick ~A", "Joystick ~B", "Calibrer A", "Calibrer B",
      "OK", "Annuler", "Centrez le joystick %c puis cliquez sur OK.", "Calibrer le joystick %c",
      "Aucun", "Axe gauche", "Axe droite", "Axe haut",
      "Axe bas", "Bouton %d", "Gauche", "Droite",
      "Haut", "Bas", "Appuyez sur une touche...",
      "Cliquez sur une case puis appuyez sur la touche.", "Cliquez sur une case puis appuyez sur un bouton", "du joystick ou bougez le manche (Suppr efface).", "Defaut"
   },
   /* IT */ {
      "Assegnazione tasti", "Tastiera", "Joystick", "~Attiva joystick",
      "Joystick ~A", "Joystick ~B", "Calibra A", "Calibra B",
      "OK", "Annulla", "Centra il joystick %c e fai clic su OK.", "Calibra joystick %c",
      "Nessuno", "Asse sinistra", "Asse destra", "Asse su",
      "Asse giu", "Pulsante %d", "Sinistra", "Destra",
      "Su", "Giu", "Premi un tasto...",
      "Fai clic su una casella e premi il tasto.", "Fai clic su una casella e premi un pulsante", "del joystick o muovi la leva (Canc cancella).", "Predefinito"
   },
};

/* text of the active language without the mnemonic tilde */
static const char *kmText(int id)
{
   static char abuf[8][100];
   static int n;
   const char *s = km_txt[(current_lang >= 0 && current_lang < 6) ? current_lang : 0][id];
   char *d;

   n = (n + 1) & 7;
   d = abuf[n];
   while(*s && d < abuf[n] + sizeof(abuf[n]) - 1)
   {
      if(*s != '~')
         *d++ = *s;
      s++;
   }
   *d = 0;
   return abuf[n];
}

/* ------------------------------------------------------------------- data */

/* joystick: 0 = none, 1-4 = button, 5-8 = axis left / right / up / down */
#define JOY_AXIS_L  5
#define JOY_AXIS_R  6
#define JOY_AXIS_U  7
#define JOY_AXIS_D  8

typedef struct _KMCFG
{
   int ver;
   int key[KM_NACT];         /* keyboard codes                             */
   int enabled;              /* joystick control on / off                  */
   int stick;                /* 1 = A, 2 = B                               */
   int act[KM_NACT];         /* 0 none, 1-4 button, 5-8 axis direction     */
}KMCFG;

static void kmDefaults(KMCFG *c, int kbd, int joy)
{
   if(kbd)
   {
      c->key[KM_LEFT]  = 0x100 | VK_LEFT;
      c->key[KM_RIGHT] = 0x100 | VK_RIGHT;
      c->key[KM_UP]    = 0x100 | VK_UP;
      c->key[KM_DOWN]  = 0x100 | VK_DOWN;
   }
   if(joy)
   {
      c->stick = 1;
      c->act[KM_LEFT]  = JOY_AXIS_L;
      c->act[KM_RIGHT] = JOY_AXIS_R;
      c->act[KM_UP]    = JOY_AXIS_U;
      c->act[KM_DOWN]  = JOY_AXIS_D;
   }
   c->ver = 1;
}

static KMCFG cfg;

static HFILE              hGame = 0;
static GAME_2DPOS_STRUCT  joyCal[3];                 /* centre of stick A (1) and B (2) */
static BOOL               bJoyAvail[2];
static GAME_STATUS_STRUCT joyNow;                    /* last status read by KmJoyPoll() */
static BOOL               bJoyNow = FALSE;

static const USHORT usButBit[4] = { JOY_BUT1_BIT, JOY_BUT2_BIT, JOY_BUT3_BIT, JOY_BUT4_BIT };

static const char *kmJoyLabel(int n)
{
   static char b[100];

   if(n == 0) return kmText(KMS_NONE);
   if(n >= 1 && n <= 4) { sprintf(b, kmText(KMS_BTN), n); return b; }
   if(n == JOY_AXIS_L) return kmText(KMS_AXL);
   if(n == JOY_AXIS_R) return kmText(KMS_AXR);
   if(n == JOY_AXIS_U) return kmText(KMS_AXU);
   if(n == JOY_AXIS_D) return kmText(KMS_AXD);
   return "?";
}

/* ----------------------------------------------------------------- keyboard */

static int kmKeyCode(ULONG fs, USHORT vkey, UCHAR scan)
{
   if(fs & KC_VIRTUALKEY)
      return 0x100 | vkey;
   if(fs & KC_SCANCODE)
      return 0x200 | scan;
   return 0;
}

int KmKeyAction(ULONG fs, USHORT vkey, UCHAR scan)
{
   int code = kmKeyCode(fs, vkey, scan), i;

   if(code == 0)
      return -1;
   for(i = 0; i < KM_NACT; i++)
      if(cfg.key[i] == code)
         return i;
   return -1;
}

/* keys that may be assigned: arrows, Home, End, PgUp, PgDn and every ordinary key */
static BOOL kmKeyAllowed(int code)
{
   if((code >> 8) == 1)
   {
      int vk = code & 0xFF;

      return vk == VK_LEFT || vk == VK_RIGHT || vk == VK_UP || vk == VK_DOWN ||
             vk == VK_HOME || vk == VK_END || vk == VK_PAGEUP || vk == VK_PAGEDOWN;
   }
   return (code >> 8) == 2 && (code & 0xFF) != 0;
}

static void kmKeyName(int code, char *buf, int cBuf)
{
   static const struct { BYTE sc; const char *name; } aMap[] = {
      {0x0E,"BkSp"}, {0x1C,"Enter"}, {0x39,"Space"},
      {0x3B,"F1"},{0x3C,"F2"},{0x3D,"F3"},{0x3E,"F4"},{0x3F,"F5"},
      {0x40,"F6"},{0x41,"F7"},{0x42,"F8"},{0x43,"F9"},{0x44,"F10"},
      {0x57,"F11"},{0x58,"F12"},
      {0x10,"Q"},{0x11,"W"},{0x12,"E"},{0x13,"R"},{0x14,"T"},
      {0x15,"Y"},{0x16,"U"},{0x17,"I"},{0x18,"O"},{0x19,"P"},
      {0x1E,"A"},{0x1F,"S"},{0x20,"D"},{0x21,"F"},{0x22,"G"},
      {0x23,"H"},{0x24,"J"},{0x25,"K"},{0x26,"L"},
      {0x2C,"Z"},{0x2D,"X"},{0x2E,"C"},{0x2F,"V"},
      {0x30,"B"},{0x31,"N"},{0x32,"M"},
      {0x02,"1"},{0x03,"2"},{0x04,"3"},{0x05,"4"},{0x06,"5"},
      {0x07,"6"},{0x08,"7"},{0x09,"8"},{0x0A,"9"},{0x0B,"0"},
      {0x0C,"-"},{0x0D,"="},{0x1A,"["},{0x1B,"]"},
      {0x27,";"},{0x28,"'"},{0x2B,"\\"},
      {0x33,","},{0x34,"."},{0x35,"/"},{0x29,"`"},
      {0x4A,"Num -"},{0x4E,"Num +"},{0x37,"Num *"},
      {0,NULL}
   };
   const char *name = NULL;
   int i;

   buf[0] = 0;
   if(code == 0)
      return;
   if((code >> 8) == 1)
   {
      switch(code & 0xFF)
      {
         case VK_LEFT:     name = "Left";  break;
         case VK_RIGHT:    name = "Right"; break;
         case VK_UP:       name = "Up";    break;
         case VK_DOWN:     name = "Down";  break;
         case VK_HOME:     name = "Home";  break;
         case VK_END:      name = "End";   break;
         case VK_PAGEUP:   name = "PgUp";  break;
         case VK_PAGEDOWN: name = "PgDn";  break;
      }
   }
   else
   {
      for(i = 0; aMap[i].name; i++)
         if(aMap[i].sc == (code & 0xFF)) { name = aMap[i].name; break; }
   }
   if(name)
   {
      strncpy(buf, name, cBuf - 1);
      buf[cBuf - 1] = 0;
   }
   else if(cBuf >= 8)
      sprintf(buf, "Key 0x%02X", code & 0xFF);
}

/* ----------------------------------------------------------------- joystick */

void KmInit(void)
{
   ULONG             action, dataLen;
   GAME_PARM_STRUCT  parms;
   GAME_CALIB_STRUCT calib;
   KMCFG             c;
   ULONG             cb = sizeof(c);

   memset(&cfg, 0, sizeof(cfg));
   kmDefaults(&cfg, 1, 1);

   if(DosOpen(GAMEPDDNAME, &hGame, &action, 0, FILE_READONLY, FILE_OPEN,
              OPEN_ACCESS_READONLY | OPEN_SHARE_DENYNONE, NULL) != NO_ERROR)
      hGame = 0;
   else
   {
      dataLen = sizeof(parms);
      if(DosDevIOCtl(hGame, IOCTL_CAT_USER, GAME_GET_PARMS, NULL, 0, NULL, &parms, dataLen, &dataLen) != NO_ERROR)
      {
         DosClose(hGame);
         hGame = 0;
      }
   }
   if(hGame != 0)
   {
      bJoyAvail[0] = (parms.useA & GAME_USE_BOTH_NEWMASK) != 0;
      bJoyAvail[1] = (parms.useB & GAME_USE_BOTH_NEWMASK) != 0;
      dataLen = sizeof(calib);
      if(DosDevIOCtl(hGame, IOCTL_CAT_USER, GAME_GET_CALIB, NULL, 0, NULL, &calib, dataLen, &dataLen) == NO_ERROR)
      {
         joyCal[1].x = calib.Ax.centre;  joyCal[1].y = calib.Ay.centre;
         joyCal[2].x = calib.Bx.centre;  joyCal[2].y = calib.By.centre;
      }
   }

   /* saved mapping */
   if(PrfQueryProfileData(HINI_USERPROFILE, (PSZ)KM_APP, (PSZ)"KeyMap", &c, &cb) && cb == sizeof(c) && c.ver == 1)
   {
      int i, ok = 1;

      for(i = 0; i < KM_NACT; i++)
      {
         if(c.act[i] < 0 || c.act[i] > 8) ok = 0;
         if(!kmKeyAllowed(c.key[i])) ok = 0;
      }
      if(c.stick < 1 || c.stick > 2) ok = 0;
      if(c.enabled < 0 || c.enabled > 1) ok = 0;
      if(ok)
         cfg = c;
   }
   if(!hGame)
      cfg.enabled = 0;
}

void KmDone(void)
{
   if(hGame)
   {
      HFILE h = hGame;
      hGame = 0;
      DosClose(h);
   }
}

static void kmSave(void)
{
   PrfWriteProfileData(HINI_USERPROFILE, (PSZ)KM_APP, (PSZ)"KeyMap", &cfg, sizeof(cfg));
}

BOOL KmJoyEnabled(void)
{
   return cfg.enabled && hGame;
}

/* once per game timer tick */
void KmJoyPoll(void)
{
   ULONG len = sizeof(joyNow);

   if(!KmJoyEnabled())
   {
      bJoyNow = FALSE;
      return;
   }
   bJoyNow = DosDevIOCtl(hGame, IOCTL_CAT_USER, GAME_GET_STATUS, NULL, 0, NULL, &joyNow, len, &len) == NO_ERROR;
}

BOOL KmJoyDown(int iAct)
{
   int c, dX, dY, tolX, tolY;
   GAME_2DPOS_STRUCT *jd, *cal;

   if(!bJoyNow || iAct < 0 || iAct >= KM_NACT)
      return FALSE;
   c = cfg.act[iAct];
   if(c == 0)
      return FALSE;
   if(c >= 1 && c <= 4)
      return (joyNow.curdata.butMask & usButBit[c - 1]) == 0;

   jd  = (cfg.stick == 1) ? &joyNow.curdata.A : &joyNow.curdata.B;
   cal = &joyCal[cfg.stick];
   tolX = abs((int)cal->x) / 10 + 1;
   tolY = abs((int)cal->y) / 10 + 1;
   if(tolX < 16) tolX = 16;
   if(tolY < 16) tolY = 16;
   dX = (int)jd->x - (int)cal->x;
   dY = (int)jd->y - (int)cal->y;
   switch(c)
   {
      case JOY_AXIS_L: return dX < -tolX;
      case JOY_AXIS_R: return dX >  tolX;
      case JOY_AXIS_U: return dY < -tolY;
      case JOY_AXIS_D: return dY >  tolY;
   }
   return FALSE;
}

/* ============================================================== dialogs */

#define WM_KM_INPUT   (WM_USER + 1)

typedef struct _KMDATA
{
   KMCFG  c;                 /* working copy */
   HWND   hwndKbd, hwndJoy;
   HWND   hwndNB;
   ULONG  ulKbdPage, ulJoyPage;
}KMDATA, *PKMDATA;

/* Enable or disable every child of hwnd except the given id */
static void kmEnableChildren(HWND hwnd, USHORT id1, BOOL en)
{
   HENUM  he = WinBeginEnumWindows(hwnd);
   HWND   hc;

   while((hc = WinGetNextWindow(he)) != NULLHANDLE)
   {
      if(WinQueryWindowUShort(hc, QWS_ID) != id1)
         WinEnableWindow(hc, en);
   }
   WinEndEnumWindows(he);
}

static PFNWP pfnEntryOrig;

/* Keys pressed in a mapping box go to the owning page as a key code */
static MRESULT EXPENTRY KmEntryProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   HWND   hwndOwner = WinQueryWindow(hwnd, QW_OWNER);
   USHORT id        = WinQueryWindowUShort(hwnd, QWS_ID);

   if(msg == WM_CHAR)
   {
      USHORT fs = SHORT1FROMMP(mp1);
      USHORT vk = SHORT2FROMMP(mp2);

      if(fs & (KC_ALT | KC_CTRL))
         return pfnEntryOrig(hwnd, msg, mp1, mp2);
      if((fs & KC_VIRTUALKEY) && (vk == VK_TAB || vk == VK_BACKTAB || vk == VK_ESC || vk == VK_F1))
         return pfnEntryOrig(hwnd, msg, mp1, mp2);
      if(!(fs & KC_KEYUP))
         WinSendMsg(hwndOwner, WM_KM_INPUT, MPFROMSHORT(id),
                    MPFROMLONG(kmKeyCode(fs, vk, CHAR4FROMMP(mp1))));
      return (MRESULT)TRUE;
   }
   return pfnEntryOrig(hwnd, msg, mp1, mp2);
}

static void kmSubclass(HWND hwndBox)
{
   PFNWP p = WinSubclassWindow(hwndBox, KmEntryProc);

   if(pfnEntryOrig == NULL)
      pfnEntryOrig = p;
}

/* ------------------------------------------------------------- keyboard page */

static void kbdShowAll(HWND hwnd, PKMDATA wd)
{
   char buf[24];
   int i;

   for(i = 0; i < KM_NACT; i++)
   {
      kmKeyName(wd->c.key[i], buf, sizeof(buf));
      WinSetDlgItemText(hwnd, (USHORT)(IDC_KM_KBOX + i), (PSZ)buf);
   }
}

static MRESULT EXPENTRY KbdPageProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   PKMDATA wd = (PKMDATA)WinQueryWindowULong(hwnd, QWL_USER);
   int i;

   switch(msg)
   {
      case WM_INITDLG:
         wd = (PKMDATA)mp2;
         WinSetWindowULong(hwnd, QWL_USER, (ULONG)wd);
         WinSetDlgItemText(hwnd, IDC_KM_KH, (PSZ)kmText(KMS_KBD_H));
         for(i = 0; i < KM_NACT; i++)
         {
            WinSetDlgItemText(hwnd, (USHORT)(IDC_KM_KLBL + i), (PSZ)kmText(KMS_LEFT + i));
            kmSubclass(WinWindowFromID(hwnd, (USHORT)(IDC_KM_KBOX + i)));
         }
         kbdShowAll(hwnd, wd);
         return (MRESULT)FALSE;

      case WM_KM_INPUT:
         {
            int r = (int)SHORT1FROMMP(mp1) - IDC_KM_KBOX;
            int code = (int)LONGFROMMP(mp2);

            if(r >= 0 && r < KM_NACT)
            {
               if(kmKeyAllowed(code))
               {
                  int j;

                  for(j = 0; j < KM_NACT; j++)
                     if(j != r && wd->c.key[j] == code)
                        wd->c.key[j] = wd->c.key[r];       /* swap with the move that had it */
                  wd->c.key[r] = code;
                  kbdShowAll(hwnd, wd);
               }
               else
                  WinAlarm(HWND_DESKTOP, WA_WARNING);
            }
         }
         return (MRESULT)TRUE;

      case WM_COMMAND:
         if(SHORT1FROMMP(mp1) == BN_KM_DEFAULTS)
         {
            kmDefaults(&wd->c, 1, 0);
            kbdShowAll(hwnd, wd);
         }
         return 0;
   }
   return WinDefDlgProc(hwnd, msg, mp1, mp2);
}

/* ------------------------------------------------------------- joystick page */

static void joyShowAll(HWND hwnd, PKMDATA wd)
{
   int i;

   for(i = 0; i < KM_NACT; i++)
      WinSetDlgItemText(hwnd, (USHORT)(IDC_KM_JBOX + i), (PSZ)kmJoyLabel(wd->c.act[i]));
}

/* the stick choice and Calibrate follow what the driver reports */
static void joyEnableState(HWND hwnd, PKMDATA wd)
{
   BOOL en = wd->c.enabled != 0;

   kmEnableChildren(hwnd, IDC_KM_JEN, en);
   WinEnableWindow(WinWindowFromID(hwnd, IDC_KM_JCALA), en && hGame && bJoyAvail[0]);
   WinEnableWindow(WinWindowFromID(hwnd, IDC_KM_JCALB), en && hGame && bJoyAvail[1]);
   if(!hGame)
      WinEnableWindow(WinWindowFromID(hwnd, IDC_KM_JEN), FALSE);
   if(!bJoyAvail[0])
      WinEnableWindow(WinWindowFromID(hwnd, IDC_KM_JPA), FALSE);
   if(!bJoyAvail[1])
      WinEnableWindow(WinWindowFromID(hwnd, IDC_KM_JPB), FALSE);
}

static void joyCalibrate(HWND hwnd, int stick)
{
   char szMsg[160], szTitle[160];
   char ch = (stick == 1) ? 'A' : 'B';

   if(!hGame)
      return;
   sprintf(szMsg,   kmText(KMS_CAL_MSG),   ch);
   sprintf(szTitle, kmText(KMS_CAL_TITLE), ch);
   if(WinMessageBox(HWND_DESKTOP, hwnd, (PSZ)szMsg, (PSZ)szTitle, 0, MB_OKCANCEL | MB_INFORMATION) == MBID_OK)
   {
      GAME_STATUS_STRUCT s;
      ULONG len = sizeof(s);

      if(DosDevIOCtl(hGame, IOCTL_CAT_USER, GAME_GET_STATUS, NULL, 0, NULL, &s, len, &len) == NO_ERROR)
      {
         if(stick == 1) { joyCal[1].x = s.curdata.A.x; joyCal[1].y = s.curdata.A.y; }
         else           { joyCal[2].x = s.curdata.B.x; joyCal[2].y = s.curdata.B.y; }
      }
   }
}

static MRESULT EXPENTRY JoyPageProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   PKMDATA wd = (PKMDATA)WinQueryWindowULong(hwnd, QWL_USER);
   static int    iSelRow;
   static USHORT usPrevButs;
   static BOOL   bPAxL, bPAxR, bPAxU, bPAxD;
   int i;

   switch(msg)
   {
      case WM_INITDLG:
         wd = (PKMDATA)mp2;
         WinSetWindowULong(hwnd, QWL_USER, (ULONG)wd);
         iSelRow = -1;
         usPrevButs = 0xFFFF;
         bPAxL = bPAxR = bPAxU = bPAxD = FALSE;

         WinSetDlgItemText(hwnd, IDC_KM_JEN,  (PSZ)kmText(KMS_JOY_EN));
         WinSetDlgItemText(hwnd, IDC_KM_JH1,  (PSZ)kmText(KMS_JOY_H1));
         WinSetDlgItemText(hwnd, IDC_KM_JH2,  (PSZ)kmText(KMS_JOY_H2));
         WinSetDlgItemText(hwnd, IDC_KM_JP,   (PSZ)kmText(KMS_TAB_JOY));
         WinSetDlgItemText(hwnd, IDC_KM_JPA,  (PSZ)kmText(KMS_JOY_A));
         WinSetDlgItemText(hwnd, IDC_KM_JPB,  (PSZ)kmText(KMS_JOY_B));
         WinSetDlgItemText(hwnd, IDC_KM_JCALA, (PSZ)kmText(KMS_CAL_A));
         WinSetDlgItemText(hwnd, IDC_KM_JCALB, (PSZ)kmText(KMS_CAL_B));
         for(i = 0; i < KM_NACT; i++)
         {
            WinSetDlgItemText(hwnd, (USHORT)(IDC_KM_JLBL + i), (PSZ)kmText(KMS_LEFT + i));
            kmSubclass(WinWindowFromID(hwnd, (USHORT)(IDC_KM_JBOX + i)));
         }
         WinSendDlgItemMsg(hwnd, IDC_KM_JEN, BM_SETCHECK, MPFROMSHORT(wd->c.enabled != 0), MPVOID);
         WinSendDlgItemMsg(hwnd, wd->c.stick == 2 ? IDC_KM_JPB : IDC_KM_JPA, BM_SETCHECK, MPFROMSHORT(1), MPVOID);
         joyShowAll(hwnd, wd);
         joyEnableState(hwnd, wd);
         WinStartTimer(WinQueryAnchorBlock(hwnd), hwnd, 1, 50);
         return (MRESULT)FALSE;

      case WM_TIMER:
         /* a new button press or stick direction goes to the focused box */
         if(hGame && wd->c.enabled && iSelRow >= 0)
         {
            GAME_STATUS_STRUCT s;
            ULONG len = sizeof(s);

            if(DosDevIOCtl(hGame, IOCTL_CAT_USER, GAME_GET_STATUS, NULL, 0, NULL, &s, len, &len) == NO_ERROR)
            {
               GAME_2DPOS_STRUCT *jd  = (wd->c.stick == 1) ? &s.curdata.A : &s.curdata.B;
               GAME_2DPOS_STRUCT *cal = &joyCal[wd->c.stick];
               int tolX = abs((int)cal->x) / 10 + 1, tolY = abs((int)cal->y) / 10 + 1;
               int dX, dY;
               USHORT curButs = s.curdata.butMask;
               USHORT pressed = usPrevButs & ~curButs;
               BOOL axL, axR, axU, axD;
               int newAct = 0;

               if(tolX < 16) tolX = 16;
               if(tolY < 16) tolY = 16;
               dX = (int)jd->x - (int)cal->x;
               dY = (int)jd->y - (int)cal->y;
               axL = dX < -tolX;  axR = dX > tolX;  axU = dY < -tolY;  axD = dY > tolY;

               if(pressed)
                  for(i = 0; i < 4; i++)
                     if(pressed & usButBit[i]) { newAct = i + 1; break; }
               if(!newAct)
               {
                  if(axL && !bPAxL) newAct = JOY_AXIS_L;
                  else if(axR && !bPAxR) newAct = JOY_AXIS_R;
                  else if(axU && !bPAxU) newAct = JOY_AXIS_U;
                  else if(axD && !bPAxD) newAct = JOY_AXIS_D;
               }
               if(newAct)
               {
                  wd->c.act[iSelRow] = newAct;
                  WinSetDlgItemText(hwnd, (USHORT)(IDC_KM_JBOX + iSelRow), (PSZ)kmJoyLabel(newAct));
               }
               usPrevButs = curButs;
               bPAxL = axL; bPAxR = axR; bPAxU = axU; bPAxD = axD;
            }
         }
         return 0;

      case WM_KM_INPUT:
         {
            int r = (int)SHORT1FROMMP(mp1) - IDC_KM_JBOX;
            int code = (int)LONGFROMMP(mp2);

            if(r >= 0 && r < KM_NACT && (code == (0x100 | VK_BACKSPACE) || code == (0x100 | VK_DELETE)))
            {
               wd->c.act[r] = 0;
               WinSetDlgItemText(hwnd, (USHORT)(IDC_KM_JBOX + r), (PSZ)kmJoyLabel(0));
            }
         }
         return (MRESULT)TRUE;

      case WM_CONTROL:
         if(SHORT1FROMMP(mp1) >= IDC_KM_JBOX && SHORT1FROMMP(mp1) < IDC_KM_JBOX + KM_NACT)
         {
            if(SHORT2FROMMP(mp1) == EN_SETFOCUS)
               iSelRow = SHORT1FROMMP(mp1) - IDC_KM_JBOX;
            else if(SHORT2FROMMP(mp1) == EN_KILLFOCUS)
               iSelRow = -1;
            return 0;
         }
         if(SHORT2FROMMP(mp1) == BN_CLICKED)
         {
            switch(SHORT1FROMMP(mp1))
            {
               case IDC_KM_JEN:
                  wd->c.enabled = (int)(SHORT)(ULONG)WinSendDlgItemMsg(hwnd, IDC_KM_JEN, BM_QUERYCHECK, MPVOID, MPVOID) != 0;
                  joyEnableState(hwnd, wd);
                  break;
               case IDC_KM_JPA: wd->c.stick = 1; break;
               case IDC_KM_JPB: wd->c.stick = 2; break;
            }
         }
         return 0;

      case WM_COMMAND:
         switch(SHORT1FROMMP(mp1))
         {
            case IDC_KM_JCALA: joyCalibrate(hwnd, 1); break;
            case IDC_KM_JCALB: joyCalibrate(hwnd, 2); break;
            case BN_KM_DEFAULTS:
               kmDefaults(&wd->c, 0, 1);
               WinSendDlgItemMsg(hwnd, IDC_KM_JPA, BM_SETCHECK, MPFROMSHORT(1), MPVOID);
               WinSendDlgItemMsg(hwnd, IDC_KM_JPB, BM_SETCHECK, MPFROMSHORT(0), MPVOID);
               joyShowAll(hwnd, wd);
               break;
         }
         return 0;

      case WM_DESTROY:
         WinStopTimer(WinQueryAnchorBlock(hwnd), hwnd, 1);
         return 0;
   }
   return WinDefDlgProc(hwnd, msg, mp1, mp2);
}

/* --------------------------------------------------------------- main dialog */

static void kmSizeNotebook(HWND hwnd, PKMDATA wd)
{
   SWP swpBtn, swpDlg;

   WinQueryWindowPos(hwnd, &swpDlg);
   WinQueryWindowPos(WinWindowFromID(hwnd, DID_OK), &swpBtn);
   WinSetWindowPos(wd->hwndNB, HWND_TOP,
      4, swpBtn.y + swpBtn.cy + 4,
      swpDlg.cx - 8,
      swpDlg.cy - (swpBtn.y + swpBtn.cy + 4) - 4 - WinQuerySysValue(HWND_DESKTOP, SV_CYTITLEBAR),
      SWP_MOVE | SWP_SIZE);
}

static MRESULT EXPENTRY KeyMapDlgProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
   PKMDATA wd = (PKMDATA)WinQueryWindowULong(hwnd, QWL_USER);

   switch(msg)
   {
      case WM_INITDLG:
         {
            SWP swpFr;

            wd = (PKMDATA)mp2;
            WinSetWindowULong(hwnd, QWL_USER, (ULONG)wd);

            WinSetWindowText(hwnd, (PSZ)kmText(KMS_TITLE));
            WinSetDlgItemText(hwnd, DID_OK,         (PSZ)kmText(KMS_OK));
            WinSetDlgItemText(hwnd, DID_CANCEL,     (PSZ)kmText(KMS_CANCEL));
            WinSetDlgItemText(hwnd, BN_KM_DEFAULTS, (PSZ)kmText(KMS_DEFAULT));
            WinQueryWindowPos(hwnd, &swpFr);
            WinSetWindowPos(hwnd, HWND_TOP,
               (WinQuerySysValue(HWND_DESKTOP, SV_CXSCREEN) - swpFr.cx) / 2,
               (WinQuerySysValue(HWND_DESKTOP, SV_CYSCREEN) - swpFr.cy) / 2,
               0, 0, SWP_MOVE | SWP_ACTIVATE);

            wd->hwndNB = WinCreateWindow(hwnd, WC_NOTEBOOK, (PSZ)"",
                           BKS_TABBEDDIALOG | BKS_BACKPAGESBR | WS_VISIBLE | WS_TABSTOP,
                           0, 0, 1, 1, hwnd, HWND_TOP, IDC_KM_NB, NULL, NULL);
            if(wd->hwndNB == NULLHANDLE)
            {
               WinDismissDlg(hwnd, DID_CANCEL);
               return (MRESULT)FALSE;
            }
            kmSizeNotebook(hwnd, wd);
            WinSendMsg(wd->hwndNB, BKM_SETNOTEBOOKCOLORS,
                       MPFROMLONG(WinQuerySysColor(HWND_DESKTOP, SYSCLR_DIALOGBACKGROUND, 0)),
                       MPFROMSHORT(BKA_BACKGROUNDPAGECOLOR));

            wd->ulKbdPage = (ULONG)WinSendMsg(wd->hwndNB, BKM_INSERTPAGE, NULL, MPFROM2SHORT(BKA_AUTOPAGESIZE | BKA_MAJOR, BKA_LAST));
            WinSendMsg(wd->hwndNB, BKM_SETTABTEXT, MPFROMLONG(wd->ulKbdPage), MPFROMP(kmText(KMS_TAB_KBD)));
            wd->ulJoyPage = (ULONG)WinSendMsg(wd->hwndNB, BKM_INSERTPAGE, NULL, MPFROM2SHORT(BKA_AUTOPAGESIZE | BKA_MAJOR, BKA_LAST));
            WinSendMsg(wd->hwndNB, BKM_SETTABTEXT, MPFROMLONG(wd->ulJoyPage), MPFROMP(kmText(KMS_TAB_JOY)));

            wd->hwndKbd = WinLoadDlg(wd->hwndNB, wd->hwndNB, KbdPageProc, NULLHANDLE, DLG_KM_KBD, wd);
            WinSendMsg(wd->hwndNB, BKM_SETPAGEWINDOWHWND, MPFROMLONG(wd->ulKbdPage), MPFROMHWND(wd->hwndKbd));
            wd->hwndJoy = WinLoadDlg(wd->hwndNB, wd->hwndNB, JoyPageProc, NULLHANDLE, DLG_KM_JOY, wd);
            WinSendMsg(wd->hwndNB, BKM_SETPAGEWINDOWHWND, MPFROMLONG(wd->ulJoyPage), MPFROMHWND(wd->hwndJoy));

            WinSendMsg(wd->hwndNB, BKM_TURNTOPAGE, MPFROMLONG(wd->ulKbdPage), MPVOID);
         }
         return (MRESULT)FALSE;

      case WM_SIZE:
         if(wd && wd->hwndNB)
            kmSizeNotebook(hwnd, wd);
         break;

      case WM_COMMAND:
         switch(SHORT1FROMMP(mp1))
         {
            case DID_OK:
               WinDismissDlg(hwnd, DID_OK);
               return 0;
            case DID_CANCEL:
               WinDismissDlg(hwnd, DID_CANCEL);
               return 0;
            case BN_KM_DEFAULTS:
               WinSendMsg(wd->hwndKbd, WM_COMMAND, MPFROMSHORT(BN_KM_DEFAULTS), MPVOID);
               WinSendMsg(wd->hwndJoy, WM_COMMAND, MPFROMSHORT(BN_KM_DEFAULTS), MPVOID);
               return 0;
         }
         return 0;
   }
   return WinDefDlgProc(hwnd, msg, mp1, mp2);
}

void KmDialog(HWND hwndOwner)
{
   KMDATA wd;

   memset(&wd, 0, sizeof(wd));
   wd.c = cfg;
   pfnEntryOrig = NULL;

   if(WinDlgBox(HWND_DESKTOP, hwndOwner, KeyMapDlgProc, NULLHANDLE, IDD_KEY_MAPPING, &wd) == DID_OK)
   {
      cfg = wd.c;
      if(!hGame)
         cfg.enabled = 0;
      kmSave();
   }
}
