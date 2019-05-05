#=============================================================
#
#	RIBBLE.MAK - Makefile for project D:\src\ribble\bcos2\ribble.prj
#		Created on 09/07/94 at 01:24
#
#=============================================================

.AUTODEPEND

#=============================================================
#		Translator Definitions
#=============================================================
CC = bcc +RIBBLE.CFG
TASM = tasm.exe
TLIB = tlib.exe
TLINK = tlink
RC = brcc.exe
RB = rc.exe
LIBPATH = \BCOS2\LIB
INCLUDEPATH = \BCOS2\INCLUDE;..\ribble;..\help;..\..\support;..\..\support\win


#=============================================================
#		Implicit Rules
#=============================================================
.c.obj:
  $(CC) -c {$< }

.cpp.obj:
  $(CC) -c {$< }

.asm.obj:
  $(TASM) -Mx $*.asm,$*.obj

.rc.res:
  $(RC) -r $*.rc

#=============================================================
#		List Macros
#=============================================================
LINK_EXCLUDE =  \
 ribble.res

LINK_INCLUDE =  \
 ..\ribble\project.def \
 cwindow.obj \
 cdialog.obj \
 makepath.obj \
 fpgline.obj \
 cumtxsem.obj \
 cthread.obj \
 cstrng.obj \
 cff.obj \
 cbr.obj \
 cassert.obj \
 teleport.obj \
 spirit.obj \
 slither.obj \
 screen.obj \
 save.obj \
 registry.obj \
 pal.obj \
 options.obj \
 monster.obj \
 map.obj \
 man.obj \
 mainwin.obj \
 level.obj \
 hiscore.obj \
 game.obj \
 edit.obj \
 config.obj \
 bomb.obj \
 about.obj

#=============================================================
#		Explicit Rules
#=============================================================
ribble.exe: ribble.cfg $(LINK_INCLUDE) $(LINK_EXCLUDE)
  $(TLINK) /B:0x10000 /c /s /Toe /aa /L$(LIBPATH) @&&|
\BCOS2\LIB\C02.OBJ+
cwindow.obj+
cdialog.obj+
makepath.obj+
fpgline.obj+
cumtxsem.obj+
cthread.obj+
cstrng.obj+
cff.obj+
cbr.obj+
cassert.obj+
teleport.obj+
spirit.obj+
slither.obj+
screen.obj+
save.obj+
registry.obj+
pal.obj+
options.obj+
monster.obj+
map.obj+
man.obj+
mainwin.obj+
level.obj+
hiscore.obj+
game.obj+
edit.obj+
config.obj+
bomb.obj+
about.obj
ribble,ribble
\BCOS2\LIB\C2MT.LIB+
\BCOS2\LIB\OS2.LIB
..\ribble\project.def
|
  rc.exe ribble.res ribble.exe

#=============================================================
#		Individual File Dependencies
#=============================================================
ribble.res: ribble.cfg ..\RIBBLE\RIBBLE.RC 
	brcc.exe -R -I$(INCLUDEPATH) -FO ribble.res ..\RIBBLE\RIBBLE.RC

cwindow.obj: ribble.cfg ..\..\support\Win\cwindow.cpp 
	$(CC) -c ..\..\support\Win\cwindow.cpp

cdialog.obj: ribble.cfg ..\..\support\Win\cdialog.cpp 
	$(CC) -c ..\..\support\Win\cdialog.cpp

makepath.obj: ribble.cfg ..\..\support\makepath.cpp 
	$(CC) -c ..\..\support\makepath.cpp

fpgline.obj: ribble.cfg ..\..\support\fpgline.cpp 
	$(CC) -c ..\..\support\fpgline.cpp

CUMtxSem.obj: ribble.cfg ..\..\support\CUMtxSem.cpp 
	$(CC) -c ..\..\support\CUMtxSem.cpp

cthread.obj: ribble.cfg ..\..\support\cthread.cpp 
	$(CC) -c ..\..\support\cthread.cpp

CSTRNG.obj: ribble.cfg ..\..\support\CSTRNG.CPP 
	$(CC) -c ..\..\support\CSTRNG.CPP

cff.obj: ribble.cfg ..\..\support\cff.cpp 
	$(CC) -c ..\..\support\cff.cpp

cbr.obj: ribble.cfg ..\..\support\cbr.cpp 
	$(CC) -c ..\..\support\cbr.cpp

cassert.obj: ribble.cfg ..\..\support\cassert.cpp 
	$(CC) -c ..\..\support\cassert.cpp

teleport.obj: ribble.cfg ..\Ribble\teleport.cpp 
	$(CC) -c ..\Ribble\teleport.cpp

spirit.obj: ribble.cfg ..\Ribble\spirit.cpp 
	$(CC) -c ..\Ribble\spirit.cpp

slither.obj: ribble.cfg ..\Ribble\slither.cpp 
	$(CC) -c ..\Ribble\slither.cpp

screen.obj: ribble.cfg ..\Ribble\screen.cpp 
	$(CC) -c ..\Ribble\screen.cpp

save.obj: ribble.cfg ..\Ribble\save.cpp 
	$(CC) -c ..\Ribble\save.cpp

registry.obj: ribble.cfg ..\Ribble\registry.cpp 
	$(CC) -c ..\Ribble\registry.cpp

pal.obj: ribble.cfg ..\Ribble\pal.cpp 
	$(CC) -c ..\Ribble\pal.cpp

options.obj: ribble.cfg ..\Ribble\options.cpp 
	$(CC) -c ..\Ribble\options.cpp

monster.obj: ribble.cfg ..\Ribble\monster.cpp 
	$(CC) -c ..\Ribble\monster.cpp

map.obj: ribble.cfg ..\Ribble\map.cpp 
	$(CC) -c ..\Ribble\map.cpp

man.obj: ribble.cfg ..\Ribble\man.cpp 
	$(CC) -c ..\Ribble\man.cpp

mainwin.obj: ribble.cfg ..\Ribble\mainwin.cpp 
	$(CC) -c ..\Ribble\mainwin.cpp

level.obj: ribble.cfg ..\Ribble\level.cpp 
	$(CC) -c ..\Ribble\level.cpp

hiscore.obj: ribble.cfg ..\Ribble\hiscore.cpp 
	$(CC) -c ..\Ribble\hiscore.cpp

game.obj: ribble.cfg ..\Ribble\game.cpp 
	$(CC) -c ..\Ribble\game.cpp

edit.obj: ribble.cfg ..\Ribble\edit.cpp 
	$(CC) -c ..\Ribble\edit.cpp

config.obj: ribble.cfg ..\Ribble\config.cpp 
	$(CC) -c ..\Ribble\config.cpp

bomb.obj: ribble.cfg ..\Ribble\bomb.cpp 
	$(CC) -c ..\Ribble\bomb.cpp

about.obj: ribble.cfg ..\Ribble\about.cpp 
	$(CC) -c ..\Ribble\about.cpp

#=============================================================
#		Compiler Configuration File
#=============================================================
ribble.cfg: ribble.mak
  copy &&|
-Oi
-Oz
-Ob
-Oe
-Oc
-L$(LIBPATH)
-I$(INCLUDEPATH)
-H=ribble.CSM
-vi
-sm
-d
-k-
-O
-Ot
-w
| ribble.cfg


