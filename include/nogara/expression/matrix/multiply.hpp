#ifndef NOGARA_EXPRESSION_MUL_MATRIX_HPP
#define NOGARA_EXPRESSION_MUL_MATRIX_HPP

//////////////////////////////////////////////////
//! @file  nogara/expression/matrix/multiply.hpp
//! @brief 行列同士の乗算クラス
//////////////////////////////////////////////////

#include <boost/mpl/equal_to.hpp>
#include <boost/utility/enable_if.hpp>
#include <nogara/expression/traits.hpp>
#include <nogara/expression/matrix/binary_expression.hpp>

__NOGARA_EXPRESSION_BEGIN

///////////////////////////////////////////////////////
//! @brief 行列同士の乗算クラス
//         E1の列とE2の行サイズが等しくなくてはならない
///////////////////////////////////////////////////////
template<class E1, class E2>
class mul_matrix : public matrix_binary_base<E1, E2, mul_matrix<E1, E2> >{
    typedef typename boost::enable_if<
        boost::mpl::equal_to<get_column<E1>, get_row<E2> >,
        mul_matrix<E1, E2> >::type                self_type;
    typedef matrix_binary_base<E1, E2, self_type> base_type;

public:
    typedef get_row<E1>    Row;
    typedef get_column<E2> Column;
    //未実装
    /*
    typedef boost::mpl::plus<boost::mpl::plus<typename E1::Weight, typename E2::Weight>,
                      boost::mpl::size_t<2> > Weight;
    */

    typename base_type::value_type apply(unsigned x, unsigned y) const {
        typename base_type::value_type result = base_type::left()(x, 0) * base_type::right()(0, y);
        for(unsigned i = 1; i < get_column<E1>::value; ++i){
            result += base_type::left()(x, i) * base_type::right()(i, y);
        }
        return result;
    }

    mul_matrix(typename base_type::argment1_type e1,
               typename base_type::argment2_type e2):base_type(e1, e2){}
};

__NOGARA_EXPRESSION_END

#endif
