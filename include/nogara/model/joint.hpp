#ifndef NOGARA_JOINT_HPP
#define NOGARA_JOINT_HPP

/////////////////////////////////////////
//! @file  nogara/model/joint.hpp
//! @brief モデルを結合させるオブジェクト
/////////////////////////////////////////

#include <list>
#include <algorithm>
#include <nogara/model/object3D.hpp>
#include <nogara/gl_graphics.hpp>

__NOGARA_BEGIN

/////////////////////////////////////////
//! @brief モデルを結合させるオブジェクト
/////////////////////////////////////////
class joint : public object3D{
protected:
    typedef std::list<object_ptr> list_type;

    //! @brief 子オブジェクト全てを描画するための関数オブジェクト
    struct drawChild{
        drawChild(matrixf const& m):pwm(m){}
        void operator ()(object_ptr const& ptr){
            auto_push_pop_matrix pp;
            ptr->draw(pwm);
        }
    private:
        matrixf const& pwm;
    };

public:
    //! @brief 子オブジェクトを追加する
    void add_child(object3D* object){
        children.push_back(object_ptr(object));
    }

    //! @brief 子オブジェクトを追加する
    void add_child(object_ptr object){
        children.push_back(object);
    }

    //! @brief 子オブジェクトの描画
    void draw(matrix<float> const &pwm) const {
        matrixf const world = local_matrix() * pwm;
        draw_impl(world);
        std::for_each(children.begin(), children.end(), drawChild(world));
    }
    //! @brief 子オブジェクトの描画
    void draw(render_system const& render) const {
        draw_impl();
        draw(render.projection_modelview_matrix());
    }

protected:
    //! @brief 描画に必要な処理を行う。子クラスこちらを継承する
    virtual void draw_impl(matrixf const& /*pwm*/) const {}
    //! @brief 描画に必要な処理を行う。子クラスこちらを継承する
    virtual void draw_impl() const {}

protected:
    list_type children;

};

__NOGARA_END

#endif
