#ifndef NOGARA_EXPRESSION_VECTOR_CONTAINER_BASE_HPP
#define NOGARA_EXPRESSION_VECTOR_CONTAINER_BASE_HPP

/////////////////////////////////////////////////////
//! @file  nogara/expression/container.hpp
//! @brief expression内で使用するコンテナ(16要素まで)
/////////////////////////////////////////////////////

#include <iterator>
#include <algorithm>
#include <nogara/expression/define.hpp>
#include <boost/mpl/size_t.hpp>

#include "define_container_macros.hpp"

__NOGARA_EXPRESSION_BEGIN

/////////////////////////////////////////////
//! @brief ベクトルに使用するコンテナの基礎
/////////////////////////////////////////////
template<class C, class T, std::size_t N>
class expression_container_base{
    typedef C                     container_type;
    typedef container_type&       container_reference;
    typedef container_type const& container_const_reference;
public:
    typedef T                                     value_type;
    typedef value_type&                           reference;
    typedef value_type const&                     const_reference;
    typedef reference                             result_type;
    typedef value_type*                           pointer;
    typedef value_type const*                     const_pointer;
    typedef pointer                               iterator;
    typedef const_pointer                         const_iterator;
    typedef std::reverse_iterator<iterator>       reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef boost::mpl::size_t<N>                 Dimension;

    static std::size_t size(){return Dimension::value;}
    
    reference       operator()(unsigned i)       {return begin()[i];}
    const_reference operator()(unsigned i) const {return begin()[i];}
    reference       operator[](unsigned i)       {return begin()[i];}
    const_reference operator[](unsigned i) const {return begin()[i];}

    void swap(expression_container_base& c){
        std::iter_swap(c.begin(), begin());
    }

    template<class D, class U>
    void swap(expression_container_base<D, U, N>& c){
        std::iter_swap(c.begin(), begin());
    }

    iterator               begin()        {return &container()._0;}
    const_iterator         begin()  const {return &container()._0;}
    iterator               end()          {return begin() + size();}
    const_iterator         end()    const {return begin() + size();}
    reverse_iterator       rbegin()       {return reverse_iterator(begin());}
    const_reverse_iterator rbegin() const {return reverse_iterator(begin());}
    reverse_iterator       rend()         {return reverse_iterator(end());}
    const_reverse_iterator rend()   const {return reverse_iterator(end());}

private:
    container_reference       container()       {return *static_cast<C*>(this);}
    container_const_reference container() const {return *static_cast<C const*>(this);}
};

/////////////////////////////////////////////
//! @brief ベクトルに使用するコンテナ
/////////////////////////////////////////////
template<typename T, std::size_t N>
struct expression_container;

template<typename T>
class expression_container<T, 1> : public expression_container_base<
    expression_container<T, 1>, T, 1>
{
    typedef expression_container<T, 1> self_type;
    typedef expression_container_base<self_type, T, 1> base_type;
public:
    
    using base_type::swap;
    MAKE_CONSTRUCTOR(1)
    MAKE_ASSIGN(1)
    T _0;
};

template<typename T>
class expression_container<T, 2> : public expression_container_base<
    expression_container<T, 2>, T, 2>
{
    typedef expression_container<T, 2> self_type;
    typedef expression_container_base<self_type, T, 2> base_type;
public:
    
    using base_type::swap;
    MAKE_CONSTRUCTOR(2)
    MAKE_ASSIGN(2)
    T _0, _1;
};

template<typename T>
class expression_container<T, 3> : public expression_container_base<
    expression_container<T, 3>, T, 3>
{
    typedef expression_container<T, 3> self_type;
    typedef expression_container_base<self_type, T, 3> base_type;
public:
    
    using base_type::swap;
    MAKE_CONSTRUCTOR(3)
    MAKE_ASSIGN(3)
    T _0, _1, _2;
};

template<typename T>
class expression_container<T, 4> : public expression_container_base<
    expression_container<T, 4>, T, 4>
{
    typedef expression_container<T, 4> self_type;
    typedef expression_container_base<self_type, T, 4> base_type;
public:
    using base_type::swap;
    MAKE_CONSTRUCTOR(4)
    MAKE_ASSIGN(4)
    T _0, _1, _2, _3;
};

template<typename T>
class expression_container<T, 5> : public expression_container_base<
    expression_container<T, 5>, T, 5>
{
    typedef expression_container<T, 5> self_type;
    typedef expression_container_base<self_type, T, 5> base_type;
public:
    using base_type::swap;
    MAKE_CONSTRUCTOR(5)
    MAKE_ASSIGN(5)
    T _0, _1, _2, _3, _4;
};

template<typename T>
class expression_container<T, 6> : public expression_container_base<
    expression_container<T, 6>, T, 6>
{
    typedef expression_container<T, 6> self_type;
    typedef expression_container_base<self_type, T, 6> base_type;
public:
    using base_type::swap;
    MAKE_CONSTRUCTOR(6)    
    MAKE_ASSIGN(6)
    T _0, _1, _2, _3, _4, _5;
};

