#pragma once
/**
    Copyright (C) powturbo 2013-2026
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
    - homepage : https://sites.google.com/site/powturbo/
    - github   : https://github.com/powturbo
    - twitter  : https://twitter.com/powturbo
    - email    : powturbo [_AT_] gmail [_DOT_] com
**/
// Intel SSE to risc-v rvv 1.0 + zvbb:
#include "conf.h"
typedef vint32m1_t   __m128i;
typedef vfloat32m1_t __m128;

#define i8v(x)  __riscv_vreinterpret_v_i8m1_i32m1(x)
#define i16v(x) __riscv_vreinterpret_v_i16m1_i32m1(x)
#define i32v(x) (x)
#define i64v(x) __riscv_vreinterpret_v_i64m1_i32m1(x)

#define u8v(x)  __riscv_vreinterpret_v_u32m1_i32m1(__riscv_vreinterpret_v_u8m1_u32m1(x))
#define u16v(x) __riscv_vreinterpret_v_u32m1_i32m1(__riscv_vreinterpret_v_u16m1_u32m1(x))
#define u32v(x) __riscv_vreinterpret_v_u32m1_i32m1(x)
#define u64v(x) __riscv_vreinterpret_v_u32m1_i32m1(__riscv_vreinterpret_v_u64m1_u32m1(x))

#define f32v(x) __riscv_vreinterpret_v_f32m1_i32m1(x)
#define f32f(x) (x)

#define vi8(x)  __riscv_vreinterpret_v_i32m1_i8m1(x)
#define vi16(x) __riscv_vreinterpret_v_i32m1_i16m1(x)
#define vi32(x) (x)
#define vi64(x) __riscv_vreinterpret_v_i32m1_i64m1(x)

#define vu8( x) __riscv_vreinterpret_v_u32m1_u8m1( __riscv_vreinterpret_v_i32m1_u32m1(x))
#define vu16(x) __riscv_vreinterpret_v_u32m1_u16m1(__riscv_vreinterpret_v_i32m1_u32m1(x))
#define vu32(x) __riscv_vreinterpret_v_i32m1_u32m1(x)
#define vu64(x) __riscv_vreinterpret_v_u32m1_u64m1(__riscv_vreinterpret_v_i32m1_u32m1(x))

#define vf32(x) __riscv_vreinterpret_v_i32m1_f32m1(x)

// --- Set : _mm_set_epi/_mm_set1_epi ---------------------------------------------------------------------------------------------------------------------------
static inline __m128i _mm_set_epi8(             int8_t e15,int8_t e14,int8_t e13,int8_t e12,int8_t e11,int8_t e10,int8_t e9,int8_t e8,int8_t e7,int8_t e6,int8_t e5,int8_t e4,int8_t e3,int8_t e2,int8_t e1,int8_t e0) {\
                                                  int8_t __attribute__((aligned(16))) t[16] = {e0,e1,e2,e3,e4,e5,e6,e7,e8,e9,e10,e11,e12,e13,e14,e15}; return i8v(__riscv_vle8_v_i8m1(t,16));\
                                                }
static inline __m128i _mm_set_epi16(            int16_t e7,int16_t e6,int16_t e5,int16_t e4,int16_t e3,int16_t e2,int16_t e1,int16_t e0) { 
                                                  int16_t __attribute__((aligned(16))) t[8] = {e0,e1,e2,e3,e4,e5,e6,e7};                               return i16v(__riscv_vle16_v_i16m1(t,8)); 
                                                }
static inline __m128i _mm_set_epi32(            int32_t e3,int32_t e2,int32_t e1, int32_t e0) { int32_t t[4] = {e0,e1,e2,e3};                          return i32v(__riscv_vle32_v_i32m1(t,4)); }
static inline __m128i _mm_set_epi64x(           int64_t e1,int64_t e0) { int64_t __attribute__((aligned(16))) t[2] = {e0,e1};                          return i64v(__riscv_vle64_v_i64m1(t,2)); }

#define _mm_setr_epi8(e15,e14,e13,e12,e11,e10,e9,e8,e7,e6,e5,e4,e3,e2,e1,e0) _mm_set_epi8(e0,e1,e2,e3,e4,e5,e6,e7,e8,e9,e10,e11,e12,e13,e14,e15)
#define _mm_setr_epi16(e7,e6,e5,e4,e3,e2,e1,e0) _mm_set_epi16( e0,e1,e2,e3,e4,e5,e6,e7)
#define _mm_setr_epi32(e3,e2,e1,e0)             _mm_set_epi32( e0,e1,e2,e3)
#define _mm_setr_epi64x(e1,e0)                  _mm_set_epi64x(e0,e0)

#define _mm_set1_epi8(  _c8_ )                  i8v( __riscv_vmv_v_x_i8m1(  _c8_, 16))
#define _mm_set1_epi16( _c16_)                  i16v(__riscv_vmv_v_x_i16m1(_c16_,  8))
#define _mm_set1_epi32( _c32_)                  i32v(__riscv_vmv_v_x_i32m1(_c32_,  4))                                             
#define _mm_set1_epi64x(_c64_)                  i64v(__riscv_vmv_v_x_i64m1(_c64_,  2))
#define _mm_set1_ps(_f32_)                      f32v(__riscv_vfmv_v_f_f32m1(_f32_, 4))

#define _mm_setzero_si128()                     u32v(__riscv_vmv_v_x_u32m1(0, 4))
#define _mm_setzero_ps()                        f32v(__riscv_vfmv_v_f_f32m1(0, 4))
                      				 
// --- Arithmetic ----------------------------------------------------------------------------------------------------------------------------------------------------
#define _mm_add_epi8(   _u_,_v_)                i8v( __riscv_vadd_vv_i8m1(   vi8( _u_), vi8( _v_), 16))
#define _mm_add_epi16(  _u_,_v_)                i16v(__riscv_vadd_vv_i16m1(  vi16(_u_), vi16(_v_),  8))
#define _mm_add_epi32(  _u_,_v_)                i32v(__riscv_vadd_vv_i32m1(  vi32(_u_), vi32(_v_),  4))
#define _mm_add_epi64(  _u_,_v_)                i64v(__riscv_vadd_vv_i64m1(  vi64(_u_), vi64(_v_),  2))

