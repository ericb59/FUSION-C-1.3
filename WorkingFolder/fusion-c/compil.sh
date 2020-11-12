#!/bin/bash
# ___________________________________________________________
#/               __           _                              \
#|              / _|         (_)                             |
#|             | |_ _   _ ___ _  ___  _ __                   |
#|             |  _| | | / __| |/ _ \| '_ \                  |
#|             | | | |_| \__ \ | (_) | | | |                 |
#|             |_|  \__,_|___/_|\___/|_| |_| *               |
#|                                                           |
#|               The MSX C Library for SDCC                  |
#|                 V1.3 - November 2020                      |
#|                                                           |
#|                         compil.sh                         |
#|               Compilation Script for MacOS                |
#|                 (may be for linux too ! ?)                |
#|                     Script version 1.1                   |
#\___________________________________________________________/
#
#  What does this file ?
#  It generate an MSX DOS executable file ready to be launch on a MSX Computer with MSX-DOS 
#  It also start the openMSX emulator if it isn't already started
# 
# 
#
# -- Self Path Indentifer. Do not change this part of the script
pushd . > /dev/null
SCRIPT_PATH="${BASH_SOURCE[0]}";
  while([ -h "${SCRIPT_PATH}" ]) do 
    cd "`dirname "${SCRIPT_PATH}"`"
    SCRIPT_PATH="$(readlink "`basename "${SCRIPT_PATH}"`")"; 
  done
cd "`dirname "${SCRIPT_PATH}"`" > /dev/null
SCRIPT_PATH="`pwd`";
popd  > /dev/null

export CURRENT_DIR="${SCRIPT_PATH}"
export PARRENT_DIR="${CURRENT_DIR%/*}"
export SCRIPT_NAME="${0##*/}"
export prog=$(echo "${1##*/}" | cut -f 1 -d '.')

# -- End of Self Path Identifizer

# -- Configuration Area. you may change default configuration values
  # -- Name of the hex2bin excutable
export HEX2BIN=hex2bin
  # -- Name of the Assembler excutable
export ASM=sdasz80 
  # -- Name of the C Compiler excutable
export CC=sdcc 
  # -- Override default value is activated by default. 1:Activated  0:deactivated
export CHECK_OVERRIDE=1
  
  #-- Where to save compilation temps files (may be usefull for debugging)
export OUT_DIR=$PARRENT_DIR/out/  
  #-- Where to find .rel files to include during compilation
export INCLUDE_DIR=$CURRENT_DIR/include/
  #-- Where to find Fusion-c's definition files (.h)
export HEADER_DIR=$CURRENT_DIR/header/
  #-- Where to find the Dynamic Library
export LIB_DIR=$CURRENT_DIR/lib/
  # -- Default CRT0 ton use
export DEFAULT_CRT0="${INCLUDE_DIR}crt0_msxdos.rel"
  # -- Default Code Address (sdcc parameter)
export DEFAULT_ADDR_CODE="0x106"
  # -- Default Data Address (sdcc parameter)
export DEFAULT_ADDR_DATA="0x0"
  # -- Default compilation Priority
export DEFAULT_PRIO="--opt-code-size"
  # -- Default openMSX Script machine to start at the end of compilation. 0:nothing  1:MSX1  2:MSX2  3:MSX2+  4:TurboR  5:MSX2-HD. 6:MSX2+HD  7:TurboR-HD
export DEFAULT_MSXVER=2
  # -- Write Autoexec.bnat to the destination with the complied program. 1:Yes  2: No
export DEFAULT_AUTOEXEC=1
  # -- Default destination folder for the compiled program
export DEFAULT_DEST_DISK="dsk/dska/"
  # -- Default destination folder for the compiled program, in case of using HD (Hard-drive)
export DEFAULT_DEST_HDA="dsk/hda-1/"
  # -- Default extension for the compiled program
export DEFAULT_EXTENSION=com
  #-- Print on concole the full compilation command line (for controle or debug purpose) 1:Medium 2:Full  0:deactivated
