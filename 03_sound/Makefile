# If you move this project you can change the directory
# to match your GBDK root directory (ex: GBDK_HOME = "C:/GBDK/"
GBDK_HOME = ../gbdk/

LCC = $(GBDK_HOME)bin/lcc

# You can uncomment the line below to turn on debug output
# LCCFLAGS += -debug # Uncomment to enable debug output
# LCCFLAGS += -v     # Uncomment for lcc verbose output

# You can set the name of the .gb ROM file here
PROJECTNAME    = Sound

BINS	    = $(PROJECTNAME).gb
CSOURCES   := $(wildcard *.c)

all:	$(BINS)

# Compile and link all source files in a single call to LCC
$(BINS):	$(CSOURCES)
	$(LCC) $(LCCFLAGS) -o $@ $(CSOURCES)

clean:
	rm -f *.o *.lst *.map *.gb *.ihx *.sym *.cdb *.adb *.asm
