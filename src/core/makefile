################################################################################
# Mithrill Core : Makefile                                                     #
# Copyright (c) 2003, Rudy Koot (Mithrill Foundation)                          #
#                                                                              #
# This program is free software; you can redistribute it and/or modify         #
# it under the terms of the GNU General Public License as published by         #
# the Free Software Foundation; either version 2 of the License, or            #
# (at your option) any later version.                                          #
################################################################################

cc = gcc -c -o
sources     = core.c cpu.c debug.c heap.c ipc.c kdb.c log.c memory.c   \
              schedule.c signal.c smp.c space.c spinlock.c syscall.c system.c  \
              vesa.c ia32/api.c

core : entry.o core.o wrapper.o ipc.o kdb.o
	ld -s -Tcore.l -o core entry.o core.o ipc.o kdb.o wrapper.o ../../bin/gcc/libgcc.a
	objcopy core -S -O elf32-i386

entry.o : ia32/entry.s
	as -o entry.o ia32/entry.s

core.o : $(sources)
	$(cc) core.o core.c

wrapper.o : ia32/wrapper.s
	nasm ia32/wrapper.s -o wrapper.o -f elf

ipc.o : ia32/ipc.s
	as ia32/ipc.s -o ipc.o

kdb.o : ia32/kdb.s
	as ia32/kdb.s -o kdb.o

clean :
	rm core
	rm entry.o
	rm core.o
	rm wrapper.o
	rm ipc.o
	rm kdb.o