export DEFAULT_VERBOSE=2


if [ -d "$OUT_DIR" ]; then
  ### Take action if $DIR exists ###
  echo "Installing config files in ${DIR}..."
else
  ###  Control will jump here if $DIR does NOT exists ###
  mkdir $OUT_DIR
fi

  # -- Other .rel you may have to include to your code
#export INC1="$(INCLUDE_DIR)"
#export INC2="$(INCLUDE_DIR)"
#export INC3="$(INCLUDE_DIR)"
#export INC4="$(INCLUDE_DIR)"
#export INC5="$(INCLUDE_DIR)"
#export INC6="$(INCLUDE_DIR)"
#export INC7="$(INCLUDE_DIR)"
#export INC8="$(INCLUDE_DIR)"
#export INC9="$(INCLUDE_DIR)"

########## END OF CONFIGURATION AREA ######################

# -- Check if Argument is provided
if [ -z "${1}" ];
then 
    echo  "ERROR: You must provide a source file !"
    exit 0
fi

# -- Check if source file exists
if [ ! -f "${1}" ]
then
  echo "ERROR: can't find ${1}"
  exit 0
fi

# -- Check  for override directives
if [ "${CHECK_OVERRIDE}" = "1" ];
then 
    # -- Override Default compilation variables --
    OPTIMIZATION_Identifier="__SDK_OPTIMIZATION__"
    MSXVERSION_Identifier="__SDK_MSXVERSION__"
    ADDRCODE_Identifier="__SDK_ADDRCODE__"
    ADDRDATA_Identifier="__SDK_ADDRDATA__"
    CRT0_Identifier="__SDK_CRT0__"
    DEST_Identifier="__SDK_DEST__"
    AUTOEXEC_Identifier="__SDK_AUTOEXEC__"
    EXT_Identifier="__SDK_EXT__"
    VERBOSE_Identifier="__SDK_VERBOSE__"

    OPTIMIZATION_VAR=`cat $1 |tr -s ' ' | grep "\#define ${OPTIMIZATION_Identifier}" | cut -d" " -f 3  | tr -d '\r\n,'`
    MSXVER_VAR=`cat $1 | tr -s ' ' | grep "\#define ${MSXVERSION_Identifier}" | cut -d" " -f 3 | tr -d '\r\n,'`
    ADDRCODE_VAR=`cat $1 | tr -s ' ' | grep "\#define ${ADDRCODE_Identifier}" | cut -d" " -f 3 | tr -d '\r\n,'`
    ADDRDATA_VAR=`cat $1 | tr -s ' ' | grep "\#define ${ADDRDATA_Identifier}" | cut -d" " -f 3 | tr -d '\r\n,'`
    CRT0_VAR=`cat $1 | tr -s ' ' | grep "\#define ${CRT0_Identifier}" | cut -d" " -f 3 | tr -d '\r\n,'`
    DEST_VAR=`cat $1 | tr -s ' ' | grep "\#define ${DEST_Identifier}" | cut -d" " -f 3 | tr -d '\r\n,'`
    AUTOEXEC_VAR=`cat $1 | tr -s ' ' | grep "\#define ${AUTOEXEC_Identifier}" | cut -d" " -f 3 | tr -d '\r\n,'`
    EXT_VAR=`cat $1 | tr -s ' ' | grep "\#define ${EXT_Identifier}" | cut -d" " -f 3 | tr -d '\r\n,'`
    VERBOSE_VAR=`cat $1 | tr -s ' ' | grep "\#define ${VERBOSE_Identifier}" | cut -d" " -f 3 | tr -d '\r\n,'`

fi
# -- END Of Override Checks --

# -- setting compilation directives 
if [ -z "${VERBOSE_VAR}" ];
then 
    VERBOSE_COMPILATION="${DEFAULT_VERBOSE}"
else
    VERBOSE_COMPILATION="${VERBOSE_VAR}"
fi

if [ -z "${ADDRDATA_VAR}" ];
then 
		ADDR_DATA="${DEFAULT_ADDR_DATA}"
