@ECHO OFF
_tools\NASM boot\bootsect.s -o _output\bootsect.bin
_tools\NASM boot\bootcode.s -o _output\bootcode.bin
_tools\NASM init\init.s -o _output\init.bin
copy /b _output\bootsect.bin + _output\bootcode.bin + _output\init.bin + _output\core.exe _image\disk.bin
cd _emu
bochs -q