#ifndef NOGARA_EXPRESSION_VECTOR_SWIZZLE_HPP
#define NOGARA_EXPRESSION_VECTOR_SWIZZLE_HPP

///////////////////////////////////////////////
//! @file  nogara/expression/vector/swizzle.hpp
//! @brief 要素参照入れ替えベクトル
///////////////////////////////////////////////


#include <boost/mpl/size_t.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/vector/vector10_c.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/at.hpp>

#include <nogara/expression/expression.hpp>
#include <nogara/expression/vector/traits.hpp>

__NOGARA_EXPRESSION_BEGIN

namespace invisible{
    template<typename item, bool is_void>
    struct swizzle_get_index_impl{
        typedef boost::mpl::size_t<0xFFFFFFFF> type;
    };

    template<typename item>
    struct swizzle_get_index_impl<item, false>{
        typedef item type;
    };

    template<typename item>
    struct swizzle_get_index :
        swizzle_get_index_impl<item, boost::mpl::is_void_<item>::value>::type{};


    template<class Seq>
    struct swizzle_indices{
        static std::size_t const limit_indices_size = 16;
        static std::size_t const indices[limit_indices_size];
    };


    template<class Seq>
    std::size_t const swizzle_indices<Seq>::indices[limit_indices_size] = {
        invisible::swizzle_get_index<typename boost::mpl::at_c<Seq,  0>::type>::value,
        invisible::swizzle_get_index<typename boost::mpl::at_c<Seq,  1>::type>::value,
        invisible::swizzle_get_index<typename boost::mpl::at_c<Seq,  2>::type>::value,
        invisible::swizzle_get_index<typename boost::mpl::at_c<Seq,  3>::type>::value,
        invisible::swizzle_get_index<typename boost::mpl::at_c<Seq,  4>::type>::value,
        invisible::swizzle_get_index<typename boost::mpl::at_c<Seq,  5>::type>::value,
        invisible::swizzle_get_index<typename boost::mpl::at_c<Seq,  6>::type>::value,
        invisible::swizzle_get_index<typename boost::mpl::at_c<Seq,  7>::type>::value,
        invisible::swizzle_get_index<typename boost::mpl::at_c<Seq,  8>::type>::value,
        invisible::swizzle_get_index<typename boost::mpl::at_c<Seq,  9>::type>::value,
        invisible::swizzle_get_index<typename boost::mpl::at_c<Seq, 10>::type>::value,
        invisible::swizzle_get_index<typename boost::mpl::at_c<Seq, 11>::type>::value,
        invisible::swizzle_get_index<typename boost::mpl::at_c<Seq, 12>::type>::value,
        invisible::swizzle_get_index<typename boost::mpl::at_c<Seq, 13>::type>::value,
        invisible::swizzle_get_index<typename boost::mpl::at_c<Seq, 14>::type>::value,
        invisible::swizzle_get_index<typename boost::mpl::at_c<Seq, 15>::type>::value,
    };
}

template<class E, class Seq>
class ref_swizzle_vector : public vector_expression<ref_swizzle_vector<E, Seq> >{
    typedef invisible::swizzle_indices<Seq> indices_type;
    typedef ref_swizzle_vector<E, Seq>      self_type;
public:
    typedef typename E::value_type      value_type;
    typedef typename E::const_reference const_reference;
    typedef typename E::reference       reference;
    typedef vector_expression<E>&       argment_type;
    typedef boost::mpl::size<Seq>       Dimension;

    ref_swizzle_vector(argment_type e):value(e){}

    using vector_expression<self_type>::operator();
    reference operator ()(unsigned i){
        return const_cast<E&>(value())(indices_type::indices[i]);
    }

    value_type operator ()(unsigned i) const {
        return value()(indices_type::indices[i]);
    }

    template<class EA>
    self_type& operator =(vector_expression<EA> const& e){
        for(std::size_t i = 0; i < get_dimension<EA>::value; ++i){
            const_cast<E&>(value())(indices_type::indices[i]) = e()(i);
        }
        return *this;
    }

private:
    argment_type value;
};

template<class E, class Seq>
class swizzle_vector : public vector_expression<swizzle_vector<E, Seq> >{
    typedef invisible::swizzle_indices<Seq> indices_type;
    typedef swizzle_vector<E, Seq> self_type;
public:
    typedef typename E::value_type      value_type;
    typedef typename E::const_reference const_reference;
    typedef value_type                  reference;
    typedef vector_expression<E> const& argment_type;
    typedef boost::mpl::size<Seq>       Dimension;

    swizzle_vector(argment_type e):value(e){}

    using vector_expression<self_type>::operator();
    reference operator ()(unsigned i) const {
        return value()(indices_type::indices[i]);
    }

private:
    argment_type value;
};

template<class Seq, class E>
inline typename boost::mpl::if_<
    boost::mpl::and_<result_is_reference<E>, boost::mpl::not_<boost::is_const<E> > >,
    ref_swizzle_vector<E, Seq>, swizzle_vector<E, Seq> >::type
swizzle(vector_expression<E>& e){
    typedef typename boost::mpl::if_<
    boost::mpl::and_<result_is_reference<E>, boost::mpl::not_<boost::is_const<E> > >,
        ref_swizzle_vector<E, Seq>, swizzle_vector<E, Seq> >::type result;
    return result(e);
}

template<class Seq, class E>
inline swizzle_vector<E, Seq> swizzle(vector_expression<E> const& e){
    return swizzle_vector<E, Seq>(e);
}


//! swizzle2

typedef boost::mpl::vector2_c<std::size_t, 0, 0> swizzle_xx;
typedef boost::mpl::vector2_c<std::size_t, 0, 1> swizzle_xy;
typedef boost::mpl::vector2_c<std::size_t, 0, 2> swizzle_xz;
typedef boost::mpl::vector2_c<std::size_t, 0, 3> swizzle_xw;
typedef boost::mpl::vector2_c<std::size_t, 1, 0> swizzle_yx;
typedef boost::mpl::vector2_c<std::size_t, 1, 1> swizzle_yy;
typedef boost::mpl::vector2_c<std::size_t, 1, 2> swizzle_yz;
typedef boost::mpl::vector2_c<std::size_t, 1, 3> swizzle_yw;
typedef boost::mpl::vector2_c<std::size_t, 2, 0> swizzle_zx;
typedef boost::mpl::vector2_c<std::size_t, 2, 1> swizzle_zy;
typedef boost::mpl::vector2_c<std::size_t, 2, 2> swizzle_zz;
typedef boost::mpl::vector2_c<std::size_t, 2, 3> swizzle_zw;
typedef boost::mpl::vector2_c<std::size_t, 3, 0> swizzle_wx;
typedef boost::mpl::vector2_c<std::size_t, 3, 1> swizzle_wy;
typedef boost::mpl::vector2_c<std::size_t, 3, 2> swizzle_wz;
typedef boost::mpl::vector2_c<std::size_t, 3, 3> swizzle_ww;


