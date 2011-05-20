#ifndef NOGARA_CAPACITOR_HPP
#define NOGARA_CAPACITOR_HPP

/////////////////////////////////////
//! @file  nogara/capacitor.hpp
//! @brief 一定容量までの値の変化構造
/////////////////////////////////////

#include <nogara/interval.hpp>

__NOGARA_BEGIN

//! @brief 設定した下限、上限までの値を格納できるクラス
template<class T>
class capacitor{
public:
    //////////////////////////////////////////////
    //! @brief コンストラクタ 上限と下限を指定する
    //! @param s 下限
    //! @param e 上限
    //////////////////////////////////////////////
    capacitor(T const& s, T const& e):cur(s), interval_(s, e){}
    
    ////////////////////////////////////////////////////////
    //! @brief コンストラクタ 現在の値と上限と下限を設定する
    //! @param c 現在の値
    //! @param s 下限
    //! @param e 上限
    ////////////////////////////////////////////////////////
    capacitor(T const& c, T const& s, T const& e):cur((c < s) ? s : (c > e) ? e : c), interval_(s, e){}
    //! @brief コピーコンストラクタ
    capacitor(capacitor const& c):cur(c.cur), interval_(.interval_){}
 
    ///////////////////////////////////////////////////////
   //! @brief  現在の値が上限に達していないか
    //! @return  現在の値が上限に達していないかを示すbool値
    ///////////////////////////////////////////////////////
    bool operator !() const {return !complete();}

    //////////////////////////////////////////////////
    //! @brief 現在の値を引数の値を足した値に更新する。
    //!        現在の値が上限に達した場合は上限に修正
    //! @param adder 足す値
    //////////////////////////////////////////////////
    template<class adder_t>
    void update(adder_t const& adder){
        if(!complete()){
            cur = cur + adder;
            if(complete()){
                cur = interval_.upper();
            }
        }
    }

    //////////////////////////
    //! @brief  現在の値を返す
    //! @return 現在の値
    //////////////////////////
    operator T const&() const{return current();}

    ///////////////////////////////////////////////////////////////////////
    //! @brief 引数の値は下限より下回ると下限に、上限より上回ると上限になる
    //! @param value 新たな値 下限 <= 新たな値 <= 上限
    ///////////////////////////////////////////////////////////////////////
    void rewind(T const& value){
        cur = (value < interval_.lower()) ? interval_.lower() :
              (value > interval_.upper()) ? interval_.upper() :
               value;
    }

    //////////////////////////
    //! @brief  現在の値を返す
    //! @return 現在の値
    //////////////////////////
    T const& current() const {return cur;}

    /////////////////////////////////////////////////
    //! @brief   現在の値が上限に達したかを返す
    //! @return  現在の値が上限に達したかを示すbool値
    /////////////////////////////////////////////////
    bool    complete() const {return cur >= interval_.upper();}

private:
    T cur;
    interval<T> const interval_;
};

//! @brief 設定した下限、上限まで、
//! 一回の上昇値を指定して値変換する際に増やしていくクラス
template<class T, class adder_t = T>
class auto_capacitor : public capacitor<T>{
public:
    //! @brief コンストラクタ 上限と下限、上昇値を指定する
    //! @param s 下限
    //! @param e 上限
    auto_capacitor(T const& s, T const& e, adder_t const& a):
        capacitor<T>(s, e), adder(a){}
    //! @brief コピーコンストラクタ
    auto_capacitor(auto_capacitor const& s):
        capacitor<T>(s), adder(s.adder){}
    //! @brief コンストラクタ 他のインスタンスから上昇値を変更してコピー
    template<class other_adder>
    auto_capacitor(auto_capacitor<T, other_adder> const& s, adder_t const& a):
        capacitor<T>(s), adder(a){}

    //! @brief  現在の値を更新して返す
    //! @return 更新された値
    operator T() const {
        const_cast<auto_capacitor*>(this)->update(adder);
        return capacitor<T>::current();
    }
private:
    adder_t const adder;
};

//! @brief  正規値(0..1)の範囲で更新されるキャパシタを返す
//! @param  上昇値
//! @return (0..1)の間で更新されるキャパシタ
template<class T, class adder>
typename boost::enable_if<
    boost::mpl::and_<boost::is_floating_point<T>, boost::is_convertible<adder, T> >,
    auto_capacitor<T, adder> >::type
normalize_auto_capacitor(adder const& a){
    return auto_capacitor<T, adder>(T(0), T(1), a);
}

__NOGARA_END

#endif
