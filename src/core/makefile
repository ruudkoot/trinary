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
              vesa.c

core : core.o
	ld -o core core.o 

entry.o : entry.c
	$(cc) entry.o entry.c

core.o : $(sources)
	$(cc) core.c

clean :
	rm core.o