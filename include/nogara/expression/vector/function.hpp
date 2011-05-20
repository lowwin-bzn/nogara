#ifndef NOGARA_EXPRESSION_VECTOR_FUNCTION_HPP
#define NOGARA_EXPRESSION_VECTOR_FUNCTION_HPP

///////////////////////////////////////////////
//! @file nogara/expression/vector/function.hpp
//! @brief ベクトル型の関数群
///////////////////////////////////////////////

#include <cassert>

#include <boost/mpl/size_t.hpp>
#include <boost/mpl/greater.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/function_types/function_type.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/mpl/at.hpp>
#include <nogara/expression/vector/vector_and_scalar.hpp>
#include <nogara/expression/vector/vector_to_scalar.hpp>
#include <nogara/expression/vector/apply.hpp>
#include <nogara/expression/vector/minor.hpp>
#include <nogara/expression/vector/swizzle.hpp>
#include <nogara/expression/vector/functor.hpp>
#include <nogara/type_traits/value_type_traits.hpp>
#include <nogara/expression/function.hpp>

__NOGARA_EXPRESSION_BEGIN

///////////////////////////////////////////
//! @brief 式の三項演算関数、式は評価される
///////////////////////////////////////////
template<class Result, class E1, class E2>
inline Result ternary(bool then,
                      vector_expression<E1> const& e1,
                      vector_expression<E2> const& e2)
{
    return then ? Result(e1) : Result(e2);
}

///////////////////////////////////////////////////////////////
//! @brief ベクトルの値それぞれを絶対値にしたベクトルを返す関数
///////////////////////////////////////////////////////////////
template<class E>
inline apply_vector_unary<E, typename E::value_type (*)(typename E::value_type)>
abs(vector_expression<E> const& val){
    typedef typename E::value_type T;
    return apply<T, T>(val, std::abs);
}

///////////////////////////////////////////
//! @brief ベクトルの値から最大値を返す関数
///////////////////////////////////////////
template<class E>
inline typename E::value_type max(vector_expression<E> const& e){
    typedef typename E::value_type const& c_ref;
    return reduce<c_ref, c_ref, c_ref>(e, std::max);
}

///////////////////////////////////////////
//! @brief ベクトルの値から最小値を返す関数
///////////////////////////////////////////
template<class E>
inline typename E::value_type min(vector_expression<E> const& e){
    typedef typename E::value_type const& c_ref;
    return reduce<c_ref, c_ref, c_ref>(e, std::min);
}

///////////////////////////////////
//! @brief ベクトルの合計を返す関数
///////////////////////////////////
template<class E>
inline typename E::value_type sum(vector_expression<E> const& e){
    return reduce(e, std::plus<typename E::value_type>());
}

///////////////////
//! @brief 内積関数
///////////////////
template<class E1, class E2>
inline typename deduct2<E1, E2>::value_type
dot(vector_expression<E1> const& e1, vector_expression<E2> const& e2){
    return sum(multiply(e1, e2));
}

///////////////////
//! @brief 外積関数
///////////////////
template<typename E1, class E2>
inline typename boost::enable_if<
    same_dimension<E1, E2>, vector_cross<E1, E2, get_dimension<E1>::value> >::type
cross(vector_expression<E1> const& e1, vector_expression<E2> const& e2){
    return vector_cross<E1, E2, get_dimension<E1>::value>(e1, e2);
}

/////////////////////////////
//! @brief 要素同士の乗算関数
/////////////////////////////
template<class E1, class E2>
inline vector_binary<E1, E2, scalar_mul<E1, E2> >
multiply(vector_expression<E1> const& v1, vector_expression<E2> const& v2){
    return vector_binary<E1, E2, scalar_mul<E1, E2> >(v1, v2);
}

/////////////////////////////
//! @brief 要素同士の除算関数
/////////////////////////////
template<class E1, class E2>
inline vector_binary<E1, E2, scalar_mul<E1, E2> >
divide(vector_expression<E1> const& v1, vector_expression<E2> const& v2){
    return vector_binary<E1, E2, scalar_mul<E1, E2> >(v1, v2);
}

///////////////////////////////////////////
//! @brief ベクトルの大きさの二乗を返す関数
///////////////////////////////////////////
template<class E>
inline typename deduct1<E>::value_type
length_sq(vector_expression<E> const& value){
    return nogara::expression::dot(value, value);
}

///////////////////////////////////
//! @brief ベクトル大きさを返す関数
///////////////////////////////////
template<class T>
inline typename deduct1<T>::real_type
length(vector_expression<T> const& value){
    using std::sqrt;
    return sqrt(nogara::expression::length_sq(value));
}

////////////////////////////////
//! @brief 2点間の距離を返す関数
////////////////////////////////
template<class E1, class E2>
inline typename deduct2<E1, E2>::real_type
distance(vector_expression<E1> const& e1, vector_expression<E2> const& e2){
    return nogara::expression::length(e1 - e2);
}

///////////////////////////////////////////////////////////////////
//! @brief 2つのベクトルの角度(ラジアン)を返す関数
//!        なお、この関数に渡すベクトルは正規化されている必要がある
///////////////////////////////////////////////////////////////////
template<class E1, class E2>
inline typename deduct2<E1, E2>::real_type
angle(vector_expression<E1> const& e1, vector_expression<E2> const& e2){
    typedef typename deduct2<E1, E2>::real_type real_t;
    real_t const dot = nogara::expression::dot(e1, e2);
    real_t const result = (dot < -1) ? -1 : (dot > 1) ? 1 : dot;
    return std::acos(result);
}

