#=============================================================
#
#	INSTALL.MAK - Makefile for project D:\src\ribble\bcos2\install.prj
#		Created on 09/07/94 at 01:23
#
#=============================================================

.AUTODEPEND

#=============================================================
#		Translator Definitions
#=============================================================
CC = bcc +INSTALL.CFG
TASM = tasm.exe
TLIB = tlib.exe
TLINK = tlink
RC = brcc.exe
RB = rc.exe
LIBPATH = \BCOS2\LIB
INCLUDEPATH = \BCOS2\INCLUDE;..\install;..\..\support;..\..\support\win


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
 install.res

LINK_INCLUDE =  \
 ..\install\install.def \
 install.obj \
 cwindow.obj \
 cdialog.obj \
 makepath.obj \
 fpgline.obj \
 cumtxsem.obj \
 cthread.obj \
 cstrng.obj \
 cff.obj \
 cbr.obj \
 cassert.obj

#=============================================================
#		Explicit Rules
#=============================================================
install.exe: install.cfg $(LINK_INCLUDE) $(LINK_EXCLUDE)
  $(TLINK) /B:0x10000 /c /s /Toe /aa /L$(LIBPATH) @&&|
\BCOS2\LIB\C02.OBJ+
install.obj+
cwindow.obj+
cdialog.obj+
makepath.obj+
fpgline.obj+
cumtxsem.obj+
cthread.obj+
cstrng.obj+
cff.obj+
cbr.obj+
cassert.obj
install,install
\BCOS2\LIB\C2MT.LIB+
\BCOS2\LIB\OS2.LIB
..\install\install.def
|
  rc.exe install.res install.exe

#=============================================================
#		Individual File Dependencies
#=============================================================
install.res: install.cfg ..\INSTALL\INSTALL.RC 
	brcc.exe -R -I$(INCLUDEPATH) -FO install.res ..\INSTALL\INSTALL.RC

install.obj: install.cfg ..\install\install.cpp 
	$(CC) -c ..\install\install.cpp

cwindow.obj: install.cfg ..\..\support\Win\cwindow.cpp 
	$(CC) -c ..\..\support\Win\cwindow.cpp

cdialog.obj: install.cfg ..\..\support\Win\cdialog.cpp 
	$(CC) -c ..\..\support\Win\cdialog.cpp

makepath.obj: install.cfg ..\..\support\makepath.cpp 
	$(CC) -c ..\..\support\makepath.cpp

fpgline.obj: install.cfg ..\..\support\fpgline.cpp 
	$(CC) -c ..\..\support\fpgline.cpp

CUMtxSem.obj: install.cfg ..\..\support\CUMtxSem.cpp 
	$(CC) -c ..\..\support\CUMtxSem.cpp

cthread.obj: install.cfg ..\..\support\cthread.cpp 
	$(CC) -c ..\..\support\cthread.cpp

CSTRNG.obj: install.cfg ..\..\support\CSTRNG.CPP 
	$(CC) -c ..\..\support\CSTRNG.CPP

cff.obj: install.cfg ..\..\support\cff.cpp 
	$(CC) -c ..\..\support\cff.cpp

cbr.obj: install.cfg ..\..\support\cbr.cpp 
	$(CC) -c ..\..\support\cbr.cpp

cassert.obj: install.cfg ..\..\support\cassert.cpp 
	$(CC) -c ..\..\support\cassert.cpp

#=============================================================
#		Compiler Configuration File
#=============================================================
install.cfg: install.mak
  copy &&|
-Oi
-Oz
-Ob
-Oe
-Oc
-L$(LIBPATH)
-I$(INCLUDEPATH)
-H=install.CSM
-vi
-sm
-d
-k-
-O
-Ot
-w
| install.cfg


