#ifndef NOGARA_TEXTURE_HPP
#define NOGARA_TEXTURE_HPP

///////////////////////////////////////
//! @file  nogara/image/texture.hpp
//! @brief テクスチャバッファ管理クラス
///////////////////////////////////////

#include <nogara/image/image.hpp>
#include <nogara/gl_traits.hpp>

__NOGARA_BEGIN

///////////////////////////////////////
//! @brief テクスチャバッファ管理クラス
///////////////////////////////////////
class texture{
    //! @brief バッファ管理用オブジェクト
    struct texture_info{
        typedef image::shared_ptr image_ptr;
        texture_info(uint_t id_, image_ptr img):id(id_), image(img){}
        ~texture_info(){glDeleteBuffers(1, &id);}
        uint_t id;
        image_ptr image;
    };

    typedef smart_ptr::shared_ptr<texture_info> info_ptr;
public:
    typedef texture_info::image_ptr image_ptr;

    //! @brief コンストラクタ
    texture(){}
    //! @biref コンストラクタ
    explicit texture(image_ptr img){bind_image(img);}
    //! @brief コンストラクタ
    explicit texture(image* img){bind_image(image_ptr(img));}
    //! @brief コピーコンストラクタ
    texture(texture const &rhs):info(rhs.info){}
    //! @brief 代入演算
    texture& operator=(texture const &rhs){
        if(&rhs != this){
            info = rhs.info;
        }
        return *this;
    }

    //! @brief テクスチャバッファを割り当てる
    void draw_begin() const {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, id());
    }

    //! @brief テクスチャバッファの割り当てを解除する
    void draw_end() const {
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    }

    //! @brief テクスチャバッファのID
    uint_t    id()    const {return info ? info->id : 0;} 
    //! @brief 画像オブジェクトの取得
    image_ptr get_image() const {return info ? info->image : image_ptr();}
private:
    //! @brief テクスチャバッファを生成し、
    //!        バッファへ画像をバインドする
    void bind_image(image_ptr img){
        uint_t id;
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, img->internal_format(), img->width(), img->height(), 0,
                     img->pixel_format(), GL_UNSIGNED_BYTE, img->data_front());
        glBindTexture(GL_TEXTURE_2D, 0);
        info.reset(new texture_info(id, img));
    }


private:
    info_ptr info;
};

///////////////////////////////////////////////////////////////////////////
//! @brief テクスチャのバインド、バインド解除をスコープ内で自動で行う構造体
///////////////////////////////////////////////////////////////////////////
struct texture_auto_drawer{
    texture_auto_drawer(texture const& t):tex(t){tex.draw_begin();}
    ~texture_auto_drawer(){tex.draw_end();}
    texture const& tex;
};

__NOGARA_END

#endif
