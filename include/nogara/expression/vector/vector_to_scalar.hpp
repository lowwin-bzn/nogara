#ifndef NOGARA_EXPRESSION_VECTOR_TO_SCALAR_HPP
#define NOGARA_EXPRESSION_VECTOR_TO_SCALAR_HPP

///////////////////////////////////////////////////////
//! @file nogara/expression/vector/vector_to_scalar.hpp
//! @brief ベクトルを演算し、スカラにするクラス
///////////////////////////////////////////////////////

#include <numeric>
#include <nogara/type_traits/deduct.hpp>
#include <nogara/expression/expression.hpp>
#include <nogara/expression/vector/get.hpp>
#include <nogara/expression/vector/reverse.hpp>
#include <nogara/expression/vector/minor.hpp>

__NOGARA_EXPRESSION_BEGIN

/////////////////////////////////////////////////////////////////
//! @brief 二項のベクトルからスカラを演算するクラスの基礎
//!        二項演算式は基本vector_binary_to_scalar_baseを継承する
//!        継承先クラスはT apply() const という
//!        メンバメソッドを持つ必要がある
////////////////////////////////////////////////////////////////
template<class E1, class E2, class Derived>
class vector_binary_to_scalar_base : public vector_expression<Derived>{
public:
    typedef typename deduct2<E1, E2>::value_type value_type;
    typedef vector_expression<E1> const&        argment1_type;
    typedef vector_expression<E2> const&        argment2_type;
    typedef boost::mpl::size_t<1>               Dimension;

    using vector_expression<Derived>::operator();
    operator value_type() const{return operator()().apply();}
protected:
    vector_binary_to_scalar_base(argment1_type e1, argment2_type e2):left(e1), right(e2){}

protected:
    argment1_type left;
    argment2_type right;
};

///////////////////////////////////////////////////
//! @brief 二項のベクトルからスカラを演算するクラス
//!        Fは static T apply(E1, E2)という
//!        staticメンバメソッドを持つ必要がある
///////////////////////////////////////////////////
template<class E1, class E2, class F>
class vector_binary_to_scalar :
    public vector_binary_to_scalar_base<E1, E2, vector_binary_to_scalar<E1, E2, F> >
{
    typedef vector_binary_to_scalar<E1, E2, F>              self_type;
    typedef vector_binary_to_scalar_base<E1, E2, self_type> base_type;
public:
    vector_binary_to_scalar(typename base_type::argment1_type e1,
                            typename base_type::argment2_type e2):base_type(e1, e2){}

    typename base_type::value_type apply() const{
        return F::apply(base_type::left, base_type::right);
    }
};

/////////////////////////////////////////////////////////////
//! @brief  ベクトルを先頭から初期値を設定して関数fで畳み込む
/////////////////////////////////////////////////////////////
template<class F, class E, class T>
inline T fold_left(vector_expression<E> const& e, T result, F f){
    return std::accumulate(e.begin(), e.end(), result, f);
}

/////////////////////////////////////////////////////////////
//! @brief  ベクトルを先頭から初期値を設定して関数fで畳み込む
/////////////////////////////////////////////////////////////
template<class R, class T1, class T2, class E, class T>
inline T fold_left(vector_expression<E> const& e, T const& t, R(*f)(T1, T2)){
    return fold_left<R(*)(T1, T2)>(e, t, f);
}

/////////////////////////////////////////////////////////////
//! @brief  ベクトルを末尾から初期値を設定して関数fで畳み込む
/////////////////////////////////////////////////////////////
template<class F, class E, class T>
inline T fold_right(vector_expression<E> const& e, T const& t, F f){
    return fold_left(nogara::expression::reverse(e), t, f);
}

/////////////////////////////////////////////////////////////
//! @brief  ベクトルを末尾から初期値を設定して関数fで畳み込む
/////////////////////////////////////////////////////////////
template<class R, class T1, class T2, class E, class T>
inline T fold_right(vector_expression<E> const& e, T const& t, R(*f)(T1, T2)){
    return R(fold_right<R(*)(T1, T2)>(e, t, f));
}

///////////////////////////////////////////////////////////////////////////////////
//! @brief  ベクトルを先頭から初期値を設定して関数fで畳み込む(実体はfold_left)
///////////////////////////////////////////////////////////////////////////////////
template<class F, class E, class T>
inline T fold(vector_expression<E> const& e, T const& t, F f){
    return fold_left(e, t, f);
}

///////////////////////////////////////////////////////////////////////////////////
//! @brief  ベクトルを先頭から初期値を設定して関数fで畳み込む(実体はfold_left)
///////////////////////////////////////////////////////////////////////////////////
template<class R, class T1, class T2, class E, class T>
inline T fold(vector_expression<E> const& e, T const& t, R(*f)(T1, T2)){
    return fold<R(*)(T1, T2)>(e, t, f);
}


///////////////////////////////////////////////////////////
//! @brief  ベクトルの先頭から順に関数fで畳み込む
///////////////////////////////////////////////////////////
template<class F, class E>
inline typename E::value_type reduce_left(vector_expression<E> const& e, F f){
    return fold_left(nogara::expression::minor<0>(e), nogara::expression::get<0>(e), f);
}

///////////////////////////////////////////////////////////
//! @brief  ベクトルの先頭から順に関数fで畳み込む
///////////////////////////////////////////////////////////
template<class R, class T1, class T2, class E>
inline typename E::value_type reduce_left(vector_expression<E> const& e, R(*f)(T1, T2)){
    return reduce_left<R(*)(T1, T2)>(e, f);
}

///////////////////////////////////////////////////////////
//! @brief  ベクトルの末尾から順に関数fで畳み込む
///////////////////////////////////////////////////////////
template<class F, class E>
inline typename E::value_type reduce_right(vector_expression<E> const& e, F f){
    typedef boost::mpl::size_t<get_dimension<E>::value - 1> last;
    return fold_right(nogara::expression::minor<last::value>(e),
                      nogara::expression::get<last::value>(e), f);
}

///////////////////////////////////////////////////////////
//! @brief  ベクトルの末尾から順に関数fで畳み込む
///////////////////////////////////////////////////////////
template<class R, class T1, class T2, class E>
inline typename E::value_type reduce_right(vector_expression<E> const& e, R(*f)(T1, T2)){
    return reduce_right<R(*)(T1, T2)>(e, f);
}

////////////////////////////////////////////////////////////////////
//! @brief  ベクトルの先頭から順に関数fで畳み込む(実体はreduce_left)
////////////////////////////////////////////////////////////////////
template<class F, class E>
inline typename E::value_type reduce(vector_expression<E> const& e, F f){
    return reduce_left(e, f);
}

////////////////////////////////////////////////////////////////////
//! @brief  ベクトルの先頭から順に関数fで畳み込む(実体はreduce_left)
////////////////////////////////////////////////////////////////////
template<class R, class T1, class T2, class E>
inline typename E::value_type reduce(vector_expression<E> const& e, R(*f)(T1, T2)){
    return reduce_left<R(*)(T1, T2)>(e, f);
}

__NOGARA_EXPRESSION_END

__NOGARA_BEGIN
using expression::fold;
using expression::fold_left;
using expression::fold_right;
using expression::reduce;
using expression::reduce_left;
using expression::reduce_right;
__NOGARA_END

#endif
