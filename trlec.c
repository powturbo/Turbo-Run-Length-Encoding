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

    TurboRLE - "Most efficient and fastest Run Length Encoding"
**/
#include <string.h> 
#include "trle.h"
#include "trle_.h"
  
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
#define USIZE 8
#include "srlec_.h"

#define USIZE 16
#include "srlec_.h"

#define USIZE 32
#include "srlec_.h"

#define USIZE 64
#include "srlec_.h"

unsigned srlec(unsigned char *in,  unsigned inlen, unsigned char *out) {
  unsigned m = 0xffffffffu, mi = 0, i, b[256] = {0}; 
  if(inlen < 1) return 0;

  hist(in,inlen,b);  		
  
  for(i = 0; i < 256; i++) 
    if(b[i] <= m) 
	  m = b[i],mi = i;
  *out++ = mi; 
  return _srlec8(in, inlen, out, mi)+1;
}

//------------------------------------------------- TurboRLE ------------------------------------------
struct u { unsigned c,i; };										//int ucmp(struct u *a, struct u *b) { if(a->c  < b->c) return -1; if(a->c  > b->c) return  1; return 0;}

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
  hist(in,inlen,b);  											//for(ip = in; ip < in_; ip++) b[*ip]++;
  
  struct u u[256]; // sort
  for(i = 0; i < 256; i++) u[i].c = b[i], u[i].i = i,b[i]=0;  	//qsort(u, 256, sizeof(u[0]), (int(*)(const void*,const void*))ucmp);	
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
    *op++ = 1; 
	*op++ = u[0].i; 
    if((i = _srlec8(in, inlen, op, u[0].i)+2) < inlen) 
	  return i;
	  
	out[0] = 0; 
	memcpy(out+1,in,inlen); 
	return inlen+1;
  } 																		
  
  *op++ = 2; 
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
  
  if(op - out >= inlen) { 
    out[0] = 0; 
	memcpy(out+1,in,inlen); 
	return inlen+1; 
  }
  return op - out;
}