else
		ADDR_DATA="${ADDRDATA_VAR}"
fi

if [ -z "${ADDRCODE_VAR}" ];
then 
		ADDR_CODE="${DEFAULT_ADDR_CODE}"
else
		ADDR_CODE="${ADDRCODE_VAR}"
fi

if [ "${OPTIMIZATION_VAR}" = "1" ];
then 
		CODEPRIO="--opt-code-speed"
else
		CODEPRIO=${DEFAULT_PRIO}
fi

if [ -z "${CRT0_VAR}" ];
then 
		CRT0="${DEFAULT_CRT0}"
else

		CRT0="${INCLUDE_DIR}${CRT0_VAR}"
fi

if [ -z "${MSXVER_VAR}" ];
then 
		MSXVER=${DEFAULT_MSXVER}
else
		MSXVER=${MSXVER_VAR}
fi

if [ -z "${AUTOEXEC_VAR}" ];
then 
    AUTOEXEC=${DEFAULT_AUTOEXEC}
else
    AUTOEXEC=${AUTOEXEC_VAR}
fi

if [ -z "${EXT_VAR}" ];
then 
    EXTENSION=${DEFAULT_EXTENSION}
else
    EXTENSION=${EXT_VAR}
fi

# -- Set Destination of final file --
export DEST=${DEFAULT_DEST_DISK}
if [ ${MSXVER} = "1" ] || [ ${MSXVER} = "2" ] || [ ${MSXVER} = "3" ] || [ ${MSXVER} = "4" ];
then
  		export DEST=$PARRENT_DIR/${DEFAULT_DEST_DISK}
fi

if [ ${MSXVER} = "5" ] || [ ${MSXVER} = "6" ] || [ ${MSXVER} = "7" ]; 
then
  		export DEST=$PARRENT_DIR/${DEFAULT_DEST_HDA}
fi

if [ -z "${DEST_VAR}" ];
then 
    echo ""
else
    export DEST=${DEST_VAR}
fi


# --
if [ "${VERBOSE_COMPILATION}" = "0" ];
then 
  echo "_____________________________________________________"
else
  echo "_____________________________________________________"
  echo ": Verbose mode: ${VERBOSE_COMPILATION}"
  echo ": Curren dir:   ${CURRENT_DIR}"
  echo ": Parrent dir:  ${PARRENT_DIR}"
  echo ": Header Dir:   ${HEADER_DIR}"
  echo ": Lib Dir:      ${LIB_DIR}"
  echo ": Source code:  ${prog}"
  echo ": Dest Folder:  ${DEST}"
  echo ": Autoexec:     ${AUTOEXEC}"
  echo ": MSX Script:   ${MSXVER}"
  echo "_____________________________________________________"
fi

########## COMPILATION PROCESS ######################
CCFLAGS="--code-loc ${ADDR_CODE} --data-loc ${ADDR_DATA} --disable-warning 196 -mz80 --no-std-crt0 ${CODEPRIO} fusion.lib -L ${LIB_DIR} -I ${HEADER_DIR} ${CRT0} ${INC1} ${INC2} ${INC3} ${INC4} ${INC5} ${INC6} ${INC7} ${INC8} ${INC9} ${prog}.c"


echo "[1/5]... ${CC} is Processing '$1' ... "

if [ "${VERBOSE_COMPILATION}" = "2" ];
then 
    echo ": Compilation command: ${CC} ${CCFLAGS}"
fi

sdcc ${CCFLAGS}

if [ ! -f "${prog}.ihx" ]
then
	 echo "ERREUR: ${CC} Compilation Error !"
	 exit 0
fi

echo "[2/5]... ${HEX2BIN} is Processing '${prog}.ihx' ... "
if [ "${VERBOSE_COMPILATION}" = "2" ];
then 
      ${HEX2BIN} -e ${EXTENSION} ${prog}.ihx
else
    
     RES=`${HEX2BIN} -e ${EXTENSION} ${prog}.ihx`
fi

