sdcc -mz80 -o build\ --code-loc 0x4020 --data-loc 0xC000 --use-stdout --no-std-crt0 libs\crt0msx.16k.4000.rel src\sprite16C_test.c
hex2bin -e bin build\sprite16C_test.ihx
copy build\sprite16C_test.bin dist\SPRIT16C.ROM
FillFile dist\SPRIT16C.ROM 16384
pause