//! swizzle3

typedef boost::mpl::vector3_c<std::size_t, 0, 0, 0> swizzle_xxx;
typedef boost::mpl::vector3_c<std::size_t, 0, 0, 1> swizzle_xxy;
typedef boost::mpl::vector3_c<std::size_t, 0, 0, 2> swizzle_xxz;
typedef boost::mpl::vector3_c<std::size_t, 0, 0, 3> swizzle_xxw;
typedef boost::mpl::vector3_c<std::size_t, 0, 1, 0> swizzle_xyx;
typedef boost::mpl::vector3_c<std::size_t, 0, 1, 1> swizzle_xyy;
typedef boost::mpl::vector3_c<std::size_t, 0, 1, 2> swizzle_xyz;
typedef boost::mpl::vector3_c<std::size_t, 0, 1, 3> swizzle_xyw;
typedef boost::mpl::vector3_c<std::size_t, 0, 2, 0> swizzle_xzx;
typedef boost::mpl::vector3_c<std::size_t, 0, 2, 1> swizzle_xzy;
typedef boost::mpl::vector3_c<std::size_t, 0, 2, 2> swizzle_xzz;
typedef boost::mpl::vector3_c<std::size_t, 0, 2, 3> swizzle_xzw;
typedef boost::mpl::vector3_c<std::size_t, 0, 3, 0> swizzle_xwx;
typedef boost::mpl::vector3_c<std::size_t, 0, 3, 1> swizzle_xwy;
typedef boost::mpl::vector3_c<std::size_t, 0, 3, 2> swizzle_xwz;
typedef boost::mpl::vector3_c<std::size_t, 0, 3, 3> swizzle_xww;

typedef boost::mpl::vector3_c<std::size_t, 1, 0, 0> swizzle_yxx;
typedef boost::mpl::vector3_c<std::size_t, 1, 0, 1> swizzle_yxy;
typedef boost::mpl::vector3_c<std::size_t, 1, 0, 2> swizzle_yxz;
typedef boost::mpl::vector3_c<std::size_t, 1, 0, 3> swizzle_yxw;
typedef boost::mpl::vector3_c<std::size_t, 1, 1, 0> swizzle_yyx;
typedef boost::mpl::vector3_c<std::size_t, 1, 1, 1> swizzle_yyy;
typedef boost::mpl::vector3_c<std::size_t, 1, 1, 2> swizzle_yyz;
typedef boost::mpl::vector3_c<std::size_t, 1, 1, 3> swizzle_yyw;
typedef boost::mpl::vector3_c<std::size_t, 1, 2, 0> swizzle_yzx;
typedef boost::mpl::vector3_c<std::size_t, 1, 2, 1> swizzle_yzy;
typedef boost::mpl::vector3_c<std::size_t, 1, 2, 2> swizzle_yzz;
typedef boost::mpl::vector3_c<std::size_t, 1, 2, 3> swizzle_yzw;
typedef boost::mpl::vector3_c<std::size_t, 1, 3, 0> swizzle_ywx;
typedef boost::mpl::vector3_c<std::size_t, 1, 3, 1> swizzle_ywy;
typedef boost::mpl::vector3_c<std::size_t, 1, 3, 2> swizzle_ywz;
typedef boost::mpl::vector3_c<std::size_t, 1, 3, 3> swizzle_yww;

typedef boost::mpl::vector3_c<std::size_t, 2, 0, 0> swizzle_zxx;
typedef boost::mpl::vector3_c<std::size_t, 2, 0, 1> swizzle_zxy;
typedef boost::mpl::vector3_c<std::size_t, 2, 0, 2> swizzle_zxz;
typedef boost::mpl::vector3_c<std::size_t, 2, 0, 3> swizzle_zxw;
typedef boost::mpl::vector3_c<std::size_t, 2, 1, 0> swizzle_zyx;
typedef boost::mpl::vector3_c<std::size_t, 2, 1, 1> swizzle_zyy;
typedef boost::mpl::vector3_c<std::size_t, 2, 1, 2> swizzle_zyz;
typedef boost::mpl::vector3_c<std::size_t, 2, 1, 3> swizzle_zyw;
typedef boost::mpl::vector3_c<std::size_t, 2, 2, 0> swizzle_zzx;
typedef boost::mpl::vector3_c<std::size_t, 2, 2, 1> swizzle_zzy;
typedef boost::mpl::vector3_c<std::size_t, 2, 2, 2> swizzle_zzz;
typedef boost::mpl::vector3_c<std::size_t, 2, 2, 3> swizzle_zzw;
typedef boost::mpl::vector3_c<std::size_t, 2, 3, 0> swizzle_zwx;
typedef boost::mpl::vector3_c<std::size_t, 2, 3, 1> swizzle_zwy;
typedef boost::mpl::vector3_c<std::size_t, 2, 3, 2> swizzle_zwz;
typedef boost::mpl::vector3_c<std::size_t, 2, 3, 3> swizzle_zww;

typedef boost::mpl::vector3_c<std::size_t, 3, 0, 0> swizzle_wxx;
typedef boost::mpl::vector3_c<std::size_t, 3, 0, 1> swizzle_wxy;
typedef boost::mpl::vector3_c<std::size_t, 3, 0, 2> swizzle_wxz;
typedef boost::mpl::vector3_c<std::size_t, 3, 0, 3> swizzle_wxw;
typedef boost::mpl::vector3_c<std::size_t, 3, 1, 0> swizzle_wyx;
typedef boost::mpl::vector3_c<std::size_t, 3, 1, 1> swizzle_wyy;
typedef boost::mpl::vector3_c<std::size_t, 3, 1, 2> swizzle_wyz;
typedef boost::mpl::vector3_c<std::size_t, 3, 1, 3> swizzle_wyw;
typedef boost::mpl::vector3_c<std::size_t, 3, 2, 0> swizzle_wzx;
typedef boost::mpl::vector3_c<std::size_t, 3, 2, 1> swizzle_wzy;
typedef boost::mpl::vector3_c<std::size_t, 3, 2, 2> swizzle_wzz;
typedef boost::mpl::vector3_c<std::size_t, 3, 2, 3> swizzle_wzw;
typedef boost::mpl::vector3_c<std::size_t, 3, 3, 0> swizzle_wwx;
typedef boost::mpl::vector3_c<std::size_t, 3, 3, 1> swizzle_wwy;
typedef boost::mpl::vector3_c<std::size_t, 3, 3, 2> swizzle_wwz;
typedef boost::mpl::vector3_c<std::size_t, 3, 3, 3> swizzle_www;



//! swizzle4

