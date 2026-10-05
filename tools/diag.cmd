@echo off
D:
cd \Projects\Games\GAME-PUZZLE-Ribble\bin
echo CWD=%CD%
if exist levels\level.1 echo FOUND-via-levels-dir
if exist levels echo LEVELS-DIR-EXISTS
if not exist levels echo NO-LEVELS-DIR
dir /b levels 2>nul
if exist level.1 echo FLAT-level1-exists
findstr /b Data levels\level.1 2>nul