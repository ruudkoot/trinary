;******************************************************************************;
;* System Initialization Entry Point                                          *;
;* Copyright (c) 2003, Rudy Koot (Trinary Technologies)                       *;
;*                                                                            *;
;* This program is free software; you can redistribute it and/or modify       *;
;* it under the terms of the GNU General Public License as published by       *;
;* the Free Software Foundation; either version 2 of the License, or          *;
;* (at your option) any later version.                                        *;
;******************************************************************************;

;******************************************************************************;
;* This modules initializes the Real Mode environment, before starting the C  *;
;* entry point of the System Initializer.                                     *;
;******************************************************************************;

bits 16
extern _init_entry
section text class=code public align=16 use16

_init_realmodeinit:

	;* Set up the data segements and the stack.                               *;
	mov ax, cs
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov sp, 0xFFFF

    ;* Start the main entry point of the System Initializor.                  *;
	jmp _init_entry

group init text