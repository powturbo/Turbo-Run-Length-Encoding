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
// Intel SSE to ARM NEON optimized for maximum speed (and compatibility gcc/clang) with possible minor changes to the source code
//-march=rv64gcv -mrvv-vector-bits=128
#pragma once
#include <arm_neon.h>
#include "conf.h"
typedef  int32x4_t __m128i;                     //  uint32x4_t can also be used
typedef float32x4_t __m128;

// neon -> 128 : return value
#define i8v(x)  vreinterpretq_s8_s32(x)
#define i16v(x) vreinterpretq_s16_s32(x)
#define i64v(x) vreinterpretq_s64_s32(x)

#define u8v(x)  vreinterpretq_u8_s32(x)
#define u16v(x) vreinterpretq_u16_s32(x)
#define u32v(x) vreinterpretq_u32_s32(x)
#define u64v(x) vreinterpretq_u64_s32(x)

#define f32i(x) vreinterpretq_f32_s32(x)
#define f32f(x) (x)

// 128 -> neon: parameters
#define vi8(x)  vreinterpretq_s32_s8(x)
#define vi16(x) vreinterpretq_s32_s16(x)
#define vi64(x) vreinterpretq_s32_s64(x)

#define vu8( x) vreinterpretq_s32_u8(x)
#define vu16(x) vreinterpretq_s32_u16(x)
#define vu32(x) vreinterpretq_s32_u32(x)
#define vu64(x) vreinterpretq_s32_u64(x)

#define if32(x) vreinterpretq_s32_f32(x)

//#define uint8x16_to_8x8x2(_v_)                  ((uint8x8x2_t) { vget_low_u8(_v_), vget_high_u8(_v_) })

// --- Set : _mm_set_epi/_mm_set1_epi ---------------------------------------------------------------------------------------------------------------------------
static inline __m128i _mm_set_epi8(             int8_t u15, int8_t u14, int8_t u13, int8_t u12, int8_t u11, int8_t u10, int8_t  u9, int8_t  u8,
                                                int8_t  u7, int8_t  u6, int8_t  u5, int8_t  u4, int8_t  u3, int8_t  u2, int8_t  u1, int8_t  u0) {
                                                  int8_t  __attribute__((aligned(16))) u[16] = { u0,u1,u2,u3,u4,u5,u6,u7,u8,u9,u10,u11,u12,u13,u14,u15 };                   return (__m128i)(vld1q_s8( u));
                                                }
static inline __m128i _mm_set_epi16(            int16_t u7, int16_t u6, int16_t u5, int16_t u4,
                                                int16_t u3, int16_t u2, int16_t u1, int16_t u0) { int16_t __attribute__((aligned(16))) u[ 8] = { u0,u1,u2,u3,u4,u5,u6,u7 }; return (__m128i)(vld1q_s16(u)); }
static inline __m128i _mm_set_epi32(            int32_t u3, int32_t u2, int32_t u1, int32_t u0) { int32_t __attribute__((aligned(16))) u[ 4] = { u0,u1,u2,u3 };             return vld1q_s32(u); }
static inline __m128i _mm_set_epi64x(           int64_t u1, int64_t u0) { int64_t __attribute__((aligned(16))) u[ 2] = { u0,u1 };                                           return (__m128i)(vld1q_s64(u)); }

#define _mm_setr_epi16(u7,u6,u5,u4,u3,u2,u1,u0) _mm_set_epi16( u0,u1,u2,u3,u4,u5,u6,u7)
#define _mm_setr_epi32(u3,u2,u1,u0)             _mm_set_epi32( u0,u1,u2,u3)
#define _mm_setr_epi64x(u1,u0)                  _mm_set_epi64x(u0,u0)

#define _mm_set1_epi8(  _u8_ )                  (__m128i)vdupq_n_u8( _u8_ )
#define _mm_set1_epi16( _u16_)                  (__m128i)vdupq_n_u16(_u16_)
#define _mm_set1_epi32( _u32_)                  (__m128i)vdupq_n_u32(_u32_)
#define _mm_set1_epi64x(_u64_)                  (__m128i)vdupq_n_u64(_u64_)
#define _mm_set1_ps(_f32_)	                (__m128)vdupq_n_f32(_f32_)

#define _mm_setzero_si128()                     (__m128i)vdupq_n_u32( 0   )
#define _mm_setzero_ps()	                (__m128)vdupq_n_f32(0)

// --- Arithmetic ----------------------------------------------------------------------------------------------------------------------------------------------------
#define _mm_add_epi8(   _u_,_v_)                (__m128i)vaddq_s8( i8v( _u_), i8v( _v_))
#define _mm_add_epi16(  _u_,_v_)                (__m128i)vaddq_s16(i16v(_u_), i16v(_v_))
#define _mm_add_epi32(  _u_,_v_)                         vaddq_s32(     _u_,       _v_)
#define _mm_add_epi64(  _u_,_v_)                (__m128i)vaddq_s64(i64v(_u_), i64v(_v_))

