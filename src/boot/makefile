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
ld = ld -m elf_i386

trifs : trifs.o
	$(ld) -s -Tia32/ibm/trifs.l -o trifs trifs.o
	objcopy -O binary trifs

trifs.o : ia32/ibm/trifs.s
	$(as) -o trifs.o ia32/ibm/trifs.s
