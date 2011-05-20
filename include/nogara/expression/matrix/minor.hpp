#ifndef NOGARA_EXPRESSION_MINOR_MATRIX_HPP
#define NOGARA_EXPRESSION_MINOR_MATRIX_HPP

///////////////////////////////////////////////////
//! @file nogara/expression/matrix/minor.hpp
//! @brief 小行列クラス
///////////////////////////////////////////////////

#include <boost/mpl/size_t.hpp>
#include <nogara/expression/traits.hpp>
#include <nogara/expression/matrix/unary_expression.hpp>

__NOGARA_EXPRESSION_BEGIN

namespace minor_matrix_invisible{
/////////////////////////////////////////////
//! @brief 内部で使用するインデックス生成関数
/////////////////////////////////////////////
template<std::size_t N>
inline unsigned get_index(unsigned n, boost::mpl::size_t<N>){
    return (n >= N) ? n + 1 : n;
}
inline unsigned get_index(unsigned n, boost::mpl::size_t<0>){
    return n + 1;
}
template<std::size_t N>
inline unsigned get_index(unsigned n){
    return get_index(n, boost::mpl::size_t<N>());
}
}

////////////////////////////////////////////////////////////
//! @brief Rで指定した行を除いた(E::Row - 1) * E::Column行列
////////////////////////////////////////////////////////////
template<class E, std::size_t R>
class row_minor_matrix : public matrix_unary_base<E, row_minor_matrix<E, R> >{
    typedef row_minor_matrix<E, R>          self_type;
    typedef matrix_unary_base<E, self_type> base_type;

public:
    typedef boost::mpl::size_t<get_row<E>::value - 1> Row;
    typedef get_column<E>                             Column;

    typename base_type::value_type apply(unsigned x, unsigned y) const {
        return base_type::value()(minor_matrix_invisible::get_index<R>(x), y);
    }

    row_minor_matrix(typename base_type::argment_type e):base_type(e){}    
};

//////////////////////////////////////////////////-
//Cで指定した列を除いたE::Row * (E::Column - 1)行列
//////////////////////////////////////////////////-
template<class E, std::size_t C>
class column_minor_matrix : public matrix_unary_base<E, column_minor_matrix<E, C> >{
    typedef column_minor_matrix<E, C>       self_type;
    typedef matrix_unary_base<E, self_type> base_type;

public:
    typedef get_row<E>                                   Row;
    typedef boost::mpl::size_t<get_column<E>::value - 1> Column;

    typename base_type::value_type apply(unsigned x, unsigned y) const {
        return base_type::value()(x, minor_matrix_invisible::get_index<C>(y));
    }

    column_minor_matrix(typename base_type::argment_type e):base_type(e){}    
};


/////////////////////////////////////////////////////////////////////////
//! @brief R, Cで指定した行, 列を除いた(E::Row - 1) * (E::Column - 1)行列
/////////////////////////////////////////////////////////////////////////
template<class E, std::size_t R, std::size_t C>
class minor_matrix : public matrix_unary_base<E, minor_matrix<E, R, C> >{
    typedef minor_matrix<E, R, C>        self_type;
    typedef matrix_unary_base<E, self_type> base_type;

public:
    typedef boost::mpl::size_t<get_row<E>::value - 1>    Row;
    typedef boost::mpl::size_t<get_column<E>::value - 1> Column;

    typename base_type::value_type apply(unsigned x, unsigned y) const {
        return base_type::value()(minor_matrix_invisible::get_index<R>(x),
                                  minor_matrix_invisible::get_index<C>(y));
    }

    minor_matrix(typename base_type::argment_type e):base_type(e){}
};

/////////////////////////////////////
//! @brief 実行時に小行列にするクラス
//         run time minor
/////////////////////////////////////
template<class E>
class rt_minor_matrix : public matrix_unary_base<E, rt_minor_matrix<E> >{
    typedef rt_minor_matrix<E>           self_type;
    typedef matrix_unary_base<E, self_type> base_type;

public:
    typedef boost::mpl::size_t<get_row<E>::value - 1>    Row;
    typedef boost::mpl::size_t<get_column<E>::value - 1> Column;

    typename base_type::value_type apply(unsigned x, unsigned y) const {
        if(x >= ignore_row){ ++x;}
        if(y >= ignore_column){ ++y;}
        return base_type::value()(x, y);
    }
    
    rt_minor_matrix(typename base_type::argment_type e,
                    std::size_t ignore_r,
                    std::size_t ignore_c):
        base_type(e), ignore_row(ignore_r), ignore_column(ignore_c)
    {assert(ignore_row < get_row<E>::value && ignore_c < get_column<E>::value);}
    
private:
    std::size_t ignore_row, ignore_column;
};


/////////////////////////////////////////////
//! @brief クラスを生成しやすくする便利関数群
/////////////////////////////////////////////
template<std::size_t R, std::size_t C, class E>
inline minor_matrix<E, R, C> minor(matrix_expression<E> const& e){
    return minor_matrix<E, R, C>(e);
}

template<std::size_t R, class E>
inline row_minor_matrix<E, R> row_minor(matrix_expression<E> const& e){
    return row_minor_matrix<E, R>(e);
}

template<std::size_t C, class E>
inline column_minor_matrix<E, C> column_minor(matrix_expression<E> const& e){
    return column_minor_matrix<E, C>(e);
}

__NOGARA_EXPRESSION_END

#endif
