/**
    Copyright (C) powturbo 2015
    GPL v2 License

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

    - email    : powturbo [AT] gmail.com
    - github   : https://github.com/powturbo
    - homepage : https://sites.google.com/site/powturbo/
    - twitter  : https://twitter.com/powturbo

    TurboRLE - "Efficient Run Length Encoding"
**/
#include <string.h>

#define likely(x)     	__builtin_expect((x),1)
#define unlikely(x)   	__builtin_expect((x),0)
//------------------------------------- Variable Byte -----------------------------------------------------
#define vbputx(__op, __x)  { typeof(__x) _x = __x; while(_x > 0x7f) { *__op++ =      _x & 0x7f;       _x >>= 7; }  *__op++ =     _x | 0x80; }

#define vbgetax(__ip, __x, __act) { unsigned _sft=0; for(__x=0;;_sft += 7) { unsigned _c = *__ip++; __x += (_c & 0x7f) << _sft; if(_c >= 0x80) { __act; break; } } }
#define vbgetx(__ip) ({ unsigned _x; vbgetax(__ip, _x, ;); _x; })

#define vbxput(__op, __x) { *__op++ = __x; if(unlikely((__x) >= 0xff)) { unsigned _xi = (__x) - 0xff; __op[-1] = 0xff; vbputx(__op, _xi); } }
#define vbxget(__ip, __x) { __x = *__ip++; if(unlikely( __x == 0xff)) { __x = vbgetx(__ip); __x+=0xff; } }

#define vbzput(__op, __x, __m, __emap) do { if(unlikely((__x) < __m)) *__op++ = __emap[__x]; else { unsigned _xi = (__x) - __m; *__op++ = __emap[__m]; vbputx(__op, _xi); } } while(0)
#define vbzget(__ip, __x, __m, __e) { __x = __e; if(unlikely( __x == __m)) { __x = vbgetx(__ip); __x+=__m; } }

//------------------------------------- Histogram ---------------------------------------------------------
static inline void hist(unsigned char *in, unsigned inlen, unsigned *cc) { // Optimized for x86
  unsigned c0[256+8]={0},c1[256+8]={0},c2[256+8]={0},c3[256+8]={0},c4[256+8]={0},c5[256+8]={0},c6[256+8]={0},c7[256+8]={0}; 

  unsigned char *ip;
  unsigned 					  cp = *(unsigned *)in;  
  for(ip = in; ip != in+(inlen&~(16-1));) {  
    unsigned 	c = cp,	d = *(unsigned *)(ip+=4); cp = *(unsigned *)(ip+=4);    
    c0[(unsigned char) c    ]++;
    c1[(unsigned char) d    ]++;
    c2[(unsigned char)(c>>8)]++; c>>=16;
    c3[(unsigned char)(d>>8)]++; d>>=16; 
    c4[(unsigned char) c    ]++;
    c5[(unsigned char) d    ]++;
    c6[ 	           c>>8 ]++;
    c7[ 	           d>>8 ]++; 
    
    		c = cp;	d = *(unsigned *)(ip+=4); cp = *(unsigned *)(ip+=4);    
    c0[(unsigned char) c    ]++;
    c1[(unsigned char) d    ]++;
    c2[(unsigned char)(c>>8)]++; c>>=16;
    c3[(unsigned char)(d>>8)]++; d>>=16;
    c4[(unsigned char) c    ]++;
    c5[(unsigned char) d    ]++;
    c6[ 	           c>>8 ]++;
    c7[ 	           d>>8 ]++; 
  }
  while(ip < in+inlen) c0[*ip++]++; 

  int i;
  for(i = 0; i < 256; i++) 
    cc[i] += c0[i]+c1[i]+c2[i]+c3[i]+c4[i]+c5[i]+c6[i]+c7[i];
}

//------------------------------------- RLE with Escape char ------------------------------------------------------------------
unsigned _srlec(unsigned char *in, unsigned inlen, unsigned char* out, int e) {
  unsigned char *ip = in, *in_ = in+inlen, *op = out;
  int c, pc = -1, i = 0;
  if(inlen < 1) return 0;
  do {
    c = ip < in_?*ip++:-1;
    if(pc == c) ++i;
	else if(i > 3) { *op++ = e;
 	  i -= 3; vbxput(op, i); 
	  *op++ = pc;
	  i = 1; 
	} else if(pc == e) { 													
	  while(i--) { *op++ = e; vbxput(op, 0); } i = 1;
    } else { while(i--) *op++ = pc; i = 1; }
  } while((pc = c) != -1); 
  return op - out;
}

