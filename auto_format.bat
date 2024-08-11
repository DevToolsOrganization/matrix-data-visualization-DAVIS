@echo off
echo davis code is formatting...
start /B astyle --project ./*.cpp,*.h
ping localhost -n 3 >nul