#define _mm_adds_epu8(  _u_,_v_)                u8v( __riscv_vsaddu_vv_u8m1(  vu8(_u_), vu8(_v_),  16))
#define _mm_adds_epu16( _u_,_v_)                u16v(__riscv_vsaddu_vv_u16m1(vu16(_u_), vu16(_v_),  8))

#define _mm_sub_epi8(   _u_,_v_)                i8v( __riscv_vsub_vv_i8m1(   vi8( _u_), vi8( _v_), 16)) 
#define _mm_sub_epi16(  _u_,_v_)                i16v(__riscv_vsub_vv_i16m1(  vi16(_u_), vi16(_v_),  8)) 
#define _mm_sub_epi32(  _u_,_v_)                i32v(__riscv_vsub_vv_i32m1(  vi32(_u_), vi32(_v_),  4)) 
#define _mm_sub_epi64(  _u_,_v_)                i64v(__riscv_vsub_vv_i64m1(  vi64(_u_), vi64(_v_),  2)) 

#define _mm_subs_epu8(  _u_,_v_)  		u8v( __riscv_vssubu_vv_u8m1( vu8( _u_), vu8( _v_), 16)) 
#define _mm_subs_epu16( _u_,_v_)		        u16v(__riscv_vssubu_vv_u16m1(vu16(_u_), vu16(_v_),  8))

#define _mm_mullo_epi16(_u_,_v_)                i16v(__riscv_vmul_vv_i16m1(  vi16(_u_), vi16(_v_),  8))
#define _mm_mullo_epi32(_u_,_v_)                i32v(__riscv_vmul_vv_i32m1(  vi32(_u_), vi32(_v_),  4))
#define  mm_mullo_epu32(_u_,_v_)                u32v( __riscv_vmul_vv_u32m1( vu32(_u_), vu32(_v_),  4))

#define _mm_mulhi_epi16(_u_,_v_)  		i16v(__riscv_vmulh_vv_i16m1( vi16(_u_), vi16(_v_),  8));
#define  mm_mulhis_epi1s(_u_,_v_)		_mm_mulhi_epi16(_u_,_v_) //Neon compatibility
#define _mm_mul_epu32(   _u_,_v_)               u32v(__riscv_vwmulu_vv_u64m2(vu32(_u_), vu32(_v_), 4))

static inline vint32m1_t _mm_madd_epi16(vint16m1_t u, vint16m1_t v) {
  vint64m2_t prod64 = __riscv_vreinterpret_v_i32m2_i64m2(__riscv_vwmul_vv_i32m2(u, v, 8));
  return __riscv_vadd_vv_i32m1(__riscv_vncvt_x_x_w_i32m1(prod64, 4), __riscv_vnsra_wx_i32m1(prod64, 32, 4), 4);
}
// --- Cast -----------------------------------------------------------------------------------------------------------------------------
#define _mm_castps_si128(_v_)                   f32v(_v_)
static inline __m128 _mm_castsi128_ps(__m128i v) {  return vf32(v); }

// --- Special math functions -----------------------------------------------------------------------------------------------------------
#define _mm_min_epi8(    _u_,_v_)		i8v( __riscv_vmin_vv_i8m1(  vi8( _u_), vi8( _v_),16))
#define _mm_min_epi16(   _u_,_v_)		i16v(__riscv_vmin_vv_i16m1( vi16(_u_), vi16(_v_), 8))
#define _mm_min_epi32(   _u_,_v_)		i32v(__riscv_vmin_vv_i32m1( vi32(_u_), vi32(_v_), 4))
#define _mm_min_epi64(   _u_,_v_)		i64v(__riscv_vmin_vv_i64m1( vi64(_u_), vi64(_v_), 2))

#define _mm_min_epu8(    _u_,_v_)               u8v( __riscv_vminu_vv_u8m1( vu8(_u_),  vu8( _v_),16))
#define _mm_min_epu16(   _u_,_v_)               u16v(__riscv_vminu_vv_u16m1(vu16(_u_), vu16(_v_), 8))
#define _mm_min_epu32(   _u_,_v_)		u32v(__riscv_vminu_vv_u32m1(vu32(_u_), vu32(_v_), 4))
#define _mm_min_epu64(   _u_,_v_)		u64v(__riscv_vminu_vv_u64m1(vu64(_u_), vu64(_v_), 2))

#define _mm_max_epi8(    _u_,_v_)               i8v( __riscv_vmax_vv_i8m1(  vi8( _u_), vi8( _v_),16))  
#define _mm_max_epi16(   _u_,_v_)               i16v(__riscv_vmax_vv_i16m1( vi16(_u_), vi16(_v_), 8))  
#define _mm_max_epi32(   _u_,_v_)               i32v(__riscv_vmax_vv_i32m1( vi32(_u_), vi32(_v_), 4))  
#define _mm_max_epi64(   _u_,_v_)               i64v(__riscv_vmax_vv_i64m1( vi64(_u_), vi64(_v_), 2))  

#define _mm_max_epu8(    _u_,_v_)               u8v( __riscv_vmaxu_vv_u8m1( vu8( _u_), vu8( _v_),16))
#define _mm_max_epu16(   _u_,_v_)               u16v(__riscv_vmaxu_vv_u16m1(vu16(_u_), vu16(_v_), 8))
#define _mm_max_epu32(   _u_,_v_)               u32v(__riscv_vmaxu_vv_u32m1(vu32(_u_), vu32(_v_), 4))
#define _mm_max_epu64(   _u_,_v_)               u64v(__riscv_vmaxu_vv_u64m1(vu64(_u_), vu64(_v_), 2))

