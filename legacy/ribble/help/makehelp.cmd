@ECHO OFF
REM Borland'c C pre-processor actually
REM does some sort of syntax checking.
REM 
REM Hence all the filtering stuff.
REM 
REM This script requires:
REM  GNU sed
REM  Borland's cpp
REM  ipfc

ECHO ON
sed -f sed.form < ribble.hc > ribble.1
cpp -P- -oribble.pp ribble.1
sed -f sed.fix < ribble.pp > ribble

rem ipfc /INF ribble
ipfc ribble

del ..\ribble.hlp
move ribble.hlp ..

