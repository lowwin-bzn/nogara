#ifndef NOGARA_EXPRESSION_QUATERNION_FUNCTION_HPP
#define NOGARA_EXPRESSION_QUATERNION_FUNCTION_HPP

///////////////////////////////////////////////////
//! @file nogara/expression/quaternion/function.hpp
//! @brief クォータニオンの関数群
///////////////////////////////////////////////////

#include <nogara/expression/quaternion/quaternion.hpp>
#include <nogara/utility.hpp>

__NOGARA_EXPRESSION_BEGIN
///////////////////////////////
//! @brief クォータニオンの逆数
///////////////////////////////
template<class E>
inline typename boost::enable_if<
    is_quaternion<E>, quaternion<typename E::value_type> >::type
inverse(vector_expression<E> const& e){
    return quaternion_conj<E>(e) / nogara::length_sq(e);
}

//////////////////////////////////////////////////////////////////
//! @brief X-Y-Zの順に回転するオイラー角をクォータニオンに変換する
//////////////////////////////////////////////////////////////////
template <class E>
inline typename boost::enable_if<
    dimension_equal_to_c<E, 3>, quaternion<typename deduct1<E>::real_type> >::type
to_quaternion_eulerXYZ(vector_expression<E> const& e){
    typedef typename deduct1<E>::real_type real_type;
    typedef vector3<real_type> real_vector3;
    typedef quaternion<real_type> result_type;

    real_vector3 const theta = e * real_type(0.5);
    real_vector3 const s = nogara::expression::apply<real_type, real_type>(theta, &std::sin);
    real_vector3 const c = nogara::expression::apply<real_type, real_type>(theta, &std::cos);

    return result_type(c(0) * c(1) * c(2) - s(0) * s(1) * s(2),
                       s(0) * c(1) * c(2) + c(0) * s(1) * s(2),
                       c(0) * s(1) * c(2) - s(0) * c(1) * s(2),
                       c(0) * s(1) * s(2) + s(0) * s(1) * c(2));
}

//////////////////////////////////////////////////////////////////
//! @brief Y-X-Zの順に回転するオイラー角をクォータニオンに変換する
//////////////////////////////////////////////////////////////////
template <class E>
inline typename boost::enable_if<
    dimension_equal_to_c<E, 3>, quaternion<typename deduct1<E>::real_type> >::type
to_quaternion_eularYXZ(vector_expression<E> const& e){
    typedef typename deduct1<E>::real_type real_type;
    typedef vector3<real_type> real_vector3;
    typedef quaternion<real_type> result_type;

    real_vector3 const theta = e * real_type(0.5);
    real_vector3 const s = nogara::expression::apply<real_type, real_type>(theta, &std::sin);
    real_vector3 const c = nogara::expression::apply<real_type, real_type>(theta, &std::cos);

    return result_type(c(1) * c(0) * c(2) + s(1) * s(0) * s(2),
                       c(1) * s(0) * c(2) + s(1) * c(0) * s(2),
                       s(1) * c(0) * c(2) - c(1) * s(0) * s(2),
                       c(1) * c(0) * s(2) - s(1) * s(0) * c(2));

}

//////////////////////////////////////////////////////////////////
//! @brief X-Y-Zの順に回転するオイラー角をクォータニオンに変換する
//////////////////////////////////////////////////////////////////
template <class T1, class T2, class T3>
inline typename boost::enable_if<
    boost::mpl::and_<nogara::expression::is_scalar<T1>,
                     nogara::expression::is_scalar<T2>,
                     nogara::expression::is_scalar<T3> >,
    quaternion<typename deduct3<T1, T2, T3>::real_type> >::type
to_quaternion_eularXYZ(T1 const& x, T2 const& y, T3 const& z){
    return to_quaternion_eularXYZ(vector3<typename deduct3<T1, T2, T3>::real_type>(x, y, z));
}

//////////////////////////////////////////////////////////////////
//! @brief Y-X-Zの順に回転するオイラー角をクォータニオンに変換する
//////////////////////////////////////////////////////////////////
template <class T1, class T2, class T3>
inline typename boost::enable_if<
    boost::mpl::and_<nogara::expression::is_scalar<T1>,
                     nogara::expression::is_scalar<T2>,
                     nogara::expression::is_scalar<T3> >,
    quaternion<typename deduct3<T1, T2, T3>::real_type> >::type
to_quaternion_eulerYXZ(T1 const& x, T2 const& y, T3 const& z){
    return to_quaternion_eularYXZ(vector3<typename deduct3<T1, T2, T3>::real_type>(x, y, z));
}

/////////////////////////////////////////////////
//! @brief オイラー角からクォータニオンに変換する
//         X-Y-Z順のオイラー角変換を使用している
/////////////////////////////////////////////////
template <class E>
inline quaternion<typename deduct1<E>::real_type>
to_quaternion(vector_expression<E> const& e){
    return to_quaternion_eulerXYZ(e);
}

