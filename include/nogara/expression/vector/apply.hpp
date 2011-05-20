#ifndef NOGARA_EXPRESSION_VECTOR_APPLY_HPP
#define NOGARA_EXPRESSION_VECTOR_APPLY_HPP

///////////////////////////////////////////////////
//! @file  nogara/expression/vector/apply.hpp
//! @brief ベクトルの要素に対し関数適用するベクトル
///////////////////////////////////////////////////

#include <nogara/expression/vector/unary_expression.hpp>
#include <nogara/expression/vector/binary_expression.hpp>

__NOGARA_EXPRESSION_BEGIN

template<class E, class F>
class apply_vector_unary : public vector_unary_base<E, apply_vector_unary<E, F> >{
    typedef apply_vector_unary<E, F>        self_type;
    typedef vector_unary_base<E, self_type> base_type;
public:
    apply_vector_unary(typename base_type::argment_type val,
                       F function):base_type(val), f(function){}

    typename base_type::value_type apply(unsigned i) const {
        return f(base_type::value()(i));
    }
private:
    F f;
};

template<class E1, class E2, class F>
class apply_vector_binary : public vector_binary_base<E1, E2, apply_vector_binary<E1, E2, F> >{
    typedef apply_vector_binary<E1, E2, F>        self_type;
    typedef vector_binary_base<E1, E2, self_type> base_type;
public:
    apply_vector_binary(typename base_type::argment1_type e1,
                        typename base_type::argment2_type e2,
                        F function):base_type(e1, e2), f(function){}

    typename base_type::value_type apply(unsigned i) const {
        return f(base_type::left()(i), base_type::right()(i));
    }
private:
    F f;
};


template<class F, class E>
apply_vector_unary<E, F> apply(vector_expression<E> const& e, F f){
    return apply_vector_unary<E, F>(e, f);
}

template<class R, class A, class E>
apply_vector_unary<E, R (*)(A)> apply(vector_expression<E> const& e, R (*f)(A)){
    return apply_vector_unary<E, R (*)(A)>(e, f);
}


template<class F, class E1, class E2>
apply_vector_binary<E1, E2, F> apply(vector_expression<E1> const& e1,
                                     vector_expression<E2> const& e2,
                                     F f)
{
    return apply_vector_binary<E1, E2, F>(e1, e2, f);
}

template<class R, class A1, class A2, class E1, class E2>
apply_vector_binary<E1, E2, R(*)(A1, A2)>
apply(vector_expression<E1> const& e1, vector_expression<E2> const& e2, R(*f)(A1, A2)){
    return apply_vector_binary<E1, E2, R(*)(A1, A2)>(e1, e2, f);
}

__NOGARA_EXPRESSION_END

__NOGARA_BEGIN
using expression::apply;
__NOGARA_END

#endif
