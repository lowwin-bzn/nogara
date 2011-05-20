#ifndef NOGARA_EXPRESSION_SCALAR_VECTOR_HPP
#define NOGARA_EXPRESSION_SCALAR_VECTOR_HPP

#include <nogara/expression/vector/iterator.hpp>
#include <nogara/type_traits/deduct.hpp>

/////////////////////////////////////////////////////
//! @file nogara/expression/vector/scalar_vector.hpp
//! @brief 一つの値のみで構成されているベクトルクラス
/////////////////////////////////////////////////////

__NOGARA_EXPRESSION_BEGIN

/////////////////////////////////////////////////////
//! @brief 一つの値のみで構成されているベクトルクラス
/////////////////////////////////////////////////////
template<typename T, std::size_t N>
class scalar_vector : public vector_expression<scalar_vector<T, N> >{
    // 自身の型
    typedef scalar_vector<T, N> self_type;
public:
    //! @brief データ型
    typedef T                                             value_type;
    //! @brief データ型の参照型
    typedef value_type&                                   reference;
    //! @brief データ型のconst参照型
    typedef value_type const&                             const_reference;
    //! @brief 自身の実数型(Tが実数型の場合はそのまま、整数型の場合は適宜変更)
    typedef typename deduct1<value_type>::real_type       real_type;
    //! @brief 式の種類を示すタグ
    typedef nogara::expression::vector_tag                expression_category;
    //! @brief 次元数
    typedef boost::mpl::size_t<N>                         Dimension;
    //! @brief イテレータ型
    typedef vector_iterator<self_type>                    iterator;
    //! @brief constイテレータ型
    typedef iterator                                      const_iterator;
    //! @brief 逆順イテレータ型
    typedef std::reverse_iterator<iterator>               reverse_iterator;
    //! @brief const逆順イテレータ型
    typedef std::reverse_iterator<const_iterator>         const_reverse_iterator;

    //! @brief コンストラクタ
    scalar_vector(){}
    //! @brief コンストラクタ 要素の初期化
    scalar_vector(T const& v):value(v){}
    //! @brief コピーコンストラクタ
    scalar_vector(self_type const& e):value(e.value){}

    using vector_expression<self_type>::operator();
    //! @brief i番目の要素の値を取り出す
    reference       operator ()(unsigned)       {return value;}
    //! @brief i番目の要素の値を取り出す
    const_reference operator ()(unsigned) const {return value;}
    //! @brief i番目の要素の値を取り出す
    reference       operator [](unsigned)       {return value;}
    //! @brief i番目の要素の値を取り出す
    const_reference operator [](unsigned) const {return value;}

    //! @brief イテレータの始点
    const_iterator         begin()  const {return const_iterator(operator()());}
    //! @brief イテレータの終点
    const_iterator         end()    const {return const_iterator(operator()(), Dimension::value);}
    //! @brief 逆順イテレータの始点
    const_reverse_iterator rbegin() const {return const_reverse_iterator(begin());}
    //! @brief 逆順イテレータの終点
    const_reverse_iterator rend()   const {return const_reverse_iterator(end());}

public:
    //! @brief 1のみで構成されたベクトル
    static self_type const one;

private:
    T value;
};

template<typename T, std::size_t N>
scalar_vector<T, N> const scalar_vector<T, N>::one(T(1));

__NOGARA_EXPRESSION_END

__NOGARA_BEGIN
using expression::scalar_vector;
__NOGARA_END
#endif
