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
#ifdef __cplusplus
extern "C" {
#endif

int _srlec(unsigned char *in, int inlen, unsigned char *out, int e);
int _srled(unsigned char *in, unsigned char *out, int outlen, int e);

int srlec(unsigned char *in, int inlen, unsigned char *out);
int srled(unsigned char *in, unsigned char *out, int outlen);

int trlec(unsigned char *in, int inlen, unsigned char *out);
int trled(unsigned char *in, unsigned char *out, int outlen);

#ifdef __cplusplus
}
#endif