/////////////////////////////////////////////////
//! @brief オイラー角からクォータニオンに変換する
//         X-Y-Z順のオイラー角変換を使用している
/////////////////////////////////////////////////
template <class T1, class T2, class T3>
inline quaternion<typename deduct3<T1, T2, T3>::real_type>
to_quaternion(T1 const& x, T2 const& y, T3 const& z){
    return to_quaternion(vector3<typename deduct3<T1, T2, T3>::real_type>(x, y, z));
}

///////////////////////
//! @brief 球面線形補間
///////////////////////
template <class E1, class E2, typename T>
inline typename boost::enable_if<
    boost::mpl::and_<quaternion_same<E1, E2>, nogara::expression::is_scalar<T> >,
    quaternion<typename deduct2<E1, E2>::value_type> >::type
slerp(vector_expression<E1> const& from, vector_expression<E2> const& to, T const& t){
    typedef typename deduct2<E1, E2>::value_type value_type;
    typedef quaternion<value_type> result_type;

    if(t < 0){
        return from;
    }else if(t > 1){
        return to;
    }

    value_type const dot = nogara::dot(from, to);
    bool const is_minus = (dot < value_type());
    value_type const cos_omega = is_minus ? -dot : dot;
    result_type const tmp = nogara::ternary<result_type>(is_minus, -to, to);

    value_type tfrom = 1 - t;
    value_type tto   = t;
    if((1 - cos_omega) > std::numeric_limits<value_type>::epsilon()){
        value_type const sin_omega = std::sqrt(1 - std::pow(cos_omega, 2));
        value_type const omega     = std::atan2(sin_omega, cos_omega);
        value_type const inv_sin   = 1 / sin_omega;

        tfrom = std::sin(tfrom * omega) * inv_sin;
        tto   = std::sin(tto   * omega) * inv_sin;
    }

    return tfrom * from + tto * tmp;
}

/////////////////////////
//! @brief 球面四角形補間
/////////////////////////
template<class E1, class E2, class E3, class E4, typename T>
quaternion<typename deduct4<E1, E2, E3, E4>::value_type>
squad(vector_expression<E1> const &q1, vector_expression<E2> const &q2,
      vector_expression<E3> const &q3, vector_expression<E4> const &q4,
      T const& t)
{
    return slerp(slerp(q1, q2, t), slerp(q3, q4, t), 2 * t * (1 - t));
}

////////////////////////////////////////////////
//! @brief X軸回りに回転するクォータニオンを返す
////////////////////////////////////////////////
template<typename T>
inline typename boost::enable_if<
    nogara::expression::is_scalar<T>, quaternion<typename deduct1<T>::real_type> >::type
quaternion_rotateX(T const& theta){
    typedef typename deduct1<T>::real_type real_type;
    real_type const theta_half = theta * real_type(0.5);
    return quaternion<real_type>(std::cos(theta_half), std::sin(theta_half),
                                 real_type(),         real_type());
}

////////////////////////////////////////////////
//! @brief Y軸回りに回転するクォータニオンを返す
////////////////////////////////////////////////
template<typename T>
inline typename boost::enable_if<
    nogara::expression::is_scalar<T>, quaternion<typename deduct1<T>::real_type> >::type
quaternion_rotateY(T const& theta){
    typedef typename deduct1<T>::real_type real_type;
    real_type const theta_half = theta * real_type(0.5);
    return quaternion<real_type>(std::cos(theta_half), real_type(),
                                 std::sin(theta_half), real_type());
}

////////////////////////////////////////////////
//! @brief Z軸回りに回転するクォータニオンを返す
////////////////////////////////////////////////
template<typename T>
inline typename boost::enable_if<
    nogara::expression::is_scalar<T>, quaternion<typename deduct1<T>::real_type> >::type
quaternion_rotateZ(T const& theta){
    typedef typename deduct1<T>::real_type real_type;
    real_type const theta_half = theta * real_type(0.5);
    return quaternion<real_type>(std::cos(theta_half), real_type(0),
                                 real_type(0), std::sin(theta_half));
}

////////////////////////////////////////////////////////////
//! @brief 回転軸axis周りにtheta回転するクォータニオンを返す
////////////////////////////////////////////////////////////
template<class E, typename T>
inline typename boost::enable_if<
    boost::mpl::and_<dimension_equal_to_c<E, 3>, nogara::expression::is_scalar<T> >,
    quaternion<typename deduct2<E, T>::real_type> >::type
quaternion_rotate_axis(vector_expression<E> const &axis, T const& theta){
    typedef typename deduct1<E>::real_type real_type;
    //assert(std::abs(length(axis) - real_type(1)) < std::numeric_limits<real_type>::epsilon());
    real_type theta_half = theta * real_type(0.5);
    real_type sin_half = std::sin(theta_half);
    return quaternion<real_type>(std::cos(theta_half), axis * sin_half);
}