// --- Logical ---------------------------------------------------------------------------------------------------------------------------
#define  mm_testnz_epu32(_u_)                   __riscv_vredmaxu_vs_u32m1_u32m1(__riscv_vmv_v_x_u32m1(0, 4), _u_, __riscv_vmv_v_x_u32m1(0, 4), 4)
#define  mm_testnz_epu8( _u_)                   __riscv_vredmaxu_vs_u8m1_u8m1(  __riscv_vmv_v_x_u8m1(0, 16), _u_, __riscv_vmv_v_x_u8m1( 0,16),16)

#define _mm_or_si128(    _u_,_v_)               i32v(__riscv_vor_vv_i32m1( vi32(_u_), vi32(_v_), 4))
#define _mm_and_si128(   _u_,_v_)               i32v(__riscv_vand_vv_i32m1(vi32(_u_), vi32(_v_), 4))
#define _mm_xor_si128(   _u_,_v_)               i32v(__riscv_vxor_vv_i32m1(vi32(_u_), vi32(_v_), 4))
  #ifdef __riscv_zvbb
#define _mm_andnot_si128(_u_, _v_) 		u32v(__riscv_vandn_vv_u32m1(vu32(_u_), vu32(_v_),4))
  #else
#define _mm_andnot_si128(_u_, _v_) 		i32v(__riscv_vand_vv_i32m1(__riscv_vnot_v_i32m1(vi32(_u_), 4), vi32(_v_), 4))
  #endif

// ---  Shift -----------------------------------------------------------------------------------------------------------------------------
#define _mm_slli_epi8(   _v_,_m_)               u8v( __riscv_vsll_vx_u8m1( vu8( _v_), _m_,16))
#define _mm_slli_epi16(  _v_,_m_)               u16v(__riscv_vsll_vx_u16m1(vu16(_v_), _m_, 8))
#define _mm_slli_epi32(  _v_,_m_)               u32v(__riscv_vsll_vx_u32m1(vu32(_v_), _m_, 4))
#define _mm_slli_epi64(  _v_,_m_)               u64v(__riscv_vsll_vx_u64m1(vu64(_v_), _m_, 2))
//#define _mm_slli_si128( _v_, _c_)               i8v((_c_) >= 16 ? __riscv_vmv_v_x_i8m1(0, 16) : ((_c_) <= 0  ? vi8(_v_) : __riscv_vslideup_vx_i8m1(__riscv_vmv_v_x_i8m1(0, 16), vi8(_v_), (_c_), 16))) 
static inline __m128i _mm_slli_si128(__m128i v, int imm) {
  if(__builtin_constant_p(imm)) { if (imm <= 0)  return v; if (imm >= 16) return u8v(__riscv_vmv_v_x_u8m1(0, 16)); }
  return u8v(__riscv_vslideup_vx_u8m1(__riscv_vmv_v_x_u8m1(0, 16), vu8(v), imm, 16));
}

#define  mm_slli_epi8(   _v_,_c_)               _mm_slli_epi8( _v_,_c_)
#define  mm_slli_epi16(  _v_,_c_)               _mm_slli_epi16(_v_,_c_) 
#define  mm_slli_epi32(  _v_,_c_)               _mm_slli_epi32(_v_,_c_)  
#define  mm_slli_epi64(  _v_,_c_)               _mm_slli_epi8( _v_,_c_)  
#define  mm_slli_si128(  _v_,_c_)               _mm_slli_si128(_v_,_c_)  

#define _mm_srli_epi8(   _v_,_m_)               u8v( __riscv_vsrl_vx_u8m1( vu8(_v_),  _m_,16))
#define _mm_srli_epi16(  _v_,_m_)               u16v(__riscv_vsrl_vx_u16m1(vu16(_v_), _m_, 8))
#define _mm_srli_epi32(  _v_,_m_)               u32v(__riscv_vsrl_vx_u32m1(vu32(_v_), _m_, 4))
#define _mm_srli_epi64(  _v_,_m_)               u64v(__riscv_vsrl_vx_u64m1(vu64(_v_), _m_, 2))
#define _mm_srli_si128(  _v_,_c_)               u8v(__riscv_vslidedown_vx_u8m1(vu8(_v_), _c_,16))

#define  mm_srli_epi16(  _v_,_c_)               _mm_srli_epi8( _v_,_c_)  
#define  mm_srli_epi16(  _v_,_c_)               _mm_srli_epi16(_v_,_c_)  
#define  mm_srli_epi32(  _v_,_c_)               _mm_srli_epi32(_v_,_c_)  
#define  mm_srli_epi64(  _v_,_c_)               _mm_srli_epi64(_v_,_c_)

#define _mm_srai_epi8(   _v_,_m_)               i8v( __riscv_vsra_vx_i8m1( vi8(  _v_), _m_,16))
#define _mm_srai_epi16(  _v_,_m_)               i16v(__riscv_vsra_vx_i16m1(vi16( _v_), _m_, 8))
#define _mm_srai_epi32(  _v_,_m_)               i32v(__riscv_vsra_vx_i32m1(vi32( _v_), _m_, 4))
#define _mm_srai_epi64(  _v_,_m_)               i64v(__riscv_vsra_vx_i64m1(vi64( _v_), _m_, 2))

#define  mm_srai_epi8(   _v_,_c_)               _mm_srai_epi8( _v_,_c_)
#define  mm_srai_epi16(  _v_,_c_)               _mm_srai_epi16(_v_,_c_)
#define  mm_srai_epi32(  _v_,_c_)               _mm_srai_epi32(_v_,_c_) 
#define  mm_srai_epi64(  _v_,_c_)               _mm_srai_epi64(_v_,_c_) 
								
#define _mm_sll_epi8(    _u_,_v_)               i8v( __riscv_vsll_vv_i8m1(  vi8( _u_), vi8( _v_),16))
#define _mm_sll_epi16(   _u_,_v_)               i16v(__riscv_vsll_vv_i16m1( vi16(_u_), vi16(_v_), 8))
#define _mm_sll_epi32(   _u_,_v_)               i32v(__riscv_vsll_vv_i32m1( vi32(_u_), vi32(_v_), 4))
#define _mm_sll_epi64(   _u_,_v_)               i64v(__riscv_vsll_vv_i64m1( vi64(_u_), vi64(_v_), 2))
												
