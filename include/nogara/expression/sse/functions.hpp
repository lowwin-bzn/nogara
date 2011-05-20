#ifndef NOGARA_EXPRESSION_SSE_FUNCTIONS_HPP
#define NOGARA_EXPRESSION_SSE_FUNCTIONS_HPP

#include <nogara/expression/sse/traits.hpp>

__NOGARA_SSE_BEGIN

inline void store(to_sse_type<double>::align_type& dest, __m128d value){
    _mm_store_pd(&dest[0], value);
}
inline void store(to_sse_type<float>::align_type& dest,  __m128  value){
    _mm_store_ps(&dest[0], value);
}
inline void store(to_sse_type<int>::align_type& dest,  __m128i value){
    _mm_store_si128(reinterpret_cast<__m128i*>(&dest[0]), value);
}

inline __m128i load(int x, int y, int z, int w){
    return _mm_set_epi32(w, z, y, x);
}
inline __m128  load(float x, float y, float z, float w){
    return _mm_set_ps(w, z, y, x);
}

inline __m128d load(double x, double y){
    return _mm_set_pd(y, x);
}
inline __m128i load(int    const (&value)[4]){
    return load(value[0], value[1], value[2], value[3]);
}
inline __m128  load(float  const (&value)[4]){
    return _mm_load_ps(value);
}
inline __m128d load(double const (&value)[2]){
    return _mm_load_pd(value);
}
inline __m128i load(to_sse_type<int>::align_type const& value){
    return load(value[0], value[1], value[2], value[3]);
}
inline __m128  load(to_sse_type<float>::align_type const& value){
    return _mm_load_ps(&value[0]);
}
inline __m128d load(to_sse_type<double>::align_type const& value){
    return _mm_load_pd(&value[0]);
}
inline __m128i load(int    const* value){
    return load(value[0], value[1], value[2], value[3]);
}
inline __m128 load(float  const* value){
    return _mm_load_ps(value);
}
inline __m128d load(double const* value){
    return _mm_load_pd(value);
}

inline __m128  scalar_vector(float v)  {return _mm_load1_ps(&v);}
inline __m128i scalar_vector(int v)    {return _mm_set_epi32(v, v, v, v);}
inline __m128d scalar_vector(double v) {return _mm_load1_pd(&v);}

inline __m128i add(__m128i x, __m128i y){return _mm_add_epi32(x, y);}
inline __m128  add(__m128  x, __m128  y){return _mm_add_ps(x, y);}
inline __m128d add(__m128d x, __m128d y){return _mm_add_pd(x, y);}

template<class T, std::size_t N>
inline typename to_sse_type<T>::type
add(T const (&x)[N], T const (&y)[N]){return add(load(x), load(y));}

inline __m128i sub(__m128i x, __m128i y){return _mm_sub_epi32(x, y);}
inline __m128  sub(__m128  x, __m128  y){return _mm_sub_ps(x, y);}
inline __m128d sub(__m128d x, __m128d y){return _mm_sub_pd(x, y);}

template<class T, std::size_t N>
inline typename to_sse_type<T>::type
sub(T const (&x)[N], T const (&y)[N]){return sub(load(x), load(y));}

inline __m128  mul(__m128  x, __m128  y){return _mm_mul_ps(x, y);}
inline __m128d mul(__m128d x, __m128d y){return _mm_mul_pd(x, y);}

inline __m128  div(__m128  x, __m128  y){return _mm_div_ps(x, y);}
inline __m128d div(__m128d x, __m128d y){return _mm_div_pd(x, y);}

#if NG_SSE_VER > NG_SSE4
inline float  dot(__m128  x, __m128  y){return sum(mul(x, y));}
inline double dot(__m128d x, __m128d y){return sum(mul(x, y));}

inline float  dot(__m128  x, __m128  y){return sum(mul(x, y));}
inline double dot(__m128d x, __m128d y){return sum(mul(x, y));}

__NOGARA_SSE_END



#endif
