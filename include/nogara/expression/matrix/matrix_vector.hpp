#ifndef NOGARA_EXPRESSION_MATRIX_VECTOR_HPP
#define NOGARA_EXPRESSION_MATRIX_VECTOR_HPP

////////////////////////////////////////////////////////
//! @file nogara/expression/matrix/matrix_vector.hpp
//! @brief 行列からベクトルを取り出すクラス
////////////////////////////////////////////////////////

#include <boost/mpl/if.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/type_traits.hpp>
#include <nogara/expression/expression.hpp>
#include <nogara/expression/traits.hpp>
#include <nogara/expression/vector/iterator.hpp>

///////////////////////////////////////////////
//! @brief 行列からベクトルを取り出すクラス群
//         行もしくは列の始点から終点を参照する
///////////////////////////////////////////////

__NOGARA_EXPRESSION_BEGIN

template<class E, std::size_t N, class Iter, class CIter, class Derived>
class matrix_vector_base : public vector_expression<Derived>{
protected:
    typedef E const& const_argment_type;
    typedef typename boost::mpl::if_<
        boost::is_const<E>, const_argment_type, E&>::type argment_type;
public:
    typedef Iter                         iterator;
    typedef CIter                        const_iterator;
    typedef std::reverse_iterator<Iter>  reverse_iterator;
    typedef std::reverse_iterator<CIter> const_reverse_iterator;
    typedef vector_tag                   expression_category;
    typedef typename E::value_type       value_type;
    typedef value_type&                  reference;
    typedef value_type const&            const_reference;
    typedef boost::mpl::size_t<N>        Dimension;

    using vector_expression<Derived>::operator();
    reference operator()(unsigned i){
        return operator()().apply(i);
    }
    const_reference operator()(unsigned i) const {
        return operator()().apply(i);
    }

    iterator begin(){
        return begin_;
    }
    const_iterator begin() const {
        return const_iterator(begin_);
    }
    iterator end(){
        return end_;
    }
    const_iterator end() const {
        return const_iterator(end_);
    }
    reverse_iterator rbegin(){
        return reverse_iterator(begin());
    }
    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(begin());
    }
    reverse_iterator rend(){
        return reverse_iterator(end());
    }
    const_reverse_iterator rend()   const {
        return const_reverse_iterator(end());
    }

    matrix_vector_base(Iter b, Iter e):begin_(b), end_(e){}

protected:
    Iter begin_, end_;
}; 

/////////////////////////////////////////////////
//! @brief 行ベクトルを取り出すためのクラス
/////////////////////////////////////////////////

template<class E>
class row_vector : public matrix_vector_base<
    E, get_row<E>::value,
    typename boost::mpl::if_<boost::is_const<E>,
                             typename E::const_row_iterator,
                             typename E::row_iterator>::type,
    typename E::const_row_iterator,
    row_vector<E> >
{
    typedef row_vector<E> self_type;
    typedef typename boost::mpl::if_<boost::is_const<E>,
                                     typename E::const_row_iterator,
                                     typename E::row_iterator>::type Iter;
    typedef typename E::const_row_iterator CIter;
    typedef matrix_vector_base<E, get_row<E>::value, Iter, CIter, self_type> base_type;
public:
    row_vector(typename base_type::argment_type value, unsigned pos):
        base_type(value().row_begin(pos), value().row_end(pos)){}
    row_vector(row_vector const& v):base_type(v.begin_, v.end_){}
    template<class T>
    row_vector(vector_expression<T> const& v){
        std::copy(v().begin(), v().end(), base_type::begin());
    }

    row_vector& operator=(row_vector const& v){
        if(&v != this){
            std::copy(v.begin(), v.end(), base_type::begin());            
        }
        return *this;
    }

    template<class T>
    row_vector& operator=(vector_expression<T> const& v){
        std::copy(v().begin(), v().end(), base_type::begin());
        return *this;
    }


    typename base_type::value_type& apply(unsigned i){
        return *(base_type::begin_ + i);
    }
    typename base_type::value_type const& apply(unsigned i) const {
        return *(base_type::begin_ + i);
    }
};

