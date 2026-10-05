.SUFFIXES: .cpp .dll

SUPPORT_SRC_DIR  = \src\support\     #
SUPPORT_INCL_DIR = \src\support\     #

SUPPORT_INCL = \
 $(SUPPORT_INCL_DIR)cassert.h     \
 $(SUPPORT_INCL_DIR)CSTRNG.H      \
 $(SUPPORT_INCL_DIR)cthread.h     \
 $(SUPPORT_INCL_DIR)CUMtxSem.h    \
 $(SUPPORT_INCL_DIR)makepath.h    

SUPPORT_OBJS = \
 cff.obj       \
 cstrng.obj    \
 cassert.obj   \
 fpgline.obj   \
 cumtxsem.obj  \
 cthread.obj   \
 makepath.obj  \
 cbr.obj

SUPPORT_REALDEF =  \
 $(SUPPORT_SRC_DIR)supportdef

SUPPORT_DEF =  \
 support.def

SUPPORT_LIBS = 

OPT_FLAG = #-O -Oi -Os
DEB_FLAG = -Ti
DEBC_FLAG = $(DEB_FLAG) $(OPT_FLAG) -D_CSET2=1 -Ft+ -Gd+ -Wall -Wcls- -Wgnr- -Wvft-
DEBL_FLAG = /de 

SUPPORT_COPT    = $(DEBC_FLAG) -I\src\support -J- -Q -Fi -Si -Gm+ -Ge- -D_MAKE_SUPPORTDLL_=1
SUPPORT_LINKOPT = -Tdp -B" $(DEBL_FLAG) /noi /noe /nologo /m:full"

all: support.lib

support.lib: support.dll
  implib /NOI /NOL $@ support.dll

support.dll: $(SUPPORT_OBJS)
  copy $(SUPPORT_REALDEF) $(SUPPORT_DEF)
  cppfilt /B /X /Q $(SUPPORT_OBJS) >>$(SUPPORT_DEF)
  icc $(SUPPORT_COPT) $(SUPPORT_LINKOPT) -Fe$@ $(SUPPORT_OBJS) $(SUPPORT_DEF) $(SUPPORT_LIBS) 2>&1 | ggrep -v conflict
  cppfilt /q $*.map >filtered.map
  mv filtered.map $*.map

$(SUPPORT_OBJS) : $(SUPPORT_INCL)

{$(SUPPORT_SRC_DIR)}.cpp.obj:
  icc $(SUPPORT_COPT) -c $<

