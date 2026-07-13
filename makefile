# powturbo  (c) Copyright 2015-2026
# Linux: "export CC=clang" "export CXX=clang". windows mingw: "set CC=gcc" "set CXX=g++" or uncomment the CC,CXX lines
CC ?= gcc
#CC ?= clang
CXX ?= g++
CX ?= clang
#CX ?= gcc
#CC = clang

#DEBUG=-DDEBUG -g
DEBUG=-DNDEBUG
JAVA_HOME ?= /usr/lib/jvm/java-8-openjdk-amd64
PREFIX ?= /usr/local
DIRBIN ?= $(PREFIX)/bin
DIRINC ?= $(PREFIX)/include
DIRLIB ?= $(PREFIX)/lib
SRC ?= lib/

#------- OS/ARCH -------------------
ifneq (,$(filter Windows%,$(OS)))
  OS := Windows
  CC=gcc
# CC=clang
# CX=gcc
  CX=clang
  CXX=g++
  ARCH=x86_64
else
  OS := $(shell uname -s)
  ARCH := $(shell uname -m)
endif
#$(info OS="$(OS)")

ifndef CROSS
else
ifeq ($(OS), Windows)
CP=$(CROSS)-unknown-elf
else
CP=$(CROSS)-linux-gnu
endif

CXX:=$(CP)-g++
ifeq ($(CX),clang)
CX=clang --target=$(CP) --sysroot=/usr/$(CP) -fuse-ld=lld
ifeq ($(CC),clang)
CC=$(CX)
else
CC:=$(CP)-gcc
endif
else
CC:=$(CP)-gcc
CX=$(CC)
endif

endif

ifneq (,$(findstring aarch64,$(CC) $(ARCH)))
  ARCH = aarch64
else ifneq (,$(findstring riscv64,$(CC) $(ARCH)))
  ARCH = riscv64
else ifneq (,$(findstring iPhone,$(ARCH)))
  ARCH = aarch64
  CFLAGS=-DHAVE_MALLOC_MALLOC
else ifneq (,$(findstring powerpc64le,$(CC) $(ARCH)))
  ARCH = ppc64le
else ifneq (,$(findstring loongarch64,$(CC) $(ARCH)))
  ARCH = loongarch64
else ifneq (,$(findstring x86_64,$(CC) $(ARCH)))
  ARCH = x86_64
endif

ifeq ($(ARCH),aarch64)
  _SSE=-march=armv8-a
  CFLAGS+=$(_SSE)
else ifeq ($(ARCH),riscv64)
#  CFLAGS=-march=rv64gcv -mabi=lp64d
  CFLAGS=-march=rv64gcv_zvbb -mabi=lp64d
else ifeq ($(ARCH),ppc64le)
  _SSE=-D__SSE4_1__
  CFLAGS=-mcpu=power9 -mtune=power9 $(_SSE)
else ifeq ($(ARCH),loongarch64)
  _SSE=-mlsx
  CFLAGS=$(_SSE)
else ifeq ($(ARCH),x86_64)
# _SSE=-mssse3 
# _SSE+=-mno-avx -mno-aes
# _SSE=-march=corei7-avx -mtune=corei7-avx
# _SSE=-march=ivybridge -mavx
  _SSE=-mavx -mpopcnt

# _AVX2=-march=skylake-avx512 -mavx512vbmi -mavx512f -mavx512vl
  _AVX2=-march=haswell
endif

CFLAGS+=-fstrict-aliasing -fPIC 
#-Wuninitialized

ifeq (,$(findstring clang, $(CC)))
  CFLAGS+=-fomit-frame-pointer -falign-loops
#-fmacro-backtrace- -fpermissivelimit=0
#OPT+=-O3 -DNDEBUG -ffp-contract=off -ffunction-sections -fdata-sections -fstrict-aliasing -falign-functions=64 -fomit-frame-pointer -ftree-vectorize -funroll-loops
endif

CFLAGS+=$(DEBUG) -w 
#-Wno-incompatible-pointer-types -pedantic #-Wno-macro-redefined #-Wall -Wno-tautological-constant-out-of-range-compare
CXXFLAGS+=-w

ifeq ($(OS),$(filter $(OS),Linux GNU/kFreeBSD GNU OpenBSD FreeBSD DragonFly NetBSD MSYS_NT Haiku))
LDFLAGS+=-lrt -lm
endif

ifeq ($(STATIC),1)
CFLAGS+=-D_STATIC
LDFLAGS+=-static
endif

CFLAGS+=$(DDEBUG) -w -Wall -std=gnu99 -DUSE_THREADS  -fstrict-aliasing -Iext $(DEFS) -Wincompatible-pointer-types
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