#define _mm_srl_epi8(    _u_,_v_)               i8v( __riscv_vsrl_vv_i8m1(  vi8( _u_), vi8( _v_),16))
#define _mm_srl_epi16(   _u_,_v_)               i16v(__riscv_vsrl_vv_i16m1( vi16(_u_), vi16(_v_), 8))
#define _mm_srl_epi32(   _u_,_v_)               i32v(__riscv_vsrl_vv_i32m1( vi32(_u_), vi32(_v_), 4))
#define _mm_srl_epi64(   _u_,_v_)               i64v(__riscv_vsrl_vv_i64m1( vi64(_u_), vi64(_v_), 2))
												
#define _mm_sllv_epi16(  _u_,_v_)               u16v(__riscv_vsll_vv_u16m1(vu16(_u_), vu16(_v_),  8))
#define _mm_sllv_epi32(  _u_,_v_)               u32v(__riscv_vsll_vv_u32m1(vu32(_u_), vu32(_v_),  4))
#define _mm_sllv_epi64(  _u_,_v_)               u64v(__riscv_vsll_vv_u64m1(vu64(_u_), vu64(_v_),  2))

#define _mm_srlv_epi16(  _u_,_v_)               u16v(__riscv_vsrl_vv_u16m1(vu16(_u_), vu16(_v_), 8))
#define _mm_srlv_epi32(  _u_,_v_)               u32v(__riscv_vsrl_vv_u32m1(vu32(_u_), vu32(_v_), 4))
#define _mm_srlv_epi64(  _u_,_v_)               u64v(__riscv_vsrl_vv_u64m1(vu64(_u_), vu64(_v_), 2))

// --- Compare --------- true/false->1/0 (all bits set) ---------------------------------------------------------------------------------
#define _mm_cmpeq_epi8(  _u_,_v_)               i8v( __riscv_vmerge_vxm_i8m1( __riscv_vmv_v_x_i8m1( 0,16), -1, __riscv_vmseq_vv_i8m1_b8(   vi8( _u_), vi8( _v_),16),16))
#define _mm_cmpeq_epi16( _u_,_v_)               i16v(__riscv_vmerge_vxm_i16m1(__riscv_vmv_v_x_i16m1(0, 8), -1, __riscv_vmseq_vv_i16m1_b16( vi16(_u_), vi16(_v_), 8), 8))
#define _mm_cmpeq_epi32( _u_,_v_)               i32v(__riscv_vmerge_vxm_i32m1(__riscv_vmv_v_x_i32m1(0, 4), -1, __riscv_vmseq_vv_i32m1_b32( vi32(_u_), vi32(_v_), 4), 4))
#define _mm_cmpeq_epi64( _u_,_v_)               i64v(__riscv_vmerge_vxm_i64m1(__riscv_vmv_v_x_i64m1(0, 2), -1, __riscv_vmseq_vv_i64m1_b64( vi64(_u_), vi64(_v_), 2), 2))

#define _mm_cmpgt_epi8(  _u_,_v_)               i8v( __riscv_vmerge_vxm_i8m1( __riscv_vmv_v_x_i8m1( 0,16), -1, __riscv_vmsgt_vv_i8m1_b8(   vi8( _u_), vi8( _v_),16),16))
#define _mm_cmpgt_epi16( _u_,_v_)               i16v(__riscv_vmerge_vxm_i16m1(__riscv_vmv_v_x_i16m1(0, 8), -1, __riscv_vmsgt_vv_i16m1_b16( vi16(_u_), vi16(_v_), 8), 8))
#define _mm_cmpgt_epi32( _u_,_v_)               i32v(__riscv_vmerge_vxm_i32m1(__riscv_vmv_v_x_i32m1(0, 4), -1, __riscv_vmsgt_vv_i32m1_b32( vi32(_u_), vi32(_v_), 4), 4))
#define _mm_cmpgt_epi64( _u_,_v_)               i64v(__riscv_vmerge_vxm_i64m1(__riscv_vmv_v_x_i64m1(0, 2), -1, __riscv_vmsgt_vv_i64m1_b64( vi64(_u_), vi64(_v_), 2), 2))

#define _mm_cmplt_epi8(  _u_,_v_)               i8v( __riscv_vmerge_vxm_i8m1( __riscv_vmv_v_x_i8m1( 0,16), -1, __riscv_vmslt_vv_i8m1_b8(   vi8( _u_), vi8( _v_),16),16))
#define _mm_cmplt_epi16( _u_,_v_)               i16v(__riscv_vmerge_vxm_i16m1(__riscv_vmv_v_x_i16m1(0, 8), -1, __riscv_vmslt_vv_i16m1_b16( vi16(_u_), vi16(_v_), 8), 8))
#define _mm_cmplt_epi32( _u_,_v_)               i32v(__riscv_vmerge_vxm_i32m1(__riscv_vmv_v_x_i32m1(0, 4), -1, __riscv_vmslt_vv_i32m1_b32( vi32(_u_), vi32(_v_), 4), 4))
#define _mm_cmplt_epi64( _u_,_v_)               i64v(__riscv_vmerge_vxm_i64m1(__riscv_vmv_v_x_i64m1(0, 2), -1, __riscv_vmslt_vv_i64m1_b64( vi64(_u_), vi64(_v_), 2), 2))

#define _mm_cmpgt_epu8(  _u_,_v_)               i8v( __riscv_vmerge_vxm_u8m1( __riscv_vmv_v_x_u8m1( 0,16), -1, __riscv_vmsgtu_vv_u8m1_b8(  vu8( _u_), vu8( _v_),16),16))
#define _mm_cmpgt_epu16( _u_,_v_)               i16v(__riscv_vmerge_vxm_u16m1(__riscv_vmv_v_x_u16m1(0, 8), -1, __riscv_vmsgtu_vv_u16m1_b16(vu16(_u_), vu16(_v_), 8), 8))
#define _mm_cmpgt_epu32( _u_,_v_)               i32v(__riscv_vmerge_vxm_u32m1(__riscv_vmv_v_x_u32m1(0, 4), -1, __riscv_vmsgtu_vv_u32m1_b32(vu32(_u_), vu32(_v_), 4), 4))
#define _mm_cmpgt_epu64( _u_,_v_)               i64v(__riscv_vmerge_vxm_u64m1(__riscv_vmv_v_x_u64m1(0, 2), -1, __riscv_vmsgtu_vv_u64m1_b64(vu64(_u_), vu64(_v_), 2), 2))

