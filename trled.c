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
         
//------------------------------------- RLE with Escape char ------------------------------------------------------------------
#define MEMSAFE
#define USIZE 64
#include "srled_.h"
#undef rmemset
#undef USIZE
#undef MEMSAFE
#undef runcpy

#define USIZE 32
#include "srled_.h"
#undef rmemset
#undef USIZE
#undef runcpy

#define USIZE 16
#include "srled_.h"
#undef rmemset
#undef USIZE
#undef runcpy

#define USIZE 8
#include "srled_.h"

unsigned srled(unsigned char *in, unsigned char *out, unsigned outlen) { return _srled8(in+1, out, outlen, *in); }

//------------------------------------- TurboRLE ------------------------------------------
unsigned trled(unsigned char *in, unsigned char *out, unsigned outlen) {
  unsigned char b[256]={0},*ip,*op=out;  
  int m = -1,i,c; 
  if(outlen < 1) return 0;

  if(!*in) {
    memcpy(out,in+1,outlen); 
	return outlen+1; 
  }
  if(*in++ == 1) 
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
