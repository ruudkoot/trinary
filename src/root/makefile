################################################################################
# Mithrill Core : Makefile                                                     #
# Copyright (c) 2003, Rudy Koot (Mithrill Foundation)                          #
#                                                                              #
# This program is free software; you can redistribute it and/or modify         #
# it under the terms of the GNU General Public License as published by         #
# the Free Software Foundation; either version 2 of the License, or            #
# (at your option) any later version.                                          #
################################################################################

name = root

$(name) : entry.o $(name).o
	ld -s -T$(name).l -o $(name) entry.o $(name).o ../../bin/gcc/libgcc.a
	objcopy $(name) -S -O binary

entry.o : entry.c
	gcc -c -o entry.o entry.c

$(name).o : $(name).c
	gcc -c -o $(name).o $(name).c
