#ifndef NOGARA_EXPRESSION_MATRIX_OPERATOR_HPP
#define NOGARA_EXPRESSION_MATRIX_OPERATOR_HPP

///////////////////////////////////////////////
//! @file nogara/expression/matrix/operator.hpp
//! @brief 行列の演算子群
///////////////////////////////////////////////

#include <nogara/expression/matrix/binary_expression.hpp>
#include <nogara/expression/matrix/unary_expression.hpp>
#include <nogara/expression/matrix/matrix_and_scalar.hpp>
#include <nogara/expression/matrix/minor.hpp>
#include <nogara/expression/matrix/multiply.hpp>
#include <nogara/expression/matrix/matrix_vector.hpp>
#include <nogara/expression/matrix/matrix_container.hpp>
#include <nogara/expression/matrix/matrix_fwd.hpp>
#include <nogara/expression/vector/vector2.hpp>
#include <nogara/expression/vector/vector3.hpp>
#include <nogara/expression/vector/vector4.hpp>

__NOGARA_EXPRESSION_BEGIN

/////////////////////////////
//! @brief ベクトル同士の加算
/////////////////////////////
template<class E1, class E2>
inline matrix_binary<E1, E2, scalar_add<E1, E2> >
operator +(matrix_expression<E1> const& e1, matrix_expression<E2> const& e2){
    return matrix_binary<E1, E2, scalar_add<E1, E2> >(e1, e2);
}

/////////////////////////////
//! @brief ベクトル同士の減算
/////////////////////////////
template<class E1, class E2>
inline matrix_binary<E1, E2, scalar_sub<E1, E2> >
operator -(matrix_expression<E1> const& e1, matrix_expression<E2> const& e2){
    return matrix_binary<E1, E2, scalar_sub<E1, E2> >(e1, e2);
}

///////////////////////////
//! @brief ベクトルの正符号
///////////////////////////
template<class E>
inline matrix_unary<E, scalar_identity<E> >
operator +(matrix_expression<E> const& val){
    return matrix_unary<E, scalar_identity<E> >(val);
}

///////////////////////////
//! @brief ベクトルの正符号
///////////////////////////
template<class E>
inline matrix_unary<E, scalar_negate<E> >
operator -(matrix_expression<E> const& val){
    return matrix_unary<E, scalar_abs<E> >(val);
}

/////////////////////////////////
//! @brief スカラとベクトルの乗算
/////////////////////////////////
template<class E, class T>
inline typename boost::enable_if<
    is_scalar<T>, scalar_and_matrix<T, E, scalar_mul<T, E> > >::type
operator *(T const& e1, matrix_expression<E> const& e2){
    return scalar_and_matrix<T, E, scalar_mul<T, E> >(e1, e2);
}

/////////////////////////////////
//! @brief ベクトルとスカラの乗算
/////////////////////////////////
template<class E, class T>
inline typename boost::enable_if<
    is_scalar<T>, matrix_and_scalar<E, T, scalar_mul<E, T> > >::type
operator *(matrix_expression<E> const& e1, T const& e2){
    return matrix_and_scalar<E, T, scalar_mul<E, T> >(e1, e2);
}

/////////////////////////////
//! @brief 行列同士の乗算
/////////////////////////////
template<class E1, class E2>
inline mul_matrix<E1, E2>
operator *(matrix_expression<E1> const& e1, matrix_expression<E2> const& e2){
    return mul_matrix<E1, E2>(e1, e2);
}


/////////////////////////////////
//! @brief 行列とスカラの除算
/////////////////////////////////
template<class E, class T>
inline typename boost::enable_if<
    is_scalar<T>, scalar_and_matrix<E, T, scalar_div<E, T> > >::type
operator /(matrix_expression<E> const& e1, T const& e2){
    return scalar_and_matrix<E, T, scalar_div<E, T> >(e1, e2);
}

/////////////////////////////////////////////////
//! @brief 等式 行、列の数が合っていなければfalse
/////////////////////////////////////////////////
template<class E1, class E2>
inline typename boost::disable_if<same_row_column<E1, E2>, bool>::type
operator ==(matrix_expression<E1> const& e1, matrix_expression<E2> const& e2){
    return false;
}

//////////////////////////////////////////////////////////
//! @brief 等式 どちらかのデータ型が浮動小数の場合は
//!        要素同士を引いた値の絶対値がepsilon以下かで判断
//////////////////////////////////////////////////////////
template<class E1, class E2>
inline typename boost::enable_if<
    nogara::either_is_float<typename E1::value_type, typename E2::value_type>, bool>::type
