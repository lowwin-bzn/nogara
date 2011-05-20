#ifndef NOGARA_EXPRESSION_QUATERNION_HPP
#define NOGARA_EXPRESSION_QUATERNION_HPP

#include <limits>
#include <boost/type_traits.hpp>
#include <boost/utility/enable_if.hpp>
#include <nogara/expression/vector/vector3.hpp>
#include <nogara/expression/quaternion/quaternion_cross.hpp>
#include <nogara/expression/quaternion/quaternion_conj.hpp>

//////////////////////////////////////////////////////
//! @file  nogara/expression/quaternion/quaternion.hpp
//! @brief クォータニオンクラス
//////////////////////////////////////////////////////

__NOGARA_EXPRESSION_BEGIN

template<typename T>
class quaternion;

////////////////////////////////////////////////////////////////////
//! @brief クォータニオンクラス
//!        ベクトルとして扱っているが、vector4と順序的な互換性はない
////////////////////////////////////////////////////////////////////
template<typename T>
class quaternion : public vector_container<quaternion<T>, T>{
    typedef quaternion<T>                  self_type;
    typedef expression_container<T, 4>     container_type;
    typedef container_type&                container_reference;
    typedef container_type const&          container_const_reference;

public:
    typedef typename boost::enable_if<
    boost::is_floating_point<T>,
    typename container_type::value_type>::type value_type;
    typedef expression::quaternion_tag expression_category;
    typedef typename container_type::iterator               iterator;
    typedef typename container_type::const_iterator         const_iterator;
    typedef typename container_type::reverse_iterator       reverse_iterator;
    typedef typename container_type::const_reverse_iterator const_reverse_iterator;
    typedef value_type&                                     reference;
    typedef value_type const&                               const_reference;
    typedef get_dimension<container_type>                   Dimension;

    quaternion():container(){}
    quaternion(T const& w, T const& x, T const& y, T const& z):container(w, x, y, z){}
    quaternion(quaternion const& other):container(other.data()){}

    template<class E>
    quaternion(vector_expression<E> const& e):
        container(get<0>(e), get<1>(e), get<2>(e), get<3>(e)){}
    template<class E>
    quaternion(T const& w, vector_expression<E> const& e,
               typename boost::enable_if<dimension_equal_to_c<E, 3> >::type* = 0):
        container(w, get<0>(e), get<1>(e), get<2>(e)){}
#if defined(NG_CPP0X)
    quaternion(quaternion&& other):container(std::forward<container_type>(other.container)){}
#endif

    self_type& operator =(quaternion const& v){
        if(&v != this){
            container = v.data();
        }
        return *this;
    }

    template<class E>
    self_type& operator =(vector_expression<E> const& e){
        w(e()(0)); x(e()(1)); y(e()(2)); z(e()(3));
        return *this;
    }

#if defined(NG_CPP0X)
    self_type& operator =(quaternion&& v){
        container = std::move(v.container);
        return *this;
    }
#endif

    template<class E>
    self_type& operator +=(vector_expression<E> const& e){
        return (*this = *this + e);
    }

    template<class E>
    self_type& operator -=(vector_expression<E> const& e){
        return (*this = *this - e);
    }

    template<class V>
    typename boost::enable_if<boost::is_convertible<V, value_type>, self_type&>::type
    operator *=(V const& val){return (*this = *this * val);}

    template<class V>
    typename boost::enable_if<boost::is_convertible<V, value_type>, self_type&>::type
    operator /=(V const& val){return (*this = *this / val);}

    container_reference       data()       {return container;}
    container_const_reference data() const {return container;}
    std::size_t               size() const {return container.size();}

    iterator                  begin()        {return container.begin();}
    const_iterator            begin()  const {return container.begin();}
    reverse_iterator          end()          {return container.begin();}
    const_reverse_iterator    end()    const {return container.begin();}
    reverse_iterator          rbegin()       {return container.rbegin();}
    const_reverse_iterator    rbegin() const {return container.rbegin();}
    reverse_iterator          rend()         {return container.rbegin();}
    const_reverse_iterator    rend()   const {return container.rbegin();}

public:
    static self_type const zero;
    static self_type const identity;
    
private:
    container_type container;
};

template<typename T>
quaternion<T> const quaternion<T>::zero(T(0), T(0), T(0), T(0));

template<typename T>
quaternion<T> const quaternion<T>::identity(T(1), T(0), T(0), T(0));

template<class E>
struct quaternion_accessor{
    typedef typename E::value_type      value_type;
    typedef typename E::reference       reference;
    typedef typename E::const_reference const_reference;
    reference       w(vector_expression<E>& e)      {return e[0];}
    const_reference w(vector_expression<E> const& e){return e[0];}
    reference       x(vector_expression<E>& e)      {return e[1];}
    const_reference x(vector_expression<E> const& e){return e[1];}
    reference       y(vector_expression<E>& e)      {return e[2];}
    const_reference y(vector_expression<E> const& e){return e[2];}
    reference       z(vector_expression<E>& e)      {return e[3];}
    const_reference z(vector_expression<E> const& e){return e[3];}
    quaternion<value_type>
    construct(const_reference w, const_reference x, const_reference y, const_reference z){
        return quaternion<value_type>(x, y, z, w);
    }
};

__NOGARA_EXPRESSION_END

__NOGARA_BEGIN
using expression::quaternion;
__NOGARA_END

#include "function.hpp"

#endif
