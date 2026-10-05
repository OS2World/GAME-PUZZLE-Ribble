# Makefile for Ribble (Open Watcom C++ on OS/2 / ArcaOS)
# wmake 2.0.1 on ArcaOS - explicit per-file rules (no pattern rules)

# ============================================================================
# Configuration
# ============================================================================

NAME    = Ribble
SRCDIR  = src
BINDIR  = bin

!ifndef WATCOM
WATCOM  = C:\WATCOM
!endif

!ifndef OS2TK
OS2TK   = C:\OS2TK45
!endif

# ============================================================================
# Tools
# ============================================================================

CCPP    = wpp386
LINK    = wlink
RC      = wrc

# ============================================================================
# Flags (per plan.txt section 2)
# ============================================================================

CFLAGS  = -bt=os2 -bm -mf -5 -fpi -Oaxt -W3 -ze -d0
CFLAGS  = $(CFLAGS) -i=$(OS2TK)\h -i=$(SRCDIR) -i=$(SRCDIR)\win -i=help

RCFLAGS = -r -bt=os2 -i=$(OS2TK)\h -i=$(SRCDIR) -i=$(SRCDIR)\bitmaps -i=help

LFLAGS  = system os2v2 pm
LFLAGS  = $(LFLAGS) option stack=65536
LFLAGS  = $(LFLAGS) option map=$(BINDIR)\$(NAME).map

# ============================================================================
# Source files
# ============================================================================

SUPPORT_OBJS = $(BINDIR)\cwindow.obj $(BINDIR)\cdialog.obj $(BINDIR)\makepath.obj $(BINDIR)\fpgline.obj $(BINDIR)\cumtxsem.obj $(BINDIR)\cthread.obj $(BINDIR)\cstrng.obj $(BINDIR)\cff.obj $(BINDIR)\cbr.obj $(BINDIR)\cassert.obj

GAME_OBJS = $(BINDIR)\about.obj $(BINDIR)\bomb.obj $(BINDIR)\config.obj $(BINDIR)\edit.obj $(BINDIR)\game.obj $(BINDIR)\hiscore.obj $(BINDIR)\level.obj $(BINDIR)\mainwin.obj $(BINDIR)\man.obj $(BINDIR)\map.obj $(BINDIR)\monster.obj $(BINDIR)\options.obj $(BINDIR)\pal.obj $(BINDIR)\registry.obj $(BINDIR)\save.obj $(BINDIR)\screen.obj $(BINDIR)\slither.obj $(BINDIR)\spirit.obj $(BINDIR)\teleport.obj

OBJS    = $(SUPPORT_OBJS) $(GAME_OBJS)

ROBJ    = $(BINDIR)\$(NAME).res
RCFILE  = $(SRCDIR)\$(NAME).rc
DEFFILE = $(SRCDIR)\$(NAME).def

# ============================================================================
# Targets
# ============================================================================

all : $(BINDIR)\$(NAME).exe .SYMBOLIC

$(BINDIR) :
	@if not exist $(BINDIR) mkdir $(BINDIR)

$(BINDIR)\$(NAME).exe : $(OBJS) $(ROBJ) $(DEFFILE)
	@echo Linking $(NAME).exe...
	@$(LINK) $(LFLAGS) name $(BINDIR)\$(NAME).exe file $(BINDIR)\*.obj library os2386.lib
	@echo Binding resources...
	@$(RC) -q -bt=os2 -fe=$(BINDIR)\$(NAME).exe $(ROBJ) $(BINDIR)\$(NAME).exe
	@if exist $(BINDIR)\$(NAME).exe echo BUILD OK

# ============================================================================
# Support library objects
# ============================================================================

$(BINDIR)\cwindow.obj : $(SRCDIR)\win\cwindow.cpp $(BINDIR)
	@echo Compiling src\win\cwindow.cpp
	@$(CCPP) $(CFLAGS) -fo=$@ $(SRCDIR)\win\cwindow.cpp

