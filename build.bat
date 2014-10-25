@ECHO OFF

REM Change the next line to [ SET ROOT=C:\mithrill ] for example.
SET ROOT=.

SET PATH=%ROOT%\bin\bochs;%ROOT%\bin\gcc;%ROOT%\bin\make;%ROOT%\bin\nasm;%ROOT%\bin\trifs-tools

CD %ROOT%\src\boot
MAKE

CD %ROOT%\src\init
MAKE

CD %ROOT%\src\core
MAKE

CD %ROOT%\src\root
MAKE

CD %ROOT%\src\test
MAKE

CD %ROOT%\src\ping
MAKE

CD %ROOT%\src\pong
MAKE

CD %ROOT%

mkfs tmp/disk 2880 36 512
ibc src/boot/trifs tmp/disk
put src/init/init tmp/disk init
put src/core/core tmp/disk core
put src/root/root tmp/disk root
put src/test/test tmp/disk test
put src/ping/ping tmp/disk ping
put src/pong/pong tmp/disk pong

cd bin\bochs
bochs -q
cd ..\..