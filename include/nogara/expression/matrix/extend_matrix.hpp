#ifndef NOGARA_EXPRESSION_EXTEND_MATRIX_HPP
#define NOGARA_EXPRESSION_EXTEND_MATRIX_HPP

////////////////////////////////////////////////////
//! @file nogara/expression/matrix/extend_matrix.hpp
//! @brief 拡張行列
////////////////////////////////////////////////////

#include <nogara/expression/matrix/unary_expression.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/less_equal.hpp>
#include <boost/utility/enable_if.hpp>
#include <nogara/type_traits/value_type_traits.hpp>

__NOGARA_EXPRESSION_BEGIN

//////////////////////////////////////////////////////////
//! @brief 元の行列より行をR個、列をC個拡張するクラス
//         なお、operator()に渡すxとyが等しい時は、1を返す
//////////////////////////////////////////////////////////
template<class E, std::size_t R, std::size_t C>
class extend_matrix : public matrix_unary_base<E, extend_matrix<E, R, C> >{
    typedef extend_matrix<E, R, C>          self_type;
    typedef matrix_unary_base<E, self_type> base_type;

public:
    typedef boost::mpl::size_t<R> Row;
    typedef boost::mpl::size_t<C> Column;

    typedef typename boost::lazy_enable_if<
        boost::mpl::and_<boost::mpl::less_equal<get_row<E>, Row>,
                         boost::mpl::less_equal<get_column<E>, Column > >,
        get_value_type<base_type> >::type  value_type;


    value_type apply(unsigned x, unsigned y) const {
        return (x < get_row<E>::value && y < get_column<E>::value) ? base_type::value()(x, y) :
                (x == y) ? value_type(1) : value_type();
    }

    extend_matrix(typename base_type::argment_type e):base_type(e){}
};

///////////////////////////////////////////
//! @brief クラスを生成しやすくする便利関数
///////////////////////////////////////////
template<std::size_t R, std::size_t C, class E>
inline extend_matrix<E, R, C> extend(matrix_expression<E> const& e){
    return extend_matrix<E, R, C >(e);
}

__NOGARA_EXPRESSION_END

__NOGARA_BEGIN
using expression::extend;
__NOGARA_END


#endif