template<typename T>
class expression_container<T, 7> : public expression_container_base<
    expression_container<T, 7>, T, 7>
{
    typedef expression_container<T, 7> self_type;
    typedef expression_container_base<self_type, T, 7> base_type;
public:
    using base_type::swap;
    MAKE_CONSTRUCTOR(7)
    MAKE_ASSIGN(7)
    T _0, _1, _2, _3, _4, _5, _6;
};

template<typename T>
class expression_container<T, 8> : public expression_container_base<
    expression_container<T, 8>, T, 8>
{
    typedef expression_container<T, 8> self_type;
    typedef expression_container_base<self_type, T, 8> base_type;
public:
    using base_type::swap;
    MAKE_CONSTRUCTOR(8)
    MAKE_ASSIGN(8)
    T _0, _1, _2, _3;
    T _4, _5, _6, _7;
};


template<typename T>
class expression_container<T, 9> : public expression_container_base<
    expression_container<T, 9>, T, 9>
{
    typedef expression_container<T, 9> self_type;
    typedef expression_container_base<self_type, T, 9> base_type;
public:
    using base_type::swap;
    MAKE_CONSTRUCTOR(9)
    MAKE_ASSIGN(9)
    T  _0,  _1,  _2, _3;
    T  _4,  _5,  _6, _7;
    T  _8;
};

template<typename T>
class expression_container<T, 10> : public expression_container_base<
    expression_container<T, 10>, T, 10>
{
    typedef expression_container<T, 10> self_type;
    typedef expression_container_base<self_type, T, 10> base_type;
public:
    using base_type::swap;
    MAKE_CONSTRUCTOR(10)
    MAKE_ASSIGN(10)
    T  _0,  _1,  _2, _3;
    T  _4,  _5,  _6, _7;
    T  _8,  _9;
};

template<typename T>
class expression_container<T, 11> : public expression_container_base<
    expression_container<T, 11>, T, 11>
{
    typedef expression_container<T, 11> self_type;
    typedef expression_container_base<self_type, T, 11> base_type;
public:
    using base_type::swap;
    MAKE_CONSTRUCTOR(11)
    MAKE_ASSIGN(11)
    T  _0,  _1,  _2, _3;
    T  _4,  _5,  _6, _7;
    T  _8,  _9, _10;
};

template<typename T>
class expression_container<T, 12> : public expression_container_base<
    expression_container<T, 12>, T, 12>
{
    typedef expression_container<T, 12> self_type;
    typedef expression_container_base<self_type, T, 12> base_type;
public:
    using base_type::swap;
    MAKE_CONSTRUCTOR(12)
    MAKE_ASSIGN(12)
    T  _0,  _1,  _2, _3;
    T  _4,  _5,  _6, _7;
    T  _8,  _9, _10, _11;
};

template<typename T>
class expression_container<T, 13> : public expression_container_base<
    expression_container<T, 13>, T, 13>
{
    typedef expression_container<T, 13> self_type;
    typedef expression_container_base<self_type, T, 13> base_type;
public:
    using base_type::swap;
    MAKE_CONSTRUCTOR(13)
    MAKE_ASSIGN(13)
    T  _0,  _1,  _2, _3;
    T  _4,  _5,  _6, _7;
    T  _8,  _9, _10, _11;
    T _12;
};

template<typename T>
class expression_container<T, 14> : public expression_container_base<
    expression_container<T, 14>, T, 14>
{
    typedef expression_container<T, 14> self_type;
    typedef expression_container_base<self_type, T, 14> base_type;
public:
    using base_type::swap;
    MAKE_CONSTRUCTOR(14)
    MAKE_ASSIGN(14)
    T  _0,  _1,  _2, _3;
    T  _4,  _5,  _6, _7;
    T  _8,  _9, _10, _11;
    T _12, _13;
};

template<typename T>
class expression_container<T, 15> : public expression_container_base<
    expression_container<T, 15>, T, 15>
{
    typedef expression_container<T, 15> self_type;
    typedef expression_container_base<self_type, T, 15> base_type;
public:
    using base_type::swap;
    MAKE_CONSTRUCTOR(15)
    MAKE_ASSIGN(15)
    T  _0,  _1,  _2, _3;
    T  _4,  _5,  _6, _7;
    T  _8,  _9, _10, _11;
    T _12, _13, _14;
};

template<typename T>
class expression_container<T, 16> : public expression_container_base<
    expression_container<T, 16>, T, 16>
{
    typedef expression_container<T, 16> self_type;
    typedef expression_container_base<self_type, T, 16> base_type;
public:
    using base_type::swap;
    MAKE_CONSTRUCTOR(16)
    MAKE_ASSIGN(16)
    T  _0,  _1,  _2, _3;
    T  _4,  _5,  _6, _7;
    T  _8,  _9, _10, _11;
    T _12, _13, _14, _15;
};


template<typename T, std::size_t N>
void swap(expression_container<T, N>& l, expression_container<T, N>& r){
    l.swap(r);
}

__NOGARA_EXPRESSION_END

#include "undef_container_macros.hpp"

#endif