#define _mm_sub_epi8(   _u_,_v_)                (__m128i)vsubq_s8( i8v( _u_), i8v( _v_))
#define _mm_sub_epi16(  _u_,_v_)                (__m128i)vsubq_s16(i16v(_u_), i16v(_v_))
#define _mm_sub_epi32(  _u_,_v_)                         vsubq_s32(     _u_,       _v_)
#define _mm_sub_epi64(  _u_,_v_)                (__m128i)vsubq_s64(i64v(_u_), i64v(_v_))

#define _mm_subs_epu8(  _u_,_v_)                (__m128i)(vqsubq_u8(  u8v( _u_), u8v( _v_)))
#define _mm_subs_epu16( _u_,_v_)                (__m128i)(vqsubq_u16(u16v(_u_), u16v(_v_)))

#define _mm_mullo_epi16(_u_,_v_)                (__m128i)vmulq_s16(i16v(_u_), i16v(_v_))
#define _mm_mullo_epi32(_u_,_v_)                vmulq_s32(_u_, _v_)
#define  mm_mullo_epu32(_u_,_v_)                (__m128i)vmulq_u32(u32v(_u_), u32v(_v_))

#define  mm_mulhis_epi16(_u_,_v_)               (__m128i)vqdmulhq_s16(i16v(_u_), i16v(_v_)) // only for small values ??
static inline __m128i _mm_mulhi_epi16(__m128i u, __m128i v) {
  int32x4_t lo   = vmull_s16(vget_low_s16( i16v(u)), vget_low_s16( i16v(v)));
  int32x4_t hi   = vmull_s16(vget_high_s16(i16v(u)), vget_high_s16(i16v(v)));
  uint16x8x2_t r = vuzpq_u16((uint16x8_t)(lo), (uint16x8_t)(hi));
  return vreinterpretq_s32_u16(r.val[1]);
}

#define _mm_mul_epu32(  _u_,_v_)                (__m128i)vmull_u32(vget_low_u32(u32v(_u_)),vget_low_u32(u32v(_v_)))
#define _mm_adds_epu16( _u_,_v_)                (__m128i)vqaddq_u16(u16v(_u_),u16v(_v_))
static inline __m128i _mm_madd_epi16(__m128i u, __m128i v) {
  int32x4_t mlo = vmull_s16(vget_low_s16( i16v(u)), vget_low_s16( i16v(v))),
            mhi = vmull_s16(vget_high_s16(i16v(u)), vget_high_s16(i16v(v)));
  int32x2_t alo = vpadd_s32(vget_low_s32(mlo), vget_high_s32(mlo)),
            ahi = vpadd_s32(vget_low_s32(mhi), vget_high_s32(mhi));
  return vcombine_s32(alo, ahi);
}

// --- Cast -----------------------------------------------------------------------------------------------------------------------------
static inline __m128i _mm_castps_si128(__m128  v) {  return (__m128i)(v); }
static inline __m128  _mm_castsi128_ps(__m128i v) {  return (__m128 )(v); }

// --- Special math functions -----------------------------------------------------------------------------------------------------------
#define _mm_min_epi8(    _u_,_v_)               (__m128i)vminq_s8( i8v( _u_), i8v( _v_))
#define _mm_min_epi16(   _u_,_v_)               (__m128i)vminq_s16(i16v(_u_), i16v(_v_))
#define _mm_min_epi32(   _u_,_v_)               vminq_s32(_u_, _v_)
#define _mm_min_epi64(   _u_,_v_)               (__m128i)vminq_s64(i64v(_u_), i64v(_v_))

#define _mm_min_epu8(    _u_,_v_)               (__m128i)vminq_u8( u8v( _u_), u8v( _v_))
#define _mm_min_epu16(   _u_,_v_)               (__m128i)vminq_u16(u16v(_u_), u16v(_v_))
#define _mm_min_epu32(   _u_,_v_)               (__m128i)vminq_u32(u32v(_u_), u32v(_v_))
#define _mm_min_epu64(   _u_,_v_)               (__m128i)vminq_u64(u64v(_u_), u64v(_v_))

#define _mm_max_epi8(    _u_,_v_)               (__m128i)(vmaxq_s8( i8v( _u_), i8v( _v_)))
#define _mm_max_epi16(   _u_,_v_)               (__m128i)(vmaxq_s16(i16v(_u_), i16v(_v_)))
#define _mm_max_epi32(   _u_,_v_)               vmaxq_s32(_u_, _v_)
#define _mm_max_epi64(   _u_,_v_)               (__m128i)(vmaxq_s64(i64v(_u_), i64v(_v_)))

