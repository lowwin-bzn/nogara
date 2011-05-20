#ifndef NOGARA_CAMERA_HPP
#define NOGARA_CAMERA_HPP

///////////////////////////////////
//! @file nogara/camera.hpp
//! @brief カメラ視点クラス
///////////////////////////////////

#include <nogara/vector.hpp>
#include <nogara/matrix.hpp>

__NOGARA_BEGIN

//! @brief カメラの位置、注視点、上部向きの情報を持つクラス
class camera_eye{
public:
    camera_eye():look_(vector3f::zero), at_(vector3f::zero), up_(vector3f::unit_y){}
    //! @brief コンストラクタ
    //! @param l 視点位置
    //! @param a 注視点位置
    //! @param u 上方向
    camera_eye(vector3f const& l, vector3f const& a, vector3f const& u = vector3f::unit_y):
        look_(l), at_(a), up_(u){}
    //! @brief コピーコンストラクタ
    camera_eye(camera_eye const& c):look_(c.look_), at_(c.at_), up_(c.up_){}

    //! @brief 代入
    camera_eye& operator=(camera_eye const& c){
        if(&c != this){
            look_     = c.look_;
            at_       = c.at_;
            up_       = c.up_;
        }
        return *this;
    }

    //! @brief カメラ位置の設定
    void look(vector3f const& v){
        look(v.x(), v.y(), v.z());
    }

    //! @brief カメラ位置の設定
    void look(float x, float y, float z){
        look_.x(x);
        look_.y(y);
        look_.z(z);
    }

    //! @brief 注視点の設定
    void at(vector3f const& v){
        at(v.x(), v.y(), v.z());
    }

    //! @brief 注視点の設定
    void at(float x, float y, float z){
        at_.x(x);
        at_.y(y);
        at_.z(z);
    }

    //! @brief カメラの上方向の設定
    void up(vector3f const& v){
        up(v.x(), v.y(), v.z());
    }

    //! @brief カメラの上方向の設定
    void up(float x, float y, float z){
        up_.x(x);
        up_.y(y);
        up_.z(z);
    }

    //! @brief 視点位置、注視点、上方向全ての値を変更する
    void look_at(vector3f const& l, vector3f const& a, vector3f const& u = vector3f::unit_y){
        look_ = l; at_ = a; up_ = u;
    }

    //! @brief カメラ行列の取得
    matrixf get_matrix() const {
        return nogara::look_at(look_, at_, up_);
    }

    //! @brief カメラ視点位置
    vector3f const& look() const {return look_;}
    //! @brief 注視点
    vector3f const& at()   const {return at_;}
    //! @brief カメラの上方向
    vector3f const& up()   const {return up_;}
    //! @brief カメラの向き
    vector3f direction()   const {return nogara::normalize(at_ - look_);}

private:
    vector3f look_, at_, up_;
};

__NOGARA_END

#endif
