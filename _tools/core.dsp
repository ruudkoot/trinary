# Microsoft Developer Studio Project File - Name="core" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=core - Win32 Trinary
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "core.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "core.mak" CFG="core - Win32 Trinary"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "core - Win32 Trinary" (based on "Win32 (x86) Application")
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
# PROP BASE Output_Dir "Trinary"
# PROP BASE Intermediate_Dir "Trinary"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../_output/"
# PROP Intermediate_Dir "../_output/"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /G3 /Gr /W4 /O2 /X /I "../lib/" /I "../core/" /FAs /FD /TP /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x413 /d "NDEBUG"
# ADD RSC /l 0x413 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 ../_output/entry.obj /nologo /base:"0xC0000000" /entry:"entry" /subsystem:windows /pdb:none /map /machine:I386 /nodefaultlib
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Desc=Finishing...
PostBuild_Cmds=cd ..	build
# End Special Build Tool
# Begin Target

# Name "core - Win32 Trinary"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "lib"

# PROP Default_Filter ""
# Begin Group "string"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\lib\string\strcat.c
# End Source File
# Begin Source File

SOURCE=..\lib\string\strchr.c
# End Source File
# Begin Source File

SOURCE=..\lib\string\strcmp.c
# End Source File
# Begin Source File

SOURCE=..\lib\string\strcpy.c
# End Source File
# Begin Source File

SOURCE=..\lib\string\strcspn.c
# End Source File
# Begin Source File

SOURCE=..\lib\string\stricmp.c
# End Source File
# Begin Source File

SOURCE=..\lib\string\strlen.c
# End Source File
# Begin Source File

SOURCE=..\lib\string\strlwr.c
# End Source File
# Begin Source File

SOURCE=..\lib\string\strncmp.c
# End Source File
# Begin Source File

SOURCE=..\lib\string\strncpy.c
# End Source File
# Begin Source File

SOURCE=..\lib\string\strnicmp.c
# End Source File
# Begin Source File

SOURCE=..\lib\string\strnpst.c
# End Source File
# Begin Source File

SOURCE=..\lib\string\strnset.c
# End Source File
# Begin Source File

SOURCE=..\lib\string\strpbrk.c
# End Source File
# Begin Source File

SOURCE=..\lib\string\strpst.c
# End Source File
# Begin Source File

SOURCE=..\lib\string\strrchr.c
# End Source File
# Begin Source File

SOURCE=..\lib\string\strrev.c
# End Source File
# Begin Source File

SOURCE=..\lib\string\strset.c
# End Source File
# Begin Source File

SOURCE=..\lib\string\strspn.c
# End Source File
# Begin Source File

SOURCE=..\lib\string\strstr.c
# End Source File
# Begin Source File

SOURCE=..\lib\string\strupr.c
# End Source File
# End Group
# Begin Group "mem"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\lib\mem\memccpy.c
# End Source File
# Begin Source File

SOURCE=..\lib\mem\memchr.c
# End Source File
# Begin Source File

SOURCE=..\lib\mem\memcmp.c
# End Source File
# Begin Source File

SOURCE=..\lib\mem\memcpy.c
# End Source File
# Begin Source File

SOURCE=..\lib\mem\memicmp.c
# End Source File
# Begin Source File

SOURCE=..\lib\mem\memmove.c
# End Source File
# Begin Source File

SOURCE=..\lib\mem\memset.c
# End Source File
# End Group
# Begin Group "math"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\lib\math\abs.c
# End Source File
# Begin Source File

SOURCE=..\lib\math\max.c
# End Source File
# Begin Source File

SOURCE=..\lib\math\min.c
# End Source File
# Begin Source File

SOURCE=..\lib\math\rotl.c
# End Source File
# Begin Source File

SOURCE=..\lib\math\rotr.c
# End Source File
# End Group
# Begin Group "convert"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\lib\convert\atoi.c
# End Source File
# Begin Source File

SOURCE=..\lib\convert\atoq.c
# End Source File
# End Group
# Begin Group "char"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\lib\char\isalnum.c
# End Source File
# Begin Source File

SOURCE=..\lib\char\isalpha.c
# End Source File
# Begin Source File

SOURCE=..\lib\char\isascii.c
# End Source File
# Begin Source File

SOURCE=..\lib\char\iscsym.c
# End Source File
# Begin Source File

SOURCE=..\lib\char\iscsymf.c
# End Source File
# Begin Source File

SOURCE=..\lib\char\isctrl.c
# End Source File
# Begin Source File

SOURCE=..\lib\char\isdigit.c
# End Source File
# Begin Source File

SOURCE=..\lib\char\isgraph.c
# End Source File
# Begin Source File

SOURCE=..\lib\char\islower.c
# End Source File
# Begin Source File

SOURCE=..\lib\char\isprint.c
# End Source File
# Begin Source File

SOURCE=..\lib\char\ispunct.c
# End Source File
# Begin Source File

SOURCE=..\lib\char\isspace.c
# End Source File
# Begin Source File

SOURCE=..\lib\char\isupper.c
# End Source File
# Begin Source File

SOURCE=..\lib\char\isxdigit.c
# End Source File
# Begin Source File

SOURCE=..\lib\char\tolower.c
# End Source File
# Begin Source File

SOURCE=..\lib\char\toupper.c
# End Source File
# End Group
# End Group
# Begin Group "core"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\core\ia32\bootlog.c
# End Source File
# Begin Source File

SOURCE=..\core\core.c
# End Source File
# Begin Source File

SOURCE=..\core\ia32\cpu.c
# End Source File
# Begin Source File

SOURCE=..\core\ia32\debug.c
# End Source File
# Begin Source File

SOURCE=..\core\entry.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\core\ia32\heap.c
# End Source File
# Begin Source File

SOURCE=..\core\ia32\io.c
# End Source File
# Begin Source File

SOURCE=..\core\ia32\mm.c
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\core\bootlog.h
# End Source File
# Begin Source File

SOURCE=..\lib\char.h
# End Source File
# Begin Source File

SOURCE=..\core\cpu.h
# End Source File
# Begin Source File

SOURCE=..\core\debug.h
# End Source File
# Begin Source File

SOURCE=..\core\heap.h
# End Source File
# Begin Source File

SOURCE=..\core\io.h
# End Source File
# Begin Source File

SOURCE=..\lib\mem.h
# End Source File
# Begin Source File

SOURCE=..\core\mm.h
# End Source File
# Begin Source File

SOURCE=..\lib\string.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
