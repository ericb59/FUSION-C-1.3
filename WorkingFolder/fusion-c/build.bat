@echo off >nul: 2>nul:
REM  ___________________________________________________________
REM /               __           _                              \
REM |              / _|         (_)                             |
REM |             | |_ _   _ ___ _  ___  _ __                   |
REM |             |  _| | | / __| |/ _ \| '_ \                  |
REM |             | | | |_| \__ \ | (_) | | | |                 |
REM |                                                           |
REM |               The MSX C Library for SDCC                  |
REM |                  V1.3 - October 2021                      |
REM |                                                           |
REM |                         compil.bat                        |
REM |               Compilation Script for Windows              |
REM |                      Script version 1.2                   |
REM \___________________________________________________________/
REM 
REM   What does this file ?
REM   It generate an MSX DOS executable file or a MSX ROM ready to be launch on a MSX Computer with MSX-DOS 
REM   It also start the openMSX emulator if it isn't already started
REM
setlocal EnableDelayedExpansion
 
rem # -- Self Path Indentifer. Do not change this part of the script
set SCRIPT_NAME=%~nx0
set CURRENT_DIR=%~dp0
set FULL_PATH= %~fs0
set sourcefile=%1
for %%f in (%sourcefile%) do set prog=%%~nf
for %%I in ("%~dp0.") do for %%J in ("%%~dpI.") do set PARENT_DIR=%%~dpnxJ


rem # -- End of Self Path Identifizer


rem # -- Configuration Area. you may change default configuration values
rem 	# -- Name of the hex2bin excutable
set HEX2BIN=hex2bin.exe
rem 	# -- Name of the Assembler excutable
set ASM=sdasz80 
rem 	# -- Name of the C Compiler excutable
set CC=sdcc 
rem 	# -- Override default value is activated by default. 1:Activated  0:deactivated
set CHECK_OVERRIDE=1
rem 	# -- Copy Temps files to Out folder (The folder will be created in WorkingFolder) 1: YES   0: No
set OUT_SAVE=1

rem  #-- OpenMSX APP path (Relative to WorkingFolder directory)
set OPENMSX_APP_PATH=openMSX\
rem  # -- OpenMSX MSX Machine Definition Screipt (relative to WorkindFolder)
set MSX_MACHINE_SCRIPT_PATH=openMSX\MSX_config\


rem  #-- Where to save compilation temps files (may be usefull for debugging)
set OUT_DIR=!PARENT_DIR!\out\
rem 	#-- Where to find .rel files to include during the compilation
set INCLUDE_DIR=%CURRENT_DIR%include\
rem 	#-- Where to find Fusion-c's definition files
set HEADER_DIR=%CURRENT_DIR%header\
rem 	#-- Where to find the Dynamic Library
set LIB_DIR=%CURRENT_DIR%lib\
rem  # -- DefaultMSWODS Stock Dir
set MSXDOS_DIR=%CURRENT_DIR%source\
rem 	# -- Default CRT0 ton use
set DEFAULT_CRT0=%INCLUDE_DIR%crt0_msxdos.rel
Rem 	# -- Default Code Address -sdcc parameter-
set DEFAULT_ADDR_CODE=0x106
rem 	# -- Default Data Address -sdcc parameter-
set DEFAULT_ADDR_DATA=0x0
rem  	# -- Default compilation Priority
set DEFAULT_PRIO=--opt-code-size
rem  	# -- Default openMSX Script machine to start at the end of compilation. 0:nothing  1:MSX1  2:MSX2  3:MSX2+  4:TurboR  5:MSX2-HD. 6:MSX2+HD  7:TurboR-HD
set DEFAULT_MSXVER=2
rem  	# -- Write Autoexec.bnat to the destination with the complied program. 1:Yes  2: No
set DEFAULT_AUTOEXEC=1
rem  	# -- Default destination folder for the compiled program
set DEFAULT_DEST_DISK=dsk\dska\
rem  	# -- Default destination folder for the compiled program, in case of using HD -Hard-drive-
set DEFAULT_DEST_HDA=dsk\hda-1\
rem -- Default destination folder for for ROM type compiled files (Extension=ROM)
set DEFAULT_DEST_ROM="dsk\rom\"

