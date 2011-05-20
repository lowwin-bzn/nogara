#ifndef NOGARA_EXPRESSION_UNARY_MATRIX_HPP
#define NOGARA_EXPRESSION_UNARY_MATRIX_HPP

///////////////////////////////////////////////////////
//! @file nogara/expression/matrix/unary_expression.hpp
//! @brief 単項演算クラス
///////////////////////////////////////////////////////

#include <nogara/expression/expression.hpp>
#include <nogara/expression/matrix/traits.hpp>

__NOGARA_EXPRESSION_BEGIN

/////////////////////////////////////////////////////////////////
//! @brief 行列の単項演算の基礎となるクラス
//!        単項演算式は基本matrix_binary_baseを継承する
//!        継承先クラスはT apply(unsigned, unsigned) const
//!        というメンバメソッドを持つ必要がある
/////////////////////////////////////////////////////////////////

template<class E, class Derived>
struct matrix_unary_base : public matrix_expression<Derived>{
    typedef typename E::value_type      value_type;
    typedef value_type                  reference;
    typedef value_type                  const_reference;
    typedef matrix_expression<E> const& argment_type;

    using matrix_expression<Derived>::operator();
    value_type operator()(std::size_t x, std::size_t y) const {
        return operator()().apply(x, y);
    }

protected:
    matrix_unary_base(argment_type e):value(e){}

protected:
    argment_type value;

};

////////////////////////////////////////////////
//! @brief 単項演算クラス
//!        第3テンプレート引数は
//!        static T apply(U const&, V const&)
//!        というクラスメソッドを持つ必要がある
////////////////////////////////////////////////
template<class E, class F>
class matrix_unary : public matrix_unary_base<E, matrix_unary<E, F> >{
    typedef matrix_unary<E, F>              self_type;
    typedef matrix_unary_base<E, self_type> base_type;

public:
    typedef get_row<E>    Row;
    typedef get_column<E> Column;

    typename base_type::value_type apply(unsigned x, unsigned y) const {
        return F::apply(base_type::value()(x, y));
    }

    matrix_unary(typename base_type::argment_type e):base_type(e){}
};

__NOGARA_EXPRESSION_END

#endif
