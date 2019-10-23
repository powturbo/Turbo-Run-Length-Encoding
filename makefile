# powturbo  (c) Copyright 2015-2019
C# Linux: "export CC=clang" "export CXX=clang". windows mingw: "set CC=gcc" "set CXX=g++" or uncomment the CC,CXX lines
CC ?= gcc
CXX ?= g++
#CC=clang-8
#CXX=clang++-8

#CC = gcc-8
#CXX = g++-8

#CC=powerpc64le-linux-gnu-gcc
#CXX=powerpc64le-linux-gnu-g++

DDEBUG=-DNDEBUG -s
#DDEBUG=-g

ifneq (,$(filter Windows%,$(OS)))
  OS := Windows
CFLAGS+=-D__int64_t=int64_t
else
  OS := $(shell uname -s)
  ARCH := $(shell uname -m)
ifneq (,$(findstring powerpc64le,$(CC)))
  ARCH = ppc64le
endif
ifneq (,$(findstring aarch64,$(CC)))
  ARCH = aarch64
endif
endif

#------ ARMv8 
ifeq ($(ARCH),aarch64)
ifneq (,$(findstring clang, $(CC)))
MSSE=-O3 -march=armv8-a -mcpu=cortex-a72 -falign-loops -fomit-frame-pointer 
else
MSSE=-O3 -march=armv8-a -mcpu=cortex-a72 -falign-loops -falign-labels -falign-functions -falign-jumps -fomit-frame-pointer
endif

else
# ----- Power9
ifeq ($(ARCH),ppc64le)
MSSE=-D__SSE__ -D__SSE2__ -D__SSE3__ -D__SSSE3__
MARCH=-march=power9 -mtune=power9
CFLAGS+=-DNO_WARN_X86_INTRINSICS
CXXFLAGS+=-DNO_WARN_X86_INTRINSICS
#------ x86_64 : minimum SSE = Sandy Bridge,  AVX2 = haswell 
else
MSSE=-march=corei7-avx -mtune=corei7-avx
# -mno-avx -mno-aes (add for Pentium based Sandy bridge)
CFLAGS+=-mssse3
MAVX2=-march=haswell
endif
endif

ifeq ($(OS),$(filter $(OS),Linux Darwin GNU/kFreeBSD GNU OpenBSD FreeBSD DragonFly NetBSD MSYS_NT Haiku))
LDFLAGS+=-lpthread -lm
ifneq ($(OS),Darwin)
LDFLAGS+=-lrt
endif
endif

# Minimum CPU architecture 
#MARCH=-march=native
MARCH=$(MSSE)

ifeq ($(AVX2),1)
MARCH+=-mbmi2 -mavx2
#CFLAGS+=-DUSE_AVX2
#CXXFLAGS+=-DUSE_AVX2
else
AVX2=0
endif

CFLAGS+=$(DDEBUG) -w -Wall -std=gnu99 -DUSE_THREADS  -fstrict-aliasing -Iext $(DEFS)
CXXFLAGS+=$(DDEBUG) -w -fpermissive -Wall -fno-rtti -Iext/FastPFor/headers $(DEFS)

all: trle

trle.o: $(TP)trle.c
	$(CC) -O2 $(CFLAGS) $(MARCH) -c $(TP)trle.c -o trle.o

trle: trlec.o trled.o trle.o
	$(CC) trle.o trlec.o trled.o $(LDFLAGS) -o trle
 
.c.o:
	$(CC) -O3 $(CFLAGS) $(MARCH) $< -c -o $@

clean:
	rm  *.o

cleanw:
	del .\*.o

