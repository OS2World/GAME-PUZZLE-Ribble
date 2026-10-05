@echo off
set WATCOM=C:\WATCOM
set PATH=C:\WATCOM\binp;%PATH%
set INCLUDE=C:\OS2TK45\h;C:\WATCOM\h
cd D:\Projects\Games\GAME-PUZZLE-Ribble\tools
C:\WATCOM\binp\wpp386 -bt=os2 -mf -5 -fpi -d0 -i=C:\OS2TK45\h -zq pidprobe.c -fo=pidprobe.obj
C:\WATCOM\binp\wlink system os2v2 name pidprobe.exe file pidprobe.obj library os2386.lib
echo BUILD-PROBE-DONE