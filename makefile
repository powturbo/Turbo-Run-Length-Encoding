# powturbo  (c) Copyright 2015
CFLAGS=-march=native -minline-all-stringops

all: trle

trled.o: trle_.h trle.h trled.c
	gcc -O2 $(CFLAGS) -c trled.c

trle: trlec.o trled.o trle.o
	gcc trle.o trlec.o trled.o -o trle
 
.c.o:
	gcc -O3 $(CFLAGS) $< -c -o $@

clean:
	rm  *.o

cleanw:
	del .\*.o
