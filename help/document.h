#define USERDOC() :userdoc.
#define ENDDOC() :euserdoc.
#define TITLE(a) :title.a
#define HEADER(a, b, c) :h##a res=b.c
#define INDEX(a, b) :i##a.b
#define INDEXID(a, b, c) :i##a id=b.c
#define PARAGRAPH() :p.
#define BOLDON() :hp2.
#define BOLDOFF() :ehp2.
#define BOLD(a) :hp2.##a##:ehp2.
#define ITALICON() :hp1.
#define ITALICOFF() :ehp1.
#define ITALIC(a) :hp1.##a##:ehp1.
#define ARTWORK(fname) :artwork name=fname.
#define ARTALIGN(fname, balign) :artwork name=fname align=balign.
#define ARTINLINE(fname, balign) :artwork name=fname align=balign runin.
#define LINK(target, text) :link reftype=hd res=target.text :elink.
#define LINEBREAK() .br
#define LMARGIN(a) :lm margin=a.
#define RMARGIN(a) :rm margin=a.
#define SQBUL() &sqbul.
#define PERIOD() &per.
