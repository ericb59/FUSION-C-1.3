sdcc -mz80 -o build\ --code-loc 0x4020 --data-loc 0xC000 --use-stdout --no-std-crt0 libs\crt0msx.16k.4000.rel libs\VDP_TMS9918_MSXBIOS.rel libs\VDP_SPRITE_MSXBIOS.rel  src\sprite8_test.c
hex2bin -e bin build\sprite8_test.ihx
copy build\sprite8_test.bin dist\SPRITE8.ROM
FillFile dist\SPRITE8.ROM 16384
pause
