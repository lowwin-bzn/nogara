#ifndef NOGARA_EXPRESSION_ACCESSOR_HPP
#define NOGARA_EXPRESSION_ACCESSOR_HPP

//! @file  nogara/expression/accessor.hpp

#include <nogara/expression/expression.hpp>
#include <nogara/expression/traits.hpp>

__NOGARA_EXPRESSION_BEGIN

namespace accessor{
    //! @brief ベクトルのx値を取得する
    template<class E>
    inline typename E::reference       x(vector_expression<E>&       e){
        return get<is_quaternion<E>::value ? 1 : 0>(e);
    }
    //! @brief ベクトルのx値を取得する
    template<class E>
    inline typename E::const_reference x(vector_expression<E> const& e){
        return get<is_quaternion<E>::value ? 1 : 0>(e);
    }

    //! @brief ベクトルのy値を取得する
    template<class E>
    inline typename E::reference       y(vector_expression<E>&       e){
        return get<is_quaternion<E>::value ? 2 : 1>(e);
    }
    //! @brief ベクトルのy値を取得する
    template<class E>
    inline typename E::const_reference y(vector_expression<E> const& e){
        return get<is_quaternion<E>::value ? 2 : 1>(e);
    }

    //! @brief ベクトルのz値を取得する
    template<class E>
    inline typename E::reference       z(vector_expression<E>&       e){
        return get<is_quaternion<E>::value ? 3 : 2>(e);
    }
    //! @brief ベクトルのz値を取得する
    template<class E>
    inline typename E::const_reference z(vector_expression<E> const& e){
        return get<is_quaternion<E>::value ? 3 : 2>(e);
    }

    //! @brief ベクトルのw値を取得する
    template<class E>
    inline typename E::reference       w(vector_expression<E>&       e){
        return get<is_quaternion<E>::value ? 0 : 3>(e);
    }
    //! @brief ベクトルのw値を取得する
    template<class E>
    inline typename E::const_reference w(vector_expression<E> const& e){
        return get<is_quaternion<E>::value ? 0 : 3>(e);
    }

    //! @brief ベクトルからr値(0番目の要素)を取得する
    template<class E>
    inline typename E::reference       r(vector_expression<E>&       e){return get<0>(e);}
    //! @brief ベクトルからr値(0番目の要素)を取得する
    template<class E>
    inline typename E::const_reference r(vector_expression<E> const& e){return get<0>(e);}
    //! @brief ベクトルからg値(1番目の要素)を取得する
    template<class E>
    inline typename E::reference       g(vector_expression<E>&       e){return get<1>(e);}
    //! @brief ベクトルからg値(1番目の要素)を取得する
    template<class E>
    inline typename E::const_reference g(vector_expression<E> const& e){return get<1>(e);}
    //! @brief ベクトルからb値(2番目の要素)を取得する
    template<class E>
    inline typename E::reference       b(vector_expression<E>&       e){return get<2>(e);}
    //! @brief ベクトルからb値(2番目の要素)を取得する
    template<class E>
    inline typename E::const_reference b(vector_expression<E> const& e){return get<2>(e);}
    //! @brief ベクトルからa値(3番目の要素)を取得する
    template<class E>
    inline typename E::reference       a(vector_expression<E>&       e){return get<3>(e);}
    //! @brief ベクトルからa値(3番目の要素)を取得する
    template<class E>
    inline typename E::const_reference a(vector_expression<E> const& e){return get<3>(e);}

    //! @brief []アクセス可能なクラスからx値(0番目の要素)を取得する
    template<class T>
    inline typename boost::disable_if<is_vector<T>, typename T::reference>::type
    x(T&       e){return e[0];}
    //! @brief []アクセス可能なクラスからx値(0番目の要素)を取得する
    template<class T>
    inline typename boost::disable_if<is_vector<T>, typename T::const_reference>::type
    x(T const& e){return e[0];}
    //! @brief []アクセス可能なクラスからy値(1番目の要素)を取得する
    template<class T>
    inline typename boost::disable_if<is_vector<T>, typename T::reference>::type
    y(T&       e){return e[1];}
    //! @brief []アクセス可能なクラスからy値(1番目の要素)を取得する
    template<class T>
    inline typename boost::disable_if<is_vector<T>, typename T::const_reference>::type
    y(T const& e){return e[1];}
    //! @brief []アクセス可能なクラスからz値(2番目の要素)を取得する
    template<class T>
    inline typename boost::disable_if<is_vector<T>, typename T::reference>::type
    z(T&       e){return e[2];}
    //! @brief []アクセス可能なクラスからz値(2番目の要素)を取得する
    template<class T>
    inline typename boost::disable_if<is_vector<T>, typename T::const_reference>::type
    z(T const& e){return e[2];}
    //! @brief []アクセス可能なクラスからw値(3番目の要素)を取得する
    template<class T>
    inline typename boost::disable_if<is_vector<T>, typename T::reference>::type
    w(T&       e){return e[3];}
    //! @brief []アクセス可能なクラスからw値(3番目の要素)を取得する
    template<class T>
    inline typename boost::disable_if<is_vector<T>, typename T::const_reference>::type
    w(T const& e){return e[3];}

