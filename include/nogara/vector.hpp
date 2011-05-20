#ifndef NOGARA_VECTOR_H
#define NOGARA_VECTOR_H

/////////////////////////////
//! @file nogara/vector.hpp
//! @brief ベクトルライブラリ
/////////////////////////////

#include <nogara/expression/vector/vector2.hpp>
#include <nogara/expression/vector/vector3.hpp>
#include <nogara/expression/vector/vector4.hpp>


__NOGARA_BEGIN
//! @typedef vector2<int> vector2i
//! @brief   int型2次元ベクトル
typedef vector2<int>   vector2i;
//! @typedef vector2<float> vector2f
//! @brief   float型2次元ベクトル
typedef vector2<float> vector2f;
//! @typedef vector3<int> vector3i
//! @brief   int型3次元ベクトル
typedef vector3<int>   vector3i;
//! @typedef vector3<float> vector3f
//! @brief   float型3次元ベクトル
typedef vector3<float> vector3f;
//! @typedef vector4<int> vector4i
//! @brief   int型4次元ベクトル
typedef vector4<int>   vector4i;
//! @typedef vector4<float> vector4f
//! @brief   float型4次元ベクトル
typedef vector4<float> vector4f;
__NOGARA_END

#endif
