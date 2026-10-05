#ifndef _CSupport_h
#define _CSupport_h

#ifdef _MAKE_SUPPORTDLL_
  #if defined(__OS2__)
    #if defined(__BORLANDC__)
      #define CSExport _export
    #elif defined(__WATCOMC__)
      #define CSExport __export
    #else
      #define CSExport _Export
    #endif
  #else
    #define CSExport _export
  #endif
#else
    #define CSExport 
#endif

#if defined(__OS2__)
  #define CSHuge
  #if defined(__OS2__)
    #define farmalloc malloc
    #define farfree free
  #endif
#else
  #if defined(__WATCOMC__)
    #define CSHuge
  #else
    #define CSHuge huge
  #endif
#endif

#endif