#define _mm_cmplt_epu8(  _u_,_v_)               i8v( __riscv_vmerge_vxm_u8m1( __riscv_vmv_v_x_u8m1( 0,16), -1, __riscv_vmsltu_vv_u8m1_b8(  vu8( _u_), vu8( _v_),16),16))
#define _mm_cmplt_epu16( _u_,_v_)               i16v(__riscv_vmerge_vxm_u16m1(__riscv_vmv_v_x_u16m1(0, 8), -1, __riscv_vmsltu_vv_u16m1_b16(vu16(_u_), vu16(_v_), 8), 8))
#define _mm_cmplt_epu32( _u_,_v_)               i32v(__riscv_vmerge_vxm_u32m1(__riscv_vmv_v_x_u32m1(0, 4), -1, __riscv_vmsltu_vv_u32m1_b32(vu32(_u_), vu32(_v_), 4), 4))
#define _mm_cmplt_epu64( _u_,_v_)               i64v(__riscv_vmerge_vxm_u64m1(__riscv_vmv_v_x_u64m1(0, 2), -1, __riscv_vmsltu_vv_u64m1_b64(vu64(_u_), vu64(_v_), 2), 2))

static inline __m128i mm_cmpgt_epu8( __m128i u, __m128i v) { return u8v( __riscv_vmerge_vxm_u8m1( __riscv_vmv_v_x_u8m1( 0,16), 0xFF,                  __riscv_vmsgtu_vv_u8m1_b8(  vu8(u),  vu8( v),16),16)); }
static inline __m128i mm_cmpgt_epu16(__m128i u, __m128i v) { return u16v(__riscv_vmerge_vxm_u16m1(__riscv_vmv_v_x_u16m1(0, 8), 0xFFFF,                __riscv_vmsgtu_vv_u16m1_b16(vu16(u), vu16(v), 8), 8)); }
static inline __m128i mm_cmpgt_epu32(__m128i u, __m128i v) { return u32v(__riscv_vmerge_vxm_u32m1(__riscv_vmv_v_x_u32m1(0, 4), 0xFFFFFFFF,            __riscv_vmsgtu_vv_u32m1_b32(vu32(u), vu32(v), 4), 4)); }
static inline __m128i mm_cmpgt_epu64(__m128i u, __m128i v) { return u64v(__riscv_vmerge_vxm_u64m1(__riscv_vmv_v_x_u64m1(0, 2), 0xFFFFFFFFFFFFFFFFull, __riscv_vmsgtu_vv_u64m1_b64(vu64(u), vu64(v), 2), 2)); }

static inline __m128i mm_cmplt_epu8( __m128i u, __m128i v) { return u8v( __riscv_vmerge_vxm_u8m1( __riscv_vmv_v_x_u8m1( 0,16), 0xFF,                  __riscv_vmsltu_vv_u8m1_b8(  vu8(u),  vu8( v),16),16)); }
static inline __m128i mm_cmplt_epu16(__m128i u, __m128i v) { return u16v(__riscv_vmerge_vxm_u16m1(__riscv_vmv_v_x_u16m1(0, 8), 0xFFFF,                __riscv_vmsltu_vv_u16m1_b16(vu16(u), vu16(v), 8), 8)); }
static inline __m128i mm_cmplt_epu32(__m128i u, __m128i v) { return u32v(__riscv_vmerge_vxm_u32m1(__riscv_vmv_v_x_u32m1(0, 4), 0xFFFFFFFF,            __riscv_vmsltu_vv_u32m1_b32(vu32(u), vu32(v), 4), 4)); }
static inline __m128i mm_cmplt_epu64(__m128i u, __m128i v) { return u64v(__riscv_vmerge_vxm_u64m1(__riscv_vmv_v_x_u64m1(0, 4), 0xFFFFFFFFFFFFFFFFull, __riscv_vmsltu_vv_u64m1_b64(vu64(u), vu64(v), 2), 2)); }

// --- Load ------------------------------------------------------------------------------------------------------------------------------------
#define _mm_loadl_epi64( _u64p_)                u64v(__riscv_vle64_v_u64m1((const uint64_t *)(_u64p_), 1))
#define  mm_loadu_epi64p(_u64p_,_u_)            u64v(__riscv_vslidedown_vx_u64m1(__riscv_vle64_v_u64m1((const uint64_t*)(_u64p_), 1), vu64(_u_), 0, 2))

static inline __m128i _mm_loadu_si128(__m128i const *_ip_) { return i32v(__riscv_vle32_v_i32m1((const int *)(_ip_),    4)); }
#define _mm_load_si128(  _ip_)                  i32v(__riscv_vle32_v_i32m1(( const uint32_t*)(_ip_),    4))
#define _mm_load_ps(     _ip_)                  i32v(__riscv_vle32_v_f32m1(( const float   *)(_ip_),    4))
#define _mm_loadu_ps(    _ip_)                  i32v(__riscv_vle32_v_f32m1(( const float   *)(_ip_),    4))
#define _mm_load1_ps(    _ip_)                  i32v(__riscv_vlse32_v_f32m1((const float   *)(_ip_), 0, 4))
#define _mm_loadl_pi(_v_,_ip_)                  i32v(__riscv_vle32_v_f32m1(( const float   *)(_ip_),    2))
#define _mm_loadh_pi(_v_,_ip_)                  i32v(__riscv_vle32_v_f32m1(( const float   *)(_ip_),    2))

