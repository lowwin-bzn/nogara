#ifndef NOGARA_OBJECT3D_HPP
#define NOGARA_OBJECT3D_HPP

////////////////////////////////////
//! @file  nogara/model/object3D.hpp
//! @brief 3Dオブジェクトの基礎型
////////////////////////////////////

#include <nogara/matrix.hpp>
#include <nogara/vector.hpp>
#include <nogara/quaternion.hpp>
#include <nogara/camera.hpp>
#include <nogara/model/transformation.hpp>
#include <nogara/smart_ptr.hpp>
#include <nogara/render_system.hpp>

__NOGARA_BEGIN

class object3D{
public:
    typedef smart_ptr::shared_ptr<object3D> shared_ptr;
    typedef shared_ptr object_ptr;

    //! @brief コンストラクタ
    object3D():transform(){}
    //! @brief コピーコンストラクタ
    object3D(object3D const& obj):transform(obj.transform){}

    virtual ~object3D(){}
    //! @brief 描画関数
    virtual void draw(matrix<float> const& parent_world_matrix) const = 0;
    //! @brief 描画関数
    virtual void draw(render_system const& render) const {
        draw(render.projection_modelview_matrix());
    }

    //! @brief オブジェクトの位置
    vector3f const& position() const {return transform.translate();}
    //! @brief オブジェクトの位置
    vector3f const& translate() const {return position();}
    //! @brief オブジェクトの位置変更
    void position(vector3f const& v){
        transform.translate(v);
    }
    //! @brief オブジェクトの位置変更
    void position(float x, float y, float z){
        transform.translate(x, y, z);
    }
    //! @brief オブジェクトの位置変更
    void translate(vector3f const& v){
        position(v);
    }
    //! @brief オブジェクトの位置変更
    void translate(float x, float y, float z){
        position(x, y, z);
    }

    //! @brief オブジェクトの大きさ
    vector3f const& scale() const {return transform.scale();}
    //! @brief オブジェクトの大きさ変更
    void scale(float x, float y, float z){
        transform.scale(x, y, z);
    }
    //! @brief オブジェクトの大きさ変更
    void scale(vector3f const &v){
        transform.scale(v);
    }

    //! @brief オブジェクトの回転情報
    quaternionf const& rotate() const {return transform.rotate();}
    //! @brief オブジェクトの回転
    void rotate(quaternion<float> const& q){
        transform.rotate(q);
    }
    //! @brief オブジェクトの回転
    void rotate(vector3f const& v, float angle){
        transform.rotate(quaternion_rotate_axis(v, angle));
    }
    //! @brief オブジェクトの回転
    void rotate(vector3f const &v){
        transform.rotate(v);
    }
    //! @brief オブジェクトの回転
    void rotate(float x, float y, float z){
        transform.rotate(x, y, z);
    }

    //! @brief オブジェクトの行列情報
    matrixf local_matrix() const {return transform.to_matrix();}

protected:
    transformation<float> transform;

};

__NOGARA_END

#endif
