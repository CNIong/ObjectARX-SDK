@Echo Off
REM PolySamp installation build script
REM .
REM Coming into this batch file we will be reliant on the following:
REM .
REM Parameters to be passed in:
REM 1. Location of the InstallShield directory (that contains binaries,
REM    and the includables in a /include directory).
REM 2. Location of the built files: asdkPolyUi.arx and AsdkPolyObj.dbx.
REM
REM ........................................................................

rem Set the proper environment variables
SET OINCLUDE=%INCLUDE%
SET OINSTRC=%INSTRC%
SET INCLUDE=%1\INCLUDE;%OINCLUDE%
SET INSTRC=%1\INCLUDE;

SET INSTERRF=INSTALL.ERR
if exist %INSTERRF% del %INSTERRF%

if exist %1\compile.exe goto cont1
goto badishielddir

:cont1
if exist %2\asdkpolyui.arx goto cont2
goto badpolydir

:cont2
if exist %2\asdkpolyobj.dbx goto cont3
goto badpolydir

:cont3
if exist data goto cont4
md data

:cont4

ECHO Standalone setup STIRLING build

@echo Building installer _SETUP.LIB AND INS >> %INSTERRF%
%1\compile setup.rul -g>> %INSTERRF%
if ERRORLEVEL 1 goto badimake
goto done

:badimake
type %INSTERRF%
echo.
echo failed to make setup.ins
echo.
goto doneFail

:badishielddir
echo Error: Could not find IShield compiler.
goto usage

:badpolydir
echo Error: Could not find PolySamp .arx/.dbx files
goto usage

:usage
echo Usage: amake [Path to Ishield] [Path to asdkPolyUi.arx/AsdkPolyObj.dbx]

:doneFail
beep
goto end

:done
if exist %INSTERRF% del %INSTERRF%
copy %2\asdkpolyui.arx data\
copy %2\asdkpolyobj.dbx data\
echo.
echo Creating package list...
%1\packlist setup.lst

:end
rem Clean up
SET INCLUDE=%OINCLUDE%
SET OINCLUDE=
SET INSTRC=%OINSTRC%
SET OINSTRC=
SET INSTERRF=

