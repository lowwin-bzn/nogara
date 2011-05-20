#ifndef NOGARA_EXPRESSION_VECTOR_MINOR_HPP
#define NOGARA_EXPRESSION_VECTOR_MINOR_HPP

//////////////////////////////////////////////
//! @file nogara/expression/vector/minor.hpp
//! @brief 一要素を除くベクトルを返すクラス
//////////////////////////////////////////////

#include <boost/mpl/size_t.hpp>
#include <boost/mpl/greater.hpp>
#include <boost/utility/enable_if.hpp>
#include <nogara/expression/vector/unary_expression.hpp>

__NOGARA_EXPRESSION_BEGIN

////////////////////////////////////////////////////////////////
//! @brief Nで指定した要素を除いた(E::Dimension - 1)次元ベクトル
//!        NがEの次元数より大きければコンパイルエラーとなる
//!
//!  -*- example -*-
//! minor_vector<vector3, 0>([1, 2, 3])    = [2, 3]
//! minor_vector<vector4, 1>([1, 2, 3, 4]) = [1, 3, 4]
////////////////////////////////////////////////////////////////

template<class E, std::size_t N>
class minor_vector : public vector_unary_base<E, minor_vector<E, N> >{
    typedef minor_vector<E, N>              self_type;
    typedef vector_unary_base<E, self_type> base_type;

    template<std::size_t X>
    unsigned index(unsigned i, boost::mpl::size_t<X>) const {return (i < X) ? i : i + 1;}
    unsigned index(unsigned i, boost::mpl::size_t<0>) const {return i + 1;}

public:
    typedef expression::vector_tag expression_category;
    typedef typename boost::enable_if<
        boost::mpl::greater<get_dimension<E>, boost::mpl::size_t<N> >,
        boost::mpl::size_t<get_dimension<E>::value - 1> >::type Dimension;

    typename base_type::value_type apply(unsigned i) const {
        return base_type::value()(index(i, boost::mpl::size_t<N>()));
    }

    minor_vector(typename base_type::argment_type e):base_type(e){}
};

///////////////////////////////////////////
//! @brief クラスを生成しやすくする便利関数
///////////////////////////////////////////
template< std::size_t N, class E>
minor_vector<E, N> minor(vector_expression<E> const& e){
    return minor_vector<E, N>(e);
}

__NOGARA_EXPRESSION_END

__NOGARA_BEGIN
using expression::minor_vector;
using expression::minor;

__NOGARA_END

#endif
