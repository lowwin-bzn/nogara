#ifndef NOGARA_EXPRESSION_QUATERNION_CROSS_HPP
#define NOGARA_EXPRESSION_QUATERNION_CROSS_HPP

//////////////////////////////////////////////////////////
//! @file nogara/expression/quaternion/quaternion_cross.hpp
//! @brief クォータニオンの外積
//////////////////////////////////////////////////////////

#include <boost/mpl/int.hpp>
#include <nogara/expression/vector/get.hpp>
#include <nogara/expression/vector/binary_expression.hpp>

__NOGARA_EXPRESSION_BEGIN

///////////////////////////////////////////////
//! @brief クォータニオンの外積関数オブジェクト
///////////////////////////////////////////////
template<class E1, class E2>
class quaternion_cross : public vector_binary_base<E1, E2, quaternion_cross<E1, E2> >{
    typedef quaternion_cross<E1, E2>              self_type;
    typedef vector_binary_base<E1, E2, self_type> base_type;
    using base_type::left; using base_type::right;

    typename base_type::value_type apply(boost::mpl::int_<0>) const {
        return get<0>(left) * get<0>(right) - get<1>(left) * get<1>(right) -
               get<2>(left) * get<2>(right) - get<3>(left) * get<3>(right);
    }
    typename base_type::value_type apply(boost::mpl::int_<1>) const {
        return get<0>(left) * get<1>(right) + get<1>(left) * get<0>(right) +
               get<2>(left) * get<3>(right) - get<3>(left) * get<2>(right);
    }
    typename base_type::value_type apply(boost::mpl::int_<2>) const {
        return get<0>(left) * get<2>(right) - get<1>(left) * get<3>(right) +
               get<2>(left) * get<0>(right) + get<3>(left) * get<1>(right);
    }
    typename base_type::value_type apply(boost::mpl::int_<3>) const {
        return get<0>(left) * get<3>(right) + get<1>(left) * get<2>(right) -
               get<2>(left) * get<1>(right) + get<3>(left) * get<0>(right);
    }

    template<int N>
    typename base_type::value_type apply(boost::mpl::int_<N>) const {
        assert(false && "vector4 out of range");
        return typename base_type::value_type();
    }
public:
    quaternion_cross(typename base_type::argment1_type l,
                     typename base_type::argment1_type r):base_type(l, r){}
    
    template<int N> typename base_type::value_type apply() const {
        return apply(boost::mpl::int_<N>());
    }

    typename base_type::value_type apply(unsigned i) const {
        switch(i){
            case 0: return apply<0>();
            case 1: return apply<1>();
            case 2: return apply<2>();
            case 3: return apply<3>();
        }
        return apply<-1>();
    }
};

//////////////////////////////////////////////
//! 外積関数オブジェクトのクォータニオン特殊化
//////////////////////////////////////////////
template<class L, class R>
class vector_cross<L, R, 4> : public boost::enable_if<
    quaternion_same<L, R>, quaternion_cross<L, R> >::type{};

__NOGARA_EXPRESSION_END


#endif
