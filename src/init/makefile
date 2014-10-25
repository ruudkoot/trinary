################################################################################
# Mithrill Core : Makefile                                                     #
# Copyright (c) 2003, Rudy Koot (Mithrill Foundation)                          #
#                                                                              #
# This program is free software; you can redistribute it and/or modify         #
# it under the terms of the GNU General Public License as published by         #
# the Free Software Foundation; either version 2 of the License, or            #
# (at your option) any later version.                                          #
################################################################################

as = as --32
cc = gcc -m32 -fno-stack-protector
ld = ld -m elf_i386

init : init.o pm32s.o pm32c.o init.l
	$(ld) -s -Tinit.l -o init init.o pm32s.o pm32c.o
	objcopy init -S -O binary

init.o : init.l ext2.c fat.c heap.c ibm.c init.c mem.c repository.c      \
         trifs.c ia32/ibm/a20.c ia32/ibm/entry.s ia32/ibm/disk.c               \
         ia32/ibm/log.c ia32/ibm/memory.c ia32/ibm/system.c
	$(cc) -Os -S -o init.s init.c
	cat ia32/ibm/entry.s init.s > init.t
	$(as) -o init.o init.t

pm32c.o : pm32.c log.c
	$(cc) -c -o pm32c.o pm32.c

pm32s.o : pm32.s
	$(as) -o pm32s.o pm32.s

