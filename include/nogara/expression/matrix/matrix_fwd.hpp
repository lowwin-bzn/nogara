#ifndef NOGARA_EXPRESSION_MATRIX_FWD_HPP
#define NOGARA_EXPRESSION_MATRIX_FWD_HPP

/////////////////////////////////////////////////
//! @file nogara/expression/matrix/matrix_fwd.hpp
//! @brief 行列で多用する関数の前方宣言
/////////////////////////////////////////////////

#include <boost/mpl/greater.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/and.hpp>
#include <boost/utility/enable_if.hpp>
#include <nogara/expression/define.hpp>

__NOGARA_EXPRESSION_BEGIN

template<std::size_t X, std::size_t Y, class E>
inline typename boost::enable_if<
    boost::mpl::and_<
        boost::mpl::greater<get_row<E>, boost::mpl::size_t<X> >,
        boost::mpl::greater<get_column<E>, boost::mpl::size_t<Y> > >,
    typename E::value_type>::type
get(matrix_expression<E> const& e);

__NOGARA_EXPRESSION_END

#endif
