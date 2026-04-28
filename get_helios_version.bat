@echo off
setlocal enabledelayedexpansion

where helios > nul 2>&1
if errorlevel 1 (
    set "HELIOS_VERSION="
) else (
    for /f "tokens=3 delims=()" %%a in ('helios --version') do (
        set "HELIOS_LINE=%%a"
        set "HELIOS_VERSION=!HELIOS_LINE:~1!"
    )
)

rem echo !HELIOS_VERSION!
for /f "delims=" %%i in ("!HELIOS_VERSION!") do @echo(%%i

endlocal