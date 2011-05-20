#ifndef NOGARA_EXPRESSION_MATRIX_SCALAR_HPP
#define NOGARA_EXPRESSION_MATRIX_SCALAR_HPP

////////////////////////////////////////////////////////
//! @file nogara/expression/matrix/matrix_and_scalar.hpp
//! @brief 行列とスカラの演算を行うクラス
////////////////////////////////////////////////////////

#include <nogara/expression/expression.hpp>
#include <nogara/expression/vector/vector1.hpp>
#include <nogara/expression/scalar/function.hpp>
#include <nogara/expression/matrix/traits.hpp>
#include <nogara/type_traits/deduct.hpp>

__NOGARA_EXPRESSION_BEGIN

////////////////////////////////////////////////////////
//! @brief 行列とスカラの演算の基礎となるクラス
//!        演算式は基本vector_and_scalar_bbaseを継承する
//!        継承先クラスはT apply(unsigned) const
//!        というメンバメソッドを持つ必要がある
////////////////////////////////////////////////////////
template<class E, class T, class Derived>
struct matrix_and_scalar_base : public matrix_expression<Derived>{
    typedef typename deduct2<E, T>::value_type value_type;
    typedef matrix_expression<E> const&        expression_argment;
    typedef vector1<T>                         scalar_argment;
    typedef get_row<E>                         Row;
    typedef get_column<E>                      Column;

    using matrix_expression<Derived>::operator();
    value_type operator()(std::size_t x, std::size_t y) const {
        return operator()().apply(x, y);
    }    

    matrix_and_scalar_base(expression_argment e, scalar_argment s):expr(e), scalar(s){}
    
protected:
    expression_argment expr;
    scalar_argment     scalar;
};


/////////////////////////////////////////////////////////
//! @brief 左辺が行列、右辺がスカラの演算を行うクラス
/////////////////////////////////////////////////////////
template<class E, class T, class F>
class matrix_and_scalar : public matrix_and_scalar_base<E, T, matrix_and_scalar<E, T, F> >{
    typedef matrix_and_scalar<E, T, F>              self_type;
    typedef matrix_and_scalar_base<E, T, self_type> base_type;
public:
    typename base_type::value_type apply(std::size_t x, std::size_t y) const {
        return F::apply(base_type::expr()(x, y), base_type::scalar());
    }

    matrix_and_scalar(typename base_type::expression_argment e,
                      typename base_type::scalar_argment s):base_type(e, s){}
};

/////////////////////////////////////////////////////////
//! @brief 左辺がスカラ、右辺が行列の演算を行うクラス
/////////////////////////////////////////////////////////
template<class T, class E, class F>
class scalar_and_matrix : public matrix_and_scalar_base<E, T, scalar_and_matrix<T, E, F> >{
    typedef scalar_and_matrix<T, E, F>              self_type;
    typedef matrix_and_scalar_base<E, T, self_type> base_type;
public:
    typename base_type::value_type apply(std::size_t x, std::size_t y) const {
        return F::apply(base_type::scalar(), base_type::expr()(x, y));
    }

    scalar_and_matrix(typename base_type::scalar_argment s,
                      typename base_type::expression_argment e):base_type(e, s){}
};

__NOGARA_EXPRESSION_END

#endif
