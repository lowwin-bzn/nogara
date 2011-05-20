#ifndef NOGARA_EXPRESSION_SCALAR_FUNCTOR_HPP
#define NOGARA_EXPRESSION_SCALAR_FUNCTOR_HPP

///////////////////////////////////////////////////////////////
//! @file nogara/expression/scalar/functor.hpp
//! @brief ベクトル、行列の式クラスに使用する関数オブジェクト群
///////////////////////////////////////////////////////////////

#include <cmath>
#include <nogara/expression/define.hpp>
#include <nogara/type_traits/deduct.hpp>

__NOGARA_EXPRESSION_BEGIN

namespace invisible{
template<class L, class R>
struct scalar_binary_functor_c{
    typedef L const& left_arg;
    typedef R const& right_arg;
    typedef typename deduct2<L, R>::value_type value_type;
    typedef value_type result_type;
};

template<class L, class R>
struct scalar_binary_functor_impl :
    public scalar_binary_functor_c<typename L::type, typename R::type>{};

template<class T>
struct scalar_unary_functor_c{
    typedef T          value_type;
    typedef T const&   argment;
    typedef value_type result_type;
};

template<class T>
struct scalar_unary_functor_impl : public scalar_unary_functor_c<typename T::type>{};

}

/////////////////////////////////////////////////////////////
//! @brief 二項演算の戻り値型推論や引数の参照を定義するクラス
/////////////////////////////////////////////////////////////
template<class L, class R>
struct scalar_binary_functor : public invisible::scalar_binary_functor_impl<
    wrrap_get_value_type<L>, wrrap_get_value_type<R> >{};

/////////////////////////////////////////////////////////////
//! @brief 単項演算の戻り値型推論や引数の参照を定義するクラス
/////////////////////////////////////////////////////////////
template<class T>
struct scalar_unary_functor :
    public invisible::scalar_unary_functor_impl<wrrap_get_value_type<T> >{};

template<class L, class R, class F, F function>
struct binary_function_binder;

template<class L, class R, class F, class A0, class A1, F (*function)(A0, A1)>
struct binary_function_binder<L, R, F (*)(A0, A1), function>{
    typedef typename scalar_binary_functor<L, R>::left_arg    left_arg;
    typedef typename scalar_binary_functor<L, R>::right_arg   right_arg;
    typedef typename scalar_binary_functor<L, R>::value_type  value_type;
    typedef typename scalar_binary_functor<L, R>::result_type result_type;

    static result_type apply(left_arg left, right_arg right){
        return (*function)(left, right);
    }
};

template<class T, class F, F function>
struct unary_function_binder;

template<class T, class F, class A0, F (*function)(A0)>
struct unary_function_binder<T, F (*)(A0), function>{
    typedef typename scalar_unary_functor<T>::argment     argment;
    typedef typename scalar_unary_functor<T>::value_type   value_type;
    typedef typename scalar_unary_functor<T>::result_type result_type;
    static result_type apply(argment val){
        return (*function)(val);
    }
};


#define DEFINE_BINARY_FUNCTOR(Name, Op)                                    \
template <class L, class R>                                                \
struct Name{                                                               \
    typedef typename scalar_binary_functor<L, R>::left_arg    left_arg;    \
    typedef typename scalar_binary_functor<L, R>::right_arg   right_arg;   \
    typedef typename scalar_binary_functor<L, R>::value_type  value_type;  \
    typedef typename scalar_binary_functor<L, R>::result_type result_type; \
    static result_type apply(left_arg l, right_arg r){                     \
        return l Op r;                                                     \
    }                                                                      \
};                                                                         \

DEFINE_BINARY_FUNCTOR(scalar_add, +)
DEFINE_BINARY_FUNCTOR(scalar_sub, -)
DEFINE_BINARY_FUNCTOR(scalar_mul, *)
DEFINE_BINARY_FUNCTOR(scalar_div, /)
DEFINE_BINARY_FUNCTOR(scalar_mod, %)

////////////////////////////////////
//! @brief +演算子の関数オブジェクト
////////////////////////////////////
template <class T>
struct scalar_identity{
    typedef typename scalar_unary_functor<T>::argment     argment;
    typedef typename scalar_unary_functor<T>::result_type result_type;
    static result_type apply(argment val){
        return val;
    }
};

////////////////////////////////////
//! @brief -演算子の関数オブジェクト
////////////////////////////////////
template <class T>
struct scalar_negate{
    typedef typename scalar_unary_functor<T>::argment     argment;
    typedef typename scalar_unary_functor<T>::result_type result_type;
    static result_type apply(argment val){
        return -val;
    }
};

////////////////////////////////////
//! @brief abs関数の関数オブジェクト
////////////////////////////////////
template <class T>
struct scalar_abs{
    typedef typename scalar_unary_functor<T>::argment     argment;
    typedef typename scalar_unary_functor<T>::result_type result_type;
    static result_type apply(argment val){
        using std::abs;
        return abs(val);
    }
};

////////////////////////////////////
//! @brief 逆数の関数オブジェクト
////////////////////////////////////
template <class T>
struct scalar_inverse{
    typedef typename scalar_unary_functor<T>::argment argment;
    typedef typename deduct1<T>::real_type            result_type;
    static result_type apply(argment val){
        return result_type(1) / val;
    }
};


__NOGARA_EXPRESSION_END

#endif
