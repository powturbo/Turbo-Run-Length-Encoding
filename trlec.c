/**
    Copyright (C) powturbo 2015-2016
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

    TurboRLE - "Most efficient and fastest Run Length Encoding"
**/
  #ifndef USIZE
#include <string.h> 
#include "conf.h"
#include "trle.h"
#include "trle_.h"
  
//------------------------------------- Histogram ---------------------------------------------------------
static inline unsigned hist(unsigned char *in, unsigned inlen, unsigned *cc) { // Optimized for x86
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
  unsigned a = 256; while(a > 1 && !cc[a-1]) a--; 
  return a;
}

//------------------------------------- RLE with Escape char ------------------------------------------------------------------
#define USIZE 16
#include "trlec.c"
#undef USIZE

#define USIZE 32
#include "trlec.c"
#undef USIZE

#define USIZE 64
#include "trlec.c"
#undef USIZE

  #if 0
#define USIZE 8
#include "trlec.c"
  #else
#define SRLEC8(pp, ip, op, e) do {\
  unsigned i = ip - pp;\
  if(i > 3) { *op++ = e; i -= 3; vbxput(op, i); *op++ = c; }\
  else if(c == e) {\
	while(i--) { *op++ = e; vbxput(op, 0); }\
  } else while(i--) *op++ = c;\
} while(0)

//000000000xx0ppp
// 00000000x........      
unsigned _srlec8(unsigned char *_in, unsigned inlen, unsigned char *out, uint8_t e) {
  uint8_t *in = (uint8_t *)_in, *ip=in, *pp = in - 1; 
  unsigned char *op = out;
  if(inlen <= ALN) goto a;
  unsigned char *in_ = _in + (inlen-ALN);
  for(; ip < in_;) {
      #if 0 //defined(__SSE__)  // SSE not faster than scalar 
	__m128i cv = _mm_set1_epi8(*ip);
	unsigned mask = _mm_movemask_epi8(_mm_cmpeq_epi8(_mm_loadu_si128((const __m128i*)(ip+1)), cv));
	if(mask == 0xffffu) ip += 16;
    else {
      uint8_t c = *ip; ip += __builtin_ctz((unsigned short)(~mask));
      SRLEC8(pp, ip, op, e);
	  pp = ip++;
    }
      #else
    unsigned long long z;
	if(!(z = ctou64(ip) ^ ctou64(ip+1))) 
	  ip += 8;
	else {
      ip += __builtin_ctzll(z)>>3; 				
      if(ip > in_) ip = in_;
      uint8_t c = *ip; 
      SRLEC8(pp, ip, op, e);
	  pp = ip++;
    }
      #endif
  }
  if(ip > in_) ip = in_; 														
  if(pp < ip) { 
    uint8_t c = *ip; 
    SRLEC8(pp, ip, op, e); 
  }
   #if ALN > 1
  a:while(ip < _in+inlen) *op++ = *ip++;
	#endif
  return op - out;
}
#endif

unsigned srlec(unsigned char *in,  unsigned inlen, unsigned char *out) {
  unsigned m = 0xffffffffu, mi = 0, i, b[256] = {0}; 
  if(inlen < 1) return 0;

  unsigned a = hist(in, inlen, b);  		
  if(b[a-1] == inlen) {
    *out = *in;
    return 1;
  }

  for(i = 0; i < 256; i++) 
    if(b[i] <= m) 
	  m = b[i],mi = i;
  *out++ = mi;                                  
  size_t l = _srlec8(in, inlen, out, mi)+1;
  if(l < inlen) return l;
  memcpy(out, in, inlen);
  return inlen;
}

//------------------------------------------------- TurboRLE ------------------------------------------
struct u { unsigned c,i; };										

#define TRLEC(pp, ip, op) do { __label__ a;\
  unsigned i = ip - pp, c = *ip;\
  if(i > 2) {\
    unsigned char *q = op; \
    vbzput(q, i-3, m, rmap); \
    if((q-op) + 1 < i) { op = q; *op++ = c; goto a; }\
  } \
  while(i--) *op++ = c; a:;\
} while(0)

unsigned trlec(unsigned char *in, unsigned inlen, unsigned char *out) {
  unsigned char *ip, *in_ = in+inlen, *op = out,*pp;
  int m,i;
  unsigned b[256] = {0}, rmap[256];
  if(inlen < 1) return 0;

  unsigned a = hist(in,inlen,b);  		
  if(b[a-1] == inlen) {
    *out = *in;
    return 1;
  }
  
  struct u u[256]; // sort
  for(i = 0; i < 256; i++) u[i].c = b[i], u[i].i = i,b[i]=0;  		
  struct u *v;													
  for(v = u + 1; v < u + 256; ++v)
    if(v->c < v[-1].c) { 
	  struct u *w, tmp = *v;
      for(w = v; w > u && tmp.c < w[-1].c; --w) *w = w[-1];
      *w = tmp;
    }  															
  																												
  for(m = -1,i = 0; i < 256 && !u[i].c; i++) 
    b[u[i].i]++, ++m;
  if(m < 0) { // no unused bytes found
    *op++ = 0; 
	*op++ = u[0].i; 
    size_t l = _srlec8(in, inlen, op, u[0].i)+2;
    if(l < inlen) return l;
    memcpy(out, in, inlen);
    return inlen;
  } 																		
  
  *op++ = 1;
  memset(op, 0, 32);
  for(m = -1,i = 0; i < 256; i++) 
    if(b[i]) { 
      op[i>>3] |= 1<<(i&7); rmap[++m] = i; 
    } 
  op += 32;

  for(ip = in, pp = in-1; ip < in+inlen-1; ip++)
    if(*ip != *(ip+1)) {
	  TRLEC(pp, ip, op);
	  pp = ip;
	}
  TRLEC(pp,ip, op);
  
  if(op - out < inlen) 
   return op - out;
  memcpy(out, in, inlen); 
  return inlen; 
}
  #else
#define uint_t TEMPLATE3(uint, USIZE, _t)

#define SRLEC(pp, ip, op, e) do {\
  unsigned i = ip - pp;\
  if(i > 3) { *(uint_t *)op = e; op+=sizeof(uint_t); i -= 3; vbxput(op, i); *(uint_t *)op = c; op+=sizeof(uint_t); }\
  else if(c == e) {\
	while(i--) { *(uint_t *)op = e; op+=sizeof(uint_t); vbxput(op, 0); }\
  } else while(i--) { *(uint_t *)op = c; op+=sizeof(uint_t); }\
} while(0)

unsigned TEMPLATE2(_srlec, USIZE)(unsigned char *_in, unsigned inlen, unsigned char *out, uint_t e) {
  uint_t *in = (uint_t *)_in, *ip, *pp = in-1; 
  unsigned char *op = out;
  for(ip = in; ip < in+inlen/sizeof(uint_t); ip++) { 
    uint_t c = *ip;
    if(c != ip[1]) {
	  SRLEC(pp,ip, op, e);
	  pp = ip;
	}
  }
  uint_t c = *ip; 
  SRLEC(pp, ip, op, e);
  
  if(USIZE > 8) {
    unsigned char *p = (unsigned char *)ip; 
	while(p < _in+inlen) 
	  *op++ = *p++; 
  }
  return op - out;
}
#undef SRLEC
#undef USIZE
  #endif

