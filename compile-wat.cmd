@echo off
rem =========================================================================
rem Compile script for Ribble (Open Watcom C++ on OS/2 / ArcaOS)
rem Run from the project root:  compile-wat.cmd
rem =========================================================================

rem Auto-detect Watcom installation (OS/2 typical paths)
if "%WATCOM%"=="" (
    if exist C:\WATCOM\binp\wcc386.exe (
        set WATCOM=C:\WATCOM
    ) else if exist C:\WATCOM\bin\wcc386.exe (
        set WATCOM=C:\WATCOM
    ) else if exist C:\WATCOM2\binp\wcc386.exe (
        set WATCOM=C:\WATCOM2
    ) else if exist D:\WATCOM\binp\wcc386.exe (
        set WATCOM=D:\WATCOM
    ) else (
        echo ERROR: Watcom not found. Set WATCOM environment variable.
        exit 1
    )
)

rem Watcom OS/2 tools are installed under binp (Open Watcom on OS/2)
if exist %WATCOM%\binp\wpp386.exe (
    set PATH=%WATCOM%\binp;%PATH%
) else (
    set PATH=%WATCOM%\bin;%PATH%
)

rem Auto-detect OS/2 Toolkit
if "%OS2TK%"=="" (
    if exist C:\OS2TK45\h\os2.h (
        set OS2TK=C:\OS2TK45
    ) else if exist C:\OS2TK\h\os2.h (
        set OS2TK=C:\OS2TK
    ) else (
        echo WARNING: OS2TK not set, defaulting to C:\OS2TK45
        set OS2TK=C:\OS2TK45
    )
)

rem Set up environment for Open Watcom on OS/2
set PATH=%WATCOM%\bin;%PATH%
set INCLUDE=%WATCOM%\h;%OS2TK%\h;src;src\win;%INCLUDE%
set LIB=%WATCOM%\lib386;%OS2TK%\lib;%LIB%

rem Log file
set LOGFILE=compile-wat.log

rem Start logging - write header
echo ========================================== > %LOGFILE%
echo Ribble Build Log >> %LOGFILE%
echo Date: %DATE% Time: %TIME% >> %LOGFILE%
echo WATCOM=%WATCOM% >> %LOGFILE%
echo OS2TK=%OS2TK% >> %LOGFILE%
echo ========================================== >> %LOGFILE%
echo. >> %LOGFILE%

rem Also show on screen
echo Building Ribble with Open Watcom...
echo WATCOM=%WATCOM%
echo OS2TK=%OS2TK%
echo Log: %LOGFILE%
echo.

rem Clean first
echo [CLEAN] Running wmake clean...
wmake -f makefile.wat clean >> %LOGFILE% 2>&1

rem Build - redirect stdout to log, show on screen via TYPE after
set FAILED=0
echo [BUILD] Running wmake all...
wmake -f makefile.wat all >> %LOGFILE% 2>&1
if errorlevel 1 set FAILED=1

rem Show build output on screen
type %LOGFILE%

rem Copy runtime data next to the exe
if "%FAILED%"=="0" (
    if exist bin\Ribble.exe (
        if exist levels\level.1 (
            if not exist bin\levels mkdir bin\levels
            copy levels\level.* bin\levels >nul
        )
        if not exist bin\help mkdir bin\help
        if exist help\ribble-en.hlp copy help\ribble-en.hlp bin\help\ribble-en.hlp >nul
        if exist help\ribble-es.hlp copy help\ribble-es.hlp bin\help\ribble-es.hlp >nul
        if exist help\ribble-nl.hlp copy help\ribble-nl.hlp bin\help\ribble-nl.hlp >nul
        if exist help\ribble-de.hlp copy help\ribble-de.hlp bin\help\ribble-de.hlp >nul
        if exist help\ribble-fr.hlp copy help\ribble-fr.hlp bin\help\ribble-fr.hlp >nul
        if exist help\ribble-it.hlp copy help\ribble-it.hlp bin\help\ribble-it.hlp >nul
    )
)

rem Check result
if "%FAILED%"=="1" goto failed
if exist bin\Ribble.exe (
    echo.
    echo BUILD OK
    echo BUILD OK >> %LOGFILE%
    exit 0
)
:failed
echo.
echo BUILD FAILED
echo BUILD FAILED >> %LOGFILE%
exit 1