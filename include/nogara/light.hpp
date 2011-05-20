#ifndef NOGARA_LIGHT_H
#define NOGARA_LIGHT_H

///////////////////////////
//! @file nogara/light.hpp
//! @brief 光源オブジェクト
///////////////////////////
#include <cassert>
#include <limits>

#include <nogara/vector.hpp>
#include <nogara/color/color.hpp>
#include <nogara/color/color_constant.hpp>
#include <nogara/gl_traits.hpp>

__NOGARA_BEGIN

///////////////////////////
//! @brief 光源オブジェクト
///////////////////////////
class light{
public:
    enum light_type{
        LIGHT_TYPE_PARALLEL = 0,
        LIGHT_TYPE_POINT = 1,
    };

    //////////////////////////////////////////////
    //! @brief コンストラクタ
    //! @param p 光源の位置
    //! @param d 光源の向かう先
    //! @param type 光源の種類(平行光源か点光源か)
    //////////////////////////////////////////////
    light(vector3f const& p, light_type type = LIGHT_TYPE_PARALLEL):
        pos(p(0), p(1), p(2), static_cast<float>(type)), dir(-vector3f::unit_z),
        dif(rgba::color_constant::white),
        amb(rgba::color_constant::black),
        spe(rgba::color_constant::white),
        exp(0), cut(180), const_att(1), linear_att(0), quad_att(0){}

    light(vector3f const& p, vector3f const& d):
        pos(p(0), p(1), p(2), LIGHT_TYPE_POINT), dir(d),
        dif(rgba::color_constant::white),
        amb(rgba::color_constant::black),
        spe(rgba::color_constant::white),
        exp(0), cut(180), const_att(1), linear_att(0), quad_att(0){}

    //! @brief 光源の位置
    vector3f position() const {
        return vector3f(pos.x(), pos.y(), pos.z());
    }

    //! @brief 光源の位置を設定する
    void posision(float x, float y, float z){
        pos.x(x); pos.y(y); pos.z(z);
    }

    //! @brief 光源の位置を設定する
    void posision(vector3f const &v){
        posision(v.x(), v.y(), v.z());
    }

    //! @brief 光の種類
    light_type type() const {
        if(std::abs(pos.w()) <= std::numeric_limits<float>::epsilon()){
            return LIGHT_TYPE_PARALLEL;
        }
        return LIGHT_TYPE_POINT;
    }

    //! @brief 光の種類を設定
    void type(light_type t){
        assert(t == LIGHT_TYPE_PARALLEL || t == LIGHT_TYPE_POINT);
        pos.w(static_cast<float>(t));
    }

    //! @brief 光の種類付き位置情報
    vector4f const& position_with_type() const {
        return pos;
    }

    //! @brief 光の方向
    vector3f const& direction() const {
        return dir;
    }

    //! @brief 光の方向を設定する
    void direction(float x, float y, float z){
        dir.x(x); dir.y(y); dir.z(z);
    }

    //! @brief 光の方向を設定する
    void direction(vector3f const &v){
        direction(v.x(), v.y(), v.z());
    }

    //! @brief 拡散光色
    rgba::color<float> const& diffuse() const {
        return dif;
    }

    //! @brief 拡散光の設定
    void diffuse(float r, float g, float b, float a){
        dif.set_color(r, g, b, a);
    }

    //! @brief 拡散光の設定
    void diffuse(unsigned int color){
        dif.set_color(color);
    }

    //! @brief 拡散光の設定
    void diffuse(rgba::color<float> const &color){
        dif.set_color(color);
    }

    //! @brief 環境光
    rgba::color<float> const& ambient() const {
        return amb;
    }

    //! @brief 環境光の設定
    void ambient(float r, float g, float b, float a){
        amb.set_color(r, g, b, a);
    }

    //! @brief 環境光の設定
    void ambient(unsigned int color){
        amb.set_color(color);
    }

    //! @brief 環境光の設定
    void ambient(rgba::color<float> const &color){
        amb.set_color(color);
    }

    //! @brief 鏡面光
    rgba::color<float> const& specular() const {
        return spe;
    }

    //! @brief 鏡面光の設定
    void specular(float r, float g, float b, float a){
        spe.set_color(r, g, b, a);
    }

    //! @brief 鏡面光の設定
    void specular(unsigned int color){
        spe.set_color(color);
    }

    //! @brief 鏡面光の設定
    void specular(rgba::color<float> const &color){
        spe.set_color(color);
    }

    //! @brief 輝度の分布
    float exponent() const {return exp;}
    //! @brief 輝度の分布の設定
    void  exponent(float value){exp = value;}
    //! @brief 最大放射角度
    float cutoff() const {return cut;}
    //! @brief 最大放射角度の設定
    void  cutoff(float value){cut = value;}
    //! @brief 一定減衰率
    float constant_attenuation() const {return const_att;}
    //! @brief 一定減衰率の設定
    void  constant_attenuation(float value){const_att = value;}
    //! @brief 線形減衰率
    float linear_attenuation() const {return linear_att;}
    //! @brief 線形減衰率の設定
    void  linear_attenuation(float value){linear_att = value;}
    //! @brief 二次減衰率
    float quadratic_attenuation() const {return quad_att;}
    //! @brief 二次減衰率の設定
    void  quadratic_attenuation(float value){quad_att = value;}

private:
    vector4f pos;
    vector3f dir;
    rgba::color<float> dif;
    rgba::color<float> amb;
    rgba::color<float> spe;
    float exp;
    float cut;
    float const_att;
    float linear_att;
    float quad_att;
};

__NOGARA_END

#endif
