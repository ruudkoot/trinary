# Microsoft Developer Studio Project File - Name="kernel" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=kernel - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "kernel.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "kernel.mak" CFG="kernel - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "kernel - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe
# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../_output"
# PROP Intermediate_Dir "../_output"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /G6 /Zp16 /W4 /O2 /I "../lib" /FAs /FD /TP /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x413 /d "NDEBUG"
# ADD RSC /l 0x413 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 ../_output/entry.obj /nologo /base:"0x0" /entry:"entry" /subsystem:windows /pdb:none /map /machine:I386 /nodefaultlib
# SUBTRACT LINK32 /verbose
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Create the Disk Image
PostBuild_Cmds=copy /b ..\_image\boot.bin + ..\_output\kernel.exe + ..\_image\prefix.bin ..\_image\disk.bin
# End Special Build Tool
# Begin Target

# Name "kernel - Win32 Release"
# Begin Group "Kernel:Source"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "cpu"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\kernel\ia32\cpu\configPentium.c
# End Source File
# End Group
# Begin Source File

SOURCE=..\kernel\ia32\bootlog.c
# End Source File
# Begin Source File

SOURCE=..\kernel\ia32\cpu.c
# End Source File
# Begin Source File

SOURCE=..\kernel\ia32\debug.c
# End Source File
# Begin Source File

SOURCE=..\kernel\ia32\heap.c
# End Source File
# Begin Source File

SOURCE=..\kernel\kernel.c
# End Source File
# Begin Source File

SOURCE=..\kernel\ia32\mm.c
# End Source File
# End Group
# Begin Group "Kernel:Headers"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\kernel\bootlog.h
# End Source File
# Begin Source File

SOURCE=..\kernel\cpu.h
# End Source File
# Begin Source File

SOURCE=..\kernel\debug.h
# End Source File
# Begin Source File

SOURCE=..\kernel\heap.h
# End Source File
# Begin Source File

SOURCE=..\kernel\mm.h
# End Source File
# End Group
# Begin Group "Library:Source"

# PROP Default_Filter "c"
# Begin Source File

SOURCE=..\lib\mem\memcpy.c
# End Source File
# Begin Source File

SOURCE=..\lib\mem\memset.c
# End Source File
# Begin Source File

SOURCE=..\lib\string\strcmp.c
# End Source File
# Begin Source File

SOURCE=..\lib\string\strcpy.c
# End Source File
# Begin Source File

SOURCE=..\lib\string\strlen.c
# End Source File
# Begin Source File

SOURCE=..\lib\string\strncmp.c
# End Source File
# Begin Source File

SOURCE=..\lib\string\strncpy.c
# End Source File
# End Group
# Begin Group "Library:Headers"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=..\lib\mem.h
# End Source File
# Begin Source File

SOURCE=..\lib\string.h
# End Source File
# End Group
# End Target
# End Project
