#ifndef NOGARA_EXPRESSION_TRAITS_HPP
#define NOGARA_EXPRESSION_TRAITS_HPP

///////////////////////////////////////////////////////
//! @file nogara/expression/traits.hpp
//! @brief nogaraで提供する線形代数の式オブジェクト特性
///////////////////////////////////////////////////////

#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/type_traits.hpp>
#include <nogara/type_traits/sfinae_check.hpp>
#include <nogara/expression/expression_tag.hpp>
#include <nogara/expression/define.hpp>

__NOGARA_EXPRESSION_BEGIN

///////////////////////////////////////////////////////////////////////////////
//! @brief nogara::expressionのクラスであるかを返すメタ関数
//         nogara::expressionのクラスはexpression_categoryというタグを持つため、
//         タグが存在するか否かでnogara::expressionか判定する
///////////////////////////////////////////////////////////////////////////////
template<class E>
class is_expression : sfinae_check{
    template<class T> static yes_type has_tag(typename T::expression_category*);
    template<class> static no_type has_tag(...);

public:
    static bool const value = (sizeof(yes_type) == sizeof(has_tag<E>(0)));
};

//expression_categoryを持たないクラスが比較対象になっても問題がないように
//no_expression_tagというカテゴリを定義付けるラッパメタ関数の本体
namespace invisible{
template<class E, bool b>
struct tag_traits_impl{
    typedef no_expression_tag type;
};

template<class E>
struct tag_traits_impl<E, true>{
    typedef typename E::expression_category type;
};

}

///////////////////////////////////////////////////////////////////////////////////
//! @brief expression_categoryを持たないクラスが比較対象になっても問題がないように
//         no_expression_tagというカテゴリを定義付けるラッパメタ関数
///////////////////////////////////////////////////////////////////////////////////
template<class E>
struct expression_tag_traits{
    typedef typename invisible::tag_traits_impl<E, is_expression<E>::value>::type type;
};

/////////////////////////////////////////////////
//! @brief 式Eの種類がtagと等しいかを返すメタ関数
/////////////////////////////////////////////////
template<class E, class tag>
struct same_expr_tag : boost::is_same<
    typename expression_tag_traits<E>::type, tag>{};

//is_scalarで使用するための前方宣言
template<class E, std::size_t N>
struct dimension_equal_to_c;

/////////////////////////////////////////////
//! @brief Eがスカラであるかを返すメタ関数
/////////////////////////////////////////////
template<class E> struct is_scalar : public boost::mpl::or_<
    dimension_equal_to_c<E, 1>, boost::is_arithmetic<E> >{};

////////////////////////////////////////////////////
//! @brief 式Eがクォータニオンであるかを返すメタ関数
////////////////////////////////////////////////////
template<class E> struct is_quaternion : public same_expr_tag<E, quaternion_tag>{};

//////////////////////////////////////////////
//! @brief 式Eがベクトルであるかを返すメタ関数
//////////////////////////////////////////////
template<class E>
struct is_vector : public boost::is_convertible<
    typename expression_tag_traits<E>::type, vector_tag>{};

//////////////////////////////////////////
//! @brief 式Eが行列であるかを返すメタ関数
//////////////////////////////////////////
template<class E> struct is_matrix : public same_expr_tag<E, matrix_tag>{};

///////////////////////////////////////////////////////
//! @brief 行列の行サイズをメタ整数クラスで返すメタ関数
///////////////////////////////////////////////////////
template<class E> struct get_row : public E::Row{};

///////////////////////////////////////////////////////
//! @brief 行列の列サイズをメタ整数クラスで返すメタ関数
///////////////////////////////////////////////////////
template<class E> struct get_column : public E::Column{};

//////////////////////////////////////////////////////////
//! @brief ベクトルの次元数ををメタ整数クラスで返すメタ関数
//////////////////////////////////////////////////////////
template<class E> struct get_dimension : public E::Dimension{};

//////////////////////////////////////////////////////
//! @brief 両辺がクォータニオンであるかを返すメタ関数
//////////////////////////////////////////////////////
template<class E1, class E2>
struct quaternion_same : public boost::mpl::and_<is_quaternion<E1>, is_quaternion<E2> >{};

//////////////////////////////////////////////////////
//! @brief referenceが参照であるかを返すメタ関数
//////////////////////////////////////////////////////
template<class E>
struct result_is_reference : public boost::mpl::and_<
    boost::is_reference<typename E::reference>,
    boost::mpl::not_<
        boost::is_const<typename boost::remove_reference<typename E::reference>::type> > >{};


__NOGARA_EXPRESSION_END

#endif
