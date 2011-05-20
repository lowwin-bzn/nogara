#ifndef NOGARA_EXPRESSION_TAG_HPP
#define NOGARA_EXPRESSION_TAG_HPP

#include <nogara/expression/define.hpp>

//////////////////////////////////////////////
//! @file nogara/expression/expression_tag.hpp
//! @brief 式の種類を決めるタグ群
//////////////////////////////////////////////

__NOGARA_EXPRESSION_BEGIN

struct no_expression_tag{};
struct matrix_tag{};
struct vector_tag{};
struct quaternion_tag : public vector_tag{};

namespace grammar{
    struct no_grammar_tag{};
    struct terminal_tag{};
    struct expression_tag{};
    struct reference_tag : public expression_tag{};
    struct calculator_tag : public expression_tag{};
}

__NOGARA_EXPRESSION_END

#endif
