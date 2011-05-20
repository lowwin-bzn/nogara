#ifndef NOGARA_EXPRESSION_REPEAT_MATRIX_HPP
#define NOGARA_EXPRESSION_REPEAT_MATRIX_HPP

////////////////////////////////////////////////////
//! @file nogara/expression/matrix/repeat.hpp
//! @brief 繰り返し行列
////////////////////////////////////////////////////

#include <cassert>
#include <boost/mpl/size_t.hpp>
#include <nogara/expression/matrix/unary_expression.hpp>

__NOGARA_EXPRESSION_BEGIN

//////////////////////////////////////////////////////////////////////////////////
//! @brief 式Eの行をR回、列をC回繰り返す行列
//         行列のサイズは(E::Row + E::Row * R) * (E::Column + E::Column * R)となる
//
// -*- example -*-
// repeat_matrix<matrix33, 2, 0>([1, 2, 3]     [1, 2, 3, 1, 2, 3, 1, 2, 3]
//                               [4, 5, 6]  =  [4, 5, 6, 4, 5, 6, 4, 5, 6]
//                               [7, 8, 9])    [7, 8, 9, 7, 8, 9, 7, 8, 9]
//
// repeat_matrix<matrix22, 2, 1>([1, 2]     =  [1, 2, 1, 2, 1, 2]
//                               [3, 4])       [3, 4, 3, 4, 3, 4]
//                                             [1, 2, 1, 2, 1, 2]
//                                             [3, 4, 3, 4, 3, 4]
//////////////////////////////////////////////////////////////////////////////////
template<class E, std::size_t R, std::size_t C>
class repeat_matrix : public matrix_unary_base<E, repeat_matrix<E, R, C> >{
    typedef repeat_matrix<E, R, C>        self_type;
    typedef matrix_unary_base<E, self_type> base_type;

public:
    typedef boost::mpl::size_t<get_row<E>::value    + get_row<E>::value    * R> Row;
    typedef boost::mpl::size_t<get_column<E>::value + get_column<E>::value * C> Column;
    //typedef typename E::Weight Weight;

    typename base_type::value_type apply(std::size_t x, std::size_t y) const {
        //assert(x < get_row<self_type>::value && y < get_column<self_type>::value);
        if(x >= get_row<E>::value)    {x %= get_row<E>::value;}
        if(y >= get_column<E>::value) {y %= get_column<E>::value;}
        return base_type::value()(x, y);
    }

    repeat_matrix(typename base_type::argment_type e):base_type(e){}
};


///////////////////////////////////////////////////////////////////////////
//! @brief クラスを生成しやすくする便利関数
//
// -*- example -*-
// repeat<2, 0>([1, 2, 3]     [1, 2, 3, 1, 2, 3, 1, 2, 3]
//              [4, 5, 6]  =  [4, 5, 6, 4, 5, 6, 4, 5, 6]
//              [7, 8, 9])    [7, 8, 9, 7, 8, 9, 7, 8, 9]
//
// repeat<2, 1>([1, 2]     =  [1, 2, 1, 2, 1, 2]
//              [3, 4])       [3, 4, 3, 4, 3, 4]
//                            [1, 2, 1, 2, 1, 2]
//                            [3, 4, 3, 4, 3, 4]
///////////////////////////////////////////////////////////////////////////
template<std::size_t x, std::size_t y, class E>
inline repeat_matrix<E, x, y> repeat(matrix_expression<E> const& e){
    return repeat_matrix<E, x, y>(e);
}

__NOGARA_EXPRESSION_END

__NOGARA_BEGIN
using expression::repeat_matrix;
using expression::repeat;
__NOGARA_END

#endif
