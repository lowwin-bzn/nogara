#ifndef NOGARA_VECTOR_UNARY_EXPRESSION_HPP
#define NOGARA_VECTOR_UNARY_EXPRESSION_HPP

///////////////////////////////////////////////////////
//! @file nogara/expression/vector/unary_expression.hpp
//!
//! @brief ベクトルの単項演算の基礎となるクラス
///////////////////////////////////////////////////////

#include <nogara/expression/expression.hpp>
#include <nogara/expression/vector/traits.hpp>
#include <nogara/expression/vector/iterator.hpp>

///////////////////////////////////////////////////////
//! @brief 単項演算の基礎となるクラス
//!        単項演算式は基本vector_unary_baseを継承する
//!        継承先クラスはT apply(unsigned) const という
//!        メンバメソッドを持つ必要がある
///////////////////////////////////////////////////////

__NOGARA_EXPRESSION_BEGIN

template<class E, class Derived>
struct vector_unary_base : public vector_expression<Derived>{
    //! @brief データ型
    typedef typename E::value_type                value_type;
    typedef value_type                            reference;
    typedef value_type                            const_reference;
    //! @brief 式の種類を示すタグ
    typedef typename E::expression_category       expression_category;
    //! @brief 引数
    typedef vector_expression<E> const&           argment_type;
    //! @brief 次元数
    typedef get_dimension<E>                      Dimension;

    //! @brief イテレータ型
    typedef vector_iterator<Derived>              iterator;
    //! @brief constイテレータ型
    typedef iterator                              const_iterator;
    //! @brief 逆順イテレータ型
    typedef std::reverse_iterator<iterator>       reverse_iterator;
    //! @brief 逆順constイテレータ型
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    using vector_expression<Derived>::operator();
    //! @brief i番目の計算結果を返す
    value_type operator()(unsigned i)const {
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
    explicit vector_unary_base(argment_type val):value(val){}

protected:
    argment_type value;    
};


/////////////////////////////////////////
//! @brief 単項演算クラス
//!        第3テンプレート引数は
//!        static T apply(T const&)という
//!        クラスメソッドを持つ必要がある
/////////////////////////////////////////
template<class E, class F>
class vector_unary : public vector_unary_base<E, vector_unary<E, F> >{
    typedef vector_unary<E, F>              self_type;
    typedef vector_unary_base<E, self_type> base_type;
public:
    //! @brief コンストラクタ
    explicit vector_unary(typename base_type::argment_type val):base_type(val){}

    //! @brief i番目の計算結果を返す
    typename base_type::value_type apply(unsigned i)const {
        return F::apply(base_type::value()(i));
    }
};

__NOGARA_EXPRESSION_END

#endif
