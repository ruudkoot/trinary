@ECHO OFF
SET PATH=.\bin;.\bin\gcc;.\bin\nasm;.\bin\bochs;.\bin\trifs-tools
SET CC=gcc -c -o
REM CC=gcc -fomit-frame-pointer -m386 -malign-double -mwide-multiply -O3 -c -mcpu=pentiumpro -o
SET LD=ld -s

DEL .\tmp\*.* /q

ECHO as: trifs.s
.\bin\gcc\as -o ./tmp/trifs.o ./src/boot/ia32/ibm/trifs.s
ECHO ld: trifs.o
.\bin\gcc\ld -s -T./src/boot/ia32/ibm/trifs.l -o ./tmp/trifs.x ./tmp/trifs.o 
ECHO oc: trifs.x
.\bin\gcc\objcopy -O binary ./tmp/trifs.x ./tmp/trifs.b

ECHO cc: entry.c
%CC% ./tmp/entry.o ./src/core/entry.c
ECHO cc: core.c
%CC% ./tmp/core.o ./src/core/core.c
ECHO as: wrapper.s
.\bin\nasm\nasm .\src\core\ia32\wrapper.s -o .\tmp\wrapper.o -f elf
ECHO ld: core
.\bin\gcc\ld -s -T./src/core/core.l -o ./tmp/core ./tmp/entry.o ./tmp/core.o ./tmp/wrapper.o ./bin/gcc/libgcc.a
ECHO oc: core
.\bin\gcc\objcopy ./tmp/core -O elf32-i386

ECHO cc: entry.c
%CC% ./tmp/rentry.o ./src/root/entry.c
ECHO cc: root.c
%CC% ./tmp/root.o ./src/root/root.c
ECHO ld: root
.\bin\gcc\ld -s -T./src/root/root.l -o ./tmp/root ./tmp/rentry.o ./tmp/root.o ./bin/gcc/libgcc.a
ECHO oc: root
.\bin\gcc\objcopy ./tmp/root -O elf32-i386

ECHO cc: init.c
.\bin\gcc\gcc -Os -S -o ./tmp/init.s ./src/init/init.c
ECHO cp: init.s
copy .\src\init\ia32\ibm\entry.s + .\tmp\init.s .\tmp\init.t
ECHO as: init.s
.\bin\gcc\as -o ./tmp/init.o ./tmp/init.t
ECHO as: init.s
.\bin\nasm\nasm .\src\init\init.s -o .\tmp\initxxx.o -f elf
ECHO ld: init
.\bin\gcc\ld -s -T./src/init/init.l -o ./tmp/init ./tmp/init.o ./tmp/initxxx.o

ECHO oc: init
.\bin\gcc\objcopy -S -O binary ./tmp/init
ECHO oc: core
.\bin\gcc\objcopy -S -O binary ./tmp/core
ECHO oc: root
.\bin\gcc\objcopy -S -O binary ./tmp/root

ECHO mv: init
COPY .\tmp\init .\sys\init
ECHO mv: core
COPY .\tmp\core .\sys\core
ECHO mv: root
COPY .\tmp\root .\sys\root

ECHO mkfs: disk
mkfs ./tmp/disk 2880 36 512
ECHO ibc: disk
ibc ./tmp/trifs.b ./tmp/disk
ECHO put: init
put ./sys/init ./tmp/disk init
ECHO put: core
put ./sys/core ./tmp/disk core
ECHO put: root
put ./sys/root ./tmp/disk root

cd .\bin\bochs
bochs -q
cd ..\..