#ifndef NOGARA_EXPRESSION_VECTOR_CONTAINER_HPP
#define NOGARA_EXPRESSION_VECTOR_CONTAINER_HPP

///////////////////////////////////////////////////////
//! @file nogara/expression/vector/vector_container.hpp
//! @brief ベクトルの基本的動作を記述したクラス
///////////////////////////////////////////////////////

#include <iterator>
#include <algorithm>
#include <nogara/expression/expression.hpp>

////////////////////////////////
//! @namespace nogara
////////////////////////////////

__NOGARA_EXPRESSION_BEGIN

///////////////////////////////////////////////
//! @brief ベクトルの基本的動作を記述したクラス
///////////////////////////////////////////////
template<class V, typename T>
struct vector_container : public vector_expression<V>{
    //! @brief データ型
    typedef T                                     value_type;
    //! @brief データ型の参照型
    typedef value_type&                           reference;
    //! @brief データ型のconst参照型
    typedef value_type const&                     const_reference;
    //! @brief イテレータ型
    typedef value_type*                           iterator;
    //! @brief constイテレータ型
    typedef value_type const*                     const_iterator;
    //! @brief 逆順イテレータ型
    typedef std::reverse_iterator<iterator>       reverse_iterator;
    //! @brief const逆順イテレータ型
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    //! @brief イテレータの始点
    iterator       begin()       {return &(operator()().data()(0));}
    //! @brief イテレータの始点
    const_iterator begin() const {return &(operator()().data()(0));}
    //! @brief イテレータの終点
    iterator       end()         {return begin() + operator()().size();}
    //! @brief イテレータの終点
    const_iterator end()   const {return begin() + operator()().size();}

    //! @brief 逆順イテレータの始点
    reverse_iterator       rbegin()       {return reverse_iterator(begin());}
    //! @brief 逆順イテレータの始点
    const_reverse_iterator rbegin() const {return const_reverse_iterator(begin());}
    //! @brief 逆順イテレータの終点
    reverse_iterator       rend()         {return reverse_iterator(end());}
    //! @brief 逆順イテレータの終点
    const_reverse_iterator rebd()   const {return const_reverse_iterator(end());}

    using vector_expression<V>::operator();
    //! @brief i番目の要素の値を取り出す
    reference       operator ()(unsigned i)       {return begin()[i];}
    //! @brief i番目の要素の値を取り出す
    const_reference operator ()(unsigned i) const {return begin()[i];}
    //! @brief i番目の要素の値を取り出す
    reference       operator [](unsigned i)       {return begin()[i];}
    //! @brief i番目の要素の値を取り出す
    const_reference operator [](unsigned i) const {return begin()[i];}

    //! @brief 値の交換を行う
    void swap(vector_container& c){std::iter_swap(begin(), c.begin());}
};

__NOGARA_EXPRESSION_END

#endif
