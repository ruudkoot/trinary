@ECHO OFF
SET PATH=.\bin;.\bin\gcc;.\bin\make;.\bin\bochs;.\bin\trifs-tools
SET CC=gcc -c -o
REM CC=gcc -fomit-frame-pointer -m386 -malign-double -mwide-multiply -O3 -c -mcpu=pentiumpro -o
SET LD=ld -s

DEL .\tmp\*.* /q
DEL .\sys\*.* /q

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
ECHO as: ipc.s
.\bin\gcc\as ./src/core/ia32/ipc.s -o ./tmp/ipc.o
ECHO as: kdb.s
.\bin\gcc\as ./src/core/ia32/kdb.s -o ./tmp/kdb.o
ECHO ld: core
.\bin\gcc\ld -s -T./src/core/core.l -o ./tmp/core ./tmp/entry.o ./tmp/core.o ./tmp/ipc.o ./tmp/kdb.o ./bin/gcc/libgcc.a
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

ECHO cc: entry.c
%CC% ./tmp/tentry.o ./src/test/entry.c
ECHO cc: test.c
%CC% ./tmp/test.o ./src/test/test.c
ECHO ld: test
.\bin\gcc\ld -s -T./src/test/test.l -o ./tmp/test ./tmp/tentry.o ./tmp/test.o ./bin/gcc/libgcc.a
ECHO oc: test
.\bin\gcc\objcopy ./tmp/test -O elf32-i386

ECHO cc: entry.c
%CC% ./tmp/pentry.o ./src/ping/entry.c
ECHO cc: ping.c
%CC% ./tmp/ping.o ./src/ping/ping.c
ECHO ld: ping
.\bin\gcc\ld -s -T./src/ping/ping.l -o ./tmp/ping ./tmp/pentry.o ./tmp/ping.o ./bin/gcc/libgcc.a
ECHO oc: ping
.\bin\gcc\objcopy ./tmp/ping -O elf32-i386

ECHO cc: entry.c
%CC% ./tmp/qentry.o ./src/pong/entry.c
ECHO cc: pong.c
%CC% ./tmp/pong.o ./src/pong/pong.c
ECHO ld: pong
.\bin\gcc\ld -s -T./src/pong/pong.l -o ./tmp/pong ./tmp/qentry.o ./tmp/pong.o ./bin/gcc/libgcc.a
ECHO oc: pong
.\bin\gcc\objcopy ./tmp/pong -O elf32-i386

ECHO cc: init.c
.\bin\gcc\gcc -Os -S -o ./tmp/init.s ./src/init/init.c
ECHO cp: init.s
copy .\src\init\ia32\ibm\entry.s + .\tmp\init.s .\tmp\init.t
ECHO as: init.s
.\bin\gcc\as -o ./tmp/init.o ./tmp/init.t
ECHO cp: pm32.c
%CC% ./tmp/pm32c.o ./src/init/pm32.c
ECHO as: pm32.s
.\bin\gcc\as -o ./tmp/pm32s.o ./src/init/pm32.s
ECHO ld: init
.\bin\gcc\ld -s -T./src/init/init.l -o ./tmp/init ./tmp/init.o ./tmp/pm32s.o ./tmp/pm32c.o

ECHO oc: init
.\bin\gcc\objcopy -S -O binary ./tmp/init
ECHO oc: core
.\bin\gcc\objcopy -S -O binary ./tmp/core
ECHO oc: root
.\bin\gcc\objcopy -S -O binary ./tmp/root
ECHO oc: test
.\bin\gcc\objcopy -S -O binary ./tmp/test
ECHO oc: ping
.\bin\gcc\objcopy -S -O binary ./tmp/ping
ECHO oc: pong
.\bin\gcc\objcopy -S -O binary ./tmp/pong

ECHO mv: init
COPY .\tmp\init .\sys\init
ECHO mv: core
COPY .\tmp\core .\sys\core
ECHO mv: root
COPY .\tmp\root .\sys\root
ECHO mv: test
COPY .\tmp\test .\sys\test
ECHO mv: test
COPY .\tmp\ping .\sys\ping
ECHO mv: test
COPY .\tmp\pong .\sys\pong

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
ECHO put: test
put ./sys/test ./tmp/disk test
ECHO put: ping
put ./sys/ping ./tmp/disk ping
ECHO put: pong
put ./sys/pong ./tmp/disk pong

cd .\bin\bochs
bochs -q
cd ..\..