$(BINDIR)\cdialog.obj : $(SRCDIR)\win\cdialog.cpp $(BINDIR)
	@echo Compiling src\win\cdialog.cpp
	@$(CCPP) $(CFLAGS) -fo=$@ $(SRCDIR)\win\cdialog.cpp

$(BINDIR)\makepath.obj : $(SRCDIR)\makepath.cpp $(BINDIR)
	@echo Compiling src\makepath.cpp
	@$(CCPP) $(CFLAGS) -fo=$@ $(SRCDIR)\makepath.cpp

$(BINDIR)\fpgline.obj : $(SRCDIR)\fpgline.cpp $(BINDIR)
	@echo Compiling src\fpgline.cpp
	@$(CCPP) $(CFLAGS) -fo=$@ $(SRCDIR)\fpgline.cpp

$(BINDIR)\cumtxsem.obj : $(SRCDIR)\cumtxsem.cpp $(BINDIR)
	@echo Compiling src\cumtxsem.cpp
	@$(CCPP) $(CFLAGS) -fo=$@ $(SRCDIR)\cumtxsem.cpp

$(BINDIR)\cthread.obj : $(SRCDIR)\cthread.cpp $(BINDIR)
	@echo Compiling src\cthread.cpp
	@$(CCPP) $(CFLAGS) -fo=$@ $(SRCDIR)\cthread.cpp

$(BINDIR)\cstrng.obj : $(SRCDIR)\cstrng.cpp $(BINDIR)
	@echo Compiling src\cstrng.cpp
	@$(CCPP) $(CFLAGS) -fo=$@ $(SRCDIR)\cstrng.cpp

$(BINDIR)\cff.obj : $(SRCDIR)\cff.cpp $(BINDIR)
	@echo Compiling src\cff.cpp
	@$(CCPP) $(CFLAGS) -fo=$@ $(SRCDIR)\cff.cpp

$(BINDIR)\cbr.obj : $(SRCDIR)\cbr.cpp $(BINDIR)
	@echo Compiling src\cbr.cpp
	@$(CCPP) $(CFLAGS) -fo=$@ $(SRCDIR)\cbr.cpp

$(BINDIR)\cassert.obj : $(SRCDIR)\cassert.cpp $(BINDIR)
	@echo Compiling src\cassert.cpp
	@$(CCPP) $(CFLAGS) -fo=$@ $(SRCDIR)\cassert.cpp

# ============================================================================
# Game objects
# ============================================================================

$(BINDIR)\about.obj : $(SRCDIR)\about.cpp $(BINDIR)
	@echo Compiling src\about.cpp
	@$(CCPP) $(CFLAGS) -fo=$@ $(SRCDIR)\about.cpp

$(BINDIR)\bomb.obj : $(SRCDIR)\bomb.cpp $(BINDIR)
	@echo Compiling src\bomb.cpp
	@$(CCPP) $(CFLAGS) -fo=$@ $(SRCDIR)\bomb.cpp

$(BINDIR)\config.obj : $(SRCDIR)\config.cpp $(BINDIR)
	@echo Compiling src\config.cpp
	@$(CCPP) $(CFLAGS) -fo=$@ $(SRCDIR)\config.cpp

$(BINDIR)\edit.obj : $(SRCDIR)\edit.cpp $(BINDIR)
	@echo Compiling src\edit.cpp
	@$(CCPP) $(CFLAGS) -fo=$@ $(SRCDIR)\edit.cpp

$(BINDIR)\game.obj : $(SRCDIR)\game.cpp $(BINDIR)
	@echo Compiling src\game.cpp
	@$(CCPP) $(CFLAGS) -fo=$@ $(SRCDIR)\game.cpp

$(BINDIR)\hiscore.obj : $(SRCDIR)\hiscore.cpp $(BINDIR)
	@echo Compiling src\hiscore.cpp
	@$(CCPP) $(CFLAGS) -fo=$@ $(SRCDIR)\hiscore.cpp