rem 	# -- Default Hex2Bin Extra Parameters Set the Final Rom Size in KB. Must be set in a Hex Value. 8000 = 32768 KB
set DEFAULT_HEX2BIN_SIZE=
rem  	# -- Default extension for the compiled program
set DEFAULT_EXTENSION=com
rem 	#-- Print on concole the full compilation command lines and etails -for controle or debug purpose-1:Medium 2:Full  0:deactivated
set DEFAULT_VERBOSE=2
rem  # -- Which version of MSX-DOS to use.  1:MSX-DOS1   2:MSX-DOS2  0:Do not change current MSXDOS file in Destination folder
set  DEFAULT_MSXDOS=0
rem  # -- Set The default ROM size, in case of compiling a ROM
set DEFAULT_ROMSIZE_VAR=8000
rem  # -- Set the Default CRT0 for ROM, in case of compiling a ROM
set DEFAULT_ROM_CRT0="${INCLUDE_DIR}crt032K.rel"
rem  # -- Default Data Address (sdcc parameter), in case of compiling a ROM
set DEFAULT_ROM_ADDR_DATA="0xC000"
rem  # -- Default Code Address (sdcc parameter), in case of compiling a ROM
set DEFAULT_ROM_ADDR_CODE="0x4010"


set CARTRIDGE_SLOT_A=""
set CARTRIDGE_SLOT_B=""

if "%OUT_SAVE%"=="1" (
	rem Create OUT_DIR. If the folder already exists, no error will be print
	mkdir %OUT_DIR% >nul: 2>nul:
)

rem 	# -- Other .rel you may have to include to your code
REM SET INC1=%INCLUDE_DIR
REM SET INC2=%INCLUDE_DIR
REM SET INC3=%INCLUDE_DIR%
REM SET INC4=%INCLUDE_DIR%
REM SET INC5=%INCLUDE_DIR%
REM SET INC6=%INCLUDE_DIR%
REM SET INC7=%INCLUDE_DIR%
REM SET INC8=%INCLUDE_DIR%
REM SET INC9=%INCLUDE_DIR%


Rem ########## END OF CONFIGURATION AREA ######################
set NOW=%date%  %time%

rem # -- Check if Argument is provided
if ["%~1"]==[""] (
        echo ERROR You must Provide a source file.
        goto _ending_
 )


rem # -- Check if source file exists
if exist %1 (
    rem file exists
) else (
    echo ERROR cannot find source file : %~1
    goto _ending_
)

Rem # -- Override Default compilation variables --
if "%CHECK_OVERRIDE%"=="1" (

	set OPTIMIZATION_Identifier=__SDK_OPTIMIZATION__
	set MSXVERSION_Identifier=__SDK_MSXVERSION__
	set ADDRCODE_Identifier=__SDK_ADDRCODE__
	set ADDRDATA_Identifier=__SDK_ADDRDATA__
	set CRT0_Identifier=__SDK_CRT0__
	set DEST_Identifier=__SDK_DEST__
	set AUTOEXEC_Identifier=__SDK_AUTOEXEC__
	set EXT_Identifier=__SDK_EXT__
	set VERBOSE_Identifier=__SDK_VERBOSE__
	set MSXDOS_Identifier=__SDK_MSXDOS__
	set ROMSIZE_Identifier="__SDK_ROMSIZE__"


	for /F "delims=" %%a in ('findstr "!OPTIMIZATION_Identifier!"  %sourcefile%') do (
		for /f "tokens=3" %%c in ("%%a") do set OPTIMIZATION_VAR=%%c
	)

	for /F "delims=" %%a in ('findstr "!MSXVERSION_Identifier!"  %sourcefile%') do (
		for /f "tokens=3" %%c in ("%%a") do set MSXVER_VAR=%%c
	)

	for /F "delims=" %%a in ('findstr "!ADDRCODE_Identifier!"  %sourcefile%') do (
		for /f "tokens=3" %%c in ("%%a") do set ADDRCODE_VAR=%%c
	)

	for /F "delims=" %%a in ('findstr "!ADDRDATA_Identifier!"  %sourcefile%') do (
		for /f "tokens=3" %%c in ("%%a") do set ADDRDATA_VAR=%%c
	)

	for /F "delims=" %%a in ('findstr "!CRT0_Identifier!" %sourcefile%') do (
		for /f "tokens=3" %%c in ("%%a") do set CRT0_VAR=%%c
	)

	for /F "delims=" %%a in ('findstr "!DEST_Identifier!"  %sourcefile%') do (
		for /f "tokens=3" %%c in ("%%a") do set DEST_VAR=%%c
	)
	for /F "delims=" %%a in ('findstr "!AUTOEXEC_Identifier!"  %sourcefile%') do (
		for /f "tokens=3" %%c in ("%%a") do set AUTOEXEC_VAR=%%c
	)

	for /F "delims=" %%a in ('findstr "!EXT_Identifier!"  %sourcefile%') do (
		for /f "tokens=3" %%c in ("%%a") do set EXT_VAR=%%c
	)

	for /F "delims=" %%a in ('findstr "!VERBOSE_Identifier!"  %sourcefile%') do (
		for /f "tokens=3" %%c in ("%%a") do set VERBOSE_VAR=%%c
	)
	for /F "delims=" %%a in ('findstr "!MSXDOS_Identifier!"  %sourcefile%') do (
		for /f "tokens=3" %%c in ("%%a") do set MSXDOS_VAR=%%c
	)
	for /F "delims=" %%a in ('findstr "!ROMSIZE_Identifier!"  %sourcefile%') do (
		for /f "tokens=3" %%c in ("%%a") do set ROMSIZE_VAR=%%c
	)

)


