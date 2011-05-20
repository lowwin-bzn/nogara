#ifndef NOGARA_EXPRESSION_IO_HPP
#define NOGARA_EXPRESSION_IO_HPP

/////////////////////////////////////////////////////////////////////////////
//! @file  nogara/expression/io.hpp
//! @brief ベクトル、行列、クォータニオンのstd::ostreamへの書き込みを提供する
/////////////////////////////////////////////////////////////////////////////

#include <ostream>
#include <iomanip>

#include <nogara/expression/expression.hpp>
#include <nogara/expression/traits.hpp>
#include <nogara/expression/vector/get.hpp>
#include <nogara/expression/matrix/matrix_fwd.hpp>

__NOGARA_EXPRESSION_BEGIN

//! @brief ベクトルのstd::ostreamへの出力
template<class E>
void output(std::ostream &os, vector_expression<E> const& v, nogara::expression::vector_tag){
    os << '(';
    for(unsigned i = 0; i < get_dimension<E>::value; ++i){
        if(i != 0){os << ',' << ' ';}
        os << v()(i);
    }
    os << ')';
}

//! @brief クォータニオンのstd::ostreamへの出力
template<class E>
void output(std::ostream &os, vector_expression<E> const& q, nogara::expression::quaternion_tag){
    os << "[" << get<0>(q) << ", (" << get<1>(q) << ", " << get<2>(q) << ", " << get<3>(q) << ")]";
}

//! @brief std::ostreamへの書き込み
template<class E>
void output(std::ostream &os, vector_expression<E> const& v){
    nogara::expression::output(os, v, typename E::expression_category());
}

//! @brief 行列のstd::ostreamへの書き込み
template<class E>
void output(std::ostream &os, matrix_expression<E> const& m){
    os << "[";
    for(unsigned y = 0; y < get_column<E>::value; ++y){
        for(unsigned x = 0; x < get_row<E>::value; ++x){
            if(x != 0 || y != 0){
                os << ", ";
            }
            if(y != 0 && x == 0){
                os << std::endl << ' ';
            }
            os << std::setw(8) << m()(x, y);
        }
    }
    os << "]";
}

//! @brief ベクトル系クラスのストリーム演算子オーバーロード
template<class E>
std::ostream& operator <<(std::ostream& os, vector_expression<E> const& e){
    output(os, e);
    return os;
}

//! @brief 行列系クラスのストリーム演算子オーバーロード
template<class E>
std::ostream& operator <<(std::ostream& os, matrix_expression<E> const& e){
    output(os, e);
    return os;
}


__NOGARA_EXPRESSION_END

#endif