#define _mm_max_epu8(    _u_,_v_)               (__m128i)vmaxq_u8( u8v( _u_), u8v( _v_))
#define _mm_max_epu16(   _u_,_v_)               (__m128i)vmaxq_u16(u16v(_u_), u16v(_v_))
#define _mm_max_epu32(   _u_,_v_)               (__m128i)vmaxq_u32(u32v(_u_), u32v(_v_))
#define _mm_max_epu64(   _u_,_v_)               (__m128i)vmaxq_u64(u64v(_u_), u64v(_v_))

// --- Logical ---------------------------------------------------------------------------------------------------------------------------
#define  mm_testnz_epu32(_u_)                   vmaxvq_u32(u32v(_u_)) //vaddvq_u32(_u_)
#define  mm_testnz_epu8( _u_)                   vmaxv_u8(_u_)
#define _mm_or_si128(    _u_,_v_)               (__m128i)vorrq_u32(u32v(_u_), u32v(_v_))
#define _mm_and_si128(   _u_,_v_)               (__m128i)vandq_u32(u32v(_u_), u32v(_v_))
#define _mm_xor_si128(   _u_,_v_)               (__m128i)veorq_u32(u32v(_u_), u32v(_v_))

#define _mm_andnot_si128(_u_, _v_)              (__m128i)vbicq_u32(u32v(_u_), u32v(_v_))

// ---  Shift -----------------------------------------------------------------------------------------------------------------------------
#define  mm_slli_epi8(   _v_,_c_)               ((_c_)<1 ? (_v_) : (__m128i)((_c_)> 7?vdupq_n_u8( 0):vshlq_n_u8( u8v( _v_), (_c_))))  // parameter c MUST be a constant / vshlq_n_u8: __constrange(0-(N-1))
#define  mm_slli_epi16(  _v_,_c_)               ((_c_)<1 ? (_v_) : (__m128i)((_c_)>15?vdupq_n_u16(0):vshlq_n_u16(u16v(_v_), (_c_))))
#define  mm_slli_epi32(  _v_,_c_)               ((_c_)<1 ? (_v_) : (__m128i)((_c_)>31?vdupq_n_u32(0):vshlq_n_u32(u32v(_v_), (_c_))))
#define  mm_slli_epi64(  _v_,_c_)               ((_c_)<1 ? (_v_) : (__m128i)((_c_)>63?vdupq_n_u64(0):vshlq_n_u64(u64v(_v_), (_c_))))
#define _mm_slli_si128(  _v_,_c_)               ((_c_)<1 ? (_v_) : (__m128i)((_c_)>15?vdupq_n_u8( 0):vextq_u8(vdupq_n_u8(0), u8v(_v_), 16-(_c_) ))) // vextq_u8: __constrange(0-15)
#define  mm_slli_si128(  _v_,_c_)               _mm_slli_si128(  _v_,_c_)

#define  mm_srli_epi8(   _v_,_c_)               ((_c_)<1 ? (_v_) : (__m128i)((_c_)> 7?vdupq_n_u8( 0):vshrq_n_u8( u8v( _v_), (_c_)))) // vshrq_n: __constrange(1-N)
#define  mm_srli_epi16(  _v_,_c_)               ((_c_)<1 ? (_v_) : (__m128i)((_c_)>15?vdupq_n_u16(0):vshrq_n_u16(u16v(_v_), (_c_))))
#define  mm_srli_epi32(  _v_,_c_)               ((_c_)<1 ? (_v_) : (__m128i)((_c_)>31?vdupq_n_u32(0):vshrq_n_u32(u32v(_v_), (_c_))))
#define  mm_srli_epi64(  _v_,_c_)               ((_c_)<1 ? (_v_) : (__m128i)((_c_)>63?vdupq_n_u64(0):vshlq_n_u64(u64v(_v_), (_c_))))
#define _mm_srli_si128(  _v_,_c_)               ((_c_)<1 ? (_v_) : (__m128i)((_c_)>15?vdupq_n_u8( 0):vextq_u8(u8v(_v_), vdupq_n_u8(0), (_c_) ))) // vextq_u8: __constrange(0-15)

#define  mm_srai_epi8(   _v_,_c_)               ((_c_)<1 ? (_v_) : (__m128i)(vshrq_n_s8( i8v( _v_), (_c_)))) // c <=  8 (vshrq_n:1-N)
#define  mm_srai_epi16(  _v_,_c_)               ((_c_)<1 ? (_v_) : (__m128i)(vshrq_n_s16(i16v(_v_), (_c_)))) // c <= 16
#define  mm_srai_epi32(  _v_,_c_)               ((_c_)<1 ? (_v_) : vshrq_n_s32( (_v_), (_c_))) // c <= 32
#define  mm_srai_epi64(  _v_,_c_)               ((_c_)<1 ? (_v_) : (__m128i)(vshrq_n_s64(i64v(_v_), (_c_)))) // c <= 64