rem # -- END Of Override Checks --

rem # -- setting compilation directives 


if "%EXT_VAR%"=="" (
		set EXTENSION=%DEFAULT_EXTENSION%
) else (
		set EXTENSION=%EXT_VAR%
)

if "%EXTENSION%"=="ROM" (
		set CRT0=%DEFAULT_ROM_CRT0%
		set ADDR_DATA=%DEFAULT_ROM_ADDR_DATA%
		set ADDR_CODE=%DEFAULT_ROM_ADDR_CODE%

) else (
		set CRT0=%DEFAULT_CRT0%
		set ADDR_DATA=%DEFAULT_ADDR_DATA%
		set ADDR_CODE=%DEFAULT_ADDR_CODE%

)


if "%CRT0_VAR%"=="" (
		REM --
) else (
		set CRT0=%INCLUDE_DIR%%CRT0_VAR%
)

if "%VERBOSE_VAR%"=="" (
		set VERBOSE_COMPILATION=%DEFAULT_VERBOSE%
) else (
		set VERBOSE_COMPILATION=%VERBOSE_VAR%
)

if "%ADDRDATA_VAR%"=="" (
		REM --
) else (
		set ADDR_DATA=%ADDRDATA_VAR%
)

if "%ADDRCODE_VAR%"=="" (
		REM --
) else (
		set ADDR_CODE=%ADDRCODE_VAR%
)


if "%OPTIMIZATION_VAR%"=="1" (
		set CODEPRIO=--opt-code-speed
) else (
		set CODEPRIO=%DEFAULT_PRIO%
)


if "%MSXVER_VAR%"=="" (
		set MSXVER=%DEFAULT_MSXVER%
) else (
		set MSXVER=%MSXVER_VAR%
)

if "%AUTOEXEC_VAR%"=="" (
		set AUTOEXEC=%DEFAULT_AUTOEXEC%
) else (
		set AUTOEXEC=%AUTOEXEC_VAR%
)

if "%ROMSIZE_VAR%"=="" (

    set ROMSIZE=%DEFAULT_ROMSIZE_VAR%
) else (
    set ROMSIZE=%ROMSIZE_VAR%
)


rem # -- Destination of final file --
set DEST=%DEFAULT_DEST_DISK%

if "%MSXVER%"=="" (
		set DEST=%DEFAULT_DEST_DISK%
)
if "%MSXVER%"=="1" (
		set DEST=%PARENT_DIR%\%DEFAULT_DEST_DISK%
)
if "%MSXVER%"=="2" (
		set DEST=%PARENT_DIR%\%DEFAULT_DEST_DISK%
)
if "%MSXVER%"=="3" (
		set DEST=%PARENT_DIR%\%DEFAULT_DEST_DISK%
)
if "%MSXVER%"=="4" (
		set DEST=%PARENT_DIR%\%DEFAULT_DEST_DISK%
)

if "%MSXVER%"=="5" (
		set DEST=%PARENT_DIR%\%DEFAULT_DEST_HDA%
)
if "%MSXVER%"=="6" (
		set DEST=%PARENT_DIR%\%DEFAULT_DEST_HDA%
)
if "%MSXVER%"=="7" (
		set DEST=%PARENT_DIR%\%DEFAULT_DEST_HDA%
)

rem # -- Set MSXDOS version to use --
if "%MSXDOS_VAR%"=="" (
		set MSXDOS=%DEFAULT_MSXDOS%
) else (
		set MSXDOS=%MSXDOS_VAR%
)



