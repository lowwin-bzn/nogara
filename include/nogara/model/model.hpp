#ifndef NOGARA_MODEL_H
#define NOGARA_MODEL_H

///////////////////////////////////
//! @file  nogara/model/model.hpp
//! @brief 3Dオブジェクトの一般型
///////////////////////////////////

#include <nogara/model/joint.hpp>
#include <nogara/model/mesh.hpp>

__NOGARA_BEGIN

//////////////////////////////////////////////////
//! @brief 3Dオブジェクトの一般型
//////////////////////////////////////////////////
class model : public joint{
public:
    //! @brief メッシュデータの共有ポインタ型
    typedef mesh::shared_ptr             mesh_ptr;
    //! @brief 自身の共有ポインタ型
    typedef smart_ptr::shared_ptr<model> shared_ptr;
    //! @brief エイリアス
    typedef shared_ptr                   model_ptr;

    //! @brief コンストラクタ
    explicit model(mesh* m):joint(), mesh_(m){}
    //! @brief コンストラクタ
    explicit model(mesh_ptr m):joint(), mesh_(m){}
    //! @brief コピーコンストラクタ
    model(model const& rhs):joint(rhs), mesh_(rhs.mesh_){}
    //! @brief 代入
    model &operator =(model const &rhs){
        if(&rhs != this){
            joint::operator =(rhs);
            mesh_ = rhs.mesh_;
        }
        return *this;
    }

    //! @brief メッシュデータを持っているか否か
    bool has_mesh() const{return static_cast<bool>(mesh_);}
    //! @brief メッシュデータの取得
    mesh_ptr get_mesh() const {return mesh_;}

private:
    //! @brief 描画に必要な処理
    virtual void draw_impl(nogara::matrix<float> const& pwm) const {
        set_world_matrix(pwm);
        if(mesh_){
            mesh_->draw(NG_TRIANGLES);
        }
    }

private:
    mesh_ptr mesh_;
};

inline model::shared_ptr make_model(mesh* mesh){
    return model::shared_ptr(new model(mesh));
}

inline model::shared_ptr make_model(mesh::shared_ptr mesh){
    return model::shared_ptr(new model(mesh));
}

inline model::shared_ptr make_model(mesh_buffer const& buffer){
    return model::shared_ptr(new model(make_mesh(buffer)));
}

__NOGARA_END

#endif