#define _mm_slli_epi8(   _v_,_m_)               (__m128i)vshlq_u8( u8v( _v_), vdupq_n_s8(  (_m_))) // parameter c integer constant/variable
#define _mm_slli_epi16(  _v_,_m_)               (__m128i)vshlq_u16(u16v(_v_), vdupq_n_s16( (_m_)))
#define _mm_slli_epi32(  _v_,_m_)               (__m128i)vshlq_u32(u32v(_v_), vdupq_n_s32( (_m_)))
#define _mm_slli_epi64(  _v_,_m_)               (__m128i)vshlq_u64(u64v(_v_), vdupq_n_s64( (_m_)))

#define _mm_srli_epi8(   _v_,_m_)               (__m128i)vshlq_u8( u8v( _v_), vdupq_n_s8( -(_m_)))
#define _mm_srli_epi16(  _v_,_m_)               (__m128i)vshlq_u16(u16v(_v_), vdupq_n_s16(-(_m_)))
#define _mm_srli_epi32(  _v_,_m_)               (__m128i)vshlq_u32(u32v(_v_), vdupq_n_s32(-(_m_)))
#define _mm_srli_epi64(  _v_,_m_)               (__m128i)vshlq_u64(u64v(_v_), vdupq_n_s64(-(_m_)))

#define _mm_srai_epi8(   _v_,_m_)               (__m128i)vshlq_s8( i8v( _v_), vdupq_n_s8( -(_m_)))
#define _mm_srai_epi16(  _v_,_m_)               (__m128i)vshlq_s16(i16v(_v_), vdupq_n_s16(-(_m_)))
#define _mm_srai_epi32(  _v_,_m_)               vshlq_s32(_v_, vdupq_n_s32(-(_m_)))
#define _mm_srai_epi64(  _v_,_m_)               (__m128i)vshlq_s64(i64v(_v_), vdupq_n_s64(-(_m_)))
#define mm_srai_epi64_63(_v_, _s_)              _mm_srai_epi64(_v_,63) 
#define _mm_sll_epi8(    _u_,_v_)               (__m128i)vshlq_s8( i8v( _u_), i8v( _v_))    // _v_:same value in all lanes
#define _mm_sll_epi16(   _u_,_v_)               (__m128i)vshlq_s16(i16v(_u_), i16v(_v_))
#define _mm_sll_epi32(   _u_,_v_)               vshlq_s32(_u_, _v_)
#define _mm_sll_epi64(   _u_,_v_)               (__m128i)vshlq_s64(i64v(_u_), i64v(_v_))

#define _mm_srl_epi8(    _u_,_v_)               (__m128i)vshrq_s8( i8v( _u_), i8v( _v_))
#define _mm_srl_epi16(   _u_,_v_)               (__m128i)vshrq_s16(i16v(_u_), i16v(_v_))
#define _mm_srl_epi32(   _u_,_v_)               vshrq_s32(_u_, _v_)
#define _mm_srl_epi64(   _u_,_v_)               (__m128i)vshrq_s64(i64v(_u_), i64v(_v_))

#define _mm_sllv_epi32(  _u_,_v_)               (__m128i)vshlq_u32(u32v(_u_), u32v(_v_))   // variable shift
#define _mm_srlv_epi32(  _u_,_v_)               (__m128i)vshlq_u32(u32v(_u_), vnegq_s32(_v_))

//---------------------------------------------- Compare --------- true/false->1/0 (all bits set) ---------------------------------
#define _mm_cmpeq_epi8(  _u_,_v_)               (__m128i)vceqq_s8( i8v( _u_), i8v( _v_))
#define _mm_cmpeq_epi16( _u_,_v_)               (__m128i)vceqq_s16(i16v(_u_), i16v(_v_))
#define _mm_cmpeq_epi32( _u_,_v_)               (__m128i)vceqq_s32(_u_, _v_)

#define _mm_cmplt_epi8(  _u_,_v_)               (__m128i)vcltq_s8( i8v( _u_), i8v( _v_))
#define _mm_cmplt_epi16( _u_,_v_)               (__m128i)vcltq_s16(i16v(_u_), i16v(_v_))
#define _mm_cmplt_epi32( _u_,_v_)               (__m128i)vcltq_s32(_u_, _v_)

#define _mm_cmpgt_epi8(  _u_,_v_)               (__m128i)vcgtq_s8( i8v( _u_), i8v( _v_))
#define _mm_cmpgt_epi16( _u_,_v_)               (__m128i)vcgtq_s16(i16v(_u_), i16v(_v_))
#define _mm_cmpgt_epi32( _u_,_v_)               (__m128i)vcgtq_s32(_u_, _v_)