rem # -- If Building a ROM --
if "${EXTENSION}"=="ROM" (
 
    set DEST=%DEFAULT_DEST_ROM%
    set LIB_FILE=fusion-ROM.lib
    set AUTOEXEC=0;
    set MSXDOS=0;
	set DEFAULT_HEX2BIN_SIZE=-l %ROMSIZE_VAR%
)


if "%DEST_VAR%"=="" (
		 echo 
) else (
		set DEST=%DEST_VAR%
)



rem # ----------

if "${EXTENSION}"=="ROM" (
	set COMPILATION_TEXT=MSX: %MSXVER%  ROM:%prog%.%EXTENSION%  SIZE: %ROMSIZE_VAR%  ADDRCODE: %ADDR_CODE%  ADDRDATA: %ADDR_DATA}%
) else (
	set COMPILATION_TEXT=MSX: %MSXVER%  MSXDOS: %MSXDOS%  Autoexec: %AUTOEXEC%  ADDRCODE: %ADDR_CODE%  ADDRDATA: %ADDR_DATA}%
)

echo /  START_COMPILATION  \\
echo ._____________________.
echo . %NOW% .
echo \_____________________/

if "%VERBOSE_COMPILATION%"=="0" (
	echo _____________________________________________________
) else (
	echo _____________________________________________________
	echo - Current Dir:      %CURRENT_DIR%
	echo - Parent Dir:       %PARENT_DIR%
	echo - Header Dir:       %HEADER_DIR%
	echo - Library:          %LIB_DIR%
	echo - Source Code:      %PROG%
	echo - Dest Folder:      %DEST%
	echo - CRT0:      %CRT0%
	echo - %COMPILATION_TEXT%
)
echo _____________________________________________________



Rem ########## COMPILATION PROCESS ######################

if "${EXTENSION}"=="ROM" (
 	rem pre-compilation
    sdcc -c -mz80 ${prog}.c -I %HEADER_DIR%
    set CCFLAGS=-o %prog%.ihx --code-loc %ADDR_CODE% --data-loc %ADDR_DATA% --disable-warning 196 -mz80 --no-std-crt0 %CODEPRIO% %LIB_FILE% -L %LIB_DIR% -I %HEADER_DIR% %CRT0% %INC1% %INC2% %INC3% %INC4% %INC5% %INC6% %INC7% %INC8% %INC9% %prog%.rel
    set CARTRIDGE_SLOT_A=-carta %DEST%%prog%.%EXTENSION%

) else (
    
    set CCFLAGS=--code-loc %ADDR_CODE% --data-loc %ADDR_DATA% --disable-warning 196 -mz80 --no-std-crt0 %CODEPRIO% fusion.lib -L %LIB_DIR% -I %HEADER_DIR% %CRT0%  %INC1% %INC2% %INC3% %INC4% %INC5% %INC6% %INC7% %INC8% %INC9% %prog%.c

)


echo [1/5]... %CC% is Processing '%sourcefile%' ... 

if "%VERBOSE_COMPILATION%"=="2" (
	echo - Compilation command line: %CC% !CCFLAGS!
	echo _____________________________________________________
)


sdcc !CCFLAGS!


if not exist %prog%.ihx (
	echo ERROR: %CC% with Compilation error !
	goto _ending_
)
echo _____________________________________________________
echo [2/5]... %HEX2BIN% is Processing %prog%.ihx' %DEFAULT_HEX2BIN_SIZE% 
if "%VERBOSE_COMPILATION%"=="2" (
	hex2bin -e %EXTENSION% %DEFAULT_HEX2BIN_SIZE% %prog%.ihx
) else (
	hex2bin -e %EXTENSION% %DEFAULT_HEX2BIN_SIZE% %prog%.ihx >nul: 2>nul:
)


if not exist %prog%.%EXTENSION% (
	echo ERROR: Hex2Bin Error !
	goto _ending_
)
 

if "%MSXDOS%"=="1" (
	echo [3a/5]... Preparing MSXDOS 1 environment
	del /Q %DEST%COMMAND2.COM >nul: 2>nul:
    del /Q %DEST%MSXDOS2.SYS >nul: 2>nul:
    del /Q %DEST%autoexec.bat >nul: 2>nul:
    copy %MSXDOS_DIR%\dos1_stock\COMMAND.COM  %DEST% >nul: 2>nul:
    copy %MSXDOS_DIR%\dos1_stock\MSXDOS.SYS  %DEST% >nul: 2>nul:
) 
if "%MSXDOS%"=="2" (
	 echo [3a/5]... Preparing MSXDOS 1 environment
	 del /Q %DEST%COMMAND.COM >nul: 2>nul:
     del /Q %DEST%MSXDOS.SYS >nul: 2>nul:
     del /Q %DEST%autoexec.bat >nul: 2>nul:
     copy %MSXDOS_DIR%\dos2_stock\COMMAND2.COM  %DEST% >nul: 2>nul:
     copy %MSXDOS_DIR%\dos2_stock\MSXDOS2.SYS  %DEST% >nul: 2>nul:
) 