typedef boost::mpl::vector4_c<std::size_t, 0, 0, 0, 0> swizzle_xxxx;
typedef boost::mpl::vector4_c<std::size_t, 0, 0, 0, 1> swizzle_xxxy;
typedef boost::mpl::vector4_c<std::size_t, 0, 0, 0, 2> swizzle_xxxz;
typedef boost::mpl::vector4_c<std::size_t, 0, 0, 0, 3> swizzle_xxxw;
typedef boost::mpl::vector4_c<std::size_t, 0, 0, 1, 0> swizzle_xxyx;
typedef boost::mpl::vector4_c<std::size_t, 0, 0, 1, 1> swizzle_xxyy;
typedef boost::mpl::vector4_c<std::size_t, 0, 0, 1, 2> swizzle_xxyz;
typedef boost::mpl::vector4_c<std::size_t, 0, 0, 1, 3> swizzle_xxyw;
typedef boost::mpl::vector4_c<std::size_t, 0, 0, 2, 0> swizzle_xxzx;
typedef boost::mpl::vector4_c<std::size_t, 0, 0, 2, 1> swizzle_xxzy;
typedef boost::mpl::vector4_c<std::size_t, 0, 0, 2, 2> swizzle_xxzz;
typedef boost::mpl::vector4_c<std::size_t, 0, 0, 2, 3> swizzle_xxzw;
typedef boost::mpl::vector4_c<std::size_t, 0, 0, 3, 0> swizzle_xxwx;
typedef boost::mpl::vector4_c<std::size_t, 0, 0, 3, 1> swizzle_xxwy;
typedef boost::mpl::vector4_c<std::size_t, 0, 0, 3, 2> swizzle_xxwz;
typedef boost::mpl::vector4_c<std::size_t, 0, 0, 3, 3> swizzle_xxww;
typedef boost::mpl::vector4_c<std::size_t, 0, 1, 0, 0> swizzle_xyxx;
typedef boost::mpl::vector4_c<std::size_t, 0, 1, 0, 1> swizzle_xyxy;
typedef boost::mpl::vector4_c<std::size_t, 0, 1, 0, 2> swizzle_xyxz;
typedef boost::mpl::vector4_c<std::size_t, 0, 1, 0, 3> swizzle_xyxw;
typedef boost::mpl::vector4_c<std::size_t, 0, 1, 1, 0> swizzle_xyyx;
typedef boost::mpl::vector4_c<std::size_t, 0, 1, 1, 1> swizzle_xyyy;
typedef boost::mpl::vector4_c<std::size_t, 0, 1, 1, 2> swizzle_xyyz;
typedef boost::mpl::vector4_c<std::size_t, 0, 1, 1, 3> swizzle_xyyw;
typedef boost::mpl::vector4_c<std::size_t, 0, 1, 2, 0> swizzle_xyzx;
typedef boost::mpl::vector4_c<std::size_t, 0, 1, 2, 1> swizzle_xyzy;
typedef boost::mpl::vector4_c<std::size_t, 0, 1, 2, 2> swizzle_xyzz;
typedef boost::mpl::vector4_c<std::size_t, 0, 1, 2, 3> swizzle_xyzw;
typedef boost::mpl::vector4_c<std::size_t, 0, 1, 3, 0> swizzle_xywx;
typedef boost::mpl::vector4_c<std::size_t, 0, 1, 3, 1> swizzle_xywy;
typedef boost::mpl::vector4_c<std::size_t, 0, 1, 3, 2> swizzle_xywz;
typedef boost::mpl::vector4_c<std::size_t, 0, 1, 3, 3> swizzle_xyww;
typedef boost::mpl::vector4_c<std::size_t, 0, 2, 0, 0> swizzle_xzxx;
typedef boost::mpl::vector4_c<std::size_t, 0, 2, 0, 1> swizzle_xzxy;
typedef boost::mpl::vector4_c<std::size_t, 0, 2, 0, 2> swizzle_xzxz;
typedef boost::mpl::vector4_c<std::size_t, 0, 2, 0, 3> swizzle_xzxw;
typedef boost::mpl::vector4_c<std::size_t, 0, 2, 1, 0> swizzle_xzyx;
typedef boost::mpl::vector4_c<std::size_t, 0, 2, 1, 1> swizzle_xzyy;
typedef boost::mpl::vector4_c<std::size_t, 0, 2, 1, 2> swizzle_xzyz;
typedef boost::mpl::vector4_c<std::size_t, 0, 2, 1, 3> swizzle_xzyw;
typedef boost::mpl::vector4_c<std::size_t, 0, 2, 2, 0> swizzle_xzzx;
typedef boost::mpl::vector4_c<std::size_t, 0, 2, 2, 1> swizzle_xzzy;
typedef boost::mpl::vector4_c<std::size_t, 0, 2, 2, 2> swizzle_xzzz;
typedef boost::mpl::vector4_c<std::size_t, 0, 2, 2, 3> swizzle_xzzw;
typedef boost::mpl::vector4_c<std::size_t, 0, 2, 3, 0> swizzle_xzwx;
typedef boost::mpl::vector4_c<std::size_t, 0, 2, 3, 1> swizzle_xzwy;
typedef boost::mpl::vector4_c<std::size_t, 0, 2, 3, 2> swizzle_xzwz;
typedef boost::mpl::vector4_c<std::size_t, 0, 2, 3, 3> swizzle_xzww;
typedef boost::mpl::vector4_c<std::size_t, 0, 3, 0, 0> swizzle_xwxx;
typedef boost::mpl::vector4_c<std::size_t, 0, 3, 0, 1> swizzle_xwxy;
typedef boost::mpl::vector4_c<std::size_t, 0, 3, 0, 2> swizzle_xwxz;
typedef boost::mpl::vector4_c<std::size_t, 0, 3, 0, 3> swizzle_xwxw;
typedef boost::mpl::vector4_c<std::size_t, 0, 3, 1, 0> swizzle_xwyx;
typedef boost::mpl::vector4_c<std::size_t, 0, 3, 1, 1> swizzle_xwyy;
typedef boost::mpl::vector4_c<std::size_t, 0, 3, 1, 2> swizzle_xwyz;
typedef boost::mpl::vector4_c<std::size_t, 0, 3, 1, 3> swizzle_xwyw;
typedef boost::mpl::vector4_c<std::size_t, 0, 3, 2, 0> swizzle_xwzx;
typedef boost::mpl::vector4_c<std::size_t, 0, 3, 2, 1> swizzle_xwzy;
typedef boost::mpl::vector4_c<std::size_t, 0, 3, 2, 2> swizzle_xwzz;
typedef boost::mpl::vector4_c<std::size_t, 0, 3, 2, 3> swizzle_xwzw;
typedef boost::mpl::vector4_c<std::size_t, 0, 3, 3, 0> swizzle_xwwx;
typedef boost::mpl::vector4_c<std::size_t, 0, 3, 3, 1> swizzle_xwwy;
typedef boost::mpl::vector4_c<std::size_t, 0, 3, 3, 2> swizzle_xwwz;
typedef boost::mpl::vector4_c<std::size_t, 0, 3, 3, 3> swizzle_xwww;