#define  mm_cmplt_epu8(  _u_,_v_)               (__m128i)vcltq_u8 (u8v( _u_), u8v( _v_))
#define  mm_cmplt_epu16( _u_,_v_)               (__m128i)vcltq_u16(u16v(_u_), u16v(_v_))
#define  mm_cmplt_epu32( _u_,_v_)               (__m128i)vcltq_u32(u32v(_u_), u32v(_v_))

#define  mm_cmpgt_epu8(  _u_,_v_)               (__m128i)vcgtq_u8 (u8v( _u_), u8v( _v_))
#define  mm_cmpgt_epu16( _u_,_v_)               (__m128i)vcgtq_u16(u16v(_u_), u16v(_v_))
#define  mm_cmpgt_epu32( _u_,_v_)               (__m128i)vcgtq_u32(u32v(_u_), u32v(_v_))

// --- Load ------------------------------------------------------------------------------------------------------------------------------------
#define _mm_loadl_epi64( _u64p_)                vcombine_s32(vld1_s32((int32_t const *)(_u64p_)), vcreate_s32(0))
#define  mm_loadu_epi64p(_u64p_,_u_)            (__m128i)vld1q_lane_u64((uint64_t *)(_u64p_), u64v(_u_), 0)
#define _mm_loadu_si128( _ip_)                  vld1q_s32((int32_t *)(_ip_))
#define _mm_load_si128(  _ip_)                  vld1q_s32(_ip_)

#define _mm_load_ps(     _ip_)	                (__m128)vld1q_f32((float32_t *)(_ip_))
#define _mm_loadu_ps(    _ip_)	                (__m128)vld1q_f32((float32_t *)(_ip_))
#define _mm_load1_ps(    _ip_)	                (__m128)vld1q_dup_f32((float32_t *)(_p_))
#define _mm_loadl_pi(_v_,_ip_) 	                (__m128)vcombine_f32((float32x2_t)vld1_f32((float32_t *)(_ip)), (float32x2_t)vget_high_f32(_v_))
#define _mm_loadh_pi(_v_,_ip_)	                (__m128)vcombine_f32((float32x2_t)vget_low_f32(_v_), (float32x2_t)vld1_f32((const float *)(_ip_)))

// --- Store ----------------------------------------------------------------------------------------------------------------------------------
#define _mm_storel_epi64(_ip_,_v_)              vst1q_lane_u64((uint64_t *)(_ip_), u64v(_v_), 0)
#define _mm_storeu_si128(_ip_,_v_)              vst1q_s32((int32_t *)(_ip_), (_v_))

#define _mm_store_ps(    _ip_,_v_)              vst1q_f32(     (float32_t *)(_ip_), (float32x4_t)(_v_))
#define _mm_storeu_ps(   _ip_,_v_)              vst1q_f32(     (float32_t *)(_ip_), (float32x4_t)(_v_))
#define _mm_store_ss(    _ip_,_v_)	        vst1q_lane_f32((float32_t *)(_ip_), (float32x4_t)(_v_), 0)

// --- Convert ----------------------------------------------------------------------------------------------------------------------------------
#define _mm_cvtsi32_si128(_x_)                  vsetq_lane_s32(_x_, vdupq_n_s32(0), 0)
#define _mm_cvtsi64_si128(_v_)                  (__m128i)vdupq_n_u64(_v_)  //vld1q_s64(_v_)
#define  mm_cvtsi64_si128p(_u64p_,_v_)          mm_loadu_epi64p(_u64p_,_v_)

#define _mm_cvtsi128_si32(_v_)                  vgetq_lane_u32(u32v(_v_), 0)
#define _mm_cvtsi128_si64(_v_)                  vgetq_lane_u64(u64v(_v_), 0)

#define _mm_cvtss_f32(_v_)                      vgetq_lane_f32((float32x4_t)(_v_), 0)

static inline __m128i _mm_cvtepu8_epi16(__m128i v) { return (__m128i)(vmovl_u8( vget_low_u8( u8v(v)))); }
static inline __m128i _mm_cvtepu8_epi32(__m128i v) { return (__m128i)(vmovl_u16(vget_low_u16(vmovl_u8( vget_low_u8(u8v(v))))));}
static inline __m128i _mm_cvtepu8_epi64(__m128i v) { return (__m128i)(vmovl_u32(vget_low_u32(vmovl_u16(vget_low_u16(vmovl_u8(vget_low_u8(u8v(v))))))));}
static inline __m128i _mm_cvtepu32_epi64(__m128i v){ return (__m128i)(vmovl_u32(vget_low_u32(u32v(v))));}

static inline __m128 _mm_cvtepi32_ps(__m128i v) {  return vcvtq_f32_s32(v); }
// --- Move -----------------------------------------------------------------------------------------------------------------------
static inline __m128i _mm_move_epi64(__m128i v) { return (__m128i)(vsetq_lane_s64(0, i64v(v), 1));}

