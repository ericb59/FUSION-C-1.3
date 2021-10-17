#!/bin/bash
CRT_SIZE=0x`grep 'A _HEADER0' $1 | cut -d' ' -f4`
CRT_STRT=0x`grep 'A _HEADER0' $1 | cut -d' ' -f8`
export ADDR_CODE=$(( $CRT_STRT + $CRT_SIZE ))
echo "obase=16; ${ADDR_CODE}" | bc