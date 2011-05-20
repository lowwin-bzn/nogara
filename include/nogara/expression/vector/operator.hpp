#ifndef NOGARA_EXPRESSION_VECTOR_OPERATOR_HPP
#define NOGARA_EXPRESSION_VECTOR_OPERATOR_HPP

///////////////////////////////////////////////
//! @file nogara/expression/vector/operator.hpp
//! @brief ベクトルの演算子オーバーロード
///////////////////////////////////////////////

#include <limits>

#include <nogara/expression/vector/binary_expression.hpp>
#include <nogara/expression/vector/unary_expression.hpp>
#include <nogara/expression/vector/vector_and_scalar.hpp>
#include <nogara/expression/vector/function.hpp>

__NOGARA_EXPRESSION_BEGIN

/////////////////////////////
//! @brief ベクトル同士の加算
/////////////////////////////
template<class E1, class E2>
inline vector_binary<E1, E2, scalar_add<E1, E2> >
operator +(vector_expression<E1> const& e1, vector_expression<E2> const& e2){
    return vector_binary<E1, E2, scalar_add<E1, E2> >(e1, e2);
}

/////////////////////////////
//! @brief ベクトル同士の減算
/////////////////////////////
template<class E1, class E2>
inline vector_binary<E1, E2, scalar_sub<E1, E2> >
operator -(vector_expression<E1> const& e1, vector_expression<E2> const& e2){
    return vector_binary<E1, E2, scalar_sub<E1, E2> >(e1, e2);
}

///////////////////////////
//! @brief ベクトルの正符号
///////////////////////////
template<class E>
inline vector_unary<E, scalar_identity<E> >
operator +(vector_expression<E> const& val){
    return vector_unary<E, scalar_identity<E> >(val);
}

///////////////////////////
//! @brief ベクトルの負符号
///////////////////////////
template<class E>
inline vector_unary<E, scalar_negate<E> >
operator -(vector_expression<E> const& val){
    return vector_unary<E, scalar_negate<E> >(val);
}

/////////////////////////////////
//! @brief ベクトルとスカラの乗算
/////////////////////////////////
template<class E, class T>
inline typename boost::enable_if<
    is_scalar<T>, scalar_and_vector<T, E, scalar_mul<T, E> > >::type
operator *(T const& e1, vector_expression<E> const& e2){
    return scalar_and_vector<T, E, scalar_mul<T, E> >(e1, e2);
}

/////////////////////////////////
//! @brief ベクトルとスカラの乗算
/////////////////////////////////
template<class E, class T>
inline typename boost::enable_if<
    is_scalar<T>, vector_and_scalar<E, T, scalar_mul<E, T> > >::type
operator *(vector_expression<E> const& e1, T const& e2){
    return vector_and_scalar<E, T, scalar_mul<E, T> >(e1, e2);
}

/////////////////////////////////
//! @brief ベクトルとスカラの除算
/////////////////////////////////
template<class E, class T>
inline typename boost::enable_if<
    is_scalar<T>, vector_and_scalar<E, T, scalar_div<E, T> > >::type
operator /(vector_expression<E> const& e1, T const& e2){
    return vector_and_scalar<E, T, scalar_div<E, T> >(e1, e2);
}

///////////////////////////////////////////////////////
//! @brief 等式 ベクトルの次元数が合っていなければfalse
///////////////////////////////////////////////////////
template<class E1, class E2>
inline typename boost::disable_if<same_dimension<E1, E2>, bool>::type
operator ==(vector_expression<E1> const& e1, vector_expression<E2> const& e2){
    return false;
}

//////////////////////////////////////////////////////////
//! @brief 等式 どちらかのデータ型が浮動小数の場合は
//!        要素同士を引いた値の絶対値がepsilon以下かで判断
//////////////////////////////////////////////////////////
template<class E1, class E2>
inline typename boost::enable_if<same_dimension<E1, E2>, bool>::type
operator ==(vector_expression<E1> const& e1, vector_expression<E2> const& e2){
    typedef typename deduct2<E1, E2>::value_type value_type;
    return std::equal(e1().begin(), e1().end(), e2().begin(), equal_test<value_type>());
}

/////////////////
//! @brief 不等号
/////////////////
template<class E1, class E2>
bool operator !=(vector_expression<E1> const& e1, vector_expression<E2> const& e2){
    return !(e1 == e2);
}

__NOGARA_EXPRESSION_END

#endif
