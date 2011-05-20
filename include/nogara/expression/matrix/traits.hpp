#ifndef NOGARA_EXPRESSION_MATRIX_TRAITS_HPP
#define NOGARA_EXPRESSION_MATRIX_TRAITS_HPP

/////////////////////////////////////////////
//! @file nogara/expression/matrix/traits.hpp
//! @brief 行列の特性メタ関数群
/////////////////////////////////////////////

#include <nogara/expression/traits.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/greater_equal.hpp>

__NOGARA_EXPRESSION_BEGIN

/////////////////////////////////////////////////////////
//! @brief 行列の行サイズがメタ整数クラスと等しいかを返す
/////////////////////////////////////////////////////////
template<class E, class N>
struct row_equal_to : public boost::mpl::if_<
    is_matrix<E>, boost::mpl::equal_to<get_row<E>, N>, boost::false_type>::type{};

///////////////////////////////////////////////////////
//! @brief 行列の行サイズがリテラル整数と等しいかを返す
///////////////////////////////////////////////////////
template<class E, std::size_t N>
struct row_equal_to_c : row_equal_to<E, boost::mpl::size_t<N> >{};

/////////////////////////////////////////////////////////
//! @brief 行列の列サイズがメタ整数クラスと等しいかを返す
/////////////////////////////////////////////////////////
template<class E, class N>
struct column_equal_to : public boost::mpl::if_<
    is_matrix<E>, boost::mpl::equal_to<get_column<E>, N>, boost::false_type>::type{};

///////////////////////////////////////////////////////
//! @brief 行列の列サイズが整数リテラルと等しいかを返す
///////////////////////////////////////////////////////
template<class E, std::size_t N>
struct column_equal_to_c : public column_equal_to<E, boost::mpl::size_t<N> >{};

/////////////////////////////////////////////////////////////
//! @brief 行列の行、列サイズがメタ整数クラスと等しいかを返す
/////////////////////////////////////////////////////////////
template<class E, class R, class C>
struct matrix_equal_to : public boost::mpl::and_<row_equal_to<E, R>, column_equal_to<E, C> >{};

///////////////////////////////////////////////////////////
//! @brief 行列の行、列サイズがリテラル整数と等しいかを返す
///////////////////////////////////////////////////////////
template<class E, std::size_t R, std::size_t C>
struct matrix_equal_to_c : public boost::mpl::and_<row_equal_to_c<E, R>, column_equal_to_c<E, C> >{};

//////////////////////////////////////////////
//! @brief 式Eが正方行列であるかを返すメタ関数
//////////////////////////////////////////////
template<class E>
struct is_square_matrix : public boost::mpl::equal_to<get_row<E>, get_column<E> >{};

/////////////////////////////////////////////////////////////////////////
//! @brief 式Eが正方行列かつメタ整数クラスNと等しい大きさかを返すメタ関数
/////////////////////////////////////////////////////////////////////////
template<class E, class N>
struct square_equal_to : public boost::mpl::and_<is_square_matrix<E>, boost::mpl::equal_to<get_row<E>, N> >{};

////////////////////////////////////////////////////////////////////////
//! @breif 式Eが正方行列かつリテラル整数Nと等しい大きさかを返すメタ関数
///////////////////////////////////////////////////////////////////////
template<class E, std::size_t N>
struct square_equal_to_c : public square_equal_to<E, boost::mpl::size_t<N> >{};

template<class E, class N>
struct over_row : public boost::mpl::greater_equal<get_row<E>, N>{};

template<class E, std::size_t N>
struct over_row_c : public over_row<E, boost::mpl::size_t<N> >{};

template<class E, class N>
struct over_column : public boost::mpl::greater_equal<get_column<E>, N>{};

template<class E, std::size_t N>
struct over_column_c : public over_column<E, boost::mpl::size_t<N> >{};

template<class E, class R, class C>
struct matrix_over_size : public boost::mpl::and_<over_row<E, R>, over_column<E, C> >{};

template<class E, std::size_t R, std::size_t C>
struct matrix_over_size_c : public boost::mpl::and_<over_row_c<E, R>, over_column_c<E, C> >{};


/////////////////////////////////////////////////
//! @brief 両辺の行サイズが等しいかを返すメタ関数
/////////////////////////////////////////////////
template<class E1, class E2>
struct same_row : public boost::mpl::if_<
    is_matrix<E1>, row_equal_to<E2, get_row<E1> >, boost::false_type>::type{};

//////////////////////////////////////////////////////////////////////////
//! @brief 両辺の行サイズが等しく、メタ整数クラスNと等しいかを返すメタ関数
//////////////////////////////////////////////////////////////////////////
template<class E1, class E2, class N>
struct same_row_equal_to : public boost::mpl::and_<same_row<E1, E2>, row_equal_to<E1, N> >{};

///////////////////////////////////////////////////////////////////////
//! @brief 両辺の行サイズが等しく、リテラル整数と等しいかを返すメタ関数
///////////////////////////////////////////////////////////////////////
template<class E1, class E2, std::size_t N>
struct same_row_equal_to_c : public boost::mpl::and_<same_row<E1, E2>, row_equal_to_c<E1, N> >{};

/////////////////////////////////////////////////
//! @brief 両辺の列サイズが等しいかを返すメタ関数
/////////////////////////////////////////////////
template<class E1, class E2>
struct same_column : public boost::mpl::if_<
    is_matrix<E1>, column_equal_to<E2, get_column<E1> >, boost::false_type>::type{};

//////////////////////////////////////////////////////////////////////////
//! @brief 両辺の列サイズが等しく、メタ整数クラスNと等しいかを返すメタ関数
//////////////////////////////////////////////////////////////////////////
template<class E1, class E2, class N>
struct same_column_equal_to : public boost::mpl::and_<
    same_column<E1, E2>, column_equal_to<E1, N> >{};

////////////////////////////////////////////////////////////////////////
//! @brief 両辺の列サイズが等しく、リテラル整数Nと等しいかを返すメタ関数
////////////////////////////////////////////////////////////////////////
template<class E1, class E2, std::size_t N>
struct same_column_equal_to_c : public boost::mpl::and_<
    same_column<E1, E2>, column_equal_to_c<E1, N> >{};

/////////////////////////////////////////////////////
//! @brief 両辺の行、列サイズが等しいかを返すメタ関数
/////////////////////////////////////////////////////
template<class E1, class E2>
struct same_row_column : public boost::mpl::and_<same_row<E1, E2>, same_column<E1, E2> >{};

/////////////////////////////////////////////////////////////////////////////////
//! @brief 両辺の行、列サイズが等しく、メタ数値クラスR, Cと等しいかを返すメタ関数
/////////////////////////////////////////////////////////////////////////////////
template<class E1, class E2, class R, class C>
struct same_row_column_equal_to : public boost::mpl::and_<
    same_row_column<E1, E2>, row_equal_to<E1, R>, column_equal_to<E2, C> >{};

///////////////////////////////////////////////////////////////////////////////
//! @brief 両辺の行、列サイズが等しく、リテラル数値R, Cと等しいかを返すメタ関数
///////////////////////////////////////////////////////////////////////////////
template<class E1, class E2, std::size_t R, std::size_t C>
struct same_row_column_equal_to_c : public boost::mpl::and_<
    same_row_column<E1, E2>, row_equal_to_c<E1, R>, column_equal_to_c<E2, C> >{};

__NOGARA_EXPRESSION_END

#endif