// --- Store ----------------------------------------------------------------------------------------------------------------------------------
#define _mm_storel_epi64(_ip_,_v_)              __riscv_vse64_v_i64m1((uint64_t *)(_ip_), vi64(_v_), 1)
#define _mm_storeu_si128(_ip_,_v_)              __riscv_vse32_v_i32m1((uint32_t *)(_ip_), vi32(_v_), 4)
#define _mm_store_ps(    _ip_,_v_)              __riscv_vse32_v_f32m1((float    *)(_ip_), vf32(_v_), 4)
#define _mm_storeu_ps(   _ip_,_v_)              __riscv_vse32_v_f32m1((float    *)(_ip_), vf32(_v_), 4)
#define _mm_store_ss(    _ip_,_v_)              __riscv_vse32_v_f32m1((float    *)(_ip_), vf32(_v_), 1)

// --- Convert ----------------------------------------------------------------------------------------------------------------------------------
#define  mm_cvtsi64_si128p(_u64p_,_v_)          mm_loadu_epi64p(_u64p_,_v_)
#define _mm_cvtsi64_si128(_v_)                  i32v(__riscv_vmv_s_x_u64m1(__riscv_vmv_v_x_u64m1(0, 2), i128_f64(_v_), 2))

#define _mm_cvtss_f32(_v_)                      f32v(__riscv_vfmv_f_s_f32m1_f32(vf32(_v_)))
static inline __m128  _mm_cvtepi32_ps(   __m128i v) { return f32f(__riscv_vfcvt_f_x_v_f32m1(vi32(v), 4)); }
static inline __m128i _mm_cvtepu8_epi16( __m128i v) { return u16v(__riscv_vzext_vf2_u16m1(__riscv_vlmul_trunc_v_u8m1_u8mf2(  vu8( v)), 8)); }
static inline __m128i _mm_cvtepu8_epi32( __m128i v) { return u32v(__riscv_vzext_vf4_u32m1(__riscv_vlmul_trunc_v_u8m1_u8mf4(  vu8( v)), 4)); }
static inline __m128i _mm_cvtepu8_epi64( __m128i v) { return u64v(__riscv_vzext_vf8_u64m1(__riscv_vlmul_trunc_v_u8m1_u8mf8(  vu8( v)), 2)); }
static inline __m128i _mm_cvtepu32_epi64(__m128i v) { return u64v(__riscv_vzext_vf2_u64m1(__riscv_vlmul_trunc_v_u32m1_u32mf2(vu32(v)), 2)); }
// --- Move -----------------------------------------------------------------------------------------------------------------------
//static inline __m128i _mm_move_epi64(__m128i v) { return (__m128i)__riscv_vmv_s_x_u64m1(__riscv_vmv_v_x_u64m1(0, 2), __riscv_vmv_x_s_u64m1_u64((vuint64m1_t)v), 2); }
// --- Probability / Statistics -------------------------
static inline __m128i _mm_avg_epu8( __m128i u, __m128i v) { return u8v( __riscv_vaaddu_vv_u8m1( vu8( u), vu8( v), 0, 16)); }
static inline __m128i _mm_avg_epu16(__m128i u, __m128i v) { return u16v(__riscv_vaaddu_vv_u16m1(vu16(u), vu16(v), 0,  8)); }
// --- Reverse bits/bytes ---------------------------------------------------------------------------------------------------------
#ifdef __riscv_zvbb
static inline __m128i mm_rbit_epi8(__m128i _v_) { return u8v(__riscv_vbrev8_v_u8m1(vu8(_v_), 16)); }
#else
static inline __m128i mm_rbit_epi8(__m128i _v_) {
  vuint64m8_t v64 = __riscv_vmul_vx_u64m8(__riscv_vzext_vf8_u64m8(vu8(_v_), 16), 0x0202020202ull, 16);
  v64 = __riscv_vand_vx_u64m8(v64, 0x010884422010ull, 16);
  v64 = __riscv_vremu_vx_u64m8(v64, 1023, 16);
  return u8v(__riscv_vncvt_x_x_w_u8m1(__riscv_vncvt_x_x_w_u16m2(__riscv_vncvt_x_x_w_u32m4(v64, 16), 16), 16));
}
#endif

#ifdef __riscv_zvbb
static inline __m128i mm_rev_epi16(__m128i v) { return u16v(__riscv_vrev8_v_u16m1(vu16(v), 8)); }
static inline __m128i mm_rev_epi32(__m128i v) { return u32v(__riscv_vrev8_v_u32m1(vu32(v), 4)); }
static inline __m128i mm_rev_epi64(__m128i v) { return u64v(__riscv_vrev8_v_u64m1(vu64(v), 2)); }
#else
static inline __m128i mm_rev_epi16(__m128i v) { uint8_t idx[16] = { 1, 0, 3, 2, 5, 4, 7, 6, 9, 8,11,10,13,12,15,14}; return i8v(__riscv_vrgather_vv_i8m1(vi8(v), __riscv_vle8_v_u8m1(idx, 16), 16));}
static inline __m128i mm_rev_epi32(__m128i v) { uint8_t idx[16] = { 3, 2, 1, 0, 7, 6, 5, 4,11,10, 9, 8,15,14,13,12}; return i8v(__riscv_vrgather_vv_i8m1(vi8(v), __riscv_vle8_v_u8m1(idx, 16), 16));}
static inline __m128i mm_rev_epi64(__m128i v) { uint8_t idx[16] = { 7, 6, 5, 4, 3, 2, 1, 0,15,14,13,12,11,10, 9, 8}; return i8v(__riscv_vrgather_vv_i8m1(vi8(v), __riscv_vle8_v_u8m1(idx, 16), 16));}
#endif
static inline __m128i mm_rev_si128(__m128i v) { uint8_t idx[16] = {15,14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0}; return i8v(__riscv_vrgather_vv_i8m1(vi8(v), __riscv_vle8_v_u8m1(idx, 16), 16));}