echo [3b/5]... Copying %prog%.%EXTENSION% to %DEST%
copy %prog%.%EXTENSION% %DEST% >nul: 2>nul:

echo [4/5]... Removing temps files...
if "%OUT_SAVE%"=="1" (
	copy %prog%.%EXTENSION% %OUT_DIR% >nul: 2>nul:
	copy %prog%.asm %OUT_DIR% >nul: 2>nul:
	copy %prog%.%ihx %OUT_DIR% >nul: 2>nul:
	copy %prog%.lk %OUT_DIR% >nul: 2>nul:
	copy %prog%.lst %OUT_DIR% >nul: 2>nul:
	copy %prog%.map %OUT_DIR% >nul: 2>nul:
	copy %prog%.noi %OUT_DIR% >nul: 2>nul:
	copy %prog%.sym %OUT_DIR% >nul: 2>nul:
	copy %prog%.rel %OUT_DIR% >nul: 2>nul:
)

del /Q %prog%.%EXTENSION% >nul: 2>nul:
del /Q %prog%.asm >nul: 2>nul:
del /Q %prog%.ihx >nul: 2>nul:
del /Q %prog%.lk >nul: 2>nul:
del /Q %prog%.lst >nul: 2>nul:
del /Q %prog%.map >nul: 2>nul:
del /Q %prog%.noi >nul: 2>nul:
del /Q %prog%.sym >nul: 2>nul:
del /Q %prog%.rel >nul: 2>nul:

if "%AUTOEXEC%" == "1" (
	echo %prog% > %DEST%/autoexec.bat
)

Rem # -- Starting OpenMSX --

if "%MSXVER%" == "0" (
	echo [5/5]... No emulation requiered.
	goto _ending_
)

Set MyProcess=openmsx.exe
tasklist | find /i "%MyProcess%">nul  && (goto _end_) || echo [5/5]... Starting openMSX with Script : %MSXVER%

if "%MSXVER%" == "1" (
	start /b /d %PARENT_DIR% %OPENMSX_APP_PATH%openmsx.exe -script %MSX_MACHINE_SCRIPT_PATH%1-emul_start_MSX1_config.txt %CARTRIDGE_SLOT_A%
)
if "%MSXVER%" == "2" (
	 start /b /d %PARENT_DIR% %OPENMSX_APP_PATH%openmsx.exe -script %MSX_MACHINE_SCRIPT_PATH%2-emul_start_MSX2_config.txt %CARTRIDGE_SLOT_A%
)
if "%MSXVER%" == "3" (
	start  /b /d %PARENT_DIR% %OPENMSX_APP_PATH%openmsx.exe -script %MSX_MACHINE_SCRIPT_PATH%3-emul_start_MSX2p_config.txt %CARTRIDGE_SLOT_A%
)
if "%MSXVER%" == "4" (
	start /b /d %PARENT_DIR% %OPENMSX_APP_PATH%openmsx.exe -script %MSX_MACHINE_SCRIPT_PATH%4-emul_start_TURBOR_config.txt %CARTRIDGE_SLOT_A%
)
if "%MSXVER%" == "5" (
	start /b /d %PARENT_DIR% %OPENMSX_APP_PATH%openmsx.exe -script %MSX_MACHINE_SCRIPT_PATH%5-emul_start_MSX2HD_config.txt %CARTRIDGE_SLOT_A%
)
if "%MSXVER%" == "6" (
	start /b /d %PARENT_DIR% %OPENMSX_APP_PATH%openmsx.exe -script %MSX_MACHINE_SCRIPT_PATH%6-emul_start_MSX2pHD_config.txt %CARTRIDGE_SLOT_A%
)
if "%MSXVER%" == "7" (
	start /b /d %PARENT_DIR% %OPENMSX_APP_PATH%openmsx.exe -script %MSX_MACHINE_SCRIPT_PATH%7-emul_start_TURBORHD_config.txt %CARTRIDGE_SLOT_A%
)
goto _ending_

:_noargument_
echo You must provide a source file
goto _ending_

:_end_
echo [5/5]... %MyProcess% is Already running

:_ending_
echo End.
EXIT /B 0
