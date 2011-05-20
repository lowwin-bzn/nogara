#ifndef NOGARA_EXPRESSION_SLICE_MATRIX_HPP
#define NOGARA_EXPRESSION_SLICE_MATRIX_HPP

////////////////////////////////////////////////////////
//! @file nogara/expression/matrix/slice.hpp
//! @brief 部分行列
////////////////////////////////////////////////////////

#include <boost/mpl/greater.hpp>
#include <boost/mpl/size_t.hpp>
#include <nogara/expression/expression.hpp>
#include <nogara/expression/function.hpp>
#include <nogara/expression/matrix/traits.hpp>

__NOGARA_EXPRESSION_BEGIN

//////////////////////////////////
//! @brief 式Eの部分行列
//!        Rowsは行の範囲
//!        Columnsは列の範囲を示す
//////////////////////////////////   
template<class E, class Rows, class Columns>
class slice_matrix : public matrix_unary_base<E, slice_matrix<E, Rows, Columns> >{
    typedef slice_matrix<E, Rows, Columns>  self_type;
    typedef matrix_unary_base<E, self_type> base_type;

public:
    typedef typename boost::enable_if<
    boost::mpl::greater<
        typename Rows::second,
        typename Rows::first>, Rows>::type row_pair;

    typedef typename boost::enable_if<
        boost::mpl::greater<
            typename Columns::second,
            typename Columns::first>, Columns>::type column_pair;
    
    typedef boost::mpl::size_t<row_pair::second::value    - row_pair::first::value>    Row;
    typedef boost::mpl::size_t<column_pair::second::value - column_pair::first::value> Column;

    typename base_type::value_type apply(std::size_t x, std::size_t y) const {
        return base_type::value()(x + row_pair::first::value, y + column_pair::first::value);
    }

    slice_matrix(typename base_type::argment_type e):base_type(e){}
};

///////////////////////////////////////////
//! @brief クラスを生成しやすくする便利関数
///////////////////////////////////////////
template<class row_slicer, class column_slicer, class E>
inline slice_matrix<E, row_slicer, column_slicer>
slice(matrix_expression<E> const& e){
    return slice_matrix<E, row_slicer, column_slicer>(e);
}

///////////////////////////////////////////
//! @brief クラスを生成しやすくする便利関数
///////////////////////////////////////////
template<std::size_t r_min, std::size_t r_max, std::size_t c_min, std::size_t c_max, class E>
inline slice_matrix<E, slicer<r_min, r_max>, slicer<c_min, c_max> >
slice_c(matrix_expression<E> const& e){
    return slice<slicer<r_min, r_max>, slicer<c_min, c_max> >(e);
}

__NOGARA_EXPRESSION_END

__NOGARA_BEGIN
using expression::slice;
using expression::slice_c;
using expression::slice_matrix;
__NOGARA_END

#endif
