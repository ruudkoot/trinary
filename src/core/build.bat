@ECHO OFF
SET ROOT=D:\Project Files
SET PATH=%ROOT%\bin\bochs;%ROOT%\bin\gcc;%ROOT%\bin\make;%ROOT%\bin\nasm;%ROOT%\bin\trifs-tools
SET CC=gcc -c -o
REM CC=gcc -fomit-frame-pointer -m386 -malign-double -mwide-multiply -O3 -c -mcpu=pentiumpro -o
SET LD=ld -s

DEL .\sys\*.* /q

cd src\boot
make
cd ..\..

cd src\core
make
cd ..\..

cd src\root
make
cd ..\..

cd src\test
make
cd ..\..

cd src\ping
make
cd ..\..

cd src\pong
make
cd ..\..

cd src\init
make
cd ..\..


REM ECHO cc: init.c
REM .\bin\gcc\gcc -Os -S -o ./tmp/init.s ./src/init/init.c
REM ECHO cp: init.s
REM copy .\src\init\ia32\ibm\entry.s + .\tmp\init.s .\tmp\init.t
REM ECHO as: init.s
REM .\bin\gcc\as -o ./tmp/init.o ./tmp/init.t
REM ECHO cp: pm32.c
REM %CC% ./tmp/pm32c.o ./src/init/pm32.c
REM ECHO as: pm32.s
REM .\bin\gcc\as -o ./tmp/pm32s.o ./src/init/pm32.s
REM ECHO ld: init
REM .\bin\gcc\ld -s -T./src/init/init.l -o ./tmp/init ./tmp/init.o ./tmp/pm32s.o ./tmp/pm32c.o

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