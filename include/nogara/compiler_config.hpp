#ifndef NOGARA_COMPILER_CONFIG_HPP
#define NOGARA_COMPILER_CONFIG_HPP

/////////////////////////////////////
//! @file  nogara/compiler_config.hpp
//! @brief コンパイラ情報を定義する
/////////////////////////////////////

#  if defined(_MSC_VER)
#    include <nogara/compiler/msc_config.hpp>
#  elif defined(__GNUC__) || defined(__clang__)
#    include <nogara/compiler/gcc_config.hpp>
//#  elif defined(__BORLANDC__)
//#    define NG_BCC
#  endif /*_MSC_VER and __GNUC__ */

#if defined(NG_CPP0X)
#  define SWAP_INCLUDE <utility>
#else
#  define SWAP_INCLUDE <algorithm>
#endif

#endif
