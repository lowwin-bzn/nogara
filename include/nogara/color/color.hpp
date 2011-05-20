#ifndef NOGARA_COLOR_HPP
#define NOGARA_COLOR_HPP

//////////////////////////////////
//! @file  nogara/color/color.hpp
//! @brief カラーライブラリ
//////////////////////////////////

#include <boost/type_traits.hpp>
#include <nogara/color/rgba/color.hpp>
#include <nogara/color/rgb/color.hpp>

__NOGARA_BEGIN

//! @brief 色型か否かを返すメタ関数
template<class C>
struct is_color : boost::false_type{};

template<class T>
struct is_color<rgba::color<T> > : boost::true_type{};

template<class T>
struct is_color<rgba::float_color<T> > : boost::true_type{};

template<class T>
struct is_color<rgba::integer_color<T> > : boost::true_type{};

template<>
struct is_color<rgba::color32> : boost::true_type{};

template<class T>
struct is_color<rgb::color<T> > : boost::true_type{};

template<class T>
struct is_color<rgb::float_color<T> > : boost::true_type{};

template<class T>
struct is_color<rgb::integer_color<T> > : boost::true_type{};

template<>
struct is_color<rgb::color24> : boost::true_type{};


__NOGARA_END

#endif
