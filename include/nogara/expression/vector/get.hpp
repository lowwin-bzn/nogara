#ifndef NOGARA_EXPRESSION_VECTOR_GET_HPP
#define NOGARA_EXPRESSION_VECTOR_GET_HPP

///////////////////////////////////////////////////////
//! @file nogara/expression/vector/vector_to_scalar.hpp
//! @brief ベクトルを演算し、スカラにするクラス
///////////////////////////////////////////////////////

#include <nogara/expression/vector/traits.hpp>

__NOGARA_EXPRESSION_BEGIN

/////////////////////////////////////////////////////////
//! @brief テンプレート引数で指定した位置の要素を返す関数
//! @param N 位置 ベクトルの次元数未満である必要がある
/////////////////////////////////////////////////////////
template<std::size_t N, class E>
inline typename boost::enable_if_c<
    (get_dimension<E>::value > N), typename E::const_reference>::type
get(vector_expression<E> const& e){return e()(N);}

/////////////////////////////////////////////////////////
//! @brief テンプレート引数で指定した位置の要素を返す関数
//! @param N 位置 ベクトルの次元数未満である必要がある
/////////////////////////////////////////////////////////
template<std::size_t N, class E>
inline typename boost::enable_if_c<
    (get_dimension<E>::value > N), typename E::reference>::type
get(vector_expression<E>& e){return e()(N);}

__NOGARA_EXPRESSION_END

__NOGARA_BEGIN
using expression::get;
__NOGARA_END

#endif
