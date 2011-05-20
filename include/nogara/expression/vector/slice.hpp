#ifndef NOGARA_EXPRESSION_VECTOR_SLICE_HPP
#define NOGARA_EXPRESSION_VECTOR_SLICE_HPP

////////////////////////////////////////////////////////
//! @file nogara/expression/vector/slice.hpp
//! @brief ベクトルから範囲を抜き出すクラス
////////////////////////////////////////////////////////

#include <nogara/expression/vector/unary_expression.hpp>
#include <nogara/expression/function.hpp>

__NOGARA_EXPRESSION_BEGIN

////////////////////////////////////////////////////////////////////////////////
//! @brief ベクトルからRangeの範囲を抜き出すクラス
//!        結果サイズはRangeのサイズになる。
//!        Rangeがの始点から終点がベクトルを超過するようであればコンパイルエラー
//!
//! -*- example -*-
//! slice_vector<vector4, slicer[2, 3)>([1, 2, 3, 4]) = [2, 3]
////////////////////////////////////////////////////////////////////////////////

template<class E, class Range>
class slice_vector : public vector_unary_base<E, slice_vector<E, Range> >{
    typedef slice_vector<E, Range>          self_type;
    typedef vector_unary_base<E, self_type> base_type;

public:
    typedef expression::vector_tag expression_category;
    typedef typename boost::enable_if<
        boost::mpl::greater<typename Range::second, typename Range::first>,
    Range>::type range;

    typedef boost::mpl::size_t<Range::second::value - Range::first::value> Dimension;

    slice_vector(typename base_type::argment_type e):base_type(e){}

    typename base_type::value_type apply(unsigned i) const {
        return base_type::value()(i + row_pair::first::value);
    }
};


///////////////////////////////////////////
//! @brief クラスを生成しやすくする便利関数
///////////////////////////////////////////
template<class Range, class E>
inline slice_vector<E, Range>
slice(vector_expression<E> const& e){
    return slice_vector<E, Range>(e);
}

///////////////////////////////////////////
//! @brief クラスを生成しやすくする便利関数
///////////////////////////////////////////
template<std::size_t Begin, std::size_t End, class E>
inline slice_vector<E, expression::slicer<Begin, End> >
slice(vector_expression<E> const& e){
    return slice<expression::slicer<Begin, End> >(e);
}

__NOGARA_EXPRESSION_END

#endif
