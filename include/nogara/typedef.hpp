#ifndef NOGARA_TYPEDEF_HPP
#define NOGARA_TYPEDEF_HPP

///////////////////////////////////
//! @file nogara/typedef.hpp
//! @brief 統一的な型定義を提供する
///////////////////////////////////

#include <nogara/nogara_define.hpp>
#include <boost/cstdint.hpp>

__NOGARA_BEGIN
typedef boost::uint8_t  uint8_t;
typedef boost::uint16_t uint16_t;
typedef boost::uint32_t uint32_t;
typedef boost::uint64_t uint64_t;

typedef boost::int8_t   int8_t;
typedef boost::int16_t  int16_t;
typedef boost::int32_t  int32_t;
typedef boost::int64_t  int64_t;

typedef unsigned int    uint_t;
typedef uint8_t         byte_t;
typedef uint16_t        word_t;
typedef uint32_t        dword_t;
typedef uint64_t        qword_t;
__NOGARA_END

using nogara::uint_t;
using nogara::byte_t;
using nogara::word_t;
using nogara::word_t;
using nogara::qword_t;

using nogara::uint8_t;
using nogara::uint16_t;
using nogara::uint32_t;
using nogara::uint64_t;

using nogara::int8_t;
using nogara::int16_t;
using nogara::int32_t;
using nogara::int64_t;

#endif
