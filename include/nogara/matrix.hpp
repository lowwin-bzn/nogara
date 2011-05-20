#ifndef NOGARA_MATRIX_H
#define NOGARA_MATRIX_H

///////////////////////////
//! @file nogara/matrix.hpp
//! @brief 行列ライブラリ
///////////////////////////

#include <nogara/expression/matrix/matrix.hpp>

__NOGARA_BEGIN
typedef matrix<float> matrixf;
typedef matrix33<float> matrix33f;
typedef matrix22<float> matrix22f;
__NOGARA_END
#endif