operator ==(matrix_expression<E1> const& e1, matrix_expression<E2> const& e2){
    typedef typename deduct2<E1, E2>::real_type value_type;
    for(std::size_t x = 0; x < get_row<E1>::value; ++x){
        for(std::size_t y = 0; y < get_column<E2>::value; ++y){
            if(!float_guess<value_type>()(e1()(x, y), e2()(x, y))){
                return false;
            }
        }
    }
    return true;
}

//////////////////////////////////////////////////
//! @brief 等式 浮動小数でない場合は単純に==で比較
//////////////////////////////////////////////////
template<class E1, class E2>
inline typename boost::disable_if<
    nogara::either_is_float<typename E1::value_type, typename E2::value_type>, bool>::type
operator ==(matrix_expression<E1> const& e1, matrix_expression<E2> const& e2){
    for(std::size_t x = 0; x < get_row<E1>::value; ++x){
        for(std::size_t y = 0; y < get_column<E2>::value; ++y){
            if(e1()(x, y) != e2()(x, y)){return false;}
        }
    }
    return true;
}

/////////////////
//! @brief 不等号
/////////////////
template<class E1, class E2>
bool operator !=(matrix_expression<E1> const& e1, matrix_expression<E2> const& e2){
    return !(e1 == e2);
}


///////////////////////////////
//! @brief ベクトル * 行列
///////////////////////////////
template<class EV, class EM>
inline typename boost::enable_if<
    boost::mpl::and_<column_equal_to_c<EM, 4>, dimension_equal_to_c<EV, 4> >,
    vector4<typename deduct2<EM, EV>::value_type> >::type
operator *(vector_expression<EV> const& v, matrix_expression<EM> const& m){
    typedef vector4<typename deduct2<EM, EV>::value_type> result;
    return result(expression::dot(v, expr_column_vector<EM, 0>(m)),
                  expression::dot(v, expr_column_vector<EM, 1>(m)),
                  expression::dot(v, expr_column_vector<EM, 2>(m)),
                  expression::dot(v, expr_column_vector<EM, 3>(m)));
}

///////////////////////////////
//! @brief 行列 * ベクトル
///////////////////////////////
template<class EM, class EV>
inline typename boost::enable_if<
    boost::mpl::and_<row_equal_to_c<EM, 4>, dimension_equal_to_c<EV, 4> >,
    vector4<typename deduct2<EM, EV>::value_type> >::type
operator *(matrix_expression<EM> const& m, vector_expression<EV> const& v){
    typedef vector4<typename deduct2<EM, EV>::value_type> result;
    return result(expression::dot(expr_row_vector<EM, 0>(m), v),
                  expression::dot(expr_row_vector<EM, 1>(m), v),
                  expression::dot(expr_row_vector<EM, 2>(m), v),
                  expression::dot(expr_row_vector<EM, 3>(m), v));
}

/////////////////////////////////////////////////////////////
//! @brief ベクトル * 行列
//!        3次元ベクトルは特別にNx4行列との乗算を可能とする
/////////////////////////////////////////////////////////////
template<class EV, class EM>
inline typename boost::enable_if<
    boost::mpl::and_<column_equal_to_c<EM, 4>, dimension_equal_to_c<EV, 3> >,
    vector3<typename deduct2<EM, EV>::value_type> >::type
operator *(vector_expression<EV> const& v, matrix_expression<EM> const& m){
    typedef vector3<typename deduct2<EM, EV>::value_type> result;
    typedef minor_matrix<EM, 3, 3> minor_m;
    return result(expression::dot(v, expr_column_vector<minor_m, 0>(minor_m(m))) + get<0, 3>(m),
                  expression::dot(v, expr_column_vector<minor_m, 1>(minor_m(m))) + get<1, 3>(m),
                  expression::dot(v, expr_column_vector<minor_m, 2>(minor_m(m))) + get<2, 3>(m));
}

/////////////////////////////////////////////////////////////
//! @brief 行列 * ベクトル
//!        3次元ベクトルは特別に4xN行列との乗算を可能とする
/////////////////////////////////////////////////////////////
template<class EM, class EV>
inline typename boost::enable_if<
    boost::mpl::and_<row_equal_to_c<EM, 4>, dimension_equal_to_c<EV, 3> >,
    vector3<typename deduct2<EM, EV>::value_type> >::type
operator *(matrix_expression<EM> const& m, vector_expression<EV> const& v){
    typedef vector3<typename deduct2<EM, EV>::value_type> result;
    typedef minor_matrix<EM, 3, 3> minor_m;
    return result(expression::dot(expr_row_vector<minor_m, 0>(minor_m(m)), v) + get<3, 0>(m),
                  expression::dot(expr_row_vector<minor_m, 1>(minor_m(m)), v) + get<3, 1>(m),
                  expression::dot(expr_row_vector<minor_m, 2>(minor_m(m)), v) + get<3, 2>(m));
}