//---------------------------------------------- Probability / Statistics -------------------------
static inline __m128i _mm_avg_epu8( __m128i u, __m128i v) { return (__m128i)(vrhaddq_u8(  u8v( u), u8v( v))); }
static inline __m128i _mm_avg_epu16(__m128i u, __m128i v) { return (__m128i)(vrhaddq_u16( u16v(u), u16v(v))); }

// --- Reverse bits/bytes ---------------------------------------------------------------------------------------------------------
#define mm_rbit_epi8(_v_)                       (__m128i)(vrbitq_u8( u8v(_v_))) // reverse bits
#define mm_rev_epi16(_v_)                       (__m128i)(vrev16q_u8(u8v(_v_)))          // reverse bytes
#define mm_rev_epi32(_v_)                       (__m128i)(vrev32q_u8(u8v(_v_)))
#define mm_rev_epi64(_v_)                       (__m128i)(vrev64q_u8(u8v(_v_)))

// --- Insert/extract ------------------------------------------------------------------------------------------------------------
//#define  mm_extract_epi32x(_v_,_i32_,_id_)      vst1q_lane_s32((int32_t *)&(_i32_), i32v(_v_),  _id_)
//#define _mm_extract_epi64x(_v_,_i64_,_id_)      vst1q_lane_s64((int64_t *)&(_i64_), i64v(_v_), _id_)

#define _mm_extract_epi8( _v_,       _id_)      vgetq_lane_u8( u8v(_v_), _id_)
#define _mm_extract_epi16(_v_,       _id_)      vgetq_lane_u16(u16v(_v_), _id_)
#define _mm_extract_epi32(_v_,       _id_)      vgetq_lane_u32(u32v(_v_), _id_)

//#define _mm_insert_epu32p(_v_,_u32p_,_id_)      vsetq_lane_u32(_u32p_, _v_, _id_)
//#define  mm_insert_epi16p(_v_,_u16p_,_id_)      vld1q_lane_u16(_u16p_, u16v(_v_), _id_)
//#define  mm_insert_epi32p(_v_,_u32p_,_id_)      vld1q_lane_u32(_u32p_, u32v(_v_), _id_)

#define _mm_insert_epi8( _v_, _idx_, _c_)       vu8( vsetq_lane_u8( _idx_, u8v( _v_), _c_))
#define _mm_insert_epi16(_v_, _idx_, _c_)       vu16(vsetq_lane_u16(_idx_, u16v(_v_), _c_))
#define _mm_insert_epi32(_v_, _idx_, _c_)       vu32(vsetq_lane_u32(_idx_, u32v(_v_), _c_))
#define _mm_insert_epi64(_v_, _idx_, _c_)       vu64(vsetq_lane_u64(_idx_, u64v(_v_), _c_))

// --- Miscellaneous ----------------------------------------------------------------------------------------------------------------
#define _mm_alignr_epi8(_u_,_v_,_m_)            (__m128i)vextq_u8(  u8v(_v_), u8v(_u_), _m_)

#define _mm_packs_epi16(   _u_,_v_)             (__m128i)vcombine_s8( vqmovn_s16(i16v(_u_)), vqmovn_s16(i16v(_v_)))
#define _mm_packs_epi32(   _u_,_v_)             (__m128i)vcombine_s16(vqmovn_s32(_u_), vqmovn_s32(_v_))
//#define _mm_packs_epu16(   _u_,_v_)                                   (__m128i)vcombine_u8(u16v(_u_), u16v(_v_))
#define _mm_packus_epi16(  _u_,_v_)                                   (__m128i)vcombine_u8( vqmovun_s16(i16v(_u_)), vqmovun_s16(i16v(_v_)))
static inline __m128i _mm_packus_epi32(__m128i u, __m128i v) { return (__m128i)vcombine_u16(vqmovun_s32(u), vqmovun_s32(v)); }

static inline uint16_t _mm_movemask_epi8(__m128i v) {
  const uint8x16_t __attribute__ ((aligned (16))) m = {1, 1<<1, 1<<2, 1<<3, 1<<4, 1<<5, 1<<6, 1<<7, 1, 1<<1, 1<<2, 1<<3, 1<<4, 1<<5, 1<<6, 1<<7};
  uint8x16_t mv = (uint8x16_t)vpaddlq_u32(vpaddlq_u16(vpaddlq_u8(vandq_u8(vcltq_s8((int8x16_t)v, vdupq_n_s8(0)), m))));
  return vgetq_lane_u8(mv, 8) << 8 | vgetq_lane_u8(mv, 0);
}

// --- Neon movemask ------ All lanes must be 0 or -1 (=0xff, 0xffff or 0xffffffff) --------------------------------------------------------------------
  #ifdef __aarch64__
