#ifndef NOGARA_UTILITY_HPP
#define NOGARA_UTILITY_HPP

///////////////////////////////////
//! @file nogara/utility.hpp
//! @brief 計算に使用する便利関数群
///////////////////////////////////

#include <cmath>
#include <nogara/typedef.hpp>
#include <nogara/type_traits/deduct.hpp>
#include <nogara/utility/byte_unit.hpp>

#if defined(__WIN32__) || defined(__WIN64__)
#  include <windows.h>
#  define MS_SLEEP_FUNCTION Sleep
#elif defined(__unix__) || defined(__linux__) || defined(__APPLE__)
#  include <unistd.h>
#  define MS_SLEEP_FUNCTION usleep
#endif
#if defined(M_PI)
#define NG_PI      M_PI
#else
#define NG_PI      3.14159265358979323846264338327950288
#endif

#define NG_RadSeed (NG_PI / 180)

__NOGARA_BEGIN

//! @brief degree to radian
template<class T>
inline typename deduct1<T>::real_type
to_radian(T degree){return NG_RadSeed * degree;}

//! @brief radian to degree 
template<class T>
inline typename deduct1<T>::real_type
to_degree(T radian){return radian / NG_RadSeed;}


//! @brief ミリ秒単位の停止
inline void ms_sleep(uint_t time){MS_SLEEP_FUNCTION(time);}

__NOGARA_END

#undef MS_SLEEP_FUNCTION


#endif
