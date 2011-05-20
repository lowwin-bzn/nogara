#ifndef NOGARA_EXPRESSION_SSE_TRAITS_HPP
#define NOGARA_EXPRESSION_SSE_TRAITS_HPP

#include <cctype>
#include <nogara/expression/sse/define.hpp>
#include <nogara/expression/container.hpp>

__NOGARA_SSE_BEGIN

template<class T> struct to_sse_type;
template<> struct to_sse_type<int>{
    static std::size_t const size = 4;
    typedef __m128i type;
    typedef expression::expression_container<int, size> NG_ALIGN16 align_type;
};

template<> struct to_sse_type<float>{
    static std::size_t const size = 4;
    typedef __m128 type;
    typedef expression::expression_container<float, size> NG_ALIGN16 align_type;
};

template<> struct to_sse_type<double>{
    static std::size_t const size = 2;
    typedef __m128d type;
    typedef expression::expression_container<double, size> NG_ALIGN16 align_type;
};

__NOGARA_SSE_END

#endif