// --- Insert/extract ------------------------------------------------------------------------------------------------------------
#define  mm_extract_epi32x(_v_,_u32_,_id_)      ((_u32_) = __riscv_vmv_x_s_u32m1_u32(__riscv_vslidedown_vx_u32m1(__riscv_vmv_v_x_u32m1(0, 4), vu32(_v_), _id_, 4)))
#define _mm_extract_epi64x(_v_,_u64_,_id_)      ((_u64_) = __riscv_vmv_x_s_u64m1_u64(__riscv_vslidedown_vx_u64m1(__riscv_vmv_v_x_u64m1(0, 2), vu64(_v_), _id_, 2)))

#define _mm_extract_epi8( _v_,       _id_)      __riscv_vmv_x_s_i8m1_i8(  __riscv_vslidedown_vx_i8m1( vi8( _v_), _id_,16))  
#define _mm_extract_epi16(_v_,       _id_)      __riscv_vmv_x_s_i16m1_i16(__riscv_vslidedown_vx_i16m1(vi16(_v_), _id_, 8))  
#define _mm_extract_epi32(_v_,       _id_)      __riscv_vmv_x_s_i32m1_i32(__riscv_vslidedown_vx_i32m1(vi32(_v_), _id_, 4))  
#define _mm_extract_epi64(_v_,       _id_)      __riscv_vmv_x_s_i64m1_i64(__riscv_vslidedown_vx_i64m1(vi64(_v_), _id_, 2))  
#define _mm_cvtsi128_si32(_v_)                  __riscv_vmv_x_s_u32m1_u32(vu32(_v_))
#define _mm_cvtsi128_si64(_v_)                  __riscv_vmv_x_s_u64m1_u64(vu64(_v_))
#define _mm_cvtsi32_si128(_x_)                  u8v(__riscv_vmv_s_x_u32m1(__riscv_vmv_v_x_u32m1(0, 4), _x_, 4))

static inline __m128i _mm_insert_epi16(__m128i v, int i, const int imm8) {  return i16v(__riscv_vslideup_vx_i16m1_tu(vi16(v), __riscv_vmv_s_x_i16m1(i, 8), imm8, 8)); }
static inline __m128i _mm_insert_epi32(__m128i v, int i, const int imm8) {  return i32v(__riscv_vslideup_vx_i32m1_tu(vi32(v), __riscv_vmv_s_x_i32m1(i, 4), imm8, 4)); }

// --- Miscellaneous ----------------------------------------------------------------------------------------------------------------
static inline __m128i _mm_alignr_epi8(__m128i u, __m128i v, int count) { //count must not be constant
  return i8v(__riscv_vget_v_i8m2_i8m1(__riscv_vslidedown_vx_i8m2(__riscv_vset_v_i8m1_i8m2(__riscv_vset_v_i8m1_i8m2(__riscv_vundefined_i8m2(), 0, vi8(v)), 1, vi8(u)), count, 32), 0));
}
static inline __m128i _mm_packs_epi16(__m128i u, __m128i v)  { return i8v( __riscv_vnclip_wx_i8m1( __riscv_vset_v_i16m1_i16m2(__riscv_vlmul_ext_v_i16m1_i16m2(vi16(u)), 1, vi16(v)), 0, __RISCV_VXRM_RNU, 16));}
static inline __m128i _mm_packs_epi32(__m128i u, __m128i v)  { return i16v(__riscv_vnclip_wx_i16m1(__riscv_vset_v_i32m1_i32m2(__riscv_vlmul_ext_v_i32m1_i32m2(vi32(u)), 1, vi32(v)), 0, __RISCV_VXRM_RNU, 8));}

static inline __m128i _mm_packus_epi16(__m128i u, __m128i v) { return u8v( __riscv_vnclipu_wx_u8m1( __riscv_vreinterpret_v_i16m2_u16m2(__riscv_vmax_vx_i16m2(__riscv_vset_v_i16m1_i16m2(__riscv_vlmul_ext_v_i16m1_i16m2(vi16(u)), 1, vi16(v)), 0, 16)), 0, __RISCV_VXRM_RNU, 16));}
static inline __m128i _mm_packus_epi32(__m128i u, __m128i v) { return u16v(__riscv_vnclipu_wx_u16m1(__riscv_vreinterpret_v_i32m2_u32m2(__riscv_vmax_vx_i32m2(__riscv_vset_v_i32m1_i32m2(__riscv_vlmul_ext_v_i32m1_i32m2(vi32(u)), 1, vi32(v)), 0,  8)), 0, __RISCV_VXRM_RNU,  8));}

static inline int _mm_movemask_epi8(__m128i v) { uint16_t r; __riscv_vsm_v_b8((uint8_t*)&r, __riscv_vmslt_vx_i8m1_b8(vi8(v), 0, 16), 16);  return r; }
//-------- Movemask ------ All lanes must be 0 or -1 (=0xff, 0xffff or 0xffffffff)
/*static inline uint16_t  mm_movemask_epu16(__m128i v) { return __riscv_vmv_x_s_u16m1_u16(__riscv_vcast_v_m_u16m1(__riscv_vmslt_vx_i16m1((vint16m1_t)v, 0, 8), 8)); }
static inline uint32_t  mm_movemask_epu32(__m128i v) { return __riscv_vmv_x_s_u32m1_u32(__riscv_vcast_v_m_u32m1(__riscv_vmslt_vx_i32m1((vint32m1_t)v, 0, 4), 4)); }
static inline uint64_t  mm_movemask_epu64(__m128i v) { return __riscv_vmv_x_s_u64m1_u64(__riscv_vcast_v_m_u64m1(__riscv_vmslt_vx_i64m1((vint64m1_t)v, 0, 2), 2)); }
static inline uint64_t  mm_movemask4_epu8(__m128i v) { return 0; }*/

// --- Swizzle : blendv / shuffle / unpacklo/unpackhi -----------------------------------------------------------------------------------
static inline __m128i _mm_blendv_epi8(__m128i _u_, __m128i _v_, __m128i _vm_) { return i8v(__riscv_vmerge_vvm_i8m1(vi8(_u_), vi8(_v_), __riscv_vmslt_vx_i8m1_b8(vi8(_vm_), 0, 16), 16)); } 