$(BINDIR)\level.obj : $(SRCDIR)\level.cpp $(BINDIR)
	@echo Compiling src\level.cpp
	@$(CCPP) $(CFLAGS) -fo=$@ $(SRCDIR)\level.cpp

$(BINDIR)\mainwin.obj : $(SRCDIR)\mainwin.cpp $(BINDIR)
	@echo Compiling src\mainwin.cpp
	@$(CCPP) $(CFLAGS) -fo=$@ $(SRCDIR)\mainwin.cpp

$(BINDIR)\man.obj : $(SRCDIR)\man.cpp $(BINDIR)
	@echo Compiling src\man.cpp
	@$(CCPP) $(CFLAGS) -fo=$@ $(SRCDIR)\man.cpp

$(BINDIR)\map.obj : $(SRCDIR)\map.cpp $(BINDIR)
	@echo Compiling src\map.cpp
	@$(CCPP) $(CFLAGS) -fo=$@ $(SRCDIR)\map.cpp

$(BINDIR)\monster.obj : $(SRCDIR)\monster.cpp $(BINDIR)
	@echo Compiling src\monster.cpp
	@$(CCPP) $(CFLAGS) -fo=$@ $(SRCDIR)\monster.cpp

$(BINDIR)\options.obj : $(SRCDIR)\options.cpp $(BINDIR)
	@echo Compiling src\options.cpp
	@$(CCPP) $(CFLAGS) -fo=$@ $(SRCDIR)\options.cpp

$(BINDIR)\pal.obj : $(SRCDIR)\pal.cpp $(BINDIR)
	@echo Compiling src\pal.cpp
	@$(CCPP) $(CFLAGS) -fo=$@ $(SRCDIR)\pal.cpp

$(BINDIR)\registry.obj : $(SRCDIR)\registry.cpp $(BINDIR)
	@echo Compiling src\registry.cpp
	@$(CCPP) $(CFLAGS) -fo=$@ $(SRCDIR)\registry.cpp

$(BINDIR)\save.obj : $(SRCDIR)\save.cpp $(BINDIR)
	@echo Compiling src\save.cpp
	@$(CCPP) $(CFLAGS) -fo=$@ $(SRCDIR)\save.cpp

$(BINDIR)\screen.obj : $(SRCDIR)\screen.cpp $(BINDIR)
	@echo Compiling src\screen.cpp
	@$(CCPP) $(CFLAGS) -fo=$@ $(SRCDIR)\screen.cpp

$(BINDIR)\slither.obj : $(SRCDIR)\slither.cpp $(BINDIR)
	@echo Compiling src\slither.cpp
	@$(CCPP) $(CFLAGS) -fo=$@ $(SRCDIR)\slither.cpp

$(BINDIR)\spirit.obj : $(SRCDIR)\spirit.cpp $(BINDIR)
	@echo Compiling src\spirit.cpp
	@$(CCPP) $(CFLAGS) -fo=$@ $(SRCDIR)\spirit.cpp

$(BINDIR)\teleport.obj : $(SRCDIR)\teleport.cpp $(BINDIR)
	@echo Compiling src\teleport.cpp
	@$(CCPP) $(CFLAGS) -fo=$@ $(SRCDIR)\teleport.cpp

# ============================================================================
# Resources
# ============================================================================

$(ROBJ) : $(RCFILE) $(SRCDIR)\resources.h help\help.h $(SRCDIR)\ribble.ico $(BINDIR)
	@echo Compiling resources...
	@$(RC) $(RCFLAGS) -fo=$(ROBJ) $(RCFILE)

# ============================================================================
# Clean
# ============================================================================

clean : .SYMBOLIC
	@if exist $(BINDIR)\*.obj del $(BINDIR)\*.obj >nul
	@if exist $(BINDIR)\$(NAME).res del $(BINDIR)\$(NAME).res >nul
	@if exist $(BINDIR)\$(NAME).exe del $(BINDIR)\$(NAME).exe >nul
	@if exist $(BINDIR)\$(NAME).map del $(BINDIR)\$(NAME).map >nul
	@echo Clean complete