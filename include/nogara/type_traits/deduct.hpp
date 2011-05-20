#ifndef NOGARA_DEDUCT_HPP
#define NOGARA_DEDUCT_HPP

#include <boost/mpl/int.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/less_equal.hpp>
#include <boost/mpl/greater.hpp>
#include <boost/type_traits.hpp>
#include <boost/numeric/ublas/traits.hpp>

#include <nogara/type_traits/value_type_traits.hpp>

///////////////////////////////////////////////////////////////////////////////////
//! @file nogara/type_traits/deduct.hpp
//! @brief 式の型推論を行うメタ関数
///////////////////////////////////////////////////////////////////////////////////

__NOGARA_BEGIN
//////////////////////////////////////////////////////////
//! @brief 右辺、もしくは左辺がfloat型か否かを返すメタ関数
//////////////////////////////////////////////////////////
template<typename T1, typename T2>
struct either_is_float : public boost::mpl::or_<
    boost::is_floating_point<T1>, boost::is_floating_point<T2> >{};

template<typename T> struct float_priority;
template<> struct float_priority<float>       : boost::mpl::int_<1>{};
template<> struct float_priority<double>      : boost::mpl::int_<2>{};
template<> struct float_priority<long double> : boost::mpl::int_<3>{};

template<class T>
struct lazy_float_priority : float_priority<typename T::type>{};

template<typename T>
struct deduct_to_real{
    typedef typename boost::mpl::eval_if<
        boost::is_floating_point<T>,
        boost::mpl::identity<T>,
        boost::mpl::if_<
            boost::mpl::less_equal<boost::mpl::sizeof_<T>, boost::mpl::sizeof_<float> >,
            float, double> >::type type;
};

/////////////////////////////////////////////////////
//! @brief 単項から計算結果の型を推論する
/////////////////////////////////////////////////////
template<class T1>
struct deduct1{
    typedef typename wrrap_get_value_type<T1>::type value_type;
    typedef typename deduct_to_real<value_type>::type real_type;
};

/////////////////////////////////////////
//! @brief 二項から計算結果の型を推論する
/////////////////////////////////////////
template<class T1, class T2>
struct deduct2{
private:
    typedef typename wrrap_get_value_type<T1>::type _1;
    typedef typename wrrap_get_value_type<T2>::type _2;
    typedef boost::numeric::ublas::promote_traits<_1, _2> promote;
public:
    typedef typename promote::promote_type value_type;
    typedef typename deduct_to_real<value_type>::type real_type;
};

/////////////////////////////////////////
//! @brief 三項から計算結果の型を推論する
/////////////////////////////////////////
template<class T1, class T2, class T3>
struct deduct3{
    typedef typename deduct2<deduct1<T1>, deduct2<T2, T3> >::value_type value_type;
    typedef typename deduct_to_real<value_type>::type        real_type;
};

/////////////////////////////////////////
//! @brief 四項から計算結果の型を推論する
/////////////////////////////////////////
template<class T1, class T2, class T3, class T4>
struct deduct4{
public:
    typedef typename deduct2<deduct2<T1, T2>, deduct2<T3, T4> >::value_type value_type;
    typedef typename deduct_to_real<value_type>::type            real_type;
};

/////////////////////////////////////////
//! @brief 五項から計算結果の型を推論する
/////////////////////////////////////////
template<class T1, class T2, class T3, class T4, class T5>
struct deduct5{
    typedef typename deduct2<deduct2<T1, T2>, deduct3<T3, T4, T5> >::value_type value_type;
    typedef typename deduct_to_real<value_type>::type real_type;
};


__NOGARA_END

#endif
