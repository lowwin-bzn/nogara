#ifndef NOGARA_INTERVAL_HPP
#define NOGARA_INTERVAL_HPP

//////////////////////////////
//! @file  nogara/interval.hpp
//! @brief 区間を表すクラス
//////////////////////////////

#include <nogara/nogara_define.hpp>

__NOGARA_BEGIN

template<class T>
struct interval{
    interval(T const& l, T const& u):lower_(l), upper_(u){}
    interval(interval const& i):lower_(i.lower_), upper_(i.upper_){}

    //! @brief 上限の値
    T const& upper() const {return upper_;}
    //! @brief 下限の値
    T const& lower() const {return lower_;}
    //! @brief 中央値
    T median() const {return (upper_ + lower_) * 0.5;}
    //! @brief 上限と下限の、引数の値に近い側の値を返す
    T nearest(T const& value) const {return (value > center()) ? upper_ : lower_;}
    //! @brief 引数の値が区間に含まれているかを返す
    bool in(T const& value) const {return value >= lower_ && value <= upper_;}

private:
    T const lower_, upper_;
};

__NOGARA_END

#endif
