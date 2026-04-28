@echo off
setlocal enabledelayedexpansion
set "str=%1"
set "isNum=1"

for /F "delims=0123456789" %%i in ("%str%") do set "isNum=0"

if %isNum%==1 (
    echo true
) else (
    echo false
)
endlocal