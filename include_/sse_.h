#ifdef __SSE2__ //----------------- intel SSE2/SSSE3 ( wraper functions compatible with intel/arm; permits to have one source code version for arm+intel) --------------
#define mm_movemask_epu32(_v_)                  _mm_movemask_ps(_mm_castsi128_ps(_v_))
#define mm_movemask_epu16(_v_)                  _mm_movemask_epi8(_v_)
#define mm_loadu_epi64p( _u64p_,_v_)            _v_ = _mm_cvtsi64_si128(ctou64(_u64p_))

#define mm_extract_epu32( _v_,       _id_)      _mm_extract_epi32(_v_, _id_)
#define mm_extract_epi32x(_v_,_u32_, _id_)      _u32_ = _mm_extract_epi32(_v_, _id_)
#define mm_extract_epi64x(_v_,_u64_, _id_)      _u64_ = _mm_extract_epi64(_v_, _id_)

//#define mm_insert_epi16p( _v_,_u16p_,_c_)       _mm_insert_epi32( _v_,ctou16(_u16p_),_c_)
//#define mm_insert_epi32p( _v_,_u32p_,_c_)       _mm_insert_epi32( _v_,ctou32(_u32p_),_c_)

#define mm_mullo_epu32(   _u_,_v_)              _mm_mullo_epi32(_u_,_v_)
#define mm_cvtsi64_si128p(_u64p_,_v_)           _v_ = _mm_cvtsi64_si128(ctou64(_u64p_))

#define mm_cmplt_epu8 (  _u_, _v_)              _mm_cmplt_epi8 (_mm_xor_si128(_u_, _mm_set1_epi8( 0x80)),       _mm_xor_si128(_v_, _mm_set1_epi8 (0x80)))
#define mm_cmplt_epu16(  _u_, _v_)              _mm_cmplt_epi16(_mm_xor_si128(_u_, _mm_set1_epi16(0x8000)),     _mm_xor_si128(_v_, _mm_set1_epi16(0x8000)))
#define mm_cmplt_epu32(  _u_, _v_)              _mm_cmplt_epi32(_mm_xor_si128(_u_, _mm_set1_epi32(0x80000000)), _mm_xor_si128(_v_, _mm_set1_epi32(0x80000000)))

#define mm_cmpgt_epu8 (  _u_, _v_)              _mm_cmpgt_epi8( _mm_xor_si128(_u_, _mm_set1_epi8 (0x80)),       _mm_xor_si128(_v_, _mm_set1_epi8 (0x80)))
#define mm_cmpgt_epu16(  _u_, _v_)              _mm_cmpgt_epi16(_mm_xor_si128(_u_, _mm_set1_epi16(0x8000)),     _mm_xor_si128(_v_, _mm_set1_epi16(0x8000)))
#define mm_cmpgt_epu32(  _u_, _v_)              _mm_cmpgt_epi32(_mm_xor_si128(_u_, _mm_set1_epi32(0x80000000)), _mm_xor_si128(_v_, _mm_set1_epi32(0x80000000)))

#define mm_shuffles_epi32(_v_, _m_)				_mm_shuffles_epi32(_v_, _m_) //small values (NEON compatibility)
#define mm_shuffle_nnnn_epi32(_v_, _n_)         _mm_shuffle_epi32(_v_, _MM_SHUFFLE(_n_,_n_,_n_,_n_))
#define mm_shuffle_2020_epi32(_v_)              _mm_shuffle_epi32(_v_, _MM_SHUFFLE(2,0,2,0))
#define mm_shuffle_2031_epi32(_v_)              _mm_shuffle_epi32(_v_, _MM_SHUFFLE(2,0,3,1))
#define mm_shuffle_3120_epi32(_v_)              _mm_shuffle_epi32(_v_, _MM_SHUFFLE(3,1,2,0))
#define mm_shuffle_3311_epi32(_v_)              _mm_shuffle_epi32(_v_, _MM_SHUFFLE(3,3,1,1))
#define mm_shuffle_3331_epi32(_v_)              _mm_shuffle_epi32(_v_, _MM_SHUFFLE(3,3,3,1))

