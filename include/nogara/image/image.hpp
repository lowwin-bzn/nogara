#ifndef NOGARA_IMAGE_HPP
#define NOGARA_IMAGE_HPP

////////////////////////////////////////
//! @file  nogara/image/image.hpp
//! @brief 基礎となる画像インタフェース
///////////////////////////////////////

#include <vector>
#include <nogara/nogara_define.hpp>
#include <nogara/typedef.hpp>
#include <nogara/vector.hpp>
#include <nogara/smart_ptr.hpp>

__NOGARA_BEGIN

///////////////////////////////////////////////
//! @brief 基礎となる画像インタフェース
//!        現在画像データを操作するなどは不可能
//!        純粋な画像データコンテナである
///////////////////////////////////////////////
class image{
public:
    //! @brief データコンテナの型
    typedef std::vector<byte_t> data_type;
    //! @brief 画像クラスの共有ポインタ
    typedef smart_ptr::shared_ptr<image> shared_ptr;

    //! @brief コンストラクタ
    image(int w, int h, uint_t ds, int inf, int pf):
        size_(w, h), internal_format_(inf), pixel_format_(pf), data_(ds, 0){}

    //! @brief コピーコンストラクタ
    image(image const& img):
        size_(img.size()),
        internal_format_(img.internal_format_), pixel_format_(img.pixel_format_),
        data_(img.data()){}


    //! @brief 画像の横サイズ
    int    width()         const {return size_.x();}
    //! @brief 画像の縦サイズ
    int    height()        const {return size_.y();}
    //! @brief 画像のサイズ
    vector2i const& size() const {return size_;}
    //! @brief データコンテナのサイズ
    uint_t data_size()     const {return data_.size();}

    data_type      & data()             {return data_;}
    data_type const& data()       const {return data_;}
    byte_t*          data_front()       {return &data_[0];}
    byte_t const*    dara_front() const {return &data_[0];}
    int pixel_format()            const {return pixel_format_;}
    int internal_format()         const {return internal_format_;}

protected:
    template<class Functor>
    void setData(Functor f){f(data_);}

protected:
    vector2i size_;
    int internal_format_, pixel_format_;
    data_type data_;
};

__NOGARA_END

#endif
