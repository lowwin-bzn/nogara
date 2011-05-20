#ifndef NOGARA_TEXTURE_BOARD_HPP
#define NOGARA_TEXTURE_BOARD_HPP

///////////////////////////////////////////////
//! @file  nogara/image/texture_board.hpp
//! @brief テクスチャを描画する矩形オブジェクト
///////////////////////////////////////////////

#include <nogara/image/texture.hpp>
#include <nogara/model/object3D.hpp>
#include <nogara/model/mesh.hpp>
#include <nogara/geometry/rect.hpp>
#include <nogara/gl_graphics.hpp>

__NOGARA_BEGIN

///////////////////////////////////////////////
//! @brief テクスチャを描画する矩形オブジェクト
///////////////////////////////////////////////
class texture_board : public object3D{
    typedef rect<float> Rect;
    typedef texture::image_ptr image_ptr;
public:
    texture_board(texture const& tex, float width, float height, Rect const& r = Rect(0, 0, 1, 1)):
        texture_(tex), size_(width, height), rect_(r){make_mesh();}
    texture_board(image* img, float width, float height, Rect const& r = Rect(0, 0, 1, 1)):
        texture_(img), size_(width, height), rect_(r){make_mesh();}
    texture_board(image_ptr img, float width, float height, Rect const& r = Rect(0, 0, 1, 1)):
        texture_(img), size_(width, height), rect_(r){make_mesh();}
    texture_board(texture_board const& board):
        object3D(board), texture_(board.texture_), size_(board.size_), rect_(board.rect_)
    {make_mesh();}

    using object3D::draw;
    //! @brief テクスチャの描画
    void draw(matrix<float> const& pwm) const {
        matrix<float> const world = local_matrix() * pwm;
        set_world_matrix(world);
        texture_auto_drawer drawer(texture_);
        if(mesh_){mesh_->draw(NG_QUADS);}
    }

    //! @brief テクスチャの変更
    void set_texture(texture const& tex){
        texture_ = tex;
    }

    //! @brief オブジェクトのサイズ
    vector2f const& size() const {return size_;}
    //! @brief オブジェクトの横サイズ
    float width()  const {return size_.x();}
    //! @brief オブジェクトの縦サイズ
    float height() const {return size_.y();}

private:
    void make_mesh(){
        mesh_ = nogara::make_mesh(make_buffer());
    }

    mesh_buffer make_buffer(){
        vector2f const half = size_ * 0.5;
        vector3f const vectors[] = {
            vector3f(-half.x(),  half.y(), 0.0f), vector3f(half.x(),  half.y(), 0.0f),
            vector3f(-half.x(), -half.y(), 0.0f), vector3f(half.x(), -half.y(), 0.0f)
        };

        vector2f const uvs[] ={
            vector2f(rect_.x, rect_.y), vector2f(rect_.x + rect_.width, rect_.y),
            vector2f(rect_.x, rect_.y + rect_.height), vector2f(rect_.x + rect_.width, rect_.y + rect_.height)
        };

        uint8_t const indices[] = {0, 1, 3, 2};
        typedef vertex1<vertices::uv_type> Vertex;
        std::vector<Vertex> vb;
        for(int i = 0; i < 4; ++i){
            vb.push_back(Vertex(vectors[i], uvs[i]));
        }
        return make_mesh_buffer(vb, indices);
    }

private:
    texture texture_;
    mesh::shared_ptr mesh_;
    vector2f size_;
    Rect rect_;
};

__NOGARA_END

#endif
