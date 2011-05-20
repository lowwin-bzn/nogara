#ifndef NOGARA_EXPRESSION_SSE_MATRIX_HPP
#define NOGARA_EXPRESSION_SSE_MATRIX_HPP

#include <nogara/expression/sse/define.hpp>

__NOGARA_SSE_DEFINE

template<class T>
class matrix{
public:
    typedef typename to_sse_type<T>::align_type pack_type;
    typedef typename to_sse_type<T>::type       sse_type;
    matrix(T _11, T _21, T _31, T _41,
           T _12, T _22, T _32, T _42,
           T _13, T _23, T _33, T _43,
           T _14, T _24, T _34, T _44)
    {}
    matrix(__m128 c1, __m128 c2, __m128 c3, __m128 c4):
        col1(c1), col2(c2), col3(c3), col4(c4){}

    matrix operator +(matrix const& rhs) const {
        return matrix(sse::add(col1, rhs.col1),
                      sse::add(col2, rhs.col2),
                      sse::add(col3, rhs.col3),
                      sse::add(col4, rhs.col4));
    }

    matrix operator -(matrix const& rhs) const {
        return matrix(sub(col1, rhs.col1),
                      sub(col2, rhs.col2),
                      sub(col3, rhs.col3),
                      sub(col4, rhs.col4));
    }

private:
    pack_type col1, col2, col3, col4;
};

__NOGARA_SSE_END

#endif
