//
// lang.h - language support for Ribble (plan.txt section 8)
//
// Language names and current-language strings are stored as ASCII only.
// Language NAMES are never translated (plan 8.3); every other submenu
// item and menu title IS translated.  The "About..." label is the
// standardized string and is identical in every language (plan 6.4).
//
// Copyright (c)1993, 1994 J.R.Shannon and D.J.Neades
// All rights reserved.
//

#ifndef _Lang_h
#define _Lang_h

#define LANG_ENGLISH   0
#define LANG_SPANISH   1
#define LANG_DUTCH     2
#define LANG_GERMAN    3
#define LANG_FRENCH    4
#define LANG_ITALIAN   5
#define NUM_LANGUAGES  6

#define STR_MENU_GAME          0
#define STR_MENU_MAPEDITOR     1
#define STR_MENU_VIEW          2
#define STR_MENU_OPTIONS       3
#define STR_MENU_HELP          4
#define STR_MENU_NEW           5
#define STR_MENU_END           6
#define STR_MENU_OPEN          7
#define STR_MENU_SAVE          8
#define STR_MENU_EXIT          9
#define STR_MENU_SETTINGS     10
#define STR_MENU_LANGUAGE     11
#define STR_MENU_SAVEONEXIT   12
#define STR_MENU_ABOUT        13
#define STR_MENU_LEVEL        14
#define STR_MENU_OPTIONSDLG   15
#define STR_MENU_VIEWMAP      16
#define STR_MENU_VIEWSTATUS   17
#define STR_MENU_FRAME        18
#define NUM_STRINGS           19

#ifndef LANG_NO_TABLES

static const char* LanguageStrings[NUM_LANGUAGES][NUM_STRINGS] =
{
  // English
  {
    "~Game",    "Map ~Editor", "~View",
    "~Options", "~Help",
    "~New Game\tCtrl+N", "~End Game\tCtrl+Q",
    "~Open...\tCtrl+O",  "~Save...\tCtrl+S",
    "E~xit\tCtrl+X",
    "~Settings...",      "~Language",
    "~Save settings on exit",
    "~About...",
    "~Level...",   "~Options...",
    "~Map...\tCtrl+M", "~Status...\tCtrl+T",
    "~Frame Controls\tCtrl+F"
  },
  // Spanish
  {
    "~Juego",     "~Editor de mapa",    "~Ver",
    "~Opciones",  "~Ayuda",
    "~Nuevo Juego\tCtrl+N", "~Terminar Juego\tCtrl+Q",
    "~Abrir...\tCtrl+O",    "~Guardar...\tCtrl+S",
    "S~alir\tCtrl+X",
    "~Ajustes...",   "~Idioma",
    "Guardar a~justes al salir",
    "~About...",
    "~Nivel...",    "~Opciones...",
    "~Mapa...\tCtrl+M",     "~Estado...\tCtrl+T",
    "~Frame Controls\tCtrl+F"
  },
  // Dutch
  {
    "~Spel",      "~Kaarteditor",  "~Beeld",
    "~Opties",    "~Help",
    "~Nieuw Spel\tCtrl+N",   "~Spel stoppen\tCtrl+Q",
    "~Openen...\tCtrl+O",    "~Opslaan...\tCtrl+S",
    "A~fsluiten\tCtrl+X",
    "~Instellingen...", "~Taal",
    "~Instellingen bij afsluiten opslaan",
    "~About...",
    "~Level...",   "~Opties...",
    "~Kaart...\tCtrl+M",   "~Status...\tCtrl+T",
    "~Frame Controls\tCtrl+F"
  },
  // German
  {
    "~Spiel",        "~Karteneditor",  "~Ansicht",
    "~Optionen",     "~Hilfe",
    "~Neues Spiel\tCtrl+N",  "~Spiel beenden\tCtrl+Q",
    "~Oeffnen...\tCtrl+O",   "~Speichern...\tCtrl+S",
    "~Beenden\tCtrl+X",
    "~Einstellungen...", "~Sprache",
    "Einstellungen beim ~Beenden speichern",
    "~About...",
    "~Level...",   "~Optionen...",
    "~Uebersicht...\tCtrl+M", "~Status...\tCtrl+T",
    "~Frame Controls\tCtrl+F"
  },
  // French
  {
    "~Jeu",       "~Editeur de carte",     "~Affichage",
    "~Options",   "~Aide",
    "~Nouveau Jeu\tCtrl+N",   "~Fin de Jeu\tCtrl+Q",
    "~Ouvrir...\tCtrl+O",     "~Enregistrer...\tCtrl+S",
    "~Quitter\tCtrl+X",
    "~Parametres...", "~Langue",
    "Enregistrer les parametres en ~quittant",
    "~About...",
    "~Niveau...",  "~Options...",
    "~Carte...\tCtrl+M",   "~Statut...\tCtrl+T",
    "~Frame Controls\tCtrl+F"
  },
  // Italian
  {
    "~Gioco",    "~Editor di mappa",   "~Visualizza",
    "~Opzioni",  "~Aiuto",
    "~Nuovo Gioco\tCtrl+N",  "~Termina Gioco\tCtrl+Q",
    "~Apri...\tCtrl+O",      "~Salva...\tCtrl+S",
    "~Esci\tCtrl+X",
    "~Impostazioni...", "~Lingua",
    "Salva impostazioni all'~uscita",
    "~About...",
    "~Livello...",  "~Opzioni...",
    "~Mappa...\tCtrl+M",    "~Stato...\tCtrl+T",
    "~Frame Controls\tCtrl+F"
  }
};

#endif  /* LANG_NO_TABLES */

extern int current_lang;
void SetLanguage(int lang);
void ApplyLanguageMenu(void);

#endif