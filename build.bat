@ECHO OFF
_tools\NASM boot\bootsect.s -o _output\bootsect.bin
_tools\NASM boot\bootcode.s -o _output\bootcode.bin
_tools\NASM sysinit\pm.s -o _output\pm.obj -f obj
cd _tools
start /wait TCW _tools\sysinit.prj /b
cd ..
_tools\TLINK _output\sysinit.obj _output\pm.obj, _output\sysinit.exe, _output\sysinit.map /s /m
copy /b _output\bootsect.bin + _output\bootcode.bin + _output\sysinit.exe _image\boots.bin
REM copy /b _image\boot.bin + _output\kernel.exe _image\disk.bin
copy /b _image\boots.bin _image\disk.bin
cd _tools
bochs -q