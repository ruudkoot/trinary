@ECHO OFF
SET DJGPP=/bin/djgpp.env
SET PATH=\bin;\
SET CC=gcc -save-temps -c -o
REM CC=gcc -fomit-frame-pointer -m386 -malign-double -mwide-multiply -O3 -c -mcpu=pentiumpro -o
SET LD=ld -s

DEL \tmp\*.* /q

CD \tmp

ECHO as: bootsect.s
\bin\nasm \src\boot\bootsect.s -o \tmp\bootsect.bin
ECHO as: bootcode.s
\bin\nasm \src\boot\bootcode.s -o \tmp\bootcode.bin
ECHO as: int.s
\bin\nasm \src\init\init.s -o \tmp\init.bin

ECHO cc: entry.c
%CC% /tmp/entry.o /src/core/entry.c
ECHO cc: core.c
%CC% /tmp/core.o /src/core/core.c
ECHO as: handler.s
\bin\nasm \src\core\handler.s -o \tmp\handler.o -f elf
ECHO ld: core
\bin\ld -s -T\core.lds -o /tmp/core /tmp/entry.o /tmp/core.o /tmp/handler.o /lib.a

ECHO cp: disk.bin
copy /b \tmp\bootsect.bin + \tmp\bootcode.bin + \tmp\init.bin + \tmp\core \tmp\disk
cd \bin
bochs -q
cd \