typedef boost::mpl::vector4_c<std::size_t, 1, 0, 0, 0> swizzle_yxxx;
typedef boost::mpl::vector4_c<std::size_t, 1, 0, 0, 1> swizzle_yxxy;
typedef boost::mpl::vector4_c<std::size_t, 1, 0, 0, 2> swizzle_yxxz;
typedef boost::mpl::vector4_c<std::size_t, 1, 0, 0, 3> swizzle_yxxw;
typedef boost::mpl::vector4_c<std::size_t, 1, 0, 1, 0> swizzle_yxyx;
typedef boost::mpl::vector4_c<std::size_t, 1, 0, 1, 1> swizzle_yxyy;
typedef boost::mpl::vector4_c<std::size_t, 1, 0, 1, 2> swizzle_yxyz;
typedef boost::mpl::vector4_c<std::size_t, 1, 0, 1, 3> swizzle_yxyw;
typedef boost::mpl::vector4_c<std::size_t, 1, 0, 2, 0> swizzle_yxzx;
typedef boost::mpl::vector4_c<std::size_t, 1, 0, 2, 1> swizzle_yxzy;
typedef boost::mpl::vector4_c<std::size_t, 1, 0, 2, 2> swizzle_yxzz;
typedef boost::mpl::vector4_c<std::size_t, 1, 0, 2, 3> swizzle_yxzw;
typedef boost::mpl::vector4_c<std::size_t, 1, 0, 3, 0> swizzle_yxwx;
typedef boost::mpl::vector4_c<std::size_t, 1, 0, 3, 1> swizzle_yxwy;
typedef boost::mpl::vector4_c<std::size_t, 1, 0, 3, 2> swizzle_yxwz;
typedef boost::mpl::vector4_c<std::size_t, 1, 0, 3, 3> swizzle_yxww;
typedef boost::mpl::vector4_c<std::size_t, 1, 1, 0, 0> swizzle_yyxx;
typedef boost::mpl::vector4_c<std::size_t, 1, 1, 0, 1> swizzle_yyxy;
typedef boost::mpl::vector4_c<std::size_t, 1, 1, 0, 2> swizzle_yyxz;
typedef boost::mpl::vector4_c<std::size_t, 1, 1, 0, 3> swizzle_yyxw;
typedef boost::mpl::vector4_c<std::size_t, 1, 1, 1, 0> swizzle_yyyx;
typedef boost::mpl::vector4_c<std::size_t, 1, 1, 1, 1> swizzle_yyyy;
typedef boost::mpl::vector4_c<std::size_t, 1, 1, 1, 2> swizzle_yyyz;
typedef boost::mpl::vector4_c<std::size_t, 1, 1, 1, 3> swizzle_yyyw;
typedef boost::mpl::vector4_c<std::size_t, 1, 1, 2, 0> swizzle_yyzx;
typedef boost::mpl::vector4_c<std::size_t, 1, 1, 2, 1> swizzle_yyzy;
typedef boost::mpl::vector4_c<std::size_t, 1, 1, 2, 2> swizzle_yyzz;
typedef boost::mpl::vector4_c<std::size_t, 1, 1, 2, 3> swizzle_yyzw;
typedef boost::mpl::vector4_c<std::size_t, 1, 1, 3, 0> swizzle_yywx;
typedef boost::mpl::vector4_c<std::size_t, 1, 1, 3, 1> swizzle_yywy;
typedef boost::mpl::vector4_c<std::size_t, 1, 1, 3, 2> swizzle_yywz;
typedef boost::mpl::vector4_c<std::size_t, 1, 1, 3, 3> swizzle_yyww;
typedef boost::mpl::vector4_c<std::size_t, 1, 2, 0, 0> swizzle_yzxx;
typedef boost::mpl::vector4_c<std::size_t, 1, 2, 0, 1> swizzle_yzxy;
typedef boost::mpl::vector4_c<std::size_t, 1, 2, 0, 2> swizzle_yzxz;
typedef boost::mpl::vector4_c<std::size_t, 1, 2, 0, 3> swizzle_yzxw;
typedef boost::mpl::vector4_c<std::size_t, 1, 2, 1, 0> swizzle_yzyx;
typedef boost::mpl::vector4_c<std::size_t, 1, 2, 1, 1> swizzle_yzyy;
typedef boost::mpl::vector4_c<std::size_t, 1, 2, 1, 2> swizzle_yzyz;
typedef boost::mpl::vector4_c<std::size_t, 1, 2, 1, 3> swizzle_yzyw;
typedef boost::mpl::vector4_c<std::size_t, 1, 2, 2, 0> swizzle_yzzx;
typedef boost::mpl::vector4_c<std::size_t, 1, 2, 2, 1> swizzle_yzzy;
typedef boost::mpl::vector4_c<std::size_t, 1, 2, 2, 2> swizzle_yzzz;
typedef boost::mpl::vector4_c<std::size_t, 1, 2, 2, 3> swizzle_yzzw;
typedef boost::mpl::vector4_c<std::size_t, 1, 2, 3, 0> swizzle_yzwx;
typedef boost::mpl::vector4_c<std::size_t, 1, 2, 3, 1> swizzle_yzwy;
typedef boost::mpl::vector4_c<std::size_t, 1, 2, 3, 2> swizzle_yzwz;
typedef boost::mpl::vector4_c<std::size_t, 1, 2, 3, 3> swizzle_yzww;
typedef boost::mpl::vector4_c<std::size_t, 1, 3, 0, 0> swizzle_ywxx;
typedef boost::mpl::vector4_c<std::size_t, 1, 3, 0, 1> swizzle_ywxy;
typedef boost::mpl::vector4_c<std::size_t, 1, 3, 0, 2> swizzle_ywxz;
typedef boost::mpl::vector4_c<std::size_t, 1, 3, 0, 3> swizzle_ywxw;
typedef boost::mpl::vector4_c<std::size_t, 1, 3, 1, 0> swizzle_ywyx;
typedef boost::mpl::vector4_c<std::size_t, 1, 3, 1, 1> swizzle_ywyy;
typedef boost::mpl::vector4_c<std::size_t, 1, 3, 1, 2> swizzle_ywyz;
typedef boost::mpl::vector4_c<std::size_t, 1, 3, 1, 3> swizzle_ywyw;
typedef boost::mpl::vector4_c<std::size_t, 1, 3, 2, 0> swizzle_ywzx;
typedef boost::mpl::vector4_c<std::size_t, 1, 3, 2, 1> swizzle_ywzy;
typedef boost::mpl::vector4_c<std::size_t, 1, 3, 2, 2> swizzle_ywzz;
typedef boost::mpl::vector4_c<std::size_t, 1, 3, 2, 3> swizzle_ywzw;
typedef boost::mpl::vector4_c<std::size_t, 1, 3, 3, 0> swizzle_ywwx;
typedef boost::mpl::vector4_c<std::size_t, 1, 3, 3, 1> swizzle_ywwy;
typedef boost::mpl::vector4_c<std::size_t, 1, 3, 3, 2> swizzle_ywwz;
typedef boost::mpl::vector4_c<std::size_t, 1, 3, 3, 3> swizzle_ywww;