///////////////////////////////////////////
//! @brief 列ベクトルを取り出すためのクラス
///////////////////////////////////////////
template<class E>
class column_vector : public matrix_vector_base<
    E, get_column<E>::value, 
    typename boost::mpl::if_<
        boost::is_const<E>,
        typename E::const_column_iterator,
        typename E::column_iterator>::type,
    typename E::const_column_iterator,
    column_vector<E> >
{
    typedef column_vector<E> self_type;
    typedef typename boost::mpl::if_<
        boost::is_const<E>,
        typename E::const_column_iterator,
        typename E::column_iterator>::type Iter;
    typedef typename E::const_column_iterator CIter;
    typedef matrix_vector_base<E, get_column<E>::value, Iter, CIter, self_type> base_type;
public:
    column_vector(typename base_type::argment_type value, unsigned pos):
        base_type(value().column_begin(pos), value().column_end(pos)){}

    column_vector(column_vector const& v):base_type(v.begin_, v.end_){}
    template<class T>
    column_vector(vector_expression<T> const& v){
        std::copy(v().begin(), v().end(), base_type::begin());
    }

    column_vector& operator=(column_vector const& v){
        if(&v != this){
            std::copy(v.begin(), v.end(), base_type::begin());            
        }
        return *this;
    }

    template<class T>
    column_vector& operator=(vector_expression<T> const& v){
        std::copy(v().begin(), v().end(), base_type::begin());
        return *this;
    }

    typename base_type::value_type& apply(unsigned i){
        return *(base_type::begin_ + i);
    }
    typename base_type::value_type const& apply(unsigned i) const {
        return *(base_type::begin_ + i);
    }
private:
    unsigned base_pos;
};


//////////////////////////////////////////////////////////////
//! @brief 行列の式クラスから行ベクトルを取り出すためのクラス
//////////////////////////////////////////////////////////////
template<class E, std::size_t N>
class expr_row_vector : public vector_expression<expr_row_vector<E, N> >{
    typedef expr_row_vector<E, N> self_type;
public:
    typedef typename E::value_type                value_type;
    typedef typename E::reference                 reference;
    typedef typename E::const_reference           const_reference;
    typedef vector_iterator<self_type>            iterator;
    typedef iterator                              const_iterator;
    typedef std::reverse_iterator<iterator>       reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef expression::vector_tag                expression_category;
    typedef get_row<E>                            Dimension;
    
    expr_row_vector(matrix_expression<E> const& e):expr(e){}

    using vector_expression<self_type>::operator();
    value_type operator()(unsigned i) const {
        return expr()(i, N);
    }

    const_iterator         begin()  const {
        return const_iterator(*this);
    }
    const_iterator         end()    const {
        return const_iterator(*this, Dimension::value);
    }
    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(begin());
    }
    const_reverse_iterator rend()   const {
        return const_reverse_iterator(end());
    }
private:
    matrix_expression<E> const& expr;
};

/////////////////////////////////////////////////////////////
//! @brief 行列の式クラスから列ベクトルを取り出すためのクラス
/////////////////////////////////////////////////////////////
template<class E, std::size_t N>
class expr_column_vector : public vector_expression<expr_column_vector<E, N> >{
    typedef expr_column_vector<E, N> self_type;
public:
    typedef typename E::value_type                value_type;
    typedef typename E::reference                 reference;
    typedef typename E::const_reference           const_reference;
    typedef vector_iterator<self_type>            iterator;
    typedef iterator                              const_iterator;
    typedef std::reverse_iterator<iterator>       reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef expression::vector_tag                expression_category;
    typedef get_column<E>                         Dimension;

    expr_column_vector(matrix_expression<E> const& e):expr(e){}

    using vector_expression<self_type>::operator();
    value_type operator()(unsigned i) const {
        return expr()(N, i);
    }

    const_iterator         begin()  const {
        return const_iterator(*this);
    }
    const_iterator         end()    const {
        return const_iterator(*this, Dimension::value);
    }
    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(begin());
    }
    const_reverse_iterator rend()   const {
        return const_reverse_iterator(end());
    }

private:
    matrix_expression<E> const& expr;
};

__NOGARA_EXPRESSION_END

#endif
