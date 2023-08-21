LCC = ../gbdk/bin/lcc

# You can set the name of the .gb ROM file here
PROJECTNAME    = 00_Nothing

all:	00_Nothing.gb

# Compile and link all source files in a single call to LCC
00_Nothing.gb:	main.c
	$(LCC) -o $@ main.c

clean:
	rm -f *.o *.lst *.map *.gb *.ihx *.sym *.cdb *.adb *.asm
