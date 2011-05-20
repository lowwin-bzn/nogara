#ifndef NOGARA_GCC_HPP
#define NOGARA_GCC_HPP

/////////////////////////////////////////
//! @file  nogara/compiler/gcc_config.hpp
//! @brief GCCの情報
/////////////////////////////////////////
#define NG_GNUC
#define NG_GNUC_VER       __GNUC__
#define NG_GNUC_MINOR     __GNUC_MINOR__

#ifndef NG_NO_USE_CPP0X

#if(NG_GNUC_VER >= 4)
#  define NG_TR1 std::tr1
#  define INCLUDE_TR1(name) <tr1/name>
#  if NG_GNUC_MINOR >= 3 && defined(__GXX_EXPERIMENTAL_CXX0X__)
#    define NG_CPP0X
#    if(NG_GNUC_MINOR >= 3)
#      define NG_HAS_STATIC_ASSERT
#    endif /* GNUC_MINOR >= 3 */
#    if(NG_GNUC_MINOR >= 4)
#      define NG_HAS_AUTO
#      define NG_HAS_INITIALIZER_LIST
#      define NG_HAS_UNIQUE_PTR
#      define NG_HAS_VARIADIC_TEMPLATES
#    endif /* GNUC_MINOR >= 4 */
#    if(NG_GNUC_MINOR >= 5)
#      define NG_HAS_LAMBDA
#      define NG_RAW_STRING
#      define NG_UNICODE_STRING
#    endif /* GNUC_MINOR >= 5 */
#    if(NG_GNUC_MINOR >= 6)
#      define NG_HAS_NULLPTR
#      define NG_HAS_CONSTEXPR
#      define NG_HAS_RANGE_BASED_FOR
#    endif /* GNUC_MINOR >= 6 */
#    undef  NG_TR1
#    define NG_TR1 std
#    undef  INCLUDE_TR1
#    define INCLUDE_TR1(name) <name>
#  endif /* CPP0X */
#endif /* TR1 */

#endif


#endif
