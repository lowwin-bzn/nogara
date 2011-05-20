#ifndef NOGARA_EXPRESSION_DIAGONAL_MATRIX_HPP
#define NOGARA_EXPRESSION_DIAGONAL_MATRIX_HPP

//////////////////////////////////////////////////////
//! @file nogara/expression/matrix/diagonal_matrix.hpp
//! @brief 対角行列
//////////////////////////////////////////////////////
#include <nogara/array.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/utility/enable_if.hpp>
#include <nogara/expression/expression.hpp>

__NOGARA_EXPRESSION_BEGIN

//////////////////////////////////////////////////////
//! @brief 対角行列
//////////////////////////////////////////////////////
template<typename T, std::size_t N>
class diagonal_matrix : public matrix_expression<diagonal_matrix<T, N> >{
    typedef diagonal_matrix<T, N> self_type;
    typedef nogara::array<T, N>   container_type;

public:
    typedef T        value_type;
    typedef T&       reference;
    typedef T const& const_reference;

    typedef expression::matrix_tag expression_category;

    typedef boost::mpl::size_t<N> Row;
    typedef boost::mpl::size_t<N> Column;

    diagonal_matrix(){}
    diagonal_matrix(self_type const& e){
        assign(e);
    }

    diagonal_matrix(value_type const (&a)[N]){
        for(std::size_t i = 0; i < N; ++i){
            data()[i] = a[i];
        }
    }

    template<class E>
    diagonal_matrix(vector_expression<E> const& v,
                    typename boost::enable_if<dimension_equal_to_c<E, N> >::type* = 0)
    {
        for(std::size_t i = 0; i < N; ++i){
            data()[i] = v()(i);
        }
    }

    diagonal_matrix(container_type const &c):container(c){}

    using matrix_expression<self_type>::operator();
    value_type operator ()(std::size_t x, std::size_t y) const {
        return (x == y) ? data()[x] : value_type();
    }

    container_type&       data()       {return container;}
    container_type const& data() const {return container;}

    self_type& operator =(self_type const& e){
        return (&e != this) ? assign(e) : *this;
    }

    self_type& assign(self_type const& e){
        container = e.data();
        return *this;
    }

private:
    container_type container;
};

///////////////////////////////////////////////////////////////////////
//! @brief 2次元, 3次元の対角行列を生成する関数
//!        主にオブジェクトの拡大、縮小に使用するためscale_matrixとする
///////////////////////////////////////////////////////////////////////

template<typename T>
inline diagonal_matrix<T, 3>
scale_matrix(T const& x, T const& y, T const& z){
    nogara::array<T, 3> values = {{x, y, z}};
    return diagonal_matrix<T, 3>(values);
}

template<typename T>
inline diagonal_matrix<T, 2>
scale_matrix(T const& x, T const& y){
    nogara::array<T, 2> values = {{x, y}};
    return diagonal_matrix<T, 2>(values);
}

template<class E>
inline typename boost::enable_if<
    dimension_equal_to_c<E, 3>, diagonal_matrix<typename E::value_type, 3> >::type
scale_matrix(vector_expression<E> const& v){
    return diagonal_matrix<typename E::value_type, 3>(v);
}

template<class E>
inline typename boost::enable_if<
    dimension_equal_to_c<E, 2>, diagonal_matrix<typename E::value_type, 2> >::type
scale_matrix(vector_expression<E> const& v){
    return diagonal_matrix<typename E::value_type, 2>(v);
}

__NOGARA_EXPRESSION_END

__NOGARA_BEGIN
using expression::diagonal_matrix;
using expression::scale_matrix;
__NOGARA_END

#endif
