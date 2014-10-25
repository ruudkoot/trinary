################################################################################
# Mithrill Core : Makefile                                                     #
# Copyright (c) 2003, Rudy Koot (Mithrill Foundation)                          #
#                                                                              #
# This program is free software; you can redistribute it and/or modify         #
# it under the terms of the GNU General Public License as published by         #
# the Free Software Foundation; either version 2 of the License, or            #
# (at your option) any later version.                                          #
################################################################################

name = test

$(name) : entry.o $(name).o
	ld -m elf_i386 -s -T$(name).l -o $(name) entry.o $(name).o
	objcopy $(name) -S -O binary

entry.o : entry.c
	gcc -m32 -c -o entry.o entry.c

$(name).o : $(name).c
	gcc -m32 -c -o $(name).o $(name).c