typedef boost::mpl::vector4_c<std::size_t, 2, 0, 0, 0> swizzle_zxxx;
typedef boost::mpl::vector4_c<std::size_t, 2, 0, 0, 1> swizzle_zxxy;
typedef boost::mpl::vector4_c<std::size_t, 2, 0, 0, 2> swizzle_zxxz;
typedef boost::mpl::vector4_c<std::size_t, 2, 0, 0, 3> swizzle_zxxw;
typedef boost::mpl::vector4_c<std::size_t, 2, 0, 1, 0> swizzle_zxyx;
typedef boost::mpl::vector4_c<std::size_t, 2, 0, 1, 1> swizzle_zxyy;
typedef boost::mpl::vector4_c<std::size_t, 2, 0, 1, 2> swizzle_zxyz;
typedef boost::mpl::vector4_c<std::size_t, 2, 0, 1, 3> swizzle_zxyw;
typedef boost::mpl::vector4_c<std::size_t, 2, 0, 2, 0> swizzle_zxzx;
typedef boost::mpl::vector4_c<std::size_t, 2, 0, 2, 1> swizzle_zxzy;
typedef boost::mpl::vector4_c<std::size_t, 2, 0, 2, 2> swizzle_zxzz;
typedef boost::mpl::vector4_c<std::size_t, 2, 0, 2, 3> swizzle_zxzw;
typedef boost::mpl::vector4_c<std::size_t, 2, 0, 3, 0> swizzle_zxwx;
typedef boost::mpl::vector4_c<std::size_t, 2, 0, 3, 1> swizzle_zxwy;
typedef boost::mpl::vector4_c<std::size_t, 2, 0, 3, 2> swizzle_zxwz;
typedef boost::mpl::vector4_c<std::size_t, 2, 0, 3, 3> swizzle_zxww;
typedef boost::mpl::vector4_c<std::size_t, 2, 1, 0, 0> swizzle_zyxx;
typedef boost::mpl::vector4_c<std::size_t, 2, 1, 0, 1> swizzle_zyxy;
typedef boost::mpl::vector4_c<std::size_t, 2, 1, 0, 2> swizzle_zyxz;
typedef boost::mpl::vector4_c<std::size_t, 2, 1, 0, 3> swizzle_zyxw;
typedef boost::mpl::vector4_c<std::size_t, 2, 1, 1, 0> swizzle_zyyx;
typedef boost::mpl::vector4_c<std::size_t, 2, 1, 1, 1> swizzle_zyyy;
typedef boost::mpl::vector4_c<std::size_t, 2, 1, 1, 2> swizzle_zyyz;
typedef boost::mpl::vector4_c<std::size_t, 2, 1, 1, 3> swizzle_zyyw;
typedef boost::mpl::vector4_c<std::size_t, 2, 1, 2, 0> swizzle_zyzx;
typedef boost::mpl::vector4_c<std::size_t, 2, 1, 2, 1> swizzle_zyzy;
typedef boost::mpl::vector4_c<std::size_t, 2, 1, 2, 2> swizzle_zyzz;
typedef boost::mpl::vector4_c<std::size_t, 2, 1, 2, 3> swizzle_zyzw;
typedef boost::mpl::vector4_c<std::size_t, 2, 1, 3, 0> swizzle_zywx;
typedef boost::mpl::vector4_c<std::size_t, 2, 1, 3, 1> swizzle_zywy;
typedef boost::mpl::vector4_c<std::size_t, 2, 1, 3, 2> swizzle_zywz;
typedef boost::mpl::vector4_c<std::size_t, 2, 1, 3, 3> swizzle_zyww;
typedef boost::mpl::vector4_c<std::size_t, 2, 2, 0, 0> swizzle_zzxx;
typedef boost::mpl::vector4_c<std::size_t, 2, 2, 0, 1> swizzle_zzxy;
typedef boost::mpl::vector4_c<std::size_t, 2, 2, 0, 2> swizzle_zzxz;
typedef boost::mpl::vector4_c<std::size_t, 2, 2, 0, 3> swizzle_zzxw;
typedef boost::mpl::vector4_c<std::size_t, 2, 2, 1, 0> swizzle_zzyx;
typedef boost::mpl::vector4_c<std::size_t, 2, 2, 1, 1> swizzle_zzyy;
typedef boost::mpl::vector4_c<std::size_t, 2, 2, 1, 2> swizzle_zzyz;
typedef boost::mpl::vector4_c<std::size_t, 2, 2, 1, 3> swizzle_zzyw;
typedef boost::mpl::vector4_c<std::size_t, 2, 2, 2, 0> swizzle_zzzx;
typedef boost::mpl::vector4_c<std::size_t, 2, 2, 2, 1> swizzle_zzzy;
typedef boost::mpl::vector4_c<std::size_t, 2, 2, 2, 2> swizzle_zzzz;
typedef boost::mpl::vector4_c<std::size_t, 2, 2, 2, 3> swizzle_zzzw;
typedef boost::mpl::vector4_c<std::size_t, 2, 2, 3, 0> swizzle_zzwx;
typedef boost::mpl::vector4_c<std::size_t, 2, 2, 3, 1> swizzle_zzwy;
typedef boost::mpl::vector4_c<std::size_t, 2, 2, 3, 2> swizzle_zzwz;
typedef boost::mpl::vector4_c<std::size_t, 2, 2, 3, 3> swizzle_zzww;
typedef boost::mpl::vector4_c<std::size_t, 2, 3, 0, 0> swizzle_zwxx;
typedef boost::mpl::vector4_c<std::size_t, 2, 3, 0, 1> swizzle_zwxy;
typedef boost::mpl::vector4_c<std::size_t, 2, 3, 0, 2> swizzle_zwxz;
typedef boost::mpl::vector4_c<std::size_t, 2, 3, 0, 3> swizzle_zwxw;
typedef boost::mpl::vector4_c<std::size_t, 2, 3, 1, 0> swizzle_zwyx;
typedef boost::mpl::vector4_c<std::size_t, 2, 3, 1, 1> swizzle_zwyy;
typedef boost::mpl::vector4_c<std::size_t, 2, 3, 1, 2> swizzle_zwyz;
typedef boost::mpl::vector4_c<std::size_t, 2, 3, 1, 3> swizzle_zwyw;
typedef boost::mpl::vector4_c<std::size_t, 2, 3, 2, 0> swizzle_zwzx;
typedef boost::mpl::vector4_c<std::size_t, 2, 3, 2, 1> swizzle_zwzy;
typedef boost::mpl::vector4_c<std::size_t, 2, 3, 2, 2> swizzle_zwzz;
typedef boost::mpl::vector4_c<std::size_t, 2, 3, 2, 3> swizzle_zwzw;
typedef boost::mpl::vector4_c<std::size_t, 2, 3, 3, 0> swizzle_zwwx;
typedef boost::mpl::vector4_c<std::size_t, 2, 3, 3, 1> swizzle_zwwy;
typedef boost::mpl::vector4_c<std::size_t, 2, 3, 3, 2> swizzle_zwwz;
typedef boost::mpl::vector4_c<std::size_t, 2, 3, 3, 3> swizzle_zwww;

