#define likely(x)     	__builtin_expect((x),1)
#define unlikely(x)   	__builtin_expect((x),0)
//------------------------------------- Variable Byte -----------------------------------------------------
#define vbputx(__op, __x)  { typeof(__x) _x = __x; while(_x > 0x7f) { *__op++ =      _x & 0x7f;       _x >>= 7; }  *__op++ =     _x | 0x80; }

#define vbgetax(__ip, __x, __act) { unsigned _sft=0; for(__x=0;;_sft += 7) { unsigned _c = *__ip++; __x += (_c & 0x7f) << _sft; if(_c >= 0x80) { __act; break; } } }
#define vbgetx(__ip) ({ unsigned _x; vbgetax(__ip, _x, ;); _x; })
 
#define vbxput(__op, __x) { *__op++ = __x; if(unlikely((__x) >= 0xff)) { unsigned _xi = (__x) - 0xff; __op[-1] = 0xff; vbputx(__op, _xi); } }
#define vbxget(__ip, __x) { __x = *__ip++; if(unlikely( __x == 0xff)) { __x = vbgetx(__ip); __x+=0xff; } }

#define vbzput(__op, __x, __m, __emap) do { if(unlikely((__x) < __m)) *__op++ = __emap[__x]; else { unsigned _xi = (__x) - __m; *__op++ = __emap[__m]; vbputx(__op, _xi); } } while(0)
#define vbzget(__ip, __x, __m, __e) { __x = __e; if(unlikely( __x == __m)) { __x = vbgetx(__ip); __x+=__m; } }
  
#ifdef MEMSAFE 
#define rmemset(__op, __c, __i) while(__i--) *__op++ = __c
#else
#define rmemset(__op, __c, __i) do { unsigned char *_up = __op; __op+=__i; unsigned long long _uc = (unsigned long long )__c<<56 | (unsigned long long )__c<<48 | (unsigned long long )__c<<40 | (unsigned long long )__c<<32 | (unsigned)__c<<24 | (unsigned)__c<<16 | (unsigned)__c<<8 | (unsigned)__c;\
  do { *(unsigned long long *)_up = _uc; _up += 8; *(unsigned long long *)_up = _uc; _up += 8; } while(_up <= __op);\
} while(0)
#endif
