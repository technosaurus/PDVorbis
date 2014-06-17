# Makefile for oggplay.

#CC = /usr/i386-linux-uclibc/bin/i386-uclibc-gcc
#CC = diet gcc
#cc = musl-gcc
#CFLAGS = -pipe -Os -mtune=i386 -static -s -Wall -I/usr/i386-linux-uclibc/usr/include
#CFLAGS = -pipe -Os -mtune=i386 -static -s -Wall 
CFLAGS = -Os -finline-small-functions -ffunction-sections -fdata-sections -fmerge-all-constants


#LDFLAGS = -L/usr/i386-linux-uclibc/lib -lm -Wl,--gc-sections,--sort-common,-s
LDFLAGS =  -Wl,--gc-sections,-s -lm
#see stb_vorbis for various size vs. speed defines
DEFINES = 
OBJECTS = oggplay.c
BINDIR = /usr/bin

oggplay: $(OBJECTS)
	$(CC) $(CFLAGS) $(DEFINES) $(OBJECTS) $(LDFLAGS) -o oggplay
	
install:
	install oggplay $(BINDIR)/minimp3
	
uninstall:
	rm -f $(BINDIR)/minimp3
		
clean:
	rm -f *.o oggplay

depend:
	gccmakedep -- $(CFLAGS) -- oggplay.c	

