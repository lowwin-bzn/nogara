#ifndef NOGARA_KEYBOARD_HPP
#define NOGARA_KEYBOARD_HPP

#include <nogara/typedef.hpp>
#include <nogara/nogara_define.hpp>

/////////////////////////////
//! @file nogara/keyboard.hpp
//! @brief キーボードの抽象化
/////////////////////////////

__NOGARA_BEGIN

///////////////////////////////////////////////////////////////////
//! @brief キーボードの抽象化
//!        必要最低限のキー定数しか設定していない
//!        キー定数以外のキーはシングルクォートでくくった数値と同じ
//!        実際のキーボード操作は他のライブラリに依存する
///////////////////////////////////////////////////////////////////
class keyboard{
    //! @brief ヘッダファイルオンリーにするためのクラス
    template<class T> struct key_buffer{static T keys[0xFF];};
    typedef key_buffer<uint8_t> buffer;
public:
    //! @brief キー定数
    enum KeyStates{
        KEY_ESCAPE    = 0x1b,
        KEY_TAB       = '\t',
        KEY_ENTER     = '\n',
        KEY_RETURN    = KEY_ENTER,
        KEY_DELETE    = 0x7F,
        KEY_F1        = 0x80 +   1,
        KEY_F2        = 0x80 +   2,
        KEY_F3        = 0x80 +   3,
        KEY_F4        = 0x80 +   4,
        KEY_F5        = 0x80 +   5,
        KEY_F6        = 0x80 +   6,
        KEY_F7        = 0x80 +   7,
        KEY_F8        = 0x80 +   8,
        KEY_F9        = 0x80 +   9,
        KEY_F10       = 0x80 +  10,
        KEY_F11       = 0x80 +  11,
        KEY_F12       = 0x80 +  12,
        KEY_LEFT      = 0x80 + 100,
        KEY_UP        = 0x80 + 101,
        KEY_RIGHT     = 0x80 + 102,
        KEY_DOWN      = 0x80 + 103,
        KEY_PAGE_UP   = 0x80 + 104,
        KEY_PAGE_DOWN = 0x80 + 105,
        KEY_HOME      = 0x80 + 106,
        KEY_END       = 0x80 + 107,
        KEY_INSERT    = 0x80 + 108,
        KEY_SHIFT     = 0x80 + 110,
        KEY_CONTROL   = 0x80 + 111,
        KEY_ALT       = 0x80 + 112,
    };

    //! @brief キーダウンを設定する(公開すべきでない)
    static void down_key_state(int key){buffer::keys[key] = 1;}
    //! @brief キーアップを設定する(公開すべきでない)
    static void up_key_state  (int key){buffer::keys[key] = 0;}

    //! @brief キーボードが押されているかを返す
    static bool is_key_down(uint8_t state){return buffer::keys[state] == 1;}
    //! @brief キーボードが押されていないかを返す
    static bool is_key_up  (uint8_t state){return !is_key_down(state);}

    //! @brief 関数オブジェクトを使って、キー情報を32ビット数値に集約する関数
    template<class Function>
    static uint_t get_key_state(Function& f){
        return f(buffer::keys);
    }
};

template<class T>
T keyboard::key_buffer<T>::keys[0xFF];

__NOGARA_END

#endif
