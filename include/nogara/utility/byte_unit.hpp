#ifndef NOGARA_BYTE_UNIT_HPP
#define NOGARA_BYTE_UNIT_HPP

///////////////////////////////////////
//! @file  nogara/utility/byte_unit.hpp
//! @brief バイト数を表す単位メタ整数
///////////////////////////////////////

#include <nogara/nogara_define.hpp>
#include <nogara/typedef.hpp>
#include <boost/mpl/integral_c.hpp>

__NOGARA_BEGIN

namespace byte_unit{
    //! @brief Byte数
    template<uint64_t N> struct Byte : public boost::mpl::integral_c<uint64_t, N>{};
    //! @brief KiB数
    template<uint64_t N> struct KiB  : public byte_unit::Byte<N * 1024>{};
    //! @brief MiB数
    template<uint64_t N> struct MiB  : public byte_unit::KiB<N * 1024>{};
    //! @brief GiB数
    template<uint64_t N> struct GiB  : public byte_unit::MiB<N * 1024>{};
    //! @brief TiB数
    template<uint64_t N> struct TiB  : public byte_unit::GiB<N * 1024>{};
    //! @brief PiB数
    template<uint64_t N> struct PiB  : public byte_unit::TiB<N * 1024>{};
    //! @brief EiB数
    template<uint64_t N> struct EiB  : public byte_unit::PiB<N * 1024>{};
}

__NOGARA_END

#endif