#define _mm_slli_epi8( _v_, _m_ )                _mm_and_si128(_mm_set1_epi8(0xff << _m_), _mm_slli_epi32(_v_, _m_ ))
#define _mm_srli_epi8( _v_, _m_ )                _mm_and_si128(_mm_set1_epi8(0xff >> _m_), _mm_srli_epi32(_v_, _m_ ))

#define  mm_slli_epi8(   _v_,_c_)               _mm_slli_epi8( _v_,_c_)  // parameter c for mm_* MUST be a constant for compatibilty with the arm functions above
#define  mm_slli_epi16(  _v_,_c_)               _mm_slli_epi16(_v_,_c_)
#define  mm_slli_epi32(  _v_,_c_)               _mm_slli_epi32(_v_,_c_)
#define  mm_slli_epi64(  _v_,_c_)               _mm_slli_epi64(_v_,_c_)
#define  mm_slli_si128(_v_, _c_ )               _mm_slli_si128(_v_,_c_)

#define  mm_srli_epi8(   _v_,_c_)               _mm_srli_epi8( _v_,_c_)
#define  mm_srli_epi16(  _v_,_c_)               _mm_srli_epi16(_v_,_c_)
#define  mm_srli_epi32(  _v_,_c_)               _mm_srli_epi32(_v_,_c_)
#define  mm_srli_epi64(  _v_,_c_)               _mm_srli_epi64(_v_,_c_)

#define  mm_srai_epi8(   _v_,_c_)               _mm_srai_epi8( _v_,_c_)
#define  mm_srai_epi16(  _v_,_c_)               _mm_srai_epi16(_v_,_c_)
#define  mm_srai_epi32(  _v_,_c_)               _mm_srai_epi32(_v_,_c_)
#define  mm_srai_epi64(  _v_,_c_)               _mm_srai_epi64(_v_,_c_)
#ifdef __AVX512F__
#define mm_srai_epi64_63(_v_)                   _mm_srai_epi64(_v_, 63)
#else
#define mm_srai_epi64_63(_v_)                   _mm_srai_epi32(_mm_shuffle_epi32(_v_, _MM_SHUFFLE(3, 3, 1, 1)), 31)
#endif

  #ifdef __SSSE3__
static ALWAYS_INLINE __m128i mm_rbit_epi8(__m128i v) { // reverse bits in bytes
  __m128i fv     = _mm_set_epi8(15, 7,11, 3,13, 5, 9, 1,14, 6,10, 2,12, 4, 8, 0), cv0f_8 = _mm_set1_epi8(0xf);
  __m128i lv = _mm_shuffle_epi8(fv,_mm_and_si128(               v,     cv0f_8));
  __m128i hv = _mm_shuffle_epi8(fv,_mm_and_si128( mm_srli_epi64(v, 4), cv0f_8));
  return _mm_or_si128( mm_slli_epi64(lv,4), hv);
}

static ALWAYS_INLINE __m128i mm_rev_epi16(__m128i v) { return _mm_shuffle_epi8(v, _mm_set_epi8(14,15,12,13,10,11, 8, 9, 6, 7, 4, 5, 2, 3, 0, 1)); } // reverse vector bytes in uint??_t
static ALWAYS_INLINE __m128i mm_rev_epi32(__m128i v) { return _mm_shuffle_epi8(v, _mm_set_epi8(12,13,14,15, 8, 9,10,11, 4, 5, 6, 7, 0, 1, 2, 3)); }
static ALWAYS_INLINE __m128i mm_rev_epi64(__m128i v) { return _mm_shuffle_epi8(v, _mm_set_epi8( 8, 9,10,11,12,13,14,15, 0, 1, 2, 3, 4, 5, 6, 7)); }
static ALWAYS_INLINE __m128i mm_rev_si128(__m128i v) { return _mm_shuffle_epi8(v, _mm_set_epi8( 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15)); }
  #endif
#endif
