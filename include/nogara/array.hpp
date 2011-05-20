#ifndef NOGARA_ARRAY_HPP
#define NOGARA_ARRAY_HPP

///////////////////////////////////////////////////
//! @file  nogara/array.hpp
//! @brief c++0xのarrayを統合的に使うためのラッパー
//! TR1以降対応のコンパイラならTR1移行のarrayを、
//! そうでなければboostのarrayを使用する
//////////////////////////////////////////////

#include <nogara/nogara_define.hpp>
#if defined(NG_TR1)
#  include INCLUDE_TR1(array)
__NOGARA_BEGIN
using NG_TR1::array;
__NOGARA_END
#else
#include <boost/array.hpp>
__NOGARA_BEGIN
using boost::array;
__NOGARA_END
#endif

#endif