typedef boost::mpl::vector4_c<std::size_t, 3, 0, 0, 0> swizzle_wxxx;
typedef boost::mpl::vector4_c<std::size_t, 3, 0, 0, 1> swizzle_wxxy;
typedef boost::mpl::vector4_c<std::size_t, 3, 0, 0, 2> swizzle_wxxz;
typedef boost::mpl::vector4_c<std::size_t, 3, 0, 0, 3> swizzle_wxxw;
typedef boost::mpl::vector4_c<std::size_t, 3, 0, 1, 0> swizzle_wxyx;
typedef boost::mpl::vector4_c<std::size_t, 3, 0, 1, 1> swizzle_wxyy;
typedef boost::mpl::vector4_c<std::size_t, 3, 0, 1, 2> swizzle_wxyz;
typedef boost::mpl::vector4_c<std::size_t, 3, 0, 1, 3> swizzle_wxyw;
typedef boost::mpl::vector4_c<std::size_t, 3, 0, 2, 0> swizzle_wxzx;
typedef boost::mpl::vector4_c<std::size_t, 3, 0, 2, 1> swizzle_wxzy;
typedef boost::mpl::vector4_c<std::size_t, 3, 0, 2, 2> swizzle_wxzz;
typedef boost::mpl::vector4_c<std::size_t, 3, 0, 2, 3> swizzle_wxzw;
typedef boost::mpl::vector4_c<std::size_t, 3, 0, 3, 0> swizzle_wxwx;
typedef boost::mpl::vector4_c<std::size_t, 3, 0, 3, 1> swizzle_wxwy;
typedef boost::mpl::vector4_c<std::size_t, 3, 0, 3, 2> swizzle_wxwz;
typedef boost::mpl::vector4_c<std::size_t, 3, 0, 3, 3> swizzle_wxww;
typedef boost::mpl::vector4_c<std::size_t, 3, 1, 0, 0> swizzle_wyxx;
typedef boost::mpl::vector4_c<std::size_t, 3, 1, 0, 1> swizzle_wyxy;
typedef boost::mpl::vector4_c<std::size_t, 3, 1, 0, 2> swizzle_wyxz;
typedef boost::mpl::vector4_c<std::size_t, 3, 1, 0, 3> swizzle_wyxw;
typedef boost::mpl::vector4_c<std::size_t, 3, 1, 1, 0> swizzle_wyyx;
typedef boost::mpl::vector4_c<std::size_t, 3, 1, 1, 1> swizzle_wyyy;
typedef boost::mpl::vector4_c<std::size_t, 3, 1, 1, 2> swizzle_wyyz;
typedef boost::mpl::vector4_c<std::size_t, 3, 1, 1, 3> swizzle_wyyw;
typedef boost::mpl::vector4_c<std::size_t, 3, 1, 2, 0> swizzle_wyzx;
typedef boost::mpl::vector4_c<std::size_t, 3, 1, 2, 1> swizzle_wyzy;
typedef boost::mpl::vector4_c<std::size_t, 3, 1, 2, 2> swizzle_wyzz;
typedef boost::mpl::vector4_c<std::size_t, 3, 1, 2, 3> swizzle_wyzw;
typedef boost::mpl::vector4_c<std::size_t, 3, 1, 3, 0> swizzle_wywx;
typedef boost::mpl::vector4_c<std::size_t, 3, 1, 3, 1> swizzle_wywy;
typedef boost::mpl::vector4_c<std::size_t, 3, 1, 3, 2> swizzle_wywz;
typedef boost::mpl::vector4_c<std::size_t, 3, 1, 3, 3> swizzle_wyww;
typedef boost::mpl::vector4_c<std::size_t, 3, 2, 0, 0> swizzle_wzxx;
typedef boost::mpl::vector4_c<std::size_t, 3, 2, 0, 1> swizzle_wzxy;
typedef boost::mpl::vector4_c<std::size_t, 3, 2, 0, 2> swizzle_wzxz;
typedef boost::mpl::vector4_c<std::size_t, 3, 2, 0, 3> swizzle_wzxw;
typedef boost::mpl::vector4_c<std::size_t, 3, 2, 1, 0> swizzle_wzyx;
typedef boost::mpl::vector4_c<std::size_t, 3, 2, 1, 1> swizzle_wzyy;
typedef boost::mpl::vector4_c<std::size_t, 3, 2, 1, 2> swizzle_wzyz;
typedef boost::mpl::vector4_c<std::size_t, 3, 2, 1, 3> swizzle_wzyw;
typedef boost::mpl::vector4_c<std::size_t, 3, 2, 2, 0> swizzle_wzzx;
typedef boost::mpl::vector4_c<std::size_t, 3, 2, 2, 1> swizzle_wzzy;
typedef boost::mpl::vector4_c<std::size_t, 3, 2, 2, 2> swizzle_wzzz;
typedef boost::mpl::vector4_c<std::size_t, 3, 2, 2, 3> swizzle_wzzw;
typedef boost::mpl::vector4_c<std::size_t, 3, 2, 3, 0> swizzle_wzwx;
typedef boost::mpl::vector4_c<std::size_t, 3, 2, 3, 1> swizzle_wzwy;
typedef boost::mpl::vector4_c<std::size_t, 3, 2, 3, 2> swizzle_wzwz;
typedef boost::mpl::vector4_c<std::size_t, 3, 2, 3, 3> swizzle_wzww;
typedef boost::mpl::vector4_c<std::size_t, 3, 3, 0, 0> swizzle_wwxx;
typedef boost::mpl::vector4_c<std::size_t, 3, 3, 0, 1> swizzle_wwxy;
typedef boost::mpl::vector4_c<std::size_t, 3, 3, 0, 2> swizzle_wwxz;
typedef boost::mpl::vector4_c<std::size_t, 3, 3, 0, 3> swizzle_wwxw;
typedef boost::mpl::vector4_c<std::size_t, 3, 3, 1, 0> swizzle_wwyx;
typedef boost::mpl::vector4_c<std::size_t, 3, 3, 1, 1> swizzle_wwyy;
typedef boost::mpl::vector4_c<std::size_t, 3, 3, 1, 2> swizzle_wwyz;
typedef boost::mpl::vector4_c<std::size_t, 3, 3, 1, 3> swizzle_wwyw;
typedef boost::mpl::vector4_c<std::size_t, 3, 3, 2, 0> swizzle_wwzx;
typedef boost::mpl::vector4_c<std::size_t, 3, 3, 2, 1> swizzle_wwzy;
typedef boost::mpl::vector4_c<std::size_t, 3, 3, 2, 2> swizzle_wwzz;
typedef boost::mpl::vector4_c<std::size_t, 3, 3, 2, 3> swizzle_wwzw;
typedef boost::mpl::vector4_c<std::size_t, 3, 3, 3, 0> swizzle_wwwx;
typedef boost::mpl::vector4_c<std::size_t, 3, 3, 3, 1> swizzle_wwwy;
typedef boost::mpl::vector4_c<std::size_t, 3, 3, 3, 2> swizzle_wwwz;
typedef boost::mpl::vector4_c<std::size_t, 3, 3, 3, 3> swizzle_wwww;


