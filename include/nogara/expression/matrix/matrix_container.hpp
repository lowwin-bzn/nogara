#ifndef MATRIX_CONTAINER_HPP
#define MATRIX_CONTAINER_HPP

/////////////////////////////////////////////////////////////////
//! @file  nogara/expression/matrix/matrix_container.hpp
//! @brief 行列クラスの基本的動作や配列を持つクラスを記述している
/////////////////////////////////////////////////////////////////

#include <nogara/array.hpp>
#include <boost/mpl/size_t.hpp>
#include <nogara/expression/matrix/matrix_vector.hpp>
#include <nogara/expression/matrix/iterator.hpp>
#include <nogara/expression/matrix/operator.hpp>
#include <iterator>

__NOGARA_EXPRESSION_BEGIN

template<typename T, std::size_t R, std::size_t C, class Derived>
class matrix_container : public matrix_expression<Derived>{
    typedef matrix_container<T, R, C, Derived> self_type;
    typedef nogara::array<T, R * C>            container_type;

public:
    typedef T        value_type;
    typedef T&       reference;
    typedef T const& const_reference;
    typedef matrix_iterators::row_iterator<self_type>          row_iterator;
    typedef matrix_iterators::const_row_iterator<self_type>    const_row_iterator;
    typedef matrix_iterators::column_iterator<self_type>       column_iterator;
    typedef matrix_iterators::const_column_iterator<self_type> const_column_iterator;
    typedef std::reverse_iterator<row_iterator>                reverse_row_iterator;
    typedef std::reverse_iterator<const_row_iterator>          const_reverse_row_iterator;
    typedef std::reverse_iterator<column_iterator>             reverse_column_iterator;
    typedef std::reverse_iterator<const_column_iterator>       const_reverse_column_iterator;

    typedef boost::mpl::size_t<R> Row;
    typedef boost::mpl::size_t<C> Column;
    //typedef boost::mpl::size_t<0> Weight;

    matrix_container(){}

    template<class E>
    matrix_container(matrix_expression<E> const& e){assign(e);}

    using matrix_expression<Derived>::operator();
    reference operator ()(unsigned x, unsigned y){
        return data()[x * get_row<self_type>::value + y];
    }

    const_reference operator ()(unsigned x, unsigned y) const {
        return data()[x * get_row<self_type>::value + y];
    }

    container_type&       data()       {return container;}
    container_type const& data() const {return container;}
    value_type*        pointer()       {return &container[0];}
    value_type const*  pointer() const {return &container[0];}

    template<class E>
    self_type& operator =(matrix_expression<E> const& e){
        return assign(e);
    }

    self_type& operator =(self_type const& e){
        return (&e != this) ? assign(e) : *this;
    }

    //行ベクトル生成メソッド
    row_vector<Derived>       rows(unsigned i){
        return row_vector<Derived>(operator()(), i);
    }
    //行ベクトル生成メソッド
    row_vector<Derived const> rows(unsigned i) const {
        return row_vector<Derived const>(operator()(), i);
    }

    //! @brief 列ベクトル生成メソッド
    column_vector<Derived>       columns(unsigned i){
        return column_vector<Derived>(operator()(), i);
    }

    //! @brief 列ベクトル生成メソッド
    column_vector<Derived const> columns(unsigned i) const {
        return column_vector<Derived const>(operator()(), i);
    }

    row_iterator row_begin(unsigned i){
        return row_iterator(operator()(), i);
    }
    const_row_iterator row_begin(unsigned i) const{
        return const_row_iterator(operator()(), i);
    }

    row_iterator row_end(unsigned i){
        return row_iterator(operator()(), i, Row::value);
    }
    const_row_iterator row_end(unsigned i) const{
        return const_row_iterator(operator()(), i, Row::value);
    }

    reverse_row_iterator row_rbegin(unsigned i){
        return reverse_row_iterator(row_begin(i));
    }
    const_reverse_row_iterator row_rbegin(unsigned i) const{
        return const_reverse_row_iterator(row_begin(i));
    }

    reverse_row_iterator row_rend(unsigned i){
        return reverse_row_iterator(row_end(i));
    }
    const_reverse_row_iterator row_rend(unsigned i) const{
        return const_reverse_row_iterator(row_end(i));
    }

    column_iterator column_begin(unsigned i){
        return column_iterator(operator()(), i);
    }
    const_column_iterator column_begin(unsigned i) const{
        return const_column_iterator(operator()(), i);
    }

    column_iterator column_end(unsigned i){
        return column_iterator(operator()(), i, Row::value);
    }
    const_column_iterator column_end(unsigned i) const{
        return const_column_iterator(operator()(), i, Row::value);
    }

    reverse_column_iterator column_rbegin(unsigned i){
        return reverse_column_iterator(column_begin(i));
    }
    const_reverse_column_iterator column_rbegin(unsigned i) const{
        return const_reverse_column_iterator(column_begin(i));
    }

    reverse_column_iterator column_rend(unsigned i){
        return reverse_column_iterator(column_end(i));
    }
    const_reverse_column_iterator column_rend(unsigned i) const{
        return const_reverse_column_iterator(column_end(i));
    }

    template<class E>
    inline typename boost::enable_if<matrix_equal_to<E, Row, Column>, self_type&>::type
    assign(matrix_expression<E> const& e){
        for(unsigned y = 0; y < get_column<self_type>::value; ++y){
            for(unsigned x = 0; x < get_row<self_type>::value; ++x){
                (*this)(x, y) = e()(x, y);
            }
        }
        return *this;
    }

protected:
    container_type container;
};

__NOGARA_EXPRESSION_END

#endif
