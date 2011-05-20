#ifndef COLOR_CONSTANT_HPP
#define COLOR_CONSTANT_HPP

//////////////////////////////////////////
//! @file  nogara/color/color_constant.hpp
//! @brief 色の定数群
//////////////////////////////////////////

#include <nogara/color/color.hpp>

__NOGARA_BEGIN

namespace rgba{

template<typename T>
struct float_color_constant{
    static rgba::color<T> const red;
    static rgba::color<T> const green;
    static rgba::color<T> const blue;
    static rgba::color<T> const white;
    static rgba::color<T> const black;
    static rgba::color<T> const grey;
    static rgba::color<T> const darkgrey;
    static rgba::color<T> const yellow;
    static rgba::color<T> const pink;
    static rgba::color<T> const purple;
    static rgba::color<T> const orange;
    static rgba::color<T> const brown;
};

template<typename T>
rgba::color<T> const float_color_constant<T>::red(1, 0, 0);
template<typename T>
rgba::color<T> const float_color_constant<T>::green(0, 1, 0);
template<typename T>
rgba::color<T> const float_color_constant<T>::blue(0, 0, 1);
template<typename T>
rgba::color<T> const float_color_constant<T>::white(1, 1, 1);
template<typename T>
rgba::color<T> const float_color_constant<T>::black(0, 0, 0);
template<typename T>
rgba::color<T> const float_color_constant<T>::grey(0.75, 0.75, 0.75);
template<typename T>
rgba::color<T> const float_color_constant<T>::darkgrey(0.5, 0.5, 0.5);
template<typename T>
rgba::color<T> const float_color_constant<T>::yellow(1, 1, 0);
template<typename T>
rgba::color<T> const float_color_constant<T>::pink(1, 0, 0.5);
template<typename T>
rgba::color<T> const float_color_constant<T>::purple(1, 0, 1);
template<typename T>
rgba::color<T> const float_color_constant<T>::orange(1, 0.5, 0.25);
template<typename T>
rgba::color<T> const float_color_constant<T>::brown(1, 0.25, 0);

typedef float_color_constant<float> color_constant;
}

namespace rgb{

template<typename T>
struct float_color_constant{
    static rgb::color<T> const red;
    static rgb::color<T> const green;
    static rgb::color<T> const blue;
    static rgb::color<T> const white;
    static rgb::color<T> const black;
    static rgb::color<T> const grey;
    static rgb::color<T> const darkgrey;
    static rgb::color<T> const yellow;
    static rgb::color<T> const pink;
    static rgb::color<T> const purple;
    static rgb::color<T> const orange;
    static rgb::color<T> const brown;
};

template<typename T>
rgb::color<T> const float_color_constant<T>::red(1, 0, 0);
template<typename T>
rgb::color<T> const float_color_constant<T>::green(0, 1, 0);
template<typename T>
rgb::color<T> const float_color_constant<T>::blue(0, 0, 1);
template<typename T>
rgb::color<T> const float_color_constant<T>::white(1, 1, 1);
template<typename T>
rgb::color<T> const float_color_constant<T>::black(0, 0, 0);
template<typename T>
rgb::color<T> const float_color_constant<T>::grey(0.75, 0.75, 0.75);
template<typename T>
rgb::color<T> const float_color_constant<T>::darkgrey(0.5, 0.5, 0.5);
template<typename T>
rgb::color<T> const float_color_constant<T>::yellow(1, 1, 0);
template<typename T>
rgb::color<T> const float_color_constant<T>::pink(1, 0, 0.5);
template<typename T>
rgb::color<T> const float_color_constant<T>::purple(1, 0, 1);
template<typename T>
rgb::color<T> const float_color_constant<T>::orange(1, 0.5, 0.25);
template<typename T>
rgb::color<T> const float_color_constant<T>::brown(1, 0.25, 0);

typedef float_color_constant<float> color_constant;
}

__NOGARA_END

#endif
