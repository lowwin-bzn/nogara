#ifndef NOGARA_EXPRESSION_QUATERNION_CONJ_HPP
#define NOGARA_EXPRESSION_QUATERNION_CONJ_HPP

//////////////////////////////////////////////////////////
//! @file nogara/expression/quaternion/quaternion_conj.hpp
//! @brief クォータニオンの共役
//////////////////////////////////////////////////////////

#include <nogara/expression/vector/unary_expression.hpp>

__NOGARA_EXPRESSION_BEGIN

///////////////////////////////////////////////
//! @brief クォータニオンの共役関数オブジェクト
///////////////////////////////////////////////
template<class E>
class quaternion_conj : public vector_unary_base<E, quaternion_conj<E> >{
    typedef quaternion_conj<E>              self_type;
    typedef vector_unary_base<E, self_type> base_type;

public:
    explicit quaternion_conj(typename base_type::argment_type val):base_type(val){}
    typename base_type::value_type apply(unsigned i) const {
        assert(i < 4 && "quaternion conj out of range");
        return (i == 0) ? base_type::value()(i) : -base_type::value()(i);
    }
};

///////////////////////////////
//! @brief クォータニオンの共役
///////////////////////////////
template<class E>
inline typename boost::enable_if<is_quaternion<E>, quaternion_conj<E> >::type
conj(vector_expression<E> const& e){
    return quaternion_conj<E>(e);
}

__NOGARA_EXPRESSION_END

__NOGARA_BEGIN
using expression::quaternion_conj;
using expression::conj;
__NOGARA_END

#endif