/////////////////////////////////////////////////////////////
//! @brief ベクトル * 行列
/////////////////////////////////////////////////////////////
template<class EV, class EM>
inline typename boost::enable_if<
    boost::mpl::and_<column_equal_to_c<EM, 3>, dimension_equal_to_c<EV, 3> >,
    vector3<typename deduct2<EM, EV>::value_type> >::type
operator *(vector_expression<EV> const& v, matrix_expression<EM> const& m){
    typedef vector3<typename deduct2<EM, EV>::value_type> result;
    return result(expression::dot(v, expr_column_vector<EM, 0>(m)),
                  expression::dot(v, expr_column_vector<EM, 1>(m)),
                  expression::dot(v, expr_column_vector<EM, 2>(m)));
}

/////////////////////////////////////////////////////////////
//! @brief 行列 * ベクトル
/////////////////////////////////////////////////////////////
template<class EM, class EV>
inline typename boost::enable_if<
    boost::mpl::and_<row_equal_to_c<EM, 3>, dimension_equal_to_c<EV, 3> >,
    vector3<typename deduct2<EM, EV>::value_type> >::type
operator *(matrix_expression<EM> const& m, vector_expression<EV> const& v){
    typedef vector3<typename deduct2<EM, EV>::value_type> result;
    return result(expression::dot(expr_row_vector<EM, 0>(m), v),
                  expression::dot(expr_row_vector<EM, 1>(m), v),
                  expression::dot(expr_row_vector<EM, 2>(m), v));
}

/////////////////////////////////////////////////////////////
//! @brief ベクトル * 行列
//!        2次元ベクトルは特別にNx3行列との乗算を可能とする
/////////////////////////////////////////////////////////////
template<class EV, class EM>
inline typename boost::enable_if<
    boost::mpl::and_<column_equal_to_c<EM, 3>, dimension_equal_to_c<EV, 2> >,
    vector2<typename deduct2<EM, EV>::value_type> >::type
operator *(vector_expression<EV> const& v, matrix_expression<EM> const& m){
    typedef vector2<typename deduct2<EM, EV>::value_type> result;
    typedef minor_matrix<EM, 2, 2> minor_m;
    return result(nogara::expression::dot(v, expr_column_vector<minor_m, 0>(minor_m(m))) + get<0, 2>(m),
                  nogara::expression::dot(v, expr_column_vector<minor_m, 1>(minor_m(m))) + get<1, 2>(m));
}

/////////////////////////////////////////////////////////////
//! @brief 行列 * ベクトル
//!        2次元ベクトルは特別に3xN行列との乗算を可能とする
/////////////////////////////////////////////////////////////
template<class EM, class EV>
inline typename boost::enable_if<
    boost::mpl::and_<row_equal_to_c<EM, 3>, dimension_equal_to_c<EV, 2> >,
    vector_type<typename deduct2<EM, EV>::value_type, 2> >::type
operator *(matrix_expression<EM> const& m, vector_expression<EV> const& v){
    typedef vector2<typename deduct2<EM, EV>::value_type> result;
    typedef minor_matrix<EM, 2, 2> minor_m;
    return result(expression::dot(expr_row_vector<minor_m, 0>(minor_m(m)), v) + get<2, 0>(m),
                  expression::dot(expr_row_vector<minor_m, 1>(minor_m(m)), v) + get<2, 1>(m));
}


/////////////////////////////////////////////////////////////
//! @brief 行列 * ベクトル
/////////////////////////////////////////////////////////////
template<class EM, class EV>
inline typename boost::lazy_enable_if<
    boost::mpl::and_<column_equal_to_c<EM, 2>, dimension_equal_to_c<EV, 2> >,
    vector_type<typename deduct2<EM, EV>::value_type, 2> >::type
operator *(matrix_expression<EM> const& m, vector_expression<EV> const& v){
    typedef typename vector_type<typename deduct2<EM, EV>::value_type, 2>::type result;
    return result(expression::dot(expr_column_vector<EM, 0>(m), v),
                  expression::dot(expr_column_vector<EM, 1>(m), v));
}

/////////////////////////////////////////////////////////////
//! @brief 行列 * ベクトル
/////////////////////////////////////////////////////////////
template<class EM, class EV>
inline typename boost::enable_if<
    boost::mpl::and_<row_equal_to_c<EM, 2>, dimension_equal_to_c<EV, 2> >,
    vector_type<typename deduct2<EM, EV>::value_type, 2> >::type
operator *(matrix_expression<EM> const& m, vector_expression<EV> const& v){
    typedef vector2<typename deduct2<EM, EV>::value_type> result;
    return result(expression::dot(expr_row_vector<EM, 0>(m), v),
                  expression::dot(expr_row_vector<EM, 1>(m), v));
}

__NOGARA_EXPRESSION_END

#endif
