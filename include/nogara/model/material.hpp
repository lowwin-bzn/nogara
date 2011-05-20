#ifndef NOGARA_MATERIAL_H
#define NOGARA_MATERIAL_H

//////////////////////////////////////
//! @file  nogara/model/material.hpp
//! @brief マテリアル情報
//////////////////////////////////////

#include <nogara/nogara_define.hpp>
#include <nogara/color/color.hpp>

__NOGARA_BEGIN

template<typename T>
struct material_initializer;

template<typename T, class Initializer = material_initializer<T> >
class material;

__NOGARA_END

__NOGARA_BEGIN

//////////////////////////////////////
//! @brief マテリアルオブジェクト
//////////////////////////////////////
template<typename T, class Initializer>
class material{
    typedef T                        value_type;
    typedef Initializer              initializer;
    typedef typename boost::mpl::if_<
        boost::is_integral<T>,
        rgba::color32, rgba::color<T> >::type color_type;
    typedef material<T, initializer> self_type;

public:
    void setDiffuse(value_type r, value_type g, value_type b, value_type a){
        setDiffuse(color_type(r, g, b, a));
    }

    void setDiffuse(color_type const &color){
        diffuse = color;
    }
    
    void setAmbient(value_type r, value_type g, value_type b, value_type a){
        setAmbient(color_type(r, g, b, a));
    }
    
    void setAmbient(color_type const &color){
        ambient = color;
    }

    void setSpecular(value_type r, value_type g, value_type b, value_type a){
        setSpecular(color_type(r, g, b, a));
    }

    void setSpecular(color_type const &color){
        specular = color;
    }
    
    void setEmissive(value_type r, value_type g, value_type b, value_type a){
        setEmissive(color_type(r, g, b, a));
    }
    
    void setEmissive(color_type const &color){
        emissive = color;
    }

    void setShininess(value_type value){
        shininess = value;
    }

    static self_type initialize(){ 
        return initializer::init();
    }
    
public:
    color_type diffuse;
    color_type ambient;
    color_type specular;
    color_type emissive;
    value_type shininess;
};

//! @brief float型のマテリアル初期値
template<>
struct material_initializer<float>{
    typedef material_initializer<float> self_type;
    typedef material<float>      material_type;
    static material_type init(){
        material_type result;
        result.setDiffuse(0.8f, 0.8f, 0.8f, 1.0f);
        result.setAmbient(0.2f, 0.2f, 0.2f, 1.0f);
        result.setSpecular(0.0f, 0.0f, 0.0f, 1.0f);
        result.setEmissive(0.0f, 0.0f, 0.0f, 1.0f);
        result.setShininess(0.0f);

        return result;
    }
};

//! @brief int型のマテリアル初期値
template<>
struct material_initializer<int>{
    typedef material_initializer<int> self_type;
    typedef material<int>      material_type;
    static material_type init(){
        material_type result;
        result.setDiffuse(204, 204, 204, 256);
        result.setAmbient( 51,  51,  51, 256);
        result.setSpecular( 0,   0,   0, 256);
        result.setEmissive( 0,   0,   0, 256);
        result.setShininess(0);
        return result;
    }
};

__NOGARA_END

#endif
