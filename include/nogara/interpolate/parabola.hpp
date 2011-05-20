#ifndef NOGARA_PARABOLA_HPP
#define NOGARA_PARABOLA_HPP

#include <nogara/vector.hpp>

////////////////////////////////////////
//! @file nogara/interpolate/parabola.hpp
//! @brief 3点補間
////////////////////////////////////////

__NOGARA_BEGIN

namespace invisible{
template<class Result, class E1, class E2, class E3, typename T>
inline Result parabola_impl(E1 const& e1, E2 const& e2, E3 const& e3, T t){
    T const ip = 1 - t;
    return (e1 * std::pow(ip, 2)) + (2 * t * ip * e2) + (e3 * std::pow(t, 2));
}
}

template<class E1, class E2, class E3, typename T>
inline typename boost::lazy_enable_if<
    boost::mpl::and_<expression::same_dimension<E1, E2>,
              expression::same_dimension<E2, E3> >,
    expression::vector_type<typename deduct4<E1, E2, E3, T>::value_type,
    expression::get_same_dimension<E2, E3>::value> >::type
parabola(expression::vector_expression<E1> const& e1,
         expression::vector_expression<E2> const& e2,
         expression::vector_expression<E3> const& e3,
         T const& t)
{
    typedef typename expression::vector_type<
        typename deduct4<E1, E2, E3, T>::value_type,
        expression::get_same_dimension<E2, E3>::value>::type Result;
    return invisible::parabola_impl<Result>(e1(), e2(), e3(), t);
}

__NOGARA_END

#endif
