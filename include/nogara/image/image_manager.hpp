#ifndef NOGARA_IMAGE_MANAGER_HPP
#define NOGARA_IMAGE_MANAGER_HPP

//////////////////////////////////////////
//! @file  /nogara/image/image_manager.hpp
//! @brief 画像の管理を行うクラス
//////////////////////////////////////////

#include <map>
#include <nogara/image/texture.hpp>

__NOGARA_BEGIN

//! @brief 画像の管理を行うクラス
class image_manager{
    typedef image::shared_ptr image_ptr;
    typedef std::map<int, texture> texture_map;
    typedef std::map<int, image_ptr> image_map;
public:
    //! @brief 画像の追加
    //! param id 画像に割り当てるID
    //! param img 画像の共有ポインタ
    void add_image(int id, image_ptr img){
        if(img){images[id] = img;}
    }
    //! @brief 画像の追加
    //! param id 画像に割り当てるID
    //! param img 画像のポインタ
    void add_image(int id, image* img){
        add_image(id, image_ptr(img));
    }

    //! @brief 画像を取得する
    //! @return 画像のポインタを返す。なければ空オブジェクト
    image_ptr get_image(int id){return images[id];}
    //! @brief  idの画像をテクスチャに割り当て、
    //!         そのテクスチャを返す
    //! @param  id 画像のID
    //! @return テクスチャオブジェクト
    texture image_bind_texture(uint_t id){
        texture_map::iterator it = textures.find(id);
        if(it == textures.end()){
            textures.insert(std::make_pair(id, texture(images[id])));
        }
        return textures[id];
    }

private:
    image_map images;
    texture_map textures;
};

__NOGARA_END

#endif
