@ECHO OFF
SET DJGPP=/bin/djgpp.env
SET PATH=\bin;
REM CC=gcc -fomit-frame-pointer -Os -ffreestanding -save-temps -c -o
SET CC=gcc -fomit-frame-pointer -m386 -malign-double -mwide-multiply -O3 -c -mcpu=pentiumpro -o
SET LD=ld -nostdlib -s 

DEL \tmp\*.* /q

ECHO cc: entry.c
ECHO cc: core.c
%CC% /tmp/entry.o /src/core/entry.c
%CC% /tmp/core.o /src/core/core.c
ECHO as: handler.s
\bin\NASM \src\core\handler.s -o \tmp\handler.o -f elf
ECHO ld: core
ld -Tcore.lds -o /tmp/core /tmp/entry.o /tmp/core.o /tmp/handler.o



ECHO as: bootsect.s
\bin\nasm \src\boot\bootsect.s -o \tmp\bootsect.bin
ECHO as: bootcode.s
\bin\nasm \src\boot\bootcode.s -o \tmp\bootcode.bin
ECHO as: int.s
\bin\nasm \src\init\init.s -o \tmp\init.bin
ECHO cp: disk.bin
copy /b \tmp\bootsect.bin + \tmp\bootcode.bin + \tmp\init.bin + \tmp\core \tmp\disk
cd bin
bochs -q
cd \