///////////////////////////////////////////////////////////////////
//! @brief 2つのベクトル正規化して角度(ラジアン)を返す関数
///////////////////////////////////////////////////////////////////
template<class E1, class E2>
inline typename deduct2<E1, E2>::real_type
normalize_angle(vector_expression<E1> const& e1, vector_expression<E2> const& e2){
    return angle(normalize(e1), normalize(e2));
}

/////////////////////////////////////////////
//! @brief 2点間の線形補間関数
//!        第三引数は0.0から1.0までの値を渡す
/////////////////////////////////////////////
template<class E1, class E2, typename T>
inline typename boost::enable_if<
    same_dimension<E1, E2>,
    apply_vector_binary<E1, E2, vector_lerp_functor<T> > >::type
lerp(vector_expression<E1> const& e1, vector_expression<E2> const& e2, T const& t){
    return apply(e1, e2, vector_lerp_functor<T>(t));
}

///////////////////////////////////////////////////////////////////
//! @brief 2点間のベクトル球面線形補間関数
//!        第三引数は0.0から1.0までの値を渡す
//!        なお、この関数に渡すベクトルは正規化されている必要がある
///////////////////////////////////////////////////////////////////
template<class E1, class E2, typename T>
inline typename vector_type<typename deduct3<E1, E2, T>::real_type,
                            get_same_dimension<E1, E2>::value>::type
slerp(vector_expression<E1> const& e1, vector_expression<E2> const& e2, T const& t){
    typedef typename deduct2<E1, E2>::real_type real_t;
    real_t const angle = nogara::expression::angle(e1, e2);
    real_t const start = std::sin(angle * (1 - t));
    real_t const end   = std::sin(angle * t);

    return normalize((start * e1 + end * e2) / std::sin(angle));
}

/////////////////////////////
//! @brief ベクトルの冪乗関数
/////////////////////////////
template<class E, class T>
inline typename boost::enable_if<
    boost::mpl::and_<boost::mpl::not_<is_quaternion<E> >, is_scalar<T> >,
    apply_vector_unary<E, pow_functor<T> > >::type
pow(vector_expression<E> const& e, T const& t){
    return apply(e, pow_functor<T>(t));
}

///////////////////////////////////////////////////
//! @brief ベクトルの正規化関数
//!        0ベクトルが渡された場合は0ベクトルが返る
///////////////////////////////////////////////////
template<class E>
inline vector_and_scalar<
    E, typename deduct1<E>::real_type, scalar_mul<E, typename deduct1<E>::real_type> >
normalize(vector_expression<E> const& e){
    typedef typename deduct1<E>::real_type real_type;
    real_type length = nogara::expression::length(e);
    if(length != real_type()){
        length = real_type(1) / length;
    }
    return e * length;
}

///////////////////////////////////////////////////
//! @brief 逆数ベクトル
///////////////////////////////////////////////////
template<class E>
inline typename boost::disable_if<
    is_quaternion<E>, vector_unary<E, scalar_inverse<E> > >::type
inverse(vector_expression<E> const& e){
    return vector_unary<E, scalar_inverse<E> >(e);
}

/////////////////////////////////////////////////////////
//! @brief 反射ベクトル
//!        この関数の第二引数は正規化されている必要がある
/////////////////////////////////////////////////////////
template<class E1, class E2>
inline typename vector_type<
    typename deduct2<E1, E2>::value_type, get_same_dimension<E1, E2>::value>::type
reflect(vector_expression<E1> const& incident, vector_expression<E2> const& normal){
    return expression::normalize(incident - 2 * expression::dot(incident, normal) * normal);
}

////////////////////////////////////////////////////////
//! @brief Fに指定したファンクタをベクトルに適応する関数
////////////////////////////////////////////////////////
template<class F, class E>
inline vector_unary<E, F> map(vector_expression<E> const& e){
    return vector_unary<E, F>(e);
}

////////////////////////////////////////////////////////
//! @brief 第二引数のファンクタをベクトルに適応する関数
////////////////////////////////////////////////////////
template<class E, class F>
inline apply_vector_unary<E, F> map(vector_expression<E> const& e, F f){
    return apply(e, f);
}

/////////////////////////////////////////////////////////
//! @brief 第二引数の関数ポインタをベクトルに適応する関数
/////////////////////////////////////////////////////////
template<class R, class A, class E>
inline apply_vector_unary<E, R(*)(A)> map(vector_expression<E> const& e, R (*f)(A)){
    return apply(e, f);
}


__NOGARA_EXPRESSION_END

__NOGARA_BEGIN
using expression::ternary;
using expression::abs;
using expression::sum;
using expression::max;
using expression::dot;
using expression::length;
using expression::length_sq;
using expression::lerp;
using expression::slerp;
using expression::pow;
using expression::cross;
using expression::normalize;
using expression::distance;
using expression::angle;
using expression::normalize_angle;
using expression::multiply;
using expression::divide;
using expression::inverse;
using expression::reflect;
using expression::map;
__NOGARA_END


#endif
