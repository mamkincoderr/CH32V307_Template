@echo off
setlocal EnableDelayedExpansion

rem ============================================================
rem  build.bat — CH32V307_Template
rem  Использование: build.bat [build|clean|rebuild|flash|configure] [gcc15|gcc12|gcc8]
rem  По умолчанию: build gcc15
rem ============================================================

set OPENOCD=C:\MounRiver\MounRiver_Studio2\resources\app\resources\win32\components\WCH\OpenOCD\OpenOCD\bin\openocd.exe
set OOCD_CFG=C:\MounRiver\MounRiver_Studio2\resources\app\resources\win32\components\WCH\OpenOCD\OpenOCD\bin\wch-riscv.cfg
set TARGET_HEX=obj\CH32V307_Template.hex

if not defined PRESET set PRESET=gcc15
if "%2"=="gcc12" set PRESET=gcc12
if "%2"=="gcc8"  set PRESET=gcc8
if "%2"=="gcc15" set PRESET=gcc15

set CMD=%1
if "%CMD%"=="" set CMD=build

if /I "%CMD%"=="build"     goto :build
if /I "%CMD%"=="clean"     goto :clean
if /I "%CMD%"=="rebuild"   goto :rebuild
if /I "%CMD%"=="flash"     goto :flash
if /I "%CMD%"=="configure" goto :configure
echo [ERROR] Неизвестная команда: %CMD%
goto :usage

:configure
echo [cmake] Конфигурация пресета %PRESET%...
cmake --preset %PRESET%
goto :end

:build
echo [cmake] Конфигурация пресета %PRESET%...
cmake --preset %PRESET%
if errorlevel 1 goto :err
echo [cmake] Сборка...
cmake --build obj
goto :end

:clean
echo [cmake] Очистка...
if exist obj (cmake --build obj --target clean) else (echo obj\ уже пуста.)
goto :end

:rebuild
echo [cmake] Полная пересборка...
if exist obj cmake --build obj --target clean
cmake --preset %PRESET%
if errorlevel 1 goto :err
cmake --build obj
goto :end

:flash
echo [openocd] Прошивка %TARGET_HEX% ...
"%OPENOCD%" -f "%OOCD_CFG%" -c "program %TARGET_HEX% verify reset exit"
goto :end

:usage
echo.
echo  build.bat [build^|clean^|rebuild^|flash^|configure] [gcc15^|gcc12^|gcc8]
echo.
echo  Примеры:
echo    build.bat build          -- сборка с GCC15 (по умолчанию)
echo    build.bat build gcc12    -- сборка с GCC12
echo    build.bat flash          -- прошить через WCH-Link
echo    set PRESET=gcc8 ^& build.bat build
echo.
goto :end

:err
echo.
echo [ERROR] Сборка завершилась с ошибкой.
exit /b 1

:end
endlocal
