@ECHO OFF
SET PATH=.\bin;.\bin\gcc;.\bin\nasm;.\bin\bochs
SET CC=gcc -ffreestanding -fno-builtin -c -O3 -o
REM CC=gcc -fomit-frame-pointer -m386 -malign-double -mwide-multiply -O3 -c -mcpu=pentiumpro -o
SET LD=ld -s

DEL .\tmp\*.* /q

ECHO as: bootsect.s
.\bin\nasm\nasm .\src\boot\bootsect.s -o .\tmp\bootsect.bin
ECHO as: bootcode.s
.\bin\nasm\nasm .\src\boot\bootcode.s -o .\tmp\bootcode.bin
ECHO as: init.s
.\bin\nasm\nasm .\src\init\init.s -o .\tmp\init.bin -f bin
ECHO as: fat12.s
.\bin\nasm\nasm .\src\boot\fat12.s -o .\tmp\fat12 -f bin

ECHO cc: entry.c
%CC% ./tmp/entry.o ./src/core/entry.c
ECHO cc: core.c
%CC% ./tmp/core.o ./src/core/core.c
ECHO as: wrapper.s
.\bin\nasm\nasm .\src\core\arch\ia32\wrapper.s -o .\tmp\wrapper.o -f elf
ECHO ld: core
.\bin\gcc\ld -s -T./src/core/core.l -o ./tmp/core ./tmp/entry.o ./tmp/core.o ./tmp/wrapper.o ./bin/gcc/libgcc.a
ECHO oc: core
.\bin\gcc\objcopy ./tmp/core -O elf32-i386

ECHO cp: disk.bin
copy /b .\tmp\bootsect.bin + .\tmp\bootcode.bin + .\tmp\init.bin + .\tmp\core .\tmp\disk
cd .\bin\bochs
bochs -q
cd ..\..