if [ ! -f "${prog}.${EXTENSION}" ]
then
	 echo "ERREUR: Hex2Bin Error !"
	 exit 0
fi


echo "[3/5]... Copying ${prog}.${EXTENSION} to ${DEST}"
cp -f ${prog}.${EXTENSION}  ${DEST}

echo "[4/5]... Removing temps files..."
cp -f ${PARRENT_DIR}/${prog}.com ${OUT_DIR}
cp -f ${PARRENT_DIR}/${prog}.asm ${OUT_DIR}
cp -f ${PARRENT_DIR}/${prog}.ihx ${OUT_DIR}
cp -f ${PARRENT_DIR}/${prog}.lk ${OUT_DIR}
cp -f ${PARRENT_DIR}/${prog}.lst ${OUT_DIR}
cp -f ${PARRENT_DIR}/${prog}.map ${OUT_DIR}
cp -f ${PARRENT_DIR}/${prog}.noi ${OUT_DIR}
cp -f ${PARRENT_DIR}/${prog}.sym ${OUT_DIR}
cp -f ${PARRENT_DIR}/${prog}.rel ${OUT_DIR}

rm ${PARRENT_DIR}/${prog}.com
rm ${PARRENT_DIR}/${prog}.asm
rm ${PARRENT_DIR}/${prog}.ihx
rm ${PARRENT_DIR}/${prog}.lk
rm ${PARRENT_DIR}/${prog}.lst
rm ${PARRENT_DIR}/${prog}.map
rm ${PARRENT_DIR}/${prog}.noi
rm ${PARRENT_DIR}/${prog}.sym
rm ${PARRENT_DIR}/${prog}.rel

if [ "${AUTOEXEC}" = "1" ];
then 
    echo "${prog}" > ${DEST}autoexec.bat
fi

# -- Starting OpenMSX --
if [ "${MSXVER}" = "0" ]; then
  echo "[5/5]... Ending."
  exit 0
fi

xopenmsx=`ps x | grep "openmsx " | grep -v grep`

if [ "${xopenmsx}" == "" ]; then
  echo "[5/5]... Starting openMSX with Script : ${MSXVER}"
  pushd $PARRENT_DIR > /dev/null 2>&1
  		if [ "${MSXVER}" = "1" ]
  		then
  			exec -c `openMSX/openMSX.app/Contents/MacOS/openmsx -script openMSX/MSX_config/1-emul_start_MSX1_config.txt` & disown
  		fi
  		if [ "${MSXVER}" = "2" ]
  		then
  			exec -c `openMSX/openMSX.app/Contents/MacOS/openmsx -script  openMSX/MSX_config/2-emul_start_MSX2_config.txt` & disown
      fi
  		if [ "${MSXVER}" = "3" ]
  		then
  			exec -c `openMSX/openMSX.app/Contents/MacOS/openmsx -script openMSX/MSX_config/3-emul_start_MSX2p_config.txt` & disown
  		fi
  		if [ "${MSXVER}" = "4" ]
  		then
  			exec -c `openMSX/openMSX.app/Contents/MacOS/openmsx -script openMSX/MSX_config/4-emul_start_TURBOR_config.txt` & disown
  		fi
     	if [ "${MSXVER}" = "5" ]
      then
        	exec -c `openMSX/openMSX.app/Contents/MacOS/openmsx -script openMSX/MSX_config/5-emul_start_MSX2HD_config.txt` & disown
      fi
      if [ "${MSXVER}" = "6" ]
      then
        	exec -c `openMSX/openMSX.app/Contents/MacOS/openmsx -script openMSX/MSX_config/6-emul_start_MSX2pHD_config.txt` & disown
      fi
      if [ "${MSXVER}" = "7" ]
      then
        	exec -c `openMSX/openMSX.app/Contents/MacOS/openmsx -script openMSX/MSX_config/7-emul_start_TURBORHD_config.txt` & disown
      fi
      popd > /dev/null 2>&1

else
  echo "[5/5]... openMSX is already running."
fi

echo "end."
exit 0