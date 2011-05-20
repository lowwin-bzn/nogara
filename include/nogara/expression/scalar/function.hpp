#ifndef NOGARA_EXPRESSION_SCALAR_FUNCTION_HPP
#define NOGARA_EXPRESSION_SCALAR_FUNCTION_HPP

////////////////////////////////////////////////
//! @file  nogara/expression/scalar/function.hpp
//! @brief スカラで扱う関数群
////////////////////////////////////////////////

__NOGARA_EXPRESSION_BEGIN

/////////////////////////////////////////////////////
//! @brief スカラ値の取得
//!        スカラオブジェクトの場合はvalue_typeに変換
/////////////////////////////////////////////////////
template<typename T>
inline typename boost::lazy_enable_if<
    boost::mpl::and_<is_scalar<T>, boost::is_arithmetic<T> >, get_value_type<T> >::type
get_scalar_value(T const& value){
    return typename T::value_type(value());
}

///////////////////////////////////////////
//! @brief スカラ値の取得
//!        通常のスカラ値の場合は単純コピー
///////////////////////////////////////////
template<typename T>
inline typename boost::enable_if<boost::is_arithmetic<T>, T>::type
get_scalar_value(T const& value){
    return value;
}

///////////////////
//! @brief 線形補間
///////////////////
template<typename T1, typename T2, typename T3>
inline typename boost::enable_if<
    boost::mpl::and_<is_scalar<T1>, is_scalar<T2>, is_scalar<T3> >,
    typename deduct3<T1, T2, T3>::value_type>::type
lerp(T1 const& left, T2 const& right, T3 const& t){
    return get_scalar_value(left) + get_scalar_value(t) *
          (get_scalar_value(right) - get_scalar_value(left));
}

template<class T>
inline typename boost::enable_if<is_scalar<T>, T>::type 
max(T const& x, T const& y){
    return x > y ? x : y;
}

template<class T>
inline typename boost::enable_if<is_scalar<T>, T>::type 
min(T const& x, T const& y){
    return x < y ? x : y;
}

template<typename T1, typename T2, typename T3>
inline typename boost::enable_if<
    boost::mpl::and_<is_scalar<T1>, is_scalar<T2>, is_scalar<T3> >,
    get_value_type<deduct3<T1, T2, T3> > >::type
clamp(T1 const& x, T2 const& max_, T3 const& min_){
    typedef typename deduct2<T1, T2>::value_type       min_type;
    typedef typename deduct2<min_type, T3>::value_type max_type;
    return nogara::expression::max<max_type>(nogara::expression::min<min_type>(x, max_), min_);
}

template<class T>
inline typename boost::lazy_enable_if<is_scalar<T>, wrrap_get_value_type<T> >::type
satutate(T const& x){
    typedef typename wrrap_get_value_type<T>::type value_type;
    return clamp(x, value_type(0), value_type(1));
}

template<class T1, class T2, class T3>
inline typename boost::lazy_enable_if<
    boost::mpl::and_<is_scalar<T1>, is_scalar<T2>, is_scalar<T3> >,
    get_value_type<deduct3<T1, T2, T3> > >::type
smoothstep(T1 const& edge0, T2 const& edge1, T3 const& t){
    typedef typename deduct3<T1, T2, T3>::value_type value_type;
    value_type const x = saturate((x - edge0) / (edge1 - edge0));
    return x * x * (3 - 2 * x);
}


__NOGARA_EXPRESSION_END

#endif
