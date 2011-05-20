#ifndef NOGARA_SFINAE_CHECK_HPP
#define NOGARA_SFINAE_CHECK_HPP

#include <nogara/nogara_define.hpp>

//////////////////////////////////////////////////////////////
//! @file  nogara/type_traits/sfinae_check.hpp
//! @brief SFINAEの制御に使う簡易なtypedefとそのインタフェース
//////////////////////////////////////////////////////////////

__NOGARA_BEGIN

//////////////////////////////////////////////////////////////
//! @brief SFINAEの制御に使う簡易なtypedefとそのインタフェース
//!        実装はこの構造体を継承するか、
//!        yes_type, no_typeだけを使用する
//////////////////////////////////////////////////////////////
struct sfinae_check{
    typedef char                   yes_type;
    typedef struct{char dummy[2];} no_type;
};

__NOGARA_END

#endif