    //! @brief []アクセス可能なクラスからr値(0番目の要素)を取得する
    template<class T>
    inline typename boost::disable_if<is_vector<T>, typename T::reference>::type
    r(T&       e){return e[0];}
    //! @brief []アクセス可能なクラスからr値(0番目の要素)を取得する
    template<class T>
    inline typename boost::disable_if<is_vector<T>, typename T::const_reference>::type
    r(T const& e){return e[0];}
    //! @brief []アクセス可能なクラスからg値(1番目の要素)を取得する
    template<class T>
    inline typename boost::disable_if<is_vector<T>, typename T::reference>::type
    g(T&       e){return e[1];}
    //! @brief []アクセス可能なクラスからg値(1番目の要素)を取得する
    template<class T>
    inline typename boost::disable_if<is_vector<T>, typename T::const_reference>::type
    g(T const& e){return e[1];}
    //! @brief []アクセス可能なクラスからb値(2番目の要素)を取得する
    template<class T>
    inline typename boost::disable_if<is_vector<T>, typename T::reference>::type
    b(T&       e){return e[2];}
    //! @brief []アクセス可能なクラスからb値(2番目の要素)を取得する
    template<class T>
    inline typename boost::disable_if<is_vector<T>, typename T::const_reference>::type
    b(T const& e){return e[2];}
    //! @brief []アクセス可能なクラスからa値(3番目の要素)を取得する
    template<class T>
    inline typename boost::disable_if<is_vector<T>, typename T::reference>::type
    a(T&       e){return e[3];}
    //! @brief []アクセス可能なクラスからa値(3番目の要素)を取得する
    template<class T>
    inline typename boost::disable_if<is_vector<T>, typename T::const_reference>::type
    a(T const& e){return e[3];}

    //! @brief 配列からx値(0番目の要素)を取得する
    template<class T, std::size_t N>
    inline typename boost::enable_if_c<(N > 1), T&>::type       x(T       (&e)[N]){return e[0];}
    //! @brief 配列からx値(0番目の要素)を取得する
    template<class T, std::size_t N>
    inline typename boost::enable_if_c<(N > 1), T const&>::type x(T const (&e)[N]){return e[0];}
    //! @brief 配列からy値(1番目の要素)を取得する
    template<class T, std::size_t N>
    inline typename boost::enable_if_c<(N > 2), T&>::type       y(T       (&e)[N]){return e[1];}
    //! @brief 配列からy値(1番目の要素)を取得する
    template<class T, std::size_t N>
    inline typename boost::enable_if_c<(N > 2), T const&>::type y(T const (&e)[N]){return e[1];}
    //! @brief 配列からz値(2番目の要素)を取得する
    template<class T, std::size_t N>
    inline typename boost::enable_if_c<(N > 3), T&>::type       z(T       (&e)[N]){return e[2];}
    //! @brief 配列からz値(2番目の要素)を取得する
    template<class T, std::size_t N>
    inline typename boost::enable_if_c<(N > 3), T const&>::type z(T const (&e)[N]){return e[2];}
    //! @brief 配列からw値(3番目の要素)を取得する
    template<class T, std::size_t N>
    inline typename boost::enable_if_c<(N > 4), T&>::type       w(T       (&e)[N]){return e[3];}
    //! @brief 配列からw値(3番目の要素)を取得する
    template<class T, std::size_t N>
    inline typename boost::enable_if_c<(N > 4), T const&>::type w(T const (&e)[N]){return e[3];}

    //! @brief 配列からr値(0番目の要素)を取得する
    template<class T, std::size_t N> inline T&       r(T       (&e)[N]){return accessor::x(e);}
    //! @brief 配列からr値(0番目の要素)を取得する
    template<class T, std::size_t N> inline T const& r(T const (&e)[N]){return accessor::x(e);}
    //! @brief 配列からg値(1番目の要素)を取得する
    template<class T, std::size_t N> inline T&       g(T       (&e)[N]){return accessor::y(e);}
    //! @brief 配列からg値(1番目の要素)を取得する
    template<class T, std::size_t N> inline T const& g(T const (&e)[N]){return accessor::y(e);}
    //! @brief 配列からb値(2番目の要素)を取得する
    template<class T, std::size_t N> inline T&       b(T       (&e)[N]){return accessor::z(e);}
    //! @brief 配列からb値(2番目の要素)を取得する
    template<class T, std::size_t N> inline T const& b(T const (&e)[N]){return accessor::z(e);}
    //! @brief 配列からa値(3番目の要素)を取得する
    template<class T, std::size_t N> inline T&       a(T       (&e)[N]){return accessor::w(e);}
    //! @brief 配列からa値(3番目の要素)を取得する
    template<class T, std::size_t N> inline T const& a(T const (&e)[N]){return accessor::w(e);}
}

__NOGARA_EXPRESSION_END


#endif
