@ECHO OFF
_tools\NASM boot\bootsect.s -o _output\bootsect.bin
_tools\NASM boot\bootcode.s -o _output\bootcode.bin
_tools\NASM init\init.s -o _output\init.bin
REM _tools\NASM sysinit\pm.s -o _output\pm.obj -f obj
REM cd _tools
REM start /wait TCW _tools\sysinit.prj /b
REM cd ..
REM _tools\TLINK @_tools\sysinit.l, _output\sysinit.exe, _output\sysinit.map /s /m
copy /b _output\bootsect.bin + _output\bootcode.bin + _output\init.bin + _output\kernel.exe _image\disk.bin
REM copy /b _image\boot.bin + _output\kernel.exe _image\disk.bin
REM copy /b _image\boot.bin _image\disk.bin
cd _tools
bochs -q