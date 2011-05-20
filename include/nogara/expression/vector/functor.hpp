#ifndef NOGARA_EXPRESSION_VECTOR_FUNCTOR_HPP
#define NOGARA_EXPRESSION_VECTOR_FUNCTOR_HPP

///////////////////////////////////////////////
//! @file  nogara/expression/vector/functor.hpp
//! @brief ベクトルで使用する関数オブジェクト群
///////////////////////////////////////////////

#include <nogara/expression/vector/binary_expression.hpp>
#include <nogara/expression/vector/unary_expression.hpp>
#include <nogara/expression/vector/get.hpp>
#include <nogara/expression/scalar/functor.hpp>
#include <nogara/expression/scalar/function.hpp>

__NOGARA_EXPRESSION_BEGIN

/////////////////////////////////////////
//! @brief 線形補間を行う関数オブジェクト
/////////////////////////////////////////
template<class T0>
class vector_lerp_functor{
public:
    vector_lerp_functor(T0 const &v):t(v){}
    template<class T1, class T2>
    typename deduct3<T0, T1, T2>::value_type operator()(T1 const& left, T2 const& right) const {
        return nogara::expression::lerp(left, right, t);
    }
private:
    T0 const t;
};

///////////////////////////////////////////////
//! @brief ベクトルの冪乗を行う関数オブジェクト
///////////////////////////////////////////////
template<class T>
class pow_functor{
public:
    pow_functor(T const &v):t(v){}
    template<class U>
    U operator()(U const& value) const {
        using std::pow; return pow(value, t);
    }
private:
    T const t;
};


////////////////////////////////////////////////////
//! @brief 2次元ベクトルの外積を行う関数オブジェクト
////////////////////////////////////////////////////
template<class E1, class E2>
struct cross2_functor{
    typedef typename boost::enable_if<
        same_dimension_equal_to<E1, E2, 2>,
        typename deduct2<E1, E2>::value_type>::type value_type;

    static value_type apply(vector_expression<E1> const& e1,
                            vector_expression<E2> const& e2)
    {
        return get<0>(e1) * get<1>(e2) - get<1>(e1) * get<0>(e2);
    }
};

/////////////////////////////////////////////////////////////////////
//  3次元ベクトル外積の中で2次元ベクトル外積を使うので前方宣言
/////////////////////////////////////////////////////////////////////
template<class L, class R, std::size_t N>
class vector_cross;

template<typename E1, class E2>
inline typename boost::enable_if<
    same_dimension<E1, E2>, vector_cross<E1, E2, get_dimension<E1>::value> >::type
cross(vector_expression<E1> const&, vector_expression<E2> const&);

////////////////////////////////////////////////////
//! @brief 外積関数オブジェクトの2次元ベクトル特殊化
////////////////////////////////////////////////////
template<class L, class R>
class vector_cross<L, R, 2> : public vector_binary_to_scalar<L, R, cross2_functor<L, R> >{
    typedef vector_cross<L, R, 2>                  self_type;
    typedef cross2_functor<L, R>                   functor;
    typedef vector_binary_to_scalar<L, R, functor> base_type;
public:
    vector_cross(typename base_type::argment1_type l,
                 typename base_type::argment2_type r):base_type(l, r){}
};

////////////////////////////////////////////////////
//! @brief 外積関数オブジェクトの3次元ベクトル特殊化
////////////////////////////////////////////////////
template<class L, class R>
class vector_cross<L, R, 3> : public vector_binary_base<L, R, vector_cross<L, R, 3> >{
    typedef vector_cross<L, R, 3>                self_type;
    typedef vector_binary_base<L, R, self_type>  base_type;

    template<int N>
    typename base_type::value_type apply() const {
        return apply(boost::mpl::int_<N>());
    }

    typename base_type::value_type apply(boost::mpl::int_<0>) const {
        return cross(minor<0>(base_type::left), minor<0>(base_type::right));
    }

    typename base_type::value_type apply(boost::mpl::int_<1>) const {
        return cross(minor<1>(base_type::right), minor<1>(base_type::left));
    }

    typename base_type::value_type apply(boost::mpl::int_<2>) const {
        return cross(minor<2>(base_type::left), minor<2>(base_type::right));
    }

    //範囲外を指定されるとエラー
    template<int N>
    typename base_type::value_type apply(boost::mpl::int_<N>) const {
        assert(false && "vector3 out of range");
        return typename base_type::value_type();
    }

public:
    vector_cross(typename base_type::argment1_type l,
                 typename base_type::argment2_type r):base_type(l, r){}

    typename base_type::value_type apply(unsigned i) const {
        switch(i){
            case 0: return apply<0>();
            case 1: return apply<1>();
            case 2: return apply<2>();
        }
        return apply<-1>();
    }
};

__NOGARA_EXPRESSION_END

#endif