///////////////////////////
//! @brief 回転軸を算出する
///////////////////////////
template<class E>
inline typename boost::enable_if<is_quaternion<E>, vector3<typename E::value_type> >::type
get_rotation_axis(vector_expression<E> const& e){
    typedef typename E::value_type value_type;
    value_type const w = get<0>(e);
    value_type const sin_theta_half_sq = value_type(1) - w * w;
    if(sin_theta_half_sq <= value_type()){
        return vector3<value_type>::unit_x;
    }

    value_type const sin_theta = value_type(1) / std::sqrt(sin_theta_half_sq);
    return vector3<value_type>(minor<0>(e) * sin_theta);
}

/////////////////////////////
//! @brief 回転角度を算出する
/////////////////////////////
template<class E>
inline typename boost::enable_if<is_quaternion<E>, typename E::value_type>::type
get_rotation_angle(vector_expression<E> const& e){
    typedef typename E::value_type value_type;
    value_type const w = get<0>(e);
    value_type const theta_half = (w <= value_type(-1)) ? NG_PI :
                                  (w >= value_type(1)) ? value_type(0) :
                                  std::acos(w);
    return 2 * theta_half;
}

/////////////////////////
//! @brief ピッチ角の取得
/////////////////////////
template<class E>
inline typename boost::enable_if<is_quaternion<E>, typename E::value_type>::type
get_pitch(vector_expression<E> const& e){
    typedef typename E::value_type value_type;
    return std::atan2(2 * nogara::sum(multiply(swizzle<swizzle_xz>(e), swizzle<swizzle_yw>(e))),
                      1 - 2 * nogara::sum(nogara::pow(swizzle<swizzle_yz>(e), 2)));
}

///////////////////////
//! @brief ヨー角の取得
///////////////////////
template<class E>
inline typename boost::enable_if<is_quaternion<E>, typename E::value_type>::type
get_yaw(vector_expression<E> const& e){
    return std::asin(2 * (get<0>(e) * get<2>(e) - get<3>(e) * get<1>(e)));
}

/////////////////////////
//! @brief ロール角の取得
/////////////////////////
template<class E>
inline typename boost::enable_if<is_quaternion<E>, typename E::value_type>::type
get_roll(vector_expression<E> const& e){
    typedef typename E::value_type value_type;
    return std::atan2(2 * (get<0>(e) * get<3>(e) - get<1>(e) * get<2>(e)),
                      1 - 2 * nogara::sum(nogara::pow(swizzle<swizzle_zw>(e), 2)));
}

///////////////////////////////////////////////
//! @brief クォータニオンからオイラー角への変換
///////////////////////////////////////////////
template<class E>
inline typename boost::enable_if<is_quaternion<E>, vector3<typename E::value_type> >::type
to_euler(vector_expression<E> const& e){
    return vector3<typename E::value_type>(nogara::expression::get_roll(e),
                                           nogara::expression::get_pitch(e),
                                           nogara::expression::get_yaw(e));
}

///////////////////////////////
//! @brief クォータニオンの冪乗
///////////////////////////////
template<class E, typename T>
inline typename boost::enable_if<
    boost::mpl::and_<is_quaternion<E>, nogara::expression::is_scalar<T> >,
    quaternion<typename E::value_type> >::type
pow(vector_expression<E> const &q, T const& exp){
    typedef typename E::value_type value_type;
    typedef quaternion<value_type> result_type;

    if(std::abs(get<0>(q)) < value_type(1.1)){
        return q;
    }

    value_type const alpha = std::acos(get<0>(q));
    value_type const newAlpha = alpha * exp;
    value_type const mult = std::sin(newAlpha) / std::sin(alpha);
    return result_type(std::cos(newAlpha), nogara::minor<0>(q) * mult);
}

///////////////////////////////
//! @brief クォータニオンの対数
///////////////////////////////
template<class E>
inline typename boost::enable_if<is_quaternion<E>, quaternion<typename E::value_type> >::type
log(vector_expression<E> const &q){
    typedef typename E::value_type value_type;
    typedef quaternion<value_type> result_type;

    value_type const alpha = std::acos(get<0>(q));
    if(alpha > value_type(0) || alpha < value_type(0)){
        value_type const aDivSin = alpha / std::sin(alpha);
        return result_type(0, aDivSin * nogara::minor<0>(q));
    }

    return result_type::zero;
}

__NOGARA_EXPRESSION_END

__NOGARA_BEGIN
using expression::inverse;
using expression::pow;
using expression::log;
using expression::slerp;
using expression::squad;
using expression::get_yaw;
using expression::get_roll;
using expression::get_pitch;
using expression::get_rotation_angle;

using expression::to_euler;
using expression::to_quaternion;
using expression::to_quaternion_eulerXYZ;
using expression::to_quaternion_eulerYXZ;
using expression::quaternion_rotate_axis;
using expression::quaternion_rotateX;
using expression::quaternion_rotateY;
using expression::quaternion_rotateZ;
__NOGARA_END

#endif