static inline int8_t   mm_movemask_epi8s(int8x8_t sv) { const int8x8_t  m = { 1, 1<<1, 1<<2, 1<<3, 1<<4, 1<< 5, 1<< 6, 1<<7 }; return vaddv_s8(  vand_s8(             sv, m)); } // short only ARM
//static inline uint16_t  mm_movemask_epu16(uint32x4_t v) { const uint16x8_t m = { 1, 1<<2, 1<<4, 1<<6, 1<<8, 1<<10, 1<<12, 1<<14}; return vaddvq_u16(vandq_u16((uint16x8_t)v, m)); }
static inline uint16_t  mm_movemask_epu16(__m128i v) { const uint16x8_t m = { 1, 1<<1, 1<<2, 1<<3, 1<<4, 1<< 5, 1<< 6, 1<<7 }; return vaddvq_u16(vandq_u16(u16v(v), m)); }
static inline uint32_t  mm_movemask_epu32(__m128i v) { const uint32x4_t m = { 1, 1<<1, 1<<2, 1<<3 };                           return vaddvq_u32(vandq_u32(u32v(v), m)); }
static inline uint64_t  mm_movemask_epu64(__m128i v) { const uint64x2_t m = { 1, 1<<1 };                                       return vaddvq_u64(vandq_u64(u64v(v), m)); }

static inline uint64_t  mm_movemask4_epu8(__m128i v) { return vget_lane_u64(vreinterpret_u64_u8(vshrn_n_u16(u16v(v), 4)), 0); }
  #else
static inline uint32_t  mm_movemask_epu32(uint32x4_t v) { const uint32x4_t mask = {1,2,4,8}, av = vandq_u32(v, mask), xv = vextq_u32(av, av, 2), ov = vorrq_u32(av, xv); return vgetq_lane_u32(vorrq_u32(ov, vextq_u32(ov, ov, 3)), 0); }
  #endif

// --- Swizzle : _mm_shuffle_epi8 / _mm_shuffle_epi32 / Pack/Unpack -----------------------------------------------------------------------------------
static inline __m128i _mm_blendv_epi8(__m128i u, __m128i v, __m128i mask) { return vu8(vbslq_u8(vreinterpretq_u8_s8(vshrq_n_s8((i8v(mask)), 7)), u8v(v), u8v(u))); }

#define _MM_SHUFFLE(_u3_,_u2_,_u1_,_u0_)        ((_u3_) << 6 | (_u2_) << 4 | (_u1_) << 2 | (_u0_))

#define _mm_shuffle_epi8(_u_, _v_)              (__m128i)vqtbl1q_s8(i8v(_u_), u8v(_v_))

#define mm_shuffle_epi32s(_v_, _m_)\
  _mm_set_epi32(vgetq_lane_u32(u32v(_v_), ((_m_)     ) & 0x3),\
                vgetq_lane_u32(u32v(_v_), ((_m_) >> 2) & 0x3),\
                vgetq_lane_u32(u32v(_v_), ((_m_) >> 4) & 0x3),\
                vgetq_lane_u32(u32v(_v_), ((_m_) >> 6) & 0x3))

#define _mm_shuffle_epi32(_v_, _c_ ) ({\
  const uint8_t _m_[16] = { (int8_t)(((_c_)        & 3) * 4),     (int8_t)(((_c_)        & 3) * 4 + 1),\
                            (int8_t)(((_c_)        & 3) * 4 + 2), (int8_t)(((_c_)        & 3) * 4 + 3),\
                            (int8_t)((((_c_) >> 2) & 3) * 4),     (int8_t)((((_c_) >> 2) & 3) * 4 + 1),\
                            (int8_t)((((_c_) >> 2) & 3) * 4 + 2), (int8_t)((((_c_) >> 2) & 3) * 4 + 3),\
                            (int8_t)((((_c_) >> 4) & 3) * 4),     (int8_t)((((_c_) >> 4) & 3) * 4 + 1),\
                            (int8_t)((((_c_) >> 4) & 3) * 4 + 2), (int8_t)((((_c_) >> 4) & 3) * 4 + 3),\
                            (int8_t)((((_c_) >> 6) & 3) * 4),     (int8_t)((((_c_) >> 6) & 3) * 4 + 1),\
                            (int8_t)((((_c_) >> 6) & 3) * 4 + 2), (int8_t)((((_c_) >> 6) & 3) * 4 + 3)\
                          };\
  (__m128i)(vqtbl1q_s8(i8v(_v_), vld1q_s8(_m_) )); \
})

  #if defined(__aarch64__)
#define               mm_shuffle_nnnn_epi32(_v_,_m_)   (__m128i)vdupq_laneq_u32(u32v(_v_), _m_)
  #else
