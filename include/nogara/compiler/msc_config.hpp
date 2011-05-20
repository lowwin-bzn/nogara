#ifndef NOGARA_MSC_HPP
#define NOGARA_MSC_HPP

/////////////////////////////////////////
//! @file  nogara/compiler/msc_config.hpp
//! @brief MSCの情報
/////////////////////////////////////////

#define NG_MSC            1
#define NG_MSC_VER        _MSC_VER
#define NG_MSC_VER_FULL   _MSC_FULL_VER

#ifndef NG_NO_USE_CPP0X

#if(NG_MSC_VER_FULL >= 150030729)
#  define NG_TR1          1
#  define INCLUDE_TR1(name) <name>
#  if(NG_MSC_VER >= 1600)
#    define NG_CPP0X  1
#    define NG_HAS_UNIQUE_PTR 1
#    define NG_HAS_LAMBDA 1
#  endif /* CPP0X */
#endif /* TR1 */

#endif

#endif
