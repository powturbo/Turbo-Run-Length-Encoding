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
#include <stdint.h>
#define likely(x)     	__builtin_expect((x),1)
#define unlikely(x)   	__builtin_expect((x),0)
//------------------------------------- Variable Byte -----------------------------------------------------
#define vbputa(__op, __x, __act) {\
       if(likely(__x < (1<< 7))) {		   			  *__op++ = __x << 1; 			 		      		__act;}\
  else if(likely(__x < (1<<14))) { *(unsigned short *)__op = __x << 2 | 0x01; __op += 2; 		      	__act;}\
  else if(likely(__x < (1<<21))) { *(unsigned short *)__op = __x << 3 | 0x03; __op += 2; *__op++ = __x >> 13; __act;}\
  else if(likely(__x < (1<<28))) { *(unsigned       *)__op = __x << 4 | 0x07; __op += 4; 		      	__act;}\
  else { 		           *(unsigned       *)__op = __x << 4 | 0x0f; __op += 4; *__op++ = __x >> 28; 	__act;}\
}
 
#define vbgeta(__ip, __x, __act) do { __x = *__ip;\
       if(!(__x & (1<<0))) { __x			     >>= 1; 		                      __ip++;    __act;}\
  else if(!(__x & (1<<1))) { __x = (*(unsigned short *)__ip) >>  2;		              __ip += 2; __act;}\
  else if(!(__x & (1<<2))) { __x = (*(unsigned short *)__ip) >>  3 | *(__ip+2) << 13; __ip += 3; __act;}\
  else if(!(__x & (1<<3))) { __x = (*(unsigned       *)__ip) >>  4; 		      	  __ip += 4; __act;}\
  else 			   	       { __x = (*(unsigned       *)__ip) >>  4 | *(__ip+4) << 28; __ip += 5; __act;}\
} while(0)

#define vbput(__op, __x) { unsigned _x__ = __x; vbputa(__op, _x__, ;); }
#define vbget(__ip) ({     unsigned _x_;        vbgeta(__ip, _x_, ;); _x_; })

#define vbxput(__op, __x) { *__op++ = __x; if(unlikely((__x) >= 0xff)) { unsigned _xi = (__x) - 0xff; __op[-1] = 0xff; vbput(__op, _xi); } }
#define vbxget(__ip, __x) { __x = *__ip++; if(unlikely( __x == 0xff)) { __x = vbget(__ip); __x+=0xff; } }

#define vbzput(__op, __x, __m, __emap) do { if(unlikely((__x) < __m)) *__op++ = __emap[__x]; else { unsigned _xi = (__x) - __m; *__op++ = __emap[__m]; vbput(__op, _xi); } } while(0)
#define vbzget(__ip, __x, __m, __e) { __x = __e; if(unlikely( __x == __m)) { __x = vbget(__ip); __x+=__m; } }
 
#define TEMPLATE2_(__x, __y) __x##__y
#define TEMPLATE2(__x, __y) TEMPLATE2_(__x,__y)

#define TEMPLATE3_(x,y,z) x ## ## y ## z
#define TEMPLATE3(x,y,z) TEMPLATE3_(x, y, z)
