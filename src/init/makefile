################################################################################
# Mithrill Core : Makefile                                                     #
# Copyright (c) 2003, Rudy Koot (Mithrill Foundation)                          #
#                                                                              #
# This program is free software; you can redistribute it and/or modify         #
# it under the terms of the GNU General Public License as published by         #
# the Free Software Foundation; either version 2 of the License, or            #
# (at your option) any later version.                                          #
################################################################################

init : init.o pm32s.o pm32c.o init.l
	ld -s -Tinit.l -o init init.o pm32s.o pm32c.o
	objcopy init -S -O binary

init.o : init.c ia32\ibm\entry.s
	gcc -Os -S -o init.s init.c
	copy ia32\ibm\entry.s + init.s init.t
	as -o init.o init.t

pm32c.o : pm32.c
	gcc -c -o pm32c.o pm32.c

pm32s.o : pm32.s
	as -o pm32s.o pm32.s