__NOGARA_EXPRESSION_END



__NOGARA_BEGIN

using expression::swizzle_vector;
using expression::ref_swizzle_vector;
using expression::swizzle;


using expression::swizzle_xx;
using expression::swizzle_xy;
using expression::swizzle_xz;
using expression::swizzle_xw;
using expression::swizzle_yx;
using expression::swizzle_yy;
using expression::swizzle_yz;
using expression::swizzle_yw;
using expression::swizzle_zx;
using expression::swizzle_zy;
using expression::swizzle_zz;
using expression::swizzle_zw;
using expression::swizzle_wx;
using expression::swizzle_wy;
using expression::swizzle_wz;
using expression::swizzle_ww;


using expression::swizzle_xxx;
using expression::swizzle_xxy;
using expression::swizzle_xxz;
using expression::swizzle_xxw;
using expression::swizzle_xyx;
using expression::swizzle_xyy;
using expression::swizzle_xyz;
using expression::swizzle_xyw;
using expression::swizzle_xzx;
using expression::swizzle_xzy;
using expression::swizzle_xzz;
using expression::swizzle_xzw;
using expression::swizzle_xwx;
using expression::swizzle_xwy;
using expression::swizzle_xwz;
using expression::swizzle_xww;

using expression::swizzle_yxx;
using expression::swizzle_yxy;
using expression::swizzle_yxz;
using expression::swizzle_yxw;
using expression::swizzle_yyx;
using expression::swizzle_yyy;
using expression::swizzle_yyz;
using expression::swizzle_yyw;
using expression::swizzle_yzx;
using expression::swizzle_yzy;
using expression::swizzle_yzz;
using expression::swizzle_yzw;
using expression::swizzle_ywx;
using expression::swizzle_ywy;
using expression::swizzle_ywz;
using expression::swizzle_yww;

using expression::swizzle_zxx;
using expression::swizzle_zxy;
using expression::swizzle_zxz;
using expression::swizzle_zxw;
using expression::swizzle_zyx;
using expression::swizzle_zyy;
using expression::swizzle_zyz;
using expression::swizzle_zyw;
using expression::swizzle_zzx;
using expression::swizzle_zzy;
using expression::swizzle_zzz;
using expression::swizzle_zzw;
using expression::swizzle_zwx;
using expression::swizzle_zwy;
using expression::swizzle_zwz;
using expression::swizzle_zww;

using expression::swizzle_wxx;
using expression::swizzle_wxy;
using expression::swizzle_wxz;
using expression::swizzle_wxw;
using expression::swizzle_wyx;
using expression::swizzle_wyy;
using expression::swizzle_wyz;
using expression::swizzle_wyw;
using expression::swizzle_wzx;
using expression::swizzle_wzy;
using expression::swizzle_wzz;
using expression::swizzle_wzw;
using expression::swizzle_wwx;
using expression::swizzle_wwy;
using expression::swizzle_wwz;
using expression::swizzle_www;



using expression::swizzle_xxxx;
using expression::swizzle_xxxy;
using expression::swizzle_xxxz;
using expression::swizzle_xxxw;
using expression::swizzle_xxyx;
using expression::swizzle_xxyy;
using expression::swizzle_xxyz;
using expression::swizzle_xxyw;
using expression::swizzle_xxzx;
using expression::swizzle_xxzy;
using expression::swizzle_xxzz;
using expression::swizzle_xxzw;
using expression::swizzle_xxwx;
using expression::swizzle_xxwy;
using expression::swizzle_xxwz;
using expression::swizzle_xxww;
using expression::swizzle_xyxx;
using expression::swizzle_xyxy;
using expression::swizzle_xyxz;
using expression::swizzle_xyxw;
using expression::swizzle_xyyx;
using expression::swizzle_xyyy;
using expression::swizzle_xyyz;
using expression::swizzle_xyyw;
using expression::swizzle_xyzx;
using expression::swizzle_xyzy;
using expression::swizzle_xyzz;
using expression::swizzle_xyzw;
using expression::swizzle_xywx;
using expression::swizzle_xywy;
using expression::swizzle_xywz;
using expression::swizzle_xyww;
using expression::swizzle_xzxx;
using expression::swizzle_xzxy;
using expression::swizzle_xzxz;
using expression::swizzle_xzxw;
using expression::swizzle_xzyx;
using expression::swizzle_xzyy;
using expression::swizzle_xzyz;
using expression::swizzle_xzyw;
using expression::swizzle_xzzx;
using expression::swizzle_xzzy;
using expression::swizzle_xzzz;
using expression::swizzle_xzzw;
using expression::swizzle_xzwx;
using expression::swizzle_xzwy;
using expression::swizzle_xzwz;
using expression::swizzle_xzww;
using expression::swizzle_xwxx;
using expression::swizzle_xwxy;
using expression::swizzle_xwxz;
using expression::swizzle_xwxw;
using expression::swizzle_xwyx;
using expression::swizzle_xwyy;
using expression::swizzle_xwyz;
using expression::swizzle_xwyw;
using expression::swizzle_xwzx;
using expression::swizzle_xwzy;
using expression::swizzle_xwzz;
using expression::swizzle_xwzw;
using expression::swizzle_xwwx;
using expression::swizzle_xwwy;
using expression::swizzle_xwwz;
using expression::swizzle_xwww;

