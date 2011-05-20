#ifndef NOGARA_EXPRESSION_VECTOR4_HPP
#define NOGARA_EXPRESSION_VECTOR4_HPP

//////////////////////////////////////////////
//! @file nogara/expression/vector/vector4.hpp
//! @brief 4次元ベクトルクラス
//////////////////////////////////////////////

#include <nogara/expression/container.hpp>
#include <nogara/expression/vector/vector_container.hpp>
#include <nogara/expression/vector/operator.hpp>

//////////////////////////////
//! @brief 4次元ベクトルクラス
//! @param T データ型
//////////////////////////////

__NOGARA_EXPRESSION_BEGIN

template<typename T>
class vector4 : public vector_container<vector4<T>, T>{
    // 自身の型
    typedef vector4<T>                     self_type;
    // 親の型
    typedef vector_container<self_type, T> base_type;
    // コンテナ型
    typedef expression_container<T, 4>     container_type;
    // コンテナの参照型
    typedef container_type&                container_reference;
    // コンテナのconst参照型
    typedef container_type const&          container_const_reference;

    typedef typename deduct1<T>::real_type r_t_;
    //normalizeの戻り値型の簡略化
    typedef vector_and_scalar<self_type, r_t_, scalar_mul<T, r_t_> >   normalize_expression;

public:
    //! @brief 自身のデータ型
    typedef typename container_type::value_type             value_type;
    //! @brief データ型の参照型
    typedef value_type&                                     reference;
    //! @brief データ型のconst参照型
    typedef value_type const&                               const_reference;
    //! @brief 自身の実数型(Tが実数型の場合はそのまま、整数型の場合は適宜変更)
    typedef typename deduct1<value_type>::real_type   real_type;
    //! @brief 式の種類を示すタグ
    typedef expression::vector_tag                          expression_category;
    //! @brief 次元数
    typedef get_dimension<container_type>                   Dimension;
    //! @brief イテレータ型
    typedef typename container_type::iterator               iterator;
    //! @brief constイテレータ型
    typedef typename container_type::const_iterator         const_iterator;
    //! @brief 逆順イテレータ型
    typedef typename container_type::reverse_iterator       reverse_iterator;
    //! @brief 逆順constイテレータ型
    typedef typename container_type::const_reverse_iterator const_reverse_iterator;

    //! @brief コンストラクタ
    vector4():container(){}
    //! @brief コピーコンストラクタ 他の4次元ベクトルからの初期化
    vector4(vector4 const& other):container(other.data()){}
    //! @brief コンストラクタ 要素の初期化
    vector4(T const& x, T const& y, T const& z, T const& w):container(x, y, z, w){}
    //! @brief コンストラクタ 配列からの初期化
    vector4(value_type (&ary)[Dimension::value]):container(ary[0], ary[1], ary[2], ary[3]){}

    //! @brief コンストラクタ ベクトル式からの初期化
    template<class E>
    vector4(vector_expression<E> const& e):container(get<0>(e), get<1>(e), get<2>(e), get<3>(e)){}

    //! @brief コンストラクタ 3次元ベクトル式からの初期化
    //!        第4要素には1を代入
    template<class E>
    vector4(vector_expression<E> const& e,
            typename boost::enable_if<dimension_equal_to_c<E, 3> >::type* = 0):
        container(get<0>(e), get<1>(e), get<2>(e), value_type(1)){}
#if defined(NG_CPP0X)
    //! @brief ムーブコンストラクタ。C++0X対応のコンパイラであれば定義される
    vector4(vector4&& other):container(std::forward<container_type>(other.container)){}
#endif

    //! @brief 他の3次元ベクトルから代入
    self_type& operator =(vector4 const& v){
        if(&v != this){
            container = v.data();
        }
        return *this;
    }

