#ifndef NOGARA_EXPRESSION_FUNCTOR_HPP
#define NOGARA_EXPRESSION_FUNCTOR_HPP

///////////////////////////////////////////////
//! @file  nogara/expression/function.hpp
//! @brief ベクトル、行列等で使用されるクラス群
///////////////////////////////////////////////
#include <nogara/expression/define.hpp>
#include <boost/mpl/pair.hpp>

__NOGARA_EXPRESSION_BEGIN

///////////////////////////////////////////
//! @brief 範囲を切り出す時に使用するクラス
///////////////////////////////////////////
template<std::size_t x, std::size_t y>
struct slicer : public boost::mpl::pair<boost::mpl::size_t<x>, boost::mpl::size_t<y> >{};

///////////////////////////////////////////////////////
//! @brief 実数の比較をする時に使用する関数オブジェクト
///////////////////////////////////////////////////////
template<typename T>
struct float_guess{
    bool operator ()(T const& _1, T const& _2){
        return std::abs(_1 - _2) <= std::sqrt(std::numeric_limits<T>::epsilon());
    }
};

//////////////////////////////////////////////////////////////////////////
//! @brief 実数とその他で比較方法を変える関数オブジェクト
//!        実数の場合は2つの差分の絶対値が最小値以下かで等しいかを判定し、
//!        それ以外は単純に == で等しいかを判定する
//////////////////////////////////////////////////////////////////////////
template<typename T>
struct equal_test : public boost::mpl::if_<
    boost::is_floating_point<T>, float_guess<T>, std::equal_to<T> >::type{};

__NOGARA_EXPRESSION_END

#endif
