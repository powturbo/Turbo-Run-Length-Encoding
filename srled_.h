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
  #ifdef MEMSAFE 
#define rmemset(__op, __c, __i) while(__i--) *__op++ = __c
  #elif defined(__SSE__)
#include <tmmintrin.h>
#define rmemset(__op, __c, __i) do { __m128i *_up = (__m128i *)__op,cv = TEMPLATE2(_mm_set1_epi, USIZE)(__c); __op+=__i; \
  do _mm_storeu_si128(_up, cv), _mm_storeu_si128(++_up, cv); while(++_up < (__m128i *)__op);\
} while(0)
  #else
#define _runcpy(_up, __op,__c) do { *(uint_t *)_up = __c; _up += sizeof(uint_t); *(uint_t *)_up = __c; _up += sizeof(uint_t); /*(uint_t *)_up = __c; _up += sizeof(uint_t); *(uint_t *)_up = __c; _up += sizeof(uint_t);*/} while(_up < (unsigned char *)__op)
    #if USIZE == 64
#define runcpy(_up, __op,__c) _runcpy(_up, __op,__c) 
    #elif USIZE == 32
#define runcpy(_up, __op,__c) unsigned long long _cc=__c; _cc=_cc<<32|_cc; _runcpy(_up, __op, _cc)
    #elif USIZE == 16
#define runcpy(_up, __op,__c) unsigned long long _cc=__c; _cc=_cc<<48|_cc<<32|_cc<<16|_cc; _runcpy(_up, __op, _cc)
    #else
#define runcpy(_up, __op,__c) unsigned long long _uc = (unsigned)__c<<24 | (unsigned)__c<<16 | (unsigned)__c<<8 | (unsigned)__c; _uc = _uc<<32|_uc; _runcpy(_up,__op,_uc);
    #endif  
#define rmemset(__op, __c, __i) do { unsigned char *_up = (unsigned char *)__op; __op+=__i; runcpy(_up,__op,__c); } while(0)
  #endif 

#define uint_t TEMPLATE3(uint, USIZE, _t)

unsigned TEMPLATE2(_srled, USIZE)(unsigned char *in, unsigned char *_out, unsigned outlen, uint_t e) {
  uint_t *out = (uint_t *)_out, *op = out, c; 
  unsigned char *ip = in;
  
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
    unsigned char *p = (unsigned char *)op; 
	while(p < _out+outlen) *p++ = *ip++; 
  }
  return ip - in;
}