#define               mm_shuffle_nnnn_epi32(_v_,_m_)   (__m128i)vdupq_n_u32(vgetq_lane_u32(u32v(_v_), _m_))
  #endif

// --- Named-lane shuffle helpers (int32x4_t / __m128i native) ---------------------------------------------------------------------------------------
static inline __m128i mm_shuffle_0101_epi32(__m128i v) { int32x2_t u = vrev64_s32(vget_low_s32(v)); return vcombine_s32(u, u); }
static inline __m128i mm_shuffle_0122_epi32(__m128i v) { return vcombine_s32(vdup_lane_s32(vget_high_s32(v), 0), vrev64_s32(vget_low_s32(v))); }
static inline __m128i mm_shuffle_0321_epi32(__m128i v) { return vextq_s32(v, v, 1); }
static inline __m128i mm_shuffle_1001_epi32(__m128i v) { return vcombine_s32(vrev64_s32(vget_low_s32(v)), vget_low_s32(v)); }
static inline __m128i mm_shuffle_1010_epi32(__m128i v) { int32x2_t u = vget_low_s32(v); return vcombine_s32(u, u); }
static inline __m128i mm_shuffle_2020_epi32(__m128i v) { return vuzp1q_s32(v, v); }
static inline __m128i mm_shuffle_2031_epi32(__m128i v) { int32x4_t x = vuzp2q_s32(v, v); int32x4_t y = vuzp1q_s32(v, v); return vcombine_s32(vget_low_s32(x), vget_low_s32(y)); }
static inline __m128i mm_shuffle_2103_epi32(__m128i v) { return vextq_s32(v, v, 3); }
static inline __m128i mm_shuffle_2301_epi32(__m128i v) { return vrev64q_s32(v); }
static inline __m128i mm_shuffle_2211_epi32(__m128i v) { return vcombine_s32(vdup_lane_s32(vget_low_s32(v), 1), vdup_lane_s32(vget_high_s32(v), 0)); }
static inline __m128i mm_shuffle_3120_epi32(__m128i v) { int32x4_t x = vuzp1q_s32(v, v); int32x4_t y = vuzp2q_s32(v, v); return vcombine_s32(vget_low_s32(x), vget_low_s32(y)); }
static inline __m128i mm_shuffle_3311_epi32(__m128i v) { return vtrn2q_s32(v, v); }
static inline __m128i mm_shuffle_3332_epi32(__m128i v) { return vcombine_s32(vget_high_s32(v), vdup_lane_s32(vget_high_s32(v), 1)); }

static inline __m128i _mm_unpacklo_epi8( __m128i _u_, __m128i _v_) { int8x8x2_t  _zv = vzip_s8 ( vget_low_s8( i8v( _u_)), vget_low_s8 (i8v( _v_)));  return (__m128i)vcombine_s8( _zv.val[0], _zv.val[1]);}
static inline __m128i _mm_unpacklo_epi16(__m128i _u_, __m128i _v_) { int16x4x2_t _zv = vzip_s16( vget_low_s16(i16v(_u_)), vget_low_s16(i16v(_v_)));  return (__m128i)vcombine_s16(_zv.val[0], _zv.val[1]);}
static inline __m128i _mm_unpacklo_epi32(__m128i _u_, __m128i _v_) { int32x2x2_t _zv = vzip_s32( vget_low_s32(     _u_ ), vget_low_s32(     _v_ ));  return          vcombine_s32(_zv.val[0], _zv.val[1]);}
static inline __m128i _mm_unpacklo_epi64(__m128i _u_, __m128i _v_) {                                                                                  return (__m128i)vcombine_s64(vget_low_s64(i64v(_u_)), vget_low_s64(i64v(_v_))); }

static inline __m128i _mm_unpackhi_epi8( __m128i _u_, __m128i _v_) { int8x8x2_t  _zv = vzip_s8 (vget_high_s8( i8v( _u_)), vget_high_s8( i8v( _v_))); return (__m128i)vcombine_s8( _zv.val[0], _zv.val[1]); }
static inline __m128i _mm_unpackhi_epi16(__m128i _u_, __m128i _v_) { int16x4x2_t _zv = vzip_s16(vget_high_s16(i16v(_u_)), vget_high_s16(i16v(_v_))); return (__m128i)vcombine_s16(_zv.val[0], _zv.val[1]); }
static inline __m128i _mm_unpackhi_epi32(__m128i _u_, __m128i _v_) { int32x2x2_t _zv = vzip_s32(vget_high_s32(     _u_ ), vget_high_s32(     _v_ )); return          vcombine_s32(_zv.val[0], _zv.val[1]); }
static inline __m128i _mm_unpackhi_epi64(__m128i _u_, __m128i _v_) {                                                                                  return (__m128i)vcombine_s64(vget_high_s64(i64v(_u_)), vget_high_s64(i64v(_v_))); }

