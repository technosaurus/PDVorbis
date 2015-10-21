# Makefile for oggplay.

#CC = /usr/i386-linux-uclibc/bin/i386-uclibc-gcc
#CC = diet gcc
#CC = musl-gcc
#CFLAGS = -pipe -Os -mtune=i386 -static -s -Wall -I/usr/i386-linux-uclibc/usr/include
#CFLAGS = -pipe -Os -mtune=i386 -static -s -Wall 
CFLAGS = -Os -ffunction-sections -fdata-sections -fmerge-all-constants \
-fomit-frame-pointer  -fno-unwind-tables -fno-asynchronous-unwind-tables

#LDFLAGS = -L/usr/i386-linux-uclibc/lib -lm -Wl,--gc-sections,--sort-common,-s
LDFLAGS =  -Wl,--gc-sections,-s -lm
#see stb_vorbis for various size vs. speed defines
DEFINES = 
OBJECTS = oggplay.c
BINDIR = /usr/bin

oggplay: $(OBJECTS)
	$(CC) $(CFLAGS) $(DEFINES) $(OBJECTS) $(LDFLAGS) -o oggplay
	
install:
	strip --strip-all -R .note -R .comment oggplay
	install oggplay $(BINDIR)/oggplay
	
uninstall:
	rm -f $(BINDIR)/oggplay
		
clean:
	rm -f *.o oggplay

depend:
	gccmakedep -- $(CFLAGS) -- oggplay.c	
