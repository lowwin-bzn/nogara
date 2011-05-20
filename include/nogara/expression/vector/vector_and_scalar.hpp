#ifndef NOGARA_EXPRESSION_VECTOR_AND_SCALAR_HPP
#define NOGARA_EXPRESSION_VECTOR_AND_SCALAR_HPP

////////////////////////////////////////////////////////
//! @file nogara/expression/vector/vector_and_scalar.hpp
//! @brief ベクトルとスカラの演算を行うクラス
////////////////////////////////////////////////////////

#include <nogara/expression/expression.hpp>
#include <nogara/expression/vector/traits.hpp>
#include <nogara/type_traits/deduct.hpp>

__NOGARA_EXPRESSION_BEGIN

////////////////////////////////////////////////////////
//! @brief ベクトルとスカラの演算の基礎となるクラス
//!        演算式は基本vector_and_scalar_bbaseを継承する
//!        継承先クラスはT apply(unsigned) const
//!        というメンバメソッドを持つ必要がある
////////////////////////////////////////////////////////

template<class E, class T, class Derived>
struct vector_and_scalar_base : public vector_expression<Derived>{
    typedef typename deduct2<E, T>::value_type value_type;
    typedef value_type reference;
    typedef value_type const_reference;
    typedef typename vector_expression_tag<E>::type  expression_category;

    typedef vector_iterator<E>                       iterator;
    typedef iterator                                 const_iterator;
    typedef std::reverse_iterator<iterator>          reverse_iterator;
    typedef std::reverse_iterator<const_iterator>    const_reverse_iterator;
    typedef vector_expression<E> const&              expression_argment;
    typedef T const                                  scalar_argment;
    typedef get_dimension<E>                         Dimension;

    using vector_expression<Derived>::operator();
    value_type operator()(unsigned i) const {
        return operator()().apply(i);
    }    

    const_iterator         begin()  const {return const_iterator(operator()());}
    const_iterator         end()    const {return const_iterator(operator()(), Dimension());}
    const_reverse_iterator rbegin() const {return const_reverse_iterator(begin());}
    const_reverse_iterator rend()   const {return const_reverse_iterator(end());}

    vector_and_scalar_base(expression_argment e, scalar_argment s):expr(e), scalar(s){}
    
protected:
    expression_argment   expr;
    scalar_argment       scalar;
};


/////////////////////////////////////////////////////////
//! @brief 左辺がベクトル、右辺がスカラの演算を行うクラス
/////////////////////////////////////////////////////////
template<class E, class T, class F>
class vector_and_scalar : public vector_and_scalar_base<E, T, vector_and_scalar<E, T, F> >{
    typedef vector_and_scalar<E, T, F>              self_type;
    typedef vector_and_scalar_base<E, T, self_type> base_type;
public:

    typename base_type::value_type apply(unsigned i) const {
        return F::apply(base_type::expr()(i), base_type::scalar);
    }

    vector_and_scalar(typename base_type::expression_argment e,
                      typename base_type::scalar_argment s):base_type(e, s){}
};

/////////////////////////////////////////////////////////
//! @brief 左辺がスカラ、右辺がベクトルの演算を行うクラス
/////////////////////////////////////////////////////////
template<class T, class E, class F>
class scalar_and_vector : public vector_and_scalar_base<E, T, scalar_and_vector<T, E, F> >{
    typedef scalar_and_vector<T, E, F>              self_type;
    typedef vector_and_scalar_base<E, T, self_type> base_type;

public:
    typename base_type::value_type apply(unsigned i) const {
        return F::apply(base_type::scalar, base_type::expr()(i));
    }

    scalar_and_vector(typename base_type::scalar_argment s,
                      typename base_type::expression_argment e):base_type(e, s){}
};


__NOGARA_EXPRESSION_END


#endif