#define _MM_SHUFFLE(_u3_,_u2_,_u1_,_u0_)        ((_u3_) << 6 | (_u2_) << 4 | (_u1_) << 2 | (_u0_))
static inline __m128i _mm_shuffle_epi8(__m128i u, __m128i v)  { return i8v(__riscv_vmerge_vxm_i8m1(__riscv_vrgather_vv_i8m1(vi8(u), __riscv_vreinterpret_v_i8m1_u8m1(__riscv_vand_vx_i8m1(vi8(v), 15, 16)), 16), 0, __riscv_vmslt_vx_i8m1_b8(vi8(v), 0, 16), 16));}


static inline __m128i _mm_shuffle_epi32(__m128i _v_, const unsigned _m_) {
  const uint32_t __attribute__((aligned(16))) idx[4] = { _m_ & 3, (_m_>>2) & 3, (_m_>>4) & 3, (_m_>>6) & 3 };
  return u32v(__riscv_vrgather_vv_u32m1(vu32(_v_), __riscv_vle32_v_u32m1(idx, 4), 4));
}
  
//#define _mm_shuffle_epi8s(_u_, _v_)             u8v( __riscv_vrgather_vv_u8m1(vu8(_u_), vu8(_v_), 16)) // 0x00-0x0F 
#define  mm_shuffle_nnnn_epi32(_v_,_m_)         u32v(__riscv_vrgather_vx_u32m1(vu32(_v_), _m_, 4))
#define mm_shuffle_3311_epi32(_v_)              _mm_shuffle_epi32(_v_, _MM_SHUFFLE(3,3,1,1))

static inline __m128i mm_shuffle_epi32s(__m128i _v_, const unsigned _m_) { return _mm_shuffle_epi32(_v_, _m_); } // (Neon compatibility
static inline __m128i mm_shuffle_2031_epi32(__m128i v) { uint32_t idx[4]={0,3,1,2}; return u32v(__riscv_vrgather_vv_u32m1(vu32(v),__riscv_vle32_v_u32m1(idx,4),4)); }
static inline __m128i mm_shuffle_3120_epi32(__m128i v) { uint32_t idx[4]={0,2,1,3}; return u32v(__riscv_vrgather_vv_u32m1(vu32(v),__riscv_vle32_v_u32m1(idx,4),4)); }
static inline __m128i mm_shuffle_2020_epi32(__m128i v) { uint32_t idx[4]={0,2,0,2}; return u32v(__riscv_vrgather_vv_u32m1(vu32(v),__riscv_vle32_v_u32m1(idx,4),4)); }

static inline __m128i _mm_unpacklo_epi8( __m128i _u_, __m128i _v_) { return u16v(__riscv_vlmul_trunc_v_u16m2_u16m1(__riscv_vor_vv_u16m2(__riscv_vzext_vf2_u16m2(vu8(_u_),8),__riscv_vsll_vx_u16m2(__riscv_vzext_vf2_u16m2(vu8(_v_),  8), 8, 8),8)));}
static inline __m128i _mm_unpacklo_epi16(__m128i _u_, __m128i _v_) { return u32v(__riscv_vlmul_trunc_v_u32m2_u32m1(__riscv_vor_vv_u32m2(__riscv_vzext_vf2_u32m2(vu16(_u_),4),__riscv_vsll_vx_u32m2(__riscv_vzext_vf2_u32m2(vu16(_v_),4),16,4),4)));}
static inline __m128i _mm_unpacklo_epi32(__m128i _u_, __m128i _v_) { return u64v(__riscv_vlmul_trunc_v_u64m2_u64m1(__riscv_vor_vv_u64m2(__riscv_vzext_vf2_u64m2(vu32(_u_),2),__riscv_vsll_vx_u64m2(__riscv_vzext_vf2_u64m2(vu32(_v_),2),32,2),2)));}
static inline __m128i _mm_unpacklo_epi64(__m128i _u_, __m128i _v_) { return u64v(__riscv_vslideup_vx_u64m1(vu64(_u_),vu64(_v_),1,2));}

static inline __m128i _mm_unpackhi_epi8( __m128i _u_, __m128i _v_) { return u16v(__riscv_vlmul_trunc_v_u16m2_u16m1(__riscv_vor_vv_u16m2(__riscv_vzext_vf2_u16m2(__riscv_vslidedown_vx_u8m1(vu8( _u_ ),8,16),8),__riscv_vsll_vx_u16m2(__riscv_vzext_vf2_u16m2(__riscv_vslidedown_vx_u8m1(vu8(  _v_),8,16),8), 8,8),8)));}
static inline __m128i _mm_unpackhi_epi16(__m128i _u_, __m128i _v_) { return u32v(__riscv_vlmul_trunc_v_u32m2_u32m1(__riscv_vor_vv_u32m2(__riscv_vzext_vf2_u32m2(__riscv_vslidedown_vx_u16m1(vu16(_u_),4, 8),4),__riscv_vsll_vx_u32m2(__riscv_vzext_vf2_u32m2(__riscv_vslidedown_vx_u16m1(vu16(_v_),4, 8),4),16,4),4)));}
static inline __m128i _mm_unpackhi_epi32(__m128i _u_, __m128i _v_) { return u64v(__riscv_vlmul_trunc_v_u64m2_u64m1(__riscv_vor_vv_u64m2(__riscv_vzext_vf2_u64m2(__riscv_vslidedown_vx_u32m1(vu32(_u_),2, 4),2),__riscv_vsll_vx_u64m2(__riscv_vzext_vf2_u64m2(__riscv_vslidedown_vx_u32m1(vu32(_v_),2, 4),2),32,2),2)));}
static inline __m128i _mm_unpackhi_epi64(__m128i _u_, __m128i _v_) { return u64v(__riscv_vslideup_vx_u64m1_tu(vu64(_v_),__riscv_vslidedown_vx_u64m1(vu64(_u_),1,2),0,1)); }

