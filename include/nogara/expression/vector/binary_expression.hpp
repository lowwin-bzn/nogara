#ifndef NOGARA_VECTOR_BINARY_EXPRESSION_HPP
#define NOGARA_VECTOR_BINARY_EXPRESSION_HPP

 ////////////////////////////////////////////////////////
//! @file nogara/expression/vector/binary_expression.hpp
//!
//! @brief ベクトルの二項演算の基礎となるクラス
////////////////////////////////////////////////////////

#include <nogara/expression/expression.hpp>
#include <nogara/expression/vector/iterator.hpp>
#include <nogara/expression/vector/traits.hpp>
#include <nogara/type_traits/deduct.hpp>

__NOGARA_EXPRESSION_BEGIN

///////////////////////////////////////////////////////
//! @brief ベクトルの二項演算の基礎となるクラス
//!        二項演算式は基本vector_binary_baseを継承する
//!        継承先クラスはT apply(unsigned) const という
//!        メンバメソッドを持つ必要がある
///////////////////////////////////////////////////////
template<class E1, class E2, class E>
struct vector_binary_base : public vector_expression<E>{
    //! @brief 二項のデータ型から類推した型
    typedef typename deduct2<E1, E2>::value_type         value_type;
    typedef value_type                                   reference;
    typedef value_type                                   const_reference;
    //! @brief 式の種類を示すタグ
    typedef typename vector_expression_tag<E1, E2>::type expression_category;
    //! @brief 左辺
    typedef vector_expression<E1> const&                 argment1_type;
    //! @brief 右辺
    typedef vector_expression<E2> const&                 argment2_type;
    //! @brief 次元数
    typedef get_same_dimension<E1, E2>                   Dimension;
    //! @brief イテレータ型
    typedef vector_iterator<E>                           iterator;
    //! @brief constイテレータ型
    typedef iterator                                     const_iterator;
    //! @brief 逆順イテレータ型
    typedef std::reverse_iterator<iterator>              reverse_iterator;
    //! @brief 逆順constイテレータ型
    typedef std::reverse_iterator<const_iterator>        const_reverse_iterator;


    using vector_expression<E>::operator();
    //! @brief i番目の計算結果を返す
    value_type operator()(unsigned i) const {
        return operator()().apply(i);
    }

    //! @brief イテレータの始点
    const_iterator         begin()  const {return const_iterator(operator()());}
    //! @brief イテレータの終点
    const_iterator         end()    const {return const_iterator(operator()(), Dimension::value);}
    //! @brief 逆順イテレータの始点
    const_reverse_iterator rbegin() const {return const_reverse_iterator(begin());}
    //! @brief 逆順イテレータの終点
    const_reverse_iterator rend()   const {return const_reverse_iterator(end());}

protected:
    //! @brief コンストラクタ
    vector_binary_base(argment1_type e1, argment2_type e2):left(e1), right(e2){}

protected:
    argment1_type left;
    argment2_type right;
};


///////////////////////////////////////////////////
//! @brief 二項演算クラス
//!        第3テンプレート引数は
//!        static T apply(U const&, V const&)という
//!        クラスメソッドを持つ必要がある
///////////////////////////////////////////////////

template<class E1, class E2, class F>
class vector_binary : public vector_binary_base<E1, E2, vector_binary<E1, E2, F> >{
    typedef vector_binary<E1, E2, F>              self_type;
    typedef vector_binary_base<E1, E2, self_type> base_type;
public:
    //! @brief コンストラクタ
    vector_binary(typename base_type::argment1_type e1,
                  typename base_type::argment2_type e2):
        base_type(e1, e2){}

    //! @brief i番目の計算結果を返す
    typename base_type::value_type apply(unsigned i) const {
        return F::apply(base_type::left()(i), base_type::right()(i));
    }
};

__NOGARA_EXPRESSION_END

#endif
