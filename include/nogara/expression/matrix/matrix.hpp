#ifndef NOGARA_EXPRESSION_MATRIX_HPP
#define NOGARA_EXPRESSION_MATRIX_HPP

/////////////////////////////////////////////
//! @file nogara/expression/matrix/matrix.hpp
//! @brief 2x2, 3x3, 4x4の正方行列クラス
//         なお、4x4行列は多用するため汎用的なmatrixという名前にしている
/////////////////////////////////////////////

#include <nogara/expression/matrix/extend_matrix.hpp>
#include <nogara/expression/matrix/matrix_container.hpp>
#include <nogara/expression/matrix/diagonal_matrix.hpp>

__NOGARA_EXPRESSION_BEGIN

template<typename T>
class matrix : public matrix_container<T, 4, 4, matrix<T> >{
    typedef matrix<T>                            self_type;
    typedef matrix_container<T, 4, 4, self_type> base_type;

public:
    matrix():base_type(){}

    template<class E>
    matrix(matrix_expression<E> const& e,
           typename boost::enable_if<square_equal_to_c<E, 4> >::type* = 0):base_type(e){}


    matrix(T const& m11, T const& m21, T const& m31, T const& m41,
           T const& m12, T const& m22, T const& m32, T const& m42,
           T const& m13, T const& m23, T const& m33, T const& m43,
           T const& m14, T const& m24, T const& m34, T const& m44)
    {
        (*this)(0, 0) = m11; (*this)(1, 0) = m21; (*this)(2, 0) = m31; (*this)(3, 0) = m41;
        (*this)(0, 1) = m12; (*this)(1, 1) = m22; (*this)(2, 1) = m32; (*this)(3, 1) = m42;
        (*this)(0, 2) = m13; (*this)(1, 2) = m23; (*this)(2, 2) = m33; (*this)(3, 2) = m43;
        (*this)(0, 3) = m14; (*this)(1, 3) = m24; (*this)(2, 3) = m34; (*this)(3, 3) = m44;
    }

    template<class E1, class E2, class E3, class E4>
    matrix(vector_expression<E1> const& v1,
           vector_expression<E2> const& v2,
           vector_expression<E3> const& v3,
           vector_expression<E4> const& v4)
    {
        (*this)(0, 0) = get<0>(v1); (*this)(1, 0) = get<1>(v1); (*this)(2, 0) = get<2>(v1); (*this)(3, 0) = get<3>(v1);
        (*this)(0, 1) = get<0>(v2); (*this)(1, 1) = get<1>(v2); (*this)(2, 1) = get<2>(v2); (*this)(3, 1) = get<3>(v2);
        (*this)(0, 2) = get<0>(v3); (*this)(1, 2) = get<1>(v3); (*this)(2, 2) = get<2>(v3); (*this)(3, 2) = get<3>(v3);
        (*this)(0, 3) = get<0>(v4); (*this)(1, 3) = get<1>(v4); (*this)(2, 3) = get<2>(v4); (*this)(3, 3) = get<3>(v4);
    }

    matrix(T const (&m)[16]){
        for(int x = 0; x < 4; ++x){
            for(int y = 0; y < 4; ++y){
                (*this)(x, y) = m[x * 4 + y];
            }
        }
    }

    static matrix const identity;
};

template<typename T>
class matrix33 : public matrix_container<T, 3, 3, matrix33<T> >{
    typedef matrix33<T>                          self_type;
    typedef matrix_container<T, 3, 3, self_type> base_type;
public:
    matrix33():base_type(){}
    template<class E>
    matrix33(matrix_expression<E> const& e):base_type(e){}

    matrix33(T const& m11, T const& m21, T const& m31,
             T const& m12, T const& m22, T const& m32,
             T const& m13, T const& m23, T const& m33)
    {
        (*this)(0, 0) = m11; (*this)(1, 0) = m21; (*this)(2, 0) = m31;
        (*this)(0, 1) = m12; (*this)(1, 1) = m22; (*this)(2, 1) = m32;
        (*this)(0, 2) = m13; (*this)(1, 2) = m23; (*this)(2, 2) = m33;
    }

    matrix33(T const (&m)[9]){
        (*this)(0, 0) = m[0]; (*this)(1, 0) = m[1]; (*this)(2, 0) = m[2];
        (*this)(0, 1) = m[3]; (*this)(1, 1) = m[4]; (*this)(2, 1) = m[5];
        (*this)(0, 2) = m[6]; (*this)(1, 2) = m[7]; (*this)(2, 2) = m[8];
    }

    template<class E1, class E2, class E3>
    matrix33(vector_expression<E1> const& v1,
             vector_expression<E2> const& v2,
             vector_expression<E3> const& v3)
    {
        (*this)(0, 0) = get<0>(v1); (*this)(1, 0) = get<1>(v1); (*this)(2, 0) = get<2>(v1);
        (*this)(0, 1) = get<0>(v2); (*this)(1, 1) = get<1>(v2); (*this)(2, 1) = get<2>(v2);
        (*this)(0, 2) = get<0>(v3); (*this)(1, 2) = get<1>(v3); (*this)(2, 2) = get<2>(v3);
    }

    static matrix33 const identity;
};

template<typename T>
class matrix22 : public matrix_container<T, 2, 2, matrix22<T> >{
    typedef matrix22<T>                          self_type;
    typedef matrix_container<T, 2, 2, self_type> base_type;
public:
    matrix22():base_type(){}
    template<class E>
    matrix22(matrix_expression<E> const& e):base_type(e){}

    matrix22(T const& m11, T const& m21,
             T const& m12, T const& m22)
    {
        (*this)(0, 0) = m11; (*this)(1, 0) = m21;
        (*this)(0, 1) = m12; (*this)(1, 1) = m22;
    }

    template<class E1, class E2>
    matrix22(vector_expression<E1> const& v1,
             vector_expression<E2> const& v2)
    {
        (*this)(0, 0) = get<0>(v1); (*this)(1, 0) = get<1>(v1);
        (*this)(0, 1) = get<0>(v2); (*this)(1, 1) = get<1>(v2);
    }

    static matrix22 const identity;
};

template<class T>
matrix<T> const matrix<T>::identity(1, 0, 0, 0,
                                    0, 1, 0, 0,
                                    0, 0, 1, 0,
                                    0, 0, 0, 1);

template<class T>
matrix33<T> const matrix33<T>::identity(1, 0, 0,
                                        0, 1, 0,
                                        0, 0, 1);

template<class T>
matrix22<T> const matrix22<T>::identity(1, 0,
                                        0, 1);

__NOGARA_EXPRESSION_END

__NOGARA_BEGIN
using expression::matrix;
using expression::matrix33;
using expression::matrix22;
__NOGARA_END

#include <nogara/expression/matrix/function.hpp>


#endif
