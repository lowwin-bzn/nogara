#ifndef NOGARA_EXPRESSION_VECTOR_EXTEND_HPP
#define NOGARA_EXPRESSION_VECTOR_EXTEND_HPP

////////////////////////////////////////////////////
//! @file nogara/expression/vector/extend.hpp
//! @brief 拡張ベクトル
////////////////////////////////////////////////////

#include <nogara/expression/vector/unary_expression.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/less_equal.hpp>
#include <boost/mpl/utility/enable_if.hpp>

__NOGARA_EXPRESSION_BEGIN

//////////////////////////////////////////////////////////
//! @brief 元のベクトルよりN次元に拡張するクラス
//!        拡張領域は0を返す
//////////////////////////////////////////////////////////
template<class E, std::size_t N>
class extend_matrix : public matrix_unary_base<E, extend_vector<E, N> >{
    typedef extend_vector<E, N>             self_type;
    typedef matrix_unary_base<E, self_type> base_type;

public:
    typedef boost::mpl::size_t<N> Dimension;

    typedef typename boost::enable_if<
        boost::mpl::less_equal<get_Dimension<E>, Dimension>,
        typename base_type::value_type>::type  value_type;


    value_type apply(unsigned i) const {
        return (i < get_dimension<E>::value) ? base_type::value()(i) : T();
    }

    extend_vector(typename base_type::argment_type e):base_type(e){}
};

///////////////////////////////////////////
//! @brief クラスを生成しやすくする便利関数
///////////////////////////////////////////
template<std::size_t N, class E>
inline extend_matrix<E, N> extend(matrix_expression<E> const& e){
    return extend_matrix<E, N>(e);
}

__NOGARA_EXPRESSION_END

__NOGARA_BEGIN
using expression::extend;
__NOGARA_END




#endif
