#ifndef NOGARA_EXPRESSION_HPP
#define NOGARA_EXPRESSION_HPP

#include <nogara/expression/expression_tag.hpp>

///////////////////////////////////////////
//! @file  nogara/expression/expression.hpp
//! @brief 式の基礎となるクラス群
///////////////////////////////////////////

__NOGARA_EXPRESSION_BEGIN

///////////////////////////////////////////
//! @brief ベクトル式の基礎となるクラス
///////////////////////////////////////////
template<class E>
struct vector_expression{
    typedef E                      expression_type;
    typedef expression::vector_tag expression_category;
    expression_type&       operator()()       {return *static_cast<expression_type*>(this);}
    expression_type const& operator()() const {return *static_cast<expression_type const*>(this);}
};

///////////////////////////////////////////
//! @brief 行列の式の基礎となるクラス
///////////////////////////////////////////
template<class E>
struct matrix_expression{
    typedef E                      expression_type;
    typedef expression::matrix_tag expression_category;
    expression_type&       operator()()       {return *static_cast<expression_type*>(this);}
    expression_type const& operator()() const {return *static_cast<expression_type const*>(this);}

};

__NOGARA_EXPRESSION_END


#endif
