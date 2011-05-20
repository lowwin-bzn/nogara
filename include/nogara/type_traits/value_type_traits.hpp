#ifndef NOGARA_VALUE_TYPE_TRAITS_HPP
#define NOGARA_VALUE_TYPE_TRAITS_HPP

////////////////////////////////////////////////////////
//! @file nogara/type_traits/value_type_traits.hpp
//! @brief value_typeに関するメタ関数群
////////////////////////////////////////////////////////

#include <boost/mpl/if.hpp>
#include <nogara/type_traits/sfinae_check.hpp>

__NOGARA_BEGIN

////////////////////////////////////////////////////////////////
//! @brief value_typeという名のtypedefがあるか否かを返すメタ関数
////////////////////////////////////////////////////////////////
template<class T>
class has_value_type : public sfinae_check{
    template<class U> static yes_type check(typename U::value_type*);
    template<class>   static no_type  check(...);

public:
    static bool const value = sizeof(yes_type) == sizeof(check<T>(0));
};


//////////////////////////////////////////////////
//! @brief Tをvalue_typeという名に変換するメタ関数
//////////////////////////////////////////////////
template<typename T>
struct value_type_wrapper{
    typedef T value_type;
};

////////////////////////////////////////////////////////////
//! @brief Tの持つvalue_typeをtypeという名に変換するメタ関数
////////////////////////////////////////////////////////////
template<class T>
struct get_value_type{
    typedef typename T::value_type type;
};

////////////////////////////////////////////////////////////////
//! @brief Tがvalue_typeという名のtypedefを持っていればそのまま、
//!        持っていなければ付随してget_value_typeに渡すメタ関数
////////////////////////////////////////////////////////////////
template<class T>
struct wrrap_get_value_type{ 
    typedef typename get_value_type<
        typename boost::mpl::if_<
            has_value_type<T>, T, value_type_wrapper<T> >::type >::type type;
};

__NOGARA_END



#endif
