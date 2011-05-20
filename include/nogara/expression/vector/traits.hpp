#ifndef NOGARA_EXPRESSION_VECTOR_TRAITS_HPP
#define NOGARA_EXPRESSION_VECTOR_TRAITS_HPP

/////////////////////////////////////////////
//! @file nogara/expression/vector/traits.hpp
//! @brief ベクトル型の特性メタ関数群
/////////////////////////////////////////////
#include <nogara/expression/traits.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits.hpp>
#include <boost/utility/enable_if.hpp>

__NOGARA_EXPRESSION_BEGIN

/////////////////////////////////////////////////////////////////
//! @brief ベクトルの次元数がメタ整数クラスと同じかを返すメタ関数
/////////////////////////////////////////////////////////////////
template<class E, class N>
struct dimension_equal_to : public boost::mpl::if_<
    is_vector<E>, boost::mpl::equal_to<get_dimension<E>, N>, boost::false_type>::type{};

///////////////////////////////////////////////////////////////
//! @brief ベクトルの次元数がリテラル整数と同じかを返すメタ関数
///////////////////////////////////////////////////////////////
template<class E, std::size_t N>
struct dimension_equal_to_c : public dimension_equal_to<E, boost::mpl::size_t<N> >{};

///////////////////////////////////////////////////////////////
//! @brief ベクトルであればベクトルとして、
//!        クォータニオンであればクォータニオンとして扱うための
//!        種類推論メタ関数
///////////////////////////////////////////////////////////////
namespace invisible{
template<class E1, class E2>
struct vector_tag_impl{
    typedef typename boost::mpl::eval_if<
        boost::mpl::and_<same_expr_tag<E1, vector_tag>, same_expr_tag<E2, vector_tag> >,
        boost::mpl::identity<vector_tag>,
        boost::mpl::if_<same_expr_tag<E1, vector_tag>,
                 typename E2::expression_category,
                 typename E1::expression_category> >::type type;
};
}

///////////////////////////////////////////////////
//! @brief ベクトルの次元数が等しいかを返すメタ関数
///////////////////////////////////////////////////
template<class E1, class E2>
struct same_dimension : public boost::mpl::if_<
    is_vector<E1>, dimension_equal_to<E2, get_dimension<E1> >, boost::false_type>::type{};

///////////////////////////////////////////////////////////////////////////////////
//! @brief ベクトルの次元数が等しく、指定した数値リテラルとも等しいかを返すメタ関数
///////////////////////////////////////////////////////////////////////////////////
template<class E1, class E2, std::size_t N>
struct same_dimension_equal_to : public boost::mpl::and_<
    same_dimension<E1, E2>, dimension_equal_to_c<E1, N> >{};

/////////////////////////////////////////////////////////
//! @brief ベクトルの次元数が等しければその次元数を返し、
//!        違っていればコンパイルエラーとするメタ関数
/////////////////////////////////////////////////////////
template<class E1, class E2>
struct get_same_dimension : public boost::enable_if<
    same_dimension<E1, E2>, get_dimension<E1> >::type{};


//////////////////////////////////////////////////////////////////////////////////////
//! @brief ベクトルの次元数が等しければベクトルの種類(ベクトル, クォータニオン)を返し、
//!        違っていればコンパイルエラーとするメタ関数
//////////////////////////////////////////////////////////////////////////////////////
template<class E1, class E2 = E1>
struct vector_expression_tag{
    typedef typename boost::lazy_enable_if<
        same_dimension<E1, E2>, invisible::vector_tag_impl<E1, E2> >::type type;
};

///////////////////////////////////////////
//! @brief 次元数と等しいベクトル型を返す
//!        後に特殊化する
///////////////////////////////////////////
template<class T, std::size_t N> struct vector_type{};

__NOGARA_EXPRESSION_END

#endif 
