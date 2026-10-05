# Ribble for OS/2

Boulder Dash style puzzle game for OS/2 and ArcaOS, modernized and
rebuilt as a 32-bit Presentation Manager application with Open Watcom.

![Ribble ScreenShot](/doc/Ribble.png)

## Status

**Version 1.1** (2026-10-04). Builds with Open Watcom C++ 2.0.1 on
ArcaOS, runs on the desktop.

## Building

On ArcaOS with Open Watcom installed:

    compile-wat.cmd

Requires OS/2 Toolkit 4.5 headers (`C:\OS2TK45\h`) and `wmake` 2.0.1
(no pattern rules; explicit per-file rules are in `makefile.wat`).

## Controls

- Arrow keys: move; Space or Ctrl+M: toggle map; Ctrl+T: status bar
- Ctrl+N New Game, Ctrl+O Open, Ctrl+S Save
- Ctrl+Q End Game, Ctrl+X Exit

## Options

- Options > Settings...: game and control settings
- Options > Language: Switch between English, Spanish, Dutch, German,
  French and Italian (stored in the OS/2 user profile; also switches
  the online help language, shipped per language in `bin/help/`)
- Options > Save settings on exit

## Layout

- `src/` sources, `bin/` build output, `doc/` documentation,
  `help/` help sources, `levels/` game levels, `legacy/` original source

## License

GNU General Public License v3. See `doc/LICENSE.txt`.

Original Ribble copyright (c) 1993, 1994 J.R. Shannon and D.J. Neades.