using expression::swizzle_yxxx;
using expression::swizzle_yxxy;
using expression::swizzle_yxxz;
using expression::swizzle_yxxw;
using expression::swizzle_yxyx;
using expression::swizzle_yxyy;
using expression::swizzle_yxyz;
using expression::swizzle_yxyw;
using expression::swizzle_yxzx;
using expression::swizzle_yxzy;
using expression::swizzle_yxzz;
using expression::swizzle_yxzw;
using expression::swizzle_yxwx;
using expression::swizzle_yxwy;
using expression::swizzle_yxwz;
using expression::swizzle_yxww;
using expression::swizzle_yyxx;
using expression::swizzle_yyxy;
using expression::swizzle_yyxz;
using expression::swizzle_yyxw;
using expression::swizzle_yyyx;
using expression::swizzle_yyyy;
using expression::swizzle_yyyz;
using expression::swizzle_yyyw;
using expression::swizzle_yyzx;
using expression::swizzle_yyzy;
using expression::swizzle_yyzz;
using expression::swizzle_yyzw;
using expression::swizzle_yywx;
using expression::swizzle_yywy;
using expression::swizzle_yywz;
using expression::swizzle_yyww;
using expression::swizzle_yzxx;
using expression::swizzle_yzxy;
using expression::swizzle_yzxz;
using expression::swizzle_yzxw;
using expression::swizzle_yzyx;
using expression::swizzle_yzyy;
using expression::swizzle_yzyz;
using expression::swizzle_yzyw;
using expression::swizzle_yzzx;
using expression::swizzle_yzzy;
using expression::swizzle_yzzz;
using expression::swizzle_yzzw;
using expression::swizzle_yzwx;
using expression::swizzle_yzwy;
using expression::swizzle_yzwz;
using expression::swizzle_yzww;
using expression::swizzle_ywxx;
using expression::swizzle_ywxy;
using expression::swizzle_ywxz;
using expression::swizzle_ywxw;
using expression::swizzle_ywyx;
using expression::swizzle_ywyy;
using expression::swizzle_ywyz;
using expression::swizzle_ywyw;
using expression::swizzle_ywzx;
using expression::swizzle_ywzy;
using expression::swizzle_ywzz;
using expression::swizzle_ywzw;
using expression::swizzle_ywwx;
using expression::swizzle_ywwy;
using expression::swizzle_ywwz;
using expression::swizzle_ywww;

using expression::swizzle_zxxx;
using expression::swizzle_zxxy;
using expression::swizzle_zxxz;
using expression::swizzle_zxxw;
using expression::swizzle_zxyx;
using expression::swizzle_zxyy;
using expression::swizzle_zxyz;
using expression::swizzle_zxyw;
using expression::swizzle_zxzx;
using expression::swizzle_zxzy;
using expression::swizzle_zxzz;
using expression::swizzle_zxzw;
using expression::swizzle_zxwx;
using expression::swizzle_zxwy;
using expression::swizzle_zxwz;
using expression::swizzle_zxww;
using expression::swizzle_zyxx;
using expression::swizzle_zyxy;
using expression::swizzle_zyxz;
using expression::swizzle_zyxw;
using expression::swizzle_zyyx;
using expression::swizzle_zyyy;
using expression::swizzle_zyyz;
using expression::swizzle_zyyw;
using expression::swizzle_zyzx;
using expression::swizzle_zyzy;
using expression::swizzle_zyzz;
using expression::swizzle_zyzw;
using expression::swizzle_zywx;
using expression::swizzle_zywy;
using expression::swizzle_zywz;
using expression::swizzle_zyww;
using expression::swizzle_zzxx;
using expression::swizzle_zzxy;
using expression::swizzle_zzxz;
using expression::swizzle_zzxw;
using expression::swizzle_zzyx;
using expression::swizzle_zzyy;
using expression::swizzle_zzyz;
using expression::swizzle_zzyw;
using expression::swizzle_zzzx;
using expression::swizzle_zzzy;
using expression::swizzle_zzzz;
using expression::swizzle_zzzw;
using expression::swizzle_zzwx;
using expression::swizzle_zzwy;
using expression::swizzle_zzwz;
using expression::swizzle_zzww;
using expression::swizzle_zwxx;
using expression::swizzle_zwxy;
using expression::swizzle_zwxz;
using expression::swizzle_zwxw;
using expression::swizzle_zwyx;
using expression::swizzle_zwyy;
using expression::swizzle_zwyz;
using expression::swizzle_zwyw;
using expression::swizzle_zwzx;
using expression::swizzle_zwzy;
using expression::swizzle_zwzz;
using expression::swizzle_zwzw;
using expression::swizzle_zwwx;
using expression::swizzle_zwwy;
using expression::swizzle_zwwz;
using expression::swizzle_zwww;

using expression::swizzle_wxxx;
using expression::swizzle_wxxy;
using expression::swizzle_wxxz;
using expression::swizzle_wxxw;
using expression::swizzle_wxyx;
using expression::swizzle_wxyy;
using expression::swizzle_wxyz;
using expression::swizzle_wxyw;
using expression::swizzle_wxzx;
using expression::swizzle_wxzy;
using expression::swizzle_wxzz;
using expression::swizzle_wxzw;
using expression::swizzle_wxwx;
using expression::swizzle_wxwy;
using expression::swizzle_wxwz;
using expression::swizzle_wxww;
using expression::swizzle_wyxx;
using expression::swizzle_wyxy;
using expression::swizzle_wyxz;
using expression::swizzle_wyxw;
using expression::swizzle_wyyx;
using expression::swizzle_wyyy;
using expression::swizzle_wyyz;
using expression::swizzle_wyyw;
using expression::swizzle_wyzx;
using expression::swizzle_wyzy;
using expression::swizzle_wyzz;
using expression::swizzle_wyzw;
using expression::swizzle_wywx;
using expression::swizzle_wywy;
using expression::swizzle_wywz;
using expression::swizzle_wyww;
using expression::swizzle_wzxx;
using expression::swizzle_wzxy;
using expression::swizzle_wzxz;
using expression::swizzle_wzxw;
using expression::swizzle_wzyx;
using expression::swizzle_wzyy;
using expression::swizzle_wzyz;
using expression::swizzle_wzyw;
using expression::swizzle_wzzx;
using expression::swizzle_wzzy;
using expression::swizzle_wzzz;
using expression::swizzle_wzzw;
using expression::swizzle_wzwx;
using expression::swizzle_wzwy;
using expression::swizzle_wzwz;
using expression::swizzle_wzww;
using expression::swizzle_wwxx;
using expression::swizzle_wwxy;
using expression::swizzle_wwxz;
using expression::swizzle_wwxw;
using expression::swizzle_wwyx;
using expression::swizzle_wwyy;
using expression::swizzle_wwyz;
using expression::swizzle_wwyw;
using expression::swizzle_wwzx;
using expression::swizzle_wwzy;
using expression::swizzle_wwzz;
using expression::swizzle_wwzw;
using expression::swizzle_wwwx;
using expression::swizzle_wwwy;
using expression::swizzle_wwwz;
using expression::swizzle_wwww;



__NOGARA_END

#endif
