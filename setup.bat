@ECHO Insert a formatted disk in drive A: and press any key to continue.
@ECHO (All data on that disk will be earased!)
@PAUSE > NUL
@ECHO Writing Boot Disk...
@_setup\rawrite -f _image\disk.bin -d a -n
@ECHO Done!
@PAUSE > NUL