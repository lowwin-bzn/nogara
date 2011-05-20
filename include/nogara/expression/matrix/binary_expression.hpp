#ifndef NOGARA_EXPRESSION_BINARY_MATRIX_HPP
#define NOGARA_EXPRESSION_BINARY_MATRIX_HPP

/////////////////////////////////////////////////////////
//! @file nogara/expression/matrix/binary_expression.hpp
//! @brief 二項演算クラス
////////////////////////////////////////////////////////

#include <nogara/type_traits/deduct.hpp>
#include <nogara/expression/expression.hpp>
#include <nogara/expression/matrix/traits.hpp>

//////////////////////////////////////////////////////////
//! @brief 行列の二項演算の基礎となるクラス
//!        二項演算式は基本matrix_binary_baseを継承する
//!        継承先クラスはT apply(unsigned, unsigned) const
//!        というメンバメソッドを持つ必要がある
//////////////////////////////////////////////////////////

__NOGARA_EXPRESSION_BEGIN

template<class E1, class E2, class Derived>
struct matrix_binary_base : public matrix_expression<Derived>{
    typedef typename deduct2<E1, E2>::value_type value_type;
    typedef value_type reference;
    typedef value_type const_reference;

    typedef matrix_expression<E1> const& argment1_type;
    typedef matrix_expression<E2> const& argment2_type;

    using matrix_expression<Derived>::operator();
    value_type operator()(unsigned x, unsigned y) const {
        return operator()().apply(x, y);
    }

protected:
    matrix_binary_base(argment1_type e1, argment2_type e2):left(e1), right(e2){}
    
protected:
    argment1_type left;
    argment2_type right;

};

////////////////////////////////////////////////
//! @brief 二項演算クラス
//!        第3テンプレート引数は
//!        static T apply(U const&, V const&)
//!        というクラスメソッドを持つ必要がある
////////////////////////////////////////////////

template<class E1, class E2, class F>
class matrix_binary : public matrix_binary_base<E1, E2, matrix_binary<E1, E2, F> >{
    typedef matrix_binary<
        E1, E2, typename boost::enable_if<same_row_column<E1, E2>, F>::type> self_type;
    typedef matrix_binary_base<E1, E2, self_type> base_type;

public:
    typedef get_row<E1>                       Row;
    typedef get_column<E2>                    Column;
                
    typename base_type::value_type apply(unsigned x, unsigned y) const {
        return F::apply(base_type::left()(x, y), base_type::right()(x, y));
    }

    matrix_binary(typename base_type::argment1_type e1,
                  typename base_type::argment2_type e2):base_type(e1, e2){}
};

__NOGARA_EXPRESSION_END

#endif
