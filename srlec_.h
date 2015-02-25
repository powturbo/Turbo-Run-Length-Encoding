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

