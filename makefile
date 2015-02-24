# powturbo  (c) Copyright 2015
CFLAGS=-march=native -minline-all-stringops

UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
LIBRT=-lrt
endif

all: trle

#trled.o: trle_.h trle.h trled.c
#	gcc -O3 $(CFLAGS) -c trled.c

trle: trlec.o trled.o trle.o
	gcc trle.o trlec.o trled.o $(LIBRT) -o trle
 
.c.o:
	gcc -O3 $(CFLAGS) $< -c -o $@

clean:
	rm  *.o

cleanw:
	del .\*.o