int _srled(unsigned char *in, unsigned char *out, int outlen, int e) {
  unsigned char *ip = in, *op = out; int c;
  while(op < out+outlen) { 
    if((c = *ip++) != e) *op++ = c;
	else { 
	  int i; vbxget(ip, i);
	  if(!i) *op++ = e;
	  else for(c = *ip++,i += 3;i--;) *op++ = c; 
    }
  }
  return ip - in;
}

int srlec(unsigned char *in,  int inlen, unsigned char *out) {
  unsigned m = 0xffffffffu, mi = 0, i, b[256] = {0}; 
  if(inlen < 1) return 0;

  hist(in,inlen,b);  		
  
  for(i = 0; i < 256; i++) if(b[i] <= m) m = b[i],mi = i;
  *out++ = mi; 
  return _srlec(in, inlen, out, mi)+1;
}

int srled(unsigned char *in, unsigned char *out, int outlen) { return _srled(in+1, out, outlen, *in); }

//------------------------------------------------- TurboRLE ------------------------------------------
struct u { unsigned c,i; };										//int ucmp(struct u *a, struct u *b) { if(a->c  < b->c) return -1; if(a->c  > b->c) return  1; return 0;}

int trlec(unsigned char *in, int inlen, unsigned char *out) {
  unsigned char *ip, *in_ = in+inlen, *op = out;
  int m,i; 
  unsigned b[256] = {0}, rmap[256]; 
  if(inlen < 1) return 0;
  hist(in,inlen,b);  											//for(ip = in; ip < in_; ip++) b[*ip]++;
  
  struct u u[256]; // sort
  for(i = 0; i < 256; i++) u[i].c = b[i], u[i].i = i,b[i]=0;  	//qsort(u, 256, sizeof(u[0]), (int(*)(const void*,const void*))ucmp);	
  struct u *v;													
  for(v = u + 1; v < u + 256; ++v)
    if(v->c < v[-1].c) { struct u *w, tmp = *v;
      for(w = v; w > u && tmp.c < w[-1].c; --w) *w = w[-1];
      *w = tmp;
    }  															
																			
  for(m = -1,i = 0; i < 256 && !u[i].c; i++) b[u[i].i]++, ++m;
  if(m < 0) { // no unused bytes found
    *op++ = 1; *op++ = u[0].i; 
    if((i = _srlec(in, inlen, op, u[0].i)+2) < inlen) return i;
	out[0] = 0; memcpy(out+1,in,inlen); return inlen+1;
  } 																		
  
  *op++ = 2; 
  memset(op, 0, 32);
  for(m = -1,i = 0; i < 256; i++) if(b[i]) { op[i>>3] |= 1<<(i&7); rmap[++m] = i; } 
  op += 32;
  
  int c, pc = -1; i = 0; ip = in;
  do {
    c = ip < in_?*ip++:-1;
    if(pc == c) ++i;
    else {	
	  if(i > 2) {
	    unsigned char *q = op; 
	    vbzput(q, i-3, m, rmap); 
	    if((q-op) + 1 < i) { op = q; *op++ = pc; i = 1; goto a; }
	  } 
	  while(i--) *op++ = pc; i = 1;
	} a:;
  } while((pc = c) != -1);  
  if(op - out >= inlen) { out[0] = 0; memcpy(out+1,in,inlen); return inlen+1; }
  return op - out;
} 
 
int trled(unsigned char *in, unsigned char *out, int outlen) {
  int m = -1,i,c; 
  unsigned char *ip,*out_ = out+outlen, b[256]={0};  
  if(outlen < 1) return 0;

  if(!*in) { memcpy(out,in+1,outlen); return outlen+1; }
  if(*in++ == 1) return _srled(in+1, out, outlen, *in)+2;
  
  for(ip = in; ip < in+32; ip++)
    for(i = 0; i < 8; ++i) 
	  if(((*ip) >> i) & 1) b[(ip-in)<<3 | i] = ++m+1; 		
		
  while(out < out_)
    if(!(c=b[*ip])) *out++ = *ip++; 						
	else { ip++; 
	  vbzget(ip, i, m, c-1);
	  c = *ip++; i+=3; while(i--) *out++ = c; 						
    }
  return ip - in;
}

//------------------------------------ RLE Benchmark --------------------------------------------------------------
// Compile : gcc -O3 -march=native trle.c -o trle
#define TEST
#ifdef TEST
//-------------------------------------- Time ---------------------------------------------------------------------  
typedef unsigned long long tm_t;
#define TM_T 1000000.0
 
  #ifdef _WIN32
