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
**/
//    TurboRLE - "Most efficient and fastest Run Length Encoding"
  #ifndef USIZE
#include <string.h>
#include "conf.h"
#include "trle.h"
#include "trle_.h"

//#define MEMSAFE         
//------------------------------------- RLE with Escape char ------------------------------------------------------------------
#define USIZE 8
#include "trled.c"
 
unsigned _srled8(uint8_t *in, uint8_t *_out, unsigned outlen, uint8_t e) { 
  uint8_t *out = (uint8_t *)_out, *op = out, c, *out_ = _out+(outlen -/*& ~*/(ALN)), *ip = in;
  if(outlen <= ALN) 
    goto a;
    #ifdef __SSE__    
  __m128i ev = _mm_set1_epi8(e);
    #else
  uint64_t ev = (uint32_t)e<<24 | (uint32_t)e<<16 | (uint32_t)e<<8 | e; ev |= ev<<32;
    #endif   
  while(op < out_) {
      #ifdef __SSE__    
    __m128i v = _mm_loadu_si128((const __m128i*)ip);
	uint32_t mask = _mm_movemask_epi8(_mm_cmpeq_epi8(v, ev));  
	_mm_storeu_si128((__m128i *)op, v);
    if(!mask) op += 16, ip += 16;
    else {
      uint32_t i = __builtin_ctz(mask); op += i; ip += i+1;
      #elif 1 
    uint64_t mask = ctou64(ip) ^ ev;
    if(mask >> 56) *op++ = *ip++;
    else {
      uint32_t i = __builtin_ctzll(mask)>>3; ctou64(op) = ctou64(ip), op += i; ip += i+1;
      #else
    if(likely((c = *(uint8_t *)ip) != e)) {
	  ip++;
	  *op++ = c; 
	} 
    else {  
	  uint32_t i;
      #endif
	  vbxget(ip, i);
	  if(likely(i)) { 
	    c   = *(uint8_t *)ip; 
		ip++; 
		i  += 3; 
		rmemset(op, c, i);
	  } else 
	    *op++ = e;
    }
  }
  if(op >= out_) { 
    int u = op - out_; 
    op   -= u; 
    ip   -= u-1; 
  }
    #if ALN > 1
  a: while(op < _out+outlen) 
       *op++ = *ip++;
    #endif
  return ip - in;
} 

unsigned _srled(uint8_t *in, uint8_t *out, unsigned outlen) {
  return _srled8(in+1, out, outlen, *in); 
}

unsigned srled(uint8_t *in, unsigned inlen, uint8_t *out, unsigned outlen) {
  if(inlen == outlen) 
    memcpy(out, in, outlen); 
  else if(inlen == 1) 
    memset(out, in[0], outlen);
  else 
    return _srled8(in+1, out, outlen, *in); 
}

//------------------------------------- TurboRLE ------------------------------------------
unsigned _trled(uint8_t *in, uint8_t *out, unsigned outlen) {
  uint8_t b[256] = {0}, *ip, *op = out;  
  int m = -1, i, c; 

  if(outlen < 1) 
    return 0;

  if(!*in++) 
    return _srled8(in+1, out, outlen, *in)+2;

  for(ip = in; ip < in+32; ip++)
    for(i = 0; i < 8; ++i) 
	  if(((*ip) >> i) & 1) 
	    b[(ip-in)<<3 | i] = ++m+1; 		
		
  while(op < out+outlen)
    if(likely(!(c=b[*ip]))) 
	  *op++ = *ip++; 						
	else { 
	  ip++; 
	  vbzget(ip, i, m, c-1);
	  c  = *ip++; 
	  i += 3; 
	  rmemset(op,c,i); 					
    }
  return ip - in;
}

unsigned trled(uint8_t *in, unsigned inlen, uint8_t *out, unsigned outlen) {
  if(inlen == outlen) 
    memcpy(out, in, outlen); 
  else if(inlen == 1) 
    memset(out, in[0], outlen);
  else 
    return _trled(in, out, outlen);
  return inlen;
}
#undef rmemset
#undef USIZE

#define USIZE 16
#include "trled.c"
#undef rmemset
#undef USIZE

#define USIZE 32
#include "trled.c"
#undef rmemset
#undef USIZE

#define USIZE 64
#include "trled.c"
  #else

  #ifdef MEMSAFE
#define rmemset(__op, __c, __i) while(__i--) *__op++ = __c
  #elif defined(__SSE__) && USIZE < 64
#include <tmmintrin.h>
#define rmemset(__op, __c, __i) do { \
  __m128i *_up = (__m128i *)__op, cv = TEMPLATE2(_mm_set1_epi, USIZE)(__c);\
  __op+=__i;\
  do _mm_storeu_si128(  _up, cv),_mm_storeu_si128(++_up, cv); while(++_up < (__m128i *)__op);\
} while(0)
  #else
#define _cset64(_cc,__c) _cc = __c
#define _cset32(_cc,__c) _cc = __c; _cc = _cc<<32|_cc
#define _cset16(_cc,__c) _cc = __c; _cc = _cc<<48|_cc<<32|_cc<<16|_cc
#define _cset8( _cc,__c) _cc = (uint32_t)__c<<24 | (uint32_t)__c<<16 | (uint32_t)__c<<8 | (uint32_t)__c; _cc = _cc<<32|_cc

#define rmemset(__op, __c, __i) do { uint8_t *_up = (uint8_t *)__op; __op +=__i;\
  uint64_t _cc; TEMPLATE2(_cset, USIZE)(_cc,__c);\
  do {\
    TEMPLATE2(ctou, USIZE)(_up) = __c; _up += USIZE/8;\
    TEMPLATE2(ctou, USIZE)(_up) = __c; _up += USIZE/8;\
  } while(_up < (uint8_t *)__op);\
} while(0)
  #endif 

#define uint_t TEMPLATE3(uint, USIZE, _t)

  #if USIZE != 8
unsigned TEMPLATE2(_srled, USIZE)(uint8_t *in, uint8_t *_out, unsigned outlen, uint_t e) {
  uint_t *out = (uint_t *)_out, *op = out, c; 
  uint8_t *ip = in;
  
  while(op < out+outlen/sizeof(uint_t)) 
    if(likely((c = *(uint_t *)ip) != e)) {
	  ip   += sizeof(uint_t);
	  *op++ = c; 
	} else { 
	  ip += sizeof(uint_t);
	  int i; vbxget(ip, i);
	  if(likely(i)) { 
	    c   = *(uint_t *)ip; 
		ip += sizeof(uint_t); 
		i  += 3; 
		rmemset(op, c, i);
	  } else 
	    *op++ = e;
    }
	
  if(USIZE > 8) {
    uint8_t *p = (uint8_t *)op; 
	while(p < _out+outlen) *p++ = *ip++; 
  }
  return ip - in;
}
  #endif
  #endif

