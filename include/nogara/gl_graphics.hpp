#ifndef NOGARA_GRAPHIC_H
#define NOGARA_GRAPHIC_H

/////////////////////////////////////////////
//! @file  nogara/gl_graphics.hpp 
//! @brief openGL関数のラッパを提供するヘッダ
/////////////////////////////////////////////

#include <vector>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/less.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/utility/noncopyable.hpp>
#include <nogara/gl_traits.hpp>
#include <nogara/typedef.hpp>
#include <nogara/light.hpp>
#include <nogara/model/material.hpp>
#include <nogara/model/buffer.hpp>
#include <nogara/vector.hpp>
#include <nogara/matrix.hpp>
#include <nogara/array.hpp>

__NOGARA_BEGIN

//! @brief glVertex2のラッパ
inline void draw_vector2(double x, double y){glVertex2d(x, y);}
//! @brief glVertex2のラッパ
inline void draw_vector2(float x, float y){glVertex2f(x, y);}
//! @brief glVertex2のラッパ
inline void draw_vector2(int x, int y){glVertex2i(x, y);}

//! @brief glVertex3のラッパ
inline void draw_vector3(double x, double y, double z){glVertex3d(x, y, z);}
//! @brief glVertex3のラッパ
inline void draw_vector3(float x, float y, float z){glVertex3f(x, y, z);}
//! @brief glVertex3のラッパ
inline void draw_vector3(int x, int y, int z){glVertex3i(x, y, z);}

//! @brief glVertex3の使用と同時にglNormalも使用する関数
inline void draw_vector3_with_normal(double const* v, double const* n){
    glNormal3dv(n);
    glVertex3dv(v);
}

//! @brief glVertex3の使用と同時にglNormalも使用する関数
inline void draw_vector3_with_normal(float const* v, float const* n){
    glNormal3fv(n);
    glVertex3fv(v);
}

//! @brief glVertex3の使用と同時にglNormalも使用する関数
inline void draw_vector3_with_normal(int const* v, int const* n){
    glNormal3iv(n);
    glVertex3iv(v);
}

//! @brief glVertex3の使用と同時にglNormalも使用する関数
inline void draw_vector3_with_normal(double const (&v)[3], double const (&n)[3]){
    glNormal3d(n[0], n[1], n[2]);
    glVertex3d(v[0], v[1], v[2]);
}

//! @brief glVertex3の使用と同時にglNormalも使用する関数
inline void draw_vector3_with_normal(float const (&v)[3], float const (&n)[3]){
    glNormal3f(n[0], n[1], n[2]);
    glVertex3f(v[0], v[1], v[2]);
}

//! @brief glVertex3の使用と同時にglNormalも使用する関数
inline void draw_vector3_with_normal(int const (&v)[3], int const (&n)[3]){
    glNormal3i(n[0], n[1], n[2]);
    glVertex3i(v[0], v[1], v[2]);
}

//! @brief glVertex2のラッパ
template<typename T>
inline void draw_vector2(nogara::vector2<T> const& v){
    drawVector2(v.x(), v.y());
}

//! @brief glVertex3のラッパ
template<typename T>
inline void draw_vector3(nogara::vector3<T> const& v){
    drawVector3(v.x(), v.y(), v.z());
}

//! @brief glVertex3の使用と同時にglNormalも使用する関数
template<typename T>
inline void draw_vector3_with_normal(nogara::vector3<T> const& v, nogara::vector3<T> const& n){
    drawVector3WithNormal(v.begin(), n.begin());
}

//! @brief 現在のworld座標行列を転送する
inline void set_world_matrix(double const* matrix){
    glLoadMatrixd(matrix);
}
//! @brief 現在のworld座標行列を転送する
inline void set_world_matrix(float const* matrix){
    glLoadMatrixf(matrix);
}
//! @brief 現在のworld座標行列を転送する
template<typename T>
inline void set_world_matrix(nogara::matrix<T> const& matrix){
    set_world_matrix(matrix.pointer());
}

//! @brief 行列のpush popをスコープ内で自動的に行うためのオブジェクト
struct auto_push_pop_matrix : boost::noncopyable{
    auto_push_pop_matrix(){glPushMatrix();}
    ~auto_push_pop_matrix(){glPopMatrix();}
};

__NOGARA_END

#endif
