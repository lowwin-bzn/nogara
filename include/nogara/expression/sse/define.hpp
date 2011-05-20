#ifndef NOGARA_EXPRESSION_SSE_DEFINE_HPP
#define NOGARA_EXPRESSION_SSE_DEFINE_HPP

#include <nogara/nogara_define.hpp>

#define __NOGARA_SSE_BEGIN __NOGARA_BEGIN namespace sse{
#define __NOGARA_SSE_END } __NOGARA_END

#if defined(__SSE__)
#  include <mmintrin.h>
#  include <xmmintrin.h>
#  define NG_SSE    10
#  define NG_SSE2   20
#  define NG_SSE3   30
#  define NG_SSSE3  35
#  define NG_SSE4   40
#  define NG_SSE4_1 41
#  define NG_SSE4_2 42
#  define NG_SSE_VER NG_SSE
#  if defined(__SSE2__)
#    include <emmintrin.h>
#    undef  NG_SSE_VER
#    define NG_SSE_VER 20
#  endif
#  if defined(__SSE3__)
#    include <pmmintrin.h>
#    undef  NG_SSE_VER
#    define NG_SSE_VER 30
#  endif
#  if defined(__SSSE3__)
#    include <tmmintrin.h>
#    undef  NG_SSE_VER
#    define NG_SSE_VER 32
#  endif
#  if defined(__SSE4_1__)
#    include <smmintrin.h>
#    undef  NG_SSE_VER
#    define NG_SSE_VER 41
#  endif
#  if defined(__SSE4_2__)
#    undef  NG_SSE_VER
#    define NG_SSE_VER 42
#    include <nmmintrin.h>
#  endif
#endif

#if defined(NG_GNUC)
#define NG_ALIGN16 __attribute__((aligned(16)))
#elif defined(NG_MSC)
#define NG_ALIGN16 _declspec(align(16))
#endif


#endif
