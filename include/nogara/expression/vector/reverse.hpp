#ifndef NOGARA_EXPRESSION_VECTOR_REVERSE_HPP
#define NOGARA_EXPRESSION_VECTOR_REVERSE_HPP

//////////////////////////////////////////////
//! @file nogara/expression/vector/reverse.hpp
//! @brief 逆順ベクトルクラス
//////////////////////////////////////////////

#include <nogara/expression/expression.hpp>
#include <nogara/expression/vector/traits.hpp>

__NOGARA_EXPRESSION_BEGIN

template<class E>
class ref_reverse_vector : public vector_expression<ref_reverse_vector<E> >{
    typedef ref_reverse_vector<E> self_type;
public:
    typedef typename E::value_type      value_type;
    typedef typename E::const_reference const_reference;
    typedef typename E::reference       reference;
    typedef vector_expression<E>&       argment_type;
    typedef get_dimension<E>            Dimension;

    ref_reverse_vector(argment_type e):value(e){}

    using vector_expression<self_type>::operator();
    reference operator ()(unsigned i){
        return value()(Dimension::value - 1 - i);
    }

    value_type operator ()(unsigned i) const {
        return value()(Dimension::value - 1 - i);
    }

    template<class EA>
    self_type& operator =(vector_expression<EA> const& e){
        for(std::size_t i = 0; i < get_dimension<EA>::value; ++i){
            operator()(i) = e()(i);
        }
        return *this;
    }

private:
    argment_type value;

};

template<class E>
class reverse_vector : public vector_expression<reverse_vector<E> >{
    typedef reverse_vector<E> self_type;
public:
    typedef typename E::value_type      value_type;
    typedef value_type                  const_reference;
    typedef value_type                  reference;
    typedef vector_expression<E> const& argment_type;
    typedef get_dimension<E>            Dimension;

    reverse_vector(argment_type e):value(e){}

    using vector_expression<self_type>::operator();
    value_type operator ()(unsigned i) const {
        return value()(Dimension::value - 1 - i);
    }

private:
    argment_type value;
};

template<class E>
inline typename boost::mpl::if_<
    boost::mpl::and_<result_is_reference<E>, boost::mpl::not_<boost::is_const<E> > >,
    ref_reverse_vector<E>, reverse_vector<E> >::type
reverse(vector_expression<E>& e){
    typedef typename boost::mpl::if_<
    boost::mpl::and_<result_is_reference<E>, boost::mpl::not_<boost::is_const<E> > >,
        ref_reverse_vector<E>, reverse_vector<E> >::type result;
    return result(e);
}

template<class E>
inline reverse_vector<E> reverse(vector_expression<E> const& e){
    return reverse_vector<E>(e);
}

__NOGARA_EXPRESSION_END

__NOGARA_BEGIN
using expression::reverse;
using expression::ref_reverse_vector;
using expression::reverse_vector;
__NOGARA_END

#endif