    //! @brief ベクトル式からの代入
    template<class E>
    typename boost::enable_if<same_dimension<self_type, E>, self_type&>::type
    operator =(vector_expression<E> const& e){
        x(get<0>(e)); y(get<1>(e)); z(get<2>(e)); w(get<3>(e));
        return *this;
    }
#if defined(NG_CPP0X)
    //! @brief ムーブ代入 C++0X対応のコンパイラであれば定義される
    self_type& operator =(vector4&& v){
        container = std::move(v.container);
        return *this;
    }
#endif

    //! @brief ベクトル式を加算する
    template<class E>
    self_type& operator +=(vector_expression<E> const& e){
        return (*this = *this + e);
    }

    //! @brief ベクトル式を減算する
    template<class E>
    self_type& operator -=(vector_expression<E> const& e){
        return (*this = *this - e);
    }

    //! @brief スカラ値を乗算する
    template<class V>
    self_type& operator *=(V const& val){
        return (*this = *this * val);
    }

    //! @brief スカラ値を除算する
    template<class V>
    self_type& operator /=(V const& val){
        return (*this = *this / val);
    }

    //! @brief xの値
    value_type const& x()    const {return data()(0);}
    //! @brief xに代入する
    void x(value_type const& value){data()(0) = value;}
    //! @brief yの値
    value_type const& y()    const {return data()(1);}
    //! @brief yに代入する
    void y(value_type const& value){data()(1) = value;}
    //! @brief zの値
    value_type const& z()    const {return data()(2);}
    //! @brief zに代入する
    void z(value_type const& value){data()(2) = value;}
    //! @brief wの値
    value_type const& w()    const {return data()(3);}
    //! @brief wに代入する
    void w(value_type const& value){data()(3) = value;}

    //! @brief コンテナを返す
    container_reference       data()       {return container;}
    //! @brief コンテナを返す
    container_const_reference data() const {return container;}
    //! @brief コンテナの大きさ
    std::size_t size() const {return container.size();}

    //! @brief イテレータの始点
    iterator               begin()        {return container.begin();}
    //! @brief イテレータの始点
    const_iterator         begin()  const {return container.begin();}
    //! @brief イテレータの終点
    iterator               end()          {return container.end();}
    //! @brief イテレータの終点
    const_iterator         end()    const {return container.end();}
    //! @brief 逆順イテレータの始点
    reverse_iterator       rbegin()       {return container.rbegin();}
    //! @brief 逆順イテレータの始点
    const_reverse_iterator rbegin() const {return container.rbegin();}
    //! @brief 逆順イテレータの終点
    reverse_iterator       rend()         {return container.rend();}
    //! @brief 逆順イテレータの終点
    const_reverse_iterator rend()   const {return container.rend();}

    //! @brief ゼロベクトル
    static self_type const zero;
    //! @brief xの単位ベクトル
    static self_type const unit_x;
    //! @brief yの単位ベクトル
    static self_type const unit_y;
    //! @brief zの単位ベクトル
    static self_type const unit_z;
    //! @brief wの単位ベクトル
    static self_type const unit_w;

private:
    container_type container;
};

template<typename T>
vector4<T> const vector4<T>::zero(T(0), T(0), T(0), T(0));
template<typename T>
vector4<T> const vector4<T>::unit_x(T(1), T(0), T(0), T(0));
template<typename T>
vector4<T> const vector4<T>::unit_y(T(0), T(1), T(0), T(0));
template<typename T>
vector4<T> const vector4<T>::unit_z(T(0), T(0), T(1), T(0));
template<typename T>
vector4<T> const vector4<T>::unit_w(T(0), T(0), T(0), T(1));

///////////////////////////////////////////
//! @brief 次元数と等しいベクトル型を返す
//!        4次元ベクトルに対する特殊化
///////////////////////////////////////////
template<class T> struct vector_type<T, 4>{
    typedef vector4<T> type;
};

__NOGARA_EXPRESSION_END

__NOGARA_BEGIN
using expression::vector4;
__NOGARA_END

#endif
