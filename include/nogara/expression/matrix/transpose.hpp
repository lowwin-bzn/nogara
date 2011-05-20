#ifndef NOGARA_EXPRESSION_TRANSPOSE_MATRIX_HPP
#define NOGARA_EXPRESSION_TRANSPOSE_MATRIX_HPP

///////////////////////////////////////////////////////
//! @file nogara/expression/matrix/transpose.hpp
//! @brief 転置行列
///////////////////////////////////////////////////////

#include <nogara/expression/matrix/unary_expression.hpp>

__NOGARA_EXPRESSION_BEGIN
/////////////////////////
//! @brief 転置行列クラス
/////////////////////////
template<class E>
class transpose_matrix : public matrix_unary_base<E, transpose_matrix<E> >{
    typedef transpose_matrix<E>             self_type;
    typedef matrix_unary_base<E, self_type> base_type;

public:
    typedef get_column<E> Row;
    typedef get_row<E>    Column;

    typename base_type::value_type apply(unsigned x, unsigned y) const {
        return base_type::value()(y, x);
    }

    transpose_matrix(typename base_type::argment_type e):base_type(e){}
};

__NOGARA_EXPRESSION_END


#endif