#include <windows.h>
static LARGE_INTEGER tps;
static tm_t tmtime(void) { LARGE_INTEGER tm; QueryPerformanceCounter(&tm); return (tm_t)(tm.QuadPart*1000000/tps.QuadPart); }
static tm_t tminit() { QueryPerformanceFrequency(&tps); tm_t t0=tmtime(),ts; while((ts = tmtime())==t0); return ts; } 
  #else
#include <time.h>
//static   tm_t tmtime(void)    { struct timeval tm; gettimeofday(&tm, NULL); return (tm_t)tm.tv_sec*1000000ull + tm.tv_usec; }
static   tm_t tmtime(void)    { struct timespec tm; clock_gettime(CLOCK_MONOTONIC, &tm); return (tm_t)tm.tv_sec*1000000ull + tm.tv_nsec/1000; }
static   tm_t tminit()        { tm_t t0=tmtime(),ts; while((ts = tmtime())==t0); return ts; }
  #endif
//---------------------------------------- bench ---------------------------------------------------------------------
#define TMPRINT(__x) { printf("%7.2f MB/s\t%s", (double)(tc>=0.000001?(((double)n*it/MBS)/(((double)tc/1)/TM_T)):0.0), __x); }
#define TMBEG for(t0 = tminit(), it=0; it < reps;) { r = 0;
#define TMEND it++; if((tc = tmtime() - t0) > tx) break; } tc = tmtime() - t0
#define MBS 1000000.0 //MiBS 1048576.0
//-------------------------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <getopt.h>
#include "mrle.c"

unsigned argtoi(char *s) {
  char *p; unsigned n = strtol(s, &p, 10),f=1; 
  switch(*p) {
     case 'k': f = 1000;       break;
     case 'm': f = 1000000;    break;
     case 'g': f = 1000000000; break;
     case 'K': f = 1<<10; 	   break;
     case 'M': f = 1<<20; 	   break;
     case 'G': f = 1<<30; 	   break;
  }
  return n*f;
}

int main(int argc, char *argv[]) { int b = 1 << 30;
  int c, digit_optind = 0, this_option_optind = optind ? optind : 1, option_index = 0;
  static struct option long_options[] = { {"blocsize", 	0, 0, 'b'}, {0,0, 0, 0}  };
  for(;;) {
    if((c = getopt_long(argc, argv, "b:", long_options, &option_index)) == -1) break;
    switch(c) {
      case  0 : printf("Option %s", long_options[option_index].name); if(optarg) printf (" with arg %s", optarg);  printf ("\n"); break;								
      case 'b': b = argtoi(optarg); break;
    }
  }
  if(argc - optind < 1) { fprintf(stderr, "File not specified\n"); exit(-1); }

  unsigned char *in,*out;
  char *inname = argv[1];  

  FILE *fi = fopen(inname,  "rb"); if(!fi ) perror(inname), exit(1);  							
  fseek(fi, 0, SEEK_END); long long flen = ftell(fi); fseek(fi, 0, SEEK_SET);
  if(flen > b) flen = b;
  int n = flen; 
  if(!(in  = (unsigned char*)malloc(n))) { fprintf(stderr, "malloc error\n"); exit(-1); }
  if(!(out = (unsigned char*)malloc(flen*4/3+1024))) { fprintf(stderr, "malloc error\n"); exit(-1); }
  n = fread(in, 1, n, fi);
  fclose(fi);
  if(n <= 0) exit(0); 																			printf("'%s' %u\n", inname,n);
    
  unsigned reps=1<<30;
  tm_t tx = 2000000;
  unsigned l;										        int r,k,it; tm_t t0,tc,c0,cc;
  
  TMBEG ; l = trlec(in, n, out); TMEND; printf("size=%10u C-Time=", l); TMPRINT("D-Time="); TMBEG trled(out, in, n); TMEND; TMPRINT("TurboRLE\n");
  TMBEG ; l = srlec(in, n, out); TMEND; printf("size=%10u C-Time=", l); TMPRINT("D-Time="); TMBEG srled(out, in, n); TMEND; TMPRINT("TurboRLE esc\n");;
  TMBEG ; l = mrlec(in, n, out); TMEND; printf("size=%10u C-Time=", l); TMPRINT("D-Time="); TMBEG mrled(out, in, n); TMEND; TMPRINT("Mespotine RLE\n");
}
#endif

