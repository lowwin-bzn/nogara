#ifndef NOGARA_EXPRESSION_MATRIX_FUNCTION_HPP
#define NOGARA_EXPRESSION_MATRIX_FUNCTION_HPP

///////////////////////////////////////////////
//! @file nogara/expression/matrix/function.hpp
//! @brief 行列の関数群
///////////////////////////////////////////////

#include <nogara/expression/quaternion/quaternion.hpp>
#include <nogara/expression/matrix/minor.hpp>
#include <nogara/expression/matrix/repeat.hpp>
#include <nogara/expression/matrix/slice.hpp>
#include <nogara/expression/matrix/transpose.hpp>
#include <nogara/expression/vector/vector2.hpp>
#include <nogara/expression/vector/vector3.hpp>
#include <nogara/expression/vector/vector4.hpp>

__NOGARA_EXPRESSION_BEGIN

///////////////////////////////////////////////////////////////////////
//! @brief テンプレート引数で指定した要素を返す関数
//!        インデックス値は行列の行サイズ、列サイズ未満である必要がある
///////////////////////////////////////////////////////////////////////
template<std::size_t X, std::size_t Y, class E>
inline typename boost::enable_if<
    boost::mpl::and_<boost::mpl::greater<get_row<E>, boost::mpl::size_t<X> >,
              boost::mpl::greater<get_column<E>, boost::mpl::size_t<Y> > >,
    typename E::value_type>::type
get(matrix_expression<E> const& e){
    return e()(X, Y);
}

/////////////////////////////////////
//! @brief 絶対値化した行列を返す関数
//////////////////////////////////////
template<class E>
inline matrix_unary<E, scalar_abs<E> >
abs(matrix_expression<E> const& val){
    return matrix_unary<E, scalar_abs<E> >(val);
}

///////////////////////////////////////////
//! @brief 式の三項演算関数、式は評価される
///////////////////////////////////////////
template<class Result, class E1, class E2>
Result ternary(bool then, matrix_expression<E1> const& e1, matrix_expression<E2> const& e2){
    return then ? Result(e1) : Result(e2);
}

////////////////////////////
//! @brief 転置行列を返す関数
/////////////////////////////
template<class E>
inline transpose_matrix<E> transpose(matrix_expression<E> const& e){
    return transpose_matrix<E>(e);
}

/////////////////////////////////////////////
//! @brief クォータニオンを行列に変換する関数
/////////////////////////////////////////////
template<class E>
inline typename boost::enable_if<is_quaternion<E>, matrix33<typename E::value_type> >::type
to_matrix(vector_expression<E> const& e){
    typedef typename E::value_type value_type;
    typedef vector3<value_type>    vector_type;
    typedef matrix33<value_type>   result_type;
    typedef minor_vector<E, 0>     minor_type;
    minor_type mv = minor<0>(e);
    vector_type const sqXYZ    = value_type(2) * nogara::expression::pow(mv, 2);
    vector_type const twiseXYZ = value_type(2) * vector_type(mv(0) * mv(1), mv(1) * mv(2), mv(2) * mv(0));
    vector_type const twiseW   = value_type(2) * get<0>(e) * mv;
    value_type  const one = value_type(1);

    return result_type(one - sqXYZ(1) - sqXYZ(2), twiseXYZ(0) + twiseW(2), twiseXYZ(2) - twiseW(1),
                       twiseXYZ(0) - twiseW(2), one - sqXYZ(0) - sqXYZ(2), twiseXYZ(1) + twiseW(0),
                       twiseXYZ(2) + twiseW(1), twiseXYZ(1) - twiseW(0), one - sqXYZ(0) - sqXYZ(1));
}

/////////////////////////////////////////////
//! @brief 行列をクォータニオンに変換する関数
/////////////////////////////////////////////
template<class E>
inline quaternion<typename deduct1<E>::real_type>
to_quaternion(matrix_expression<E> const& e){
    typedef typename E::value_type         value_type;
    typedef typename deduct1<E>::real_type real_type;
    typedef quaternion<value_type>         quaternion_type;
    typedef vector3<value_type>            vector3_type;
    vector3_type const diagonal(get<0, 0>(e), get<1, 1>(e), get<2, 2>(e));

    value_type const elem[] = {
        diagonal(0) + diagonal(1) + diagonal(2),
        diagonal(0) - diagonal(1) - diagonal(2),
        diagonal(2) + diagonal(0) - diagonal(1),
        diagonal(1) + diagonal(0) - diagonal(2),
    };

    int index = 0;
    for(int i = 1; i < 4; ++i){
        if(elem[i] > elem[index]){index = i;}
    }

    real_type const biggest_value = std::sqrt(elem[index] + value_type(1)) * real_type(0.5);
    real_type const mult = real_type(0.25) / biggest_value;

    vector3_type const left( get<0, 1>(e), get<1, 2>(e), get<2, 0>(e));
    vector3_type const right(get<1, 0>(e), get<2, 1>(e), get<0, 2>(e));

    typedef scalar_add<value_type, value_type> add_func;
    typedef scalar_sub<value_type, value_type> sub_func;
    vector_binary<vector3_type, vector3_type, add_func> const add(left, right);
    vector_binary<vector3_type, vector3_type, sub_func> const sub(left, right);

    return (index == 0) ?
        quaternion_type(biggest_value, sub(1) * mult, sub(2) * mult, sub(0) * mult) :
           (index == 1) ?
        quaternion_type(sub(1) * mult, biggest_value, add(0) * mult, add(2) * mult) : 
           (index == 2) ?
        quaternion_type(sub(2) * mult, add(0) * mult, biggest_value, add(1) * mult) :
        quaternion_type(sub(0) * mult, add(2) * mult, sub(1) * mult, biggest_value);
}

//////////////////////////////////////
//! @brief 2 * 2の行列式計算をする関数
//////////////////////////////////////
template<class E>
inline typename boost::enable_if<square_equal_to_c<E, 2>, typename E::value_type>::type
determinant(matrix_expression<E> const& e){
    return get<0, 0>(e) * get<1, 1>(e) - get<0, 1>(e) * get<1, 0>(e);
}

//////////////////////////////////////
//! @brief 3 * 3の行列式計算をする関数
//////////////////////////////////////
template<class E>
inline typename boost::enable_if<square_equal_to_c<E, 3>, typename E::value_type>::type
determinant(matrix_expression<E> const& e){
    vector3<typename E::value_type> const det(determinant(minor<0, 0>(e)),
                                              determinant(slice_c<2, 4, 1, 3>(repeat<1, 0>(e))),
                                              determinant(minor<2, 0>(e)));

    return dot(expr_row_vector<E, 0>(e), det);
}


//////////////////////////////////////
//! @brief 4 * 4の行列式計算をする関数
//////////////////////////////////////
template<class E>
inline typename boost::enable_if<square_equal_to_c<E, 4>, typename E::value_type>::type
determinant(matrix_expression<E> const& e){
    typedef typename E::value_type value_type;

    value_type const det[] = {get<2, 2>(e) * get<3, 3>(e), get<2, 3>(e) * get<3, 2>(e),
                              get<2, 3>(e) * get<3, 1>(e), get<2, 1>(e) * get<3, 3>(e),
                              get<2, 1>(e) * get<3, 2>(e), get<2, 2>(e) * get<3, 1>(e),
                              get<2, 0>(e) * get<3, 3>(e), get<2, 3>(e) * get<3, 0>(e),
                              get<2, 2>(e) * get<3, 0>(e), get<2, 0>(e) * get<3, 2>(e),
                              get<2, 0>(e) * get<3, 1>(e), get<2, 1>(e) * get<3, 0>(e)};
    vector3<value_type> const v11(get<1, 1>(e) * (det[0] - det[1]),
                                  get<1, 2>(e) * (det[2] - det[3]),
                                  get<1, 3>(e) * (det[4] - det[5]));

    vector3<value_type> const v12(get<1, 0>(e) * (det[1] - det[0]),
                                  get<1, 2>(e) * (det[6] - det[7]),
                                  get<1, 3>(e) * (det[8] - det[9]));

    vector3<value_type> const v13(get<1, 0>(e) * (det[3]  - det[2]),
                                  get<1, 1>(e) * (det[7]  - det[6]),
                                  get<1, 3>(e) * (det[10] - det[11]));

    vector3<value_type> const v14(get<1, 0>(e) * (det[5]  - det[4]),
                                  get<1, 1>(e) * (det[9]  - det[8]),
                                  get<1, 2>(e) * (det[11] - det[10]));

    return dot(expr_column_vector<E, 0>(e),
               vector4<value_type>(sum(v11), sum(v12), sum(v13), sum(v14)));
}


//////////////////////////////////////
//! @brief 4 * 4行列の逆行列を返す関数
//////////////////////////////////////
template<class E>
inline typename boost::enable_if<
    square_equal_to_c<E, 4>, matrix<typename deduct1<E>::real_type> >::type
inverse(matrix_expression<E> const& e){
    typedef typename E::value_type value_type;
    typedef vector2<value_type> vector2_type;
    typedef vector3<value_type> vector3_type;
    typedef vector4<value_type> vector4_type;
    typedef typename deduct1<value_type>::real_type real_type;

    value_type const values[] = {get<2, 2>(e) * get<3, 3>(e), get<2, 3>(e) * get<3, 2>(e),
                                 get<2, 3>(e) * get<3, 1>(e), get<2, 1>(e) * get<3, 3>(e),
                                 get<2, 1>(e) * get<3, 2>(e), get<2, 2>(e) * get<3, 1>(e),
                                 get<2, 0>(e) * get<3, 3>(e), get<2, 3>(e) * get<3, 0>(e),
                                 get<2, 2>(e) * get<3, 0>(e), get<2, 0>(e) * get<3, 2>(e),
                                 get<2, 0>(e) * get<3, 1>(e), get<2, 1>(e) * get<3, 0>(e)};
    vector2_type const X12(values[0]  - values[1],  values[1]  - values[0]);
    vector2_type const X34(values[2]  - values[3],  values[3]  - values[2]);
    vector2_type const X56(values[4]  - values[5],  values[5]  - values[4]);
    vector2_type const X78(values[6]  - values[7],  values[7]  - values[6]);
    vector2_type const X910(values[8]  - values[9],  values[9]  - values[8]);
    vector2_type const X1112(values[10] - values[11], values[11] - values[10]);

    expr_column_vector<E, 1> const column1_v(e);

    vector4_type const d(dot(minor<0>(column1_v), vector3_type(X12(0), X34(0),  X56(0))),
                         dot(minor<1>(column1_v), vector3_type(X12(1), X78(0),  X910(0))),
                         dot(minor<2>(column1_v), vector3_type(X34(1), X78(1),  X1112(0))),
                         dot(minor<3>(column1_v), vector3_type(X56(1), X910(1), X1112(1))));

    expr_column_vector<E, 0> const column0_v(e);
    value_type const det = dot(column0_v, d);

    if(det == value_type()){
        return matrix<real_type>::identity;
    }

    vector4_type const d2(dot(minor<0>(column0_v), vector3_type(X12(1),  X34(1),   X56(1))),
                          dot(minor<1>(column0_v), vector3_type(X12(0),  X78(1),  X910(1))),
                          dot(minor<2>(column0_v), vector3_type(X34(0),  X78(0), X1112(1))),
                          dot(minor<3>(column0_v), vector3_type(X56(0), X910(0), X1112(0))));

    matrix<value_type> b( d, d2, vector4_type::zero, vector4_type::zero);

    int const index[][3] = {{1, 2, 3}, {2, 3, 0}, {3, 0, 1}, {0, 1, 2}};
    for(int y = 2; y < 4; ++y){
        int const x1 = index[y][0], x2 = index[y][1], x3 = index[y][2];
        for(int x = 0; x < 4; ++x){
            int const y1 = index[x][0], y2 = index[x][1], y3 = index[x][2];
            int const k = ((x + y) % 2) ? -1 : 1;
            b(x, y) = k *
                (e()(x1, y1) * (e()(x2, y2) * e()(x3, y3) - e()(x2, y3) * e()(x3, y2)) +
                 e()(x1, y2) * (e()(x2, y3) * e()(x3, y1) - e()(x2, y1) * e()(x3, y3)) +
                 e()(x1, y3) * (e()(x2, y1) * e()(x3, y2) - e()(x2, y2) * e()(x3, y1)));
        }
    }

    return (real_type(1) / det) * b;
}

//////////////////////////////////////
//! @brief 3 * 3行列の逆行列を返す関数
//////////////////////////////////////
template<class E>
inline typename boost::enable_if<
    square_equal_to_c<E, 3>, matrix33<typename deduct1<E>::real_type> >::type
inverse(matrix_expression<E> const& e){
    typedef typename E::value_type         value_type;
    typedef vector3<value_type>            vector3_type;
    typedef typename deduct1<E>::real_type real_type;

    vector3_type const detV(determinant(minor<0, 0>(e)),
                            determinant(slice_c<2, 4, 1, 3>(repeat<1, 0>(e))),
                            determinant(minor<2, 0>(e)));
    value_type const det = dot(expr_row_vector<E, 0>(e), detV);

    if(det == value_type()){
        return matrix33<real_type>::identity;
    }

    int const index[][2] = {{1, 2}, {0, 2}, {0, 1}};
    matrix33<value_type> b(detV(0), value_type(), value_type(), 
                           detV(1), value_type(), value_type(), 
                           detV(2), value_type(), value_type());

    for(int x = 1; x < 3; ++x){
        int const y1 = index[x][0], y2 = index[x][1];
        for(int y = 0; y < 3; ++y){
            int const x1 = index[y][0], x2 = index[y][1];
            int const k = ((y + x) % 2) ? -1 : 1;
            b(x, y) = k * (e()(x1, y1) * e()(x2, y2) - e()(x1, y2) * e()(x2, y1));
        }
    }

    return (real_type(1) / det) * b;
}

///////////////////////////////////
//! @brief 2 * 2の逆行列を返す関数
///////////////////////////////////
template<class E>
inline typename boost::enable_if<
    square_equal_to_c<E, 2>, matrix22<typename deduct1<E>::real_type> >::type
inverse(matrix_expression<E> const& e){
    typedef typename E::value_type value_type;
    typedef typename deduct1<E>::real_type real_type;

    value_type const det = determinant(e);
    if(det == value_type()){
        return matrix22<real_type>::identity;
    }

    matrix22<value_type> b( get<1, 1>(e), -get<1, 0>(e),
                           -get<0, 1>(e),  get<0, 0>(e));
    return (real_type(1) / det) * b;
}


/////////////////////////////////
//! @brief 回転行列を生成する関数
/////////////////////////////////
template<class E>
inline typename boost::enable_if<is_quaternion<E>, matrix33<typename E::value_type> >::type
rotate_matrix(vector_expression<E> const& q){return to_matrix(q);}

/////////////////////////////////
//! @brief 回転行列を生成する関数
/////////////////////////////////
template<class T>
inline typename boost::enable_if<boost::is_arithmetic<T>, matrix33<T> >::type
rotate_matrix(T const& x, T const& y, T const& z){return rotate_matrix(to_quaternion(x, y, z));}

/////////////////////////////////
//! @brief 回転行列を生成する関数
/////////////////////////////////
template<class E>
inline typename boost::enable_if<dimension_equal_to_c<E, 3>, matrix33<typename E::value_type> >::type
rotate_matrix(vector_expression<E> const& v){return rotate_matrix(to_quaternion(v));}

/////////////////////////////////
//! @brief 回転行列を生成する関数
/////////////////////////////////
template<typename E>
inline typename boost::enable_if<square_equal_to_c<E, 3>, matrix33<typename E::value_type> >::type
rotate_matrix(matrix_expression<E> const& e){return matrix33<typename E::value_type>(e);}

/////////////////////////////////
//! @brief 回転行列を生成する関数
/////////////////////////////////
template<class T>
inline matrix33<T>
rotate_matrix(T const& m11, T const& m21, T const& m31,
              T const& m12, T const& m22, T const& m32,
              T const& m13, T const& m23, T const& m33)
{
    return matrix33<T>(m11, m21, m32,
                       m12, m22, m32,
                       m13, m23, m33);
}

/////////////////////////////////
//! @brief 回転行列を生成する関数
/////////////////////////////////
template<class T>
inline typename boost::enable_if<boost::is_arithmetic<T>, matrix33<T> >::type
rotate_matrix(T const (&m)[9]){
    return matrix33<T>(m);
}

/////////////////////////////////
//! @brief 回転行列を生成する関数
/////////////////////////////////
template<class E1, class E2, class E3>
inline typename boost::enable_if<
    boost::mpl::and_<same_dimension<E1, E2>, same_dimension_equal_to<E2, E3, 3> >,
    matrix33<typename deduct3<E1, E2, E3>::value_type> >::type
rotate_matrix(vector_expression<E1> const& v1,
              vector_expression<E2> const& v2,
              vector_expression<E3> const& v3)
{
    return matrix33<typename deduct3<E1, E2, E3>::value_type>(v1, v2, v3);
}

//////////////////////////////////////
//! @brief 並行移動行列を生成する関数
//////////////////////////////////////
template<class T>
matrix<T> translate_matrix(T const& x, T const& y, T const& z){
    return matrix<T>(1, 0, 0, x,
                     0, 1, 0, y,
                     0, 0, 1, z,
                     0, 0, 0, 1);
}

//////////////////////////////////////
//! @brief 並行移動行列を生成する関数
//////////////////////////////////////
template<class E>
inline typename boost::enable_if<dimension_equal_to_c<E, 3>, matrix<typename E::value_type> >::type
translate_matrix(vector_expression<E> const& e){
    return translate_matrix(get<0>(e), get<1>(e), get<2>(e));
}

//////////////////////////////////////
//! @brief 並行移動行列を生成する関数
//////////////////////////////////////
template<class E>
inline typename boost::enable_if<
    dimension_equal_to_c<E, 4>, matrix<typename E::value_type> >::type
translate_matrix(vector_expression<E> const& e){
    return matrix<typename E::value_type>(1, 0, 0, get<0>(e),
                                          0, 1, 0, get<1>(e),
                                          0, 0, 1, get<2>(e),
                                          0, 0, 0, get<3>(e));
}


/////////////////////////////////////////////
//!@ brief 視野変換(カメラ)行列を生成する関数
/////////////////////////////////////////////
template<class E1, class E2, class E3>
inline typename boost::enable_if<
    boost::mpl::and_<same_dimension<E1, E2>, same_dimension_equal_to<E2, E3, 3> >,
    matrix<typename deduct3<E1, E2, E3>::value_type> >::type
look_at(vector_expression<E1> const &look,
        vector_expression<E2> const &at,
        vector_expression<E3> const &up)
{
    typedef typename deduct3<E1, E2, E3>::value_type value_type;
    typedef matrix<value_type> result_type;

    vector3<value_type> const z(normalize(look - at));
    vector3<value_type> const x(normalize(cross(up, z)));
    vector3<value_type> const y(cross(z, x));
    vector3<value_type> const d(-dot(x, look), -dot(y, look), -dot(z, look));

    return result_type(x(0), y(0), z(0), d(0),
                       x(1), y(1), z(1), d(1),
                       x(2), y(2), z(2), d(2),
                          0,    0,    0,    1);
}

///////////////////////////////////////////////////
//!@ brief 透視射影変換行列を生成する関数
///////////////////////////////////////////////////
template<class T1, class T2, class T3, class T4>
inline matrix<typename deduct4<T1, T2, T3, T4>::value_type>
perspective_matrix(T1 fovy, T2 aspect, T3 near, T4 far){
    typedef typename deduct4<T1, T2, T3, T4>::value_type T;
    T const cot = 1 / std::tan(fovy * 0.5);
    T const inv_f_n = 1.0 / (far - near);
    return matrix<T>(cot / aspect, 0,                       0,                         0,
                     0,          cot,                       0,                         0,
                     0,            0, -(near + far) * inv_f_n, -(2 * near * far) * inv_f_n,
                     0,            0,                      -1,                         0);
}

///////////////////////////////////////////////////
//! @brief 透視射影変換行列を生成する関数
///////////////////////////////////////////////////
template<class T1, class T2, class T3, class T4, class T5>
inline matrix<typename deduct5<T1, T2, T3, T4, T5>::value_type>
perspective_matrix(T1 fovy, T2 width, T3 height, T4 near, T5 far){
    typedef typename deduct1<T3>::real_type RT3;
    return perspective_matrix(fovy, RT3(height) / width, near, far);
}

////////////////////////////////////////////////////////
//! @brief 透視射影変換行列の逆行列を生成する関数
////////////////////////////////////////////////////////
template<class T1, class T2, class T3, class T4>
inline matrix<typename deduct4<T1, T2, T3, T4>::value_type>
inverse_perspective_matrix(T1 fovy, T2 aspect, T3 near, T4 far){
    typedef typename deduct4<T1, T2, T3, T4>::value_type T;
    T const tan = std::tan(fovy * 0.5);
    T const inv_nf2 = 1.0 / (2 * near * far);
    return matrix<T>(tan * aspect, 0,                       0,                       0,
                     0,          tan,                       0,                       0,
                     0,            0,                       0,                      -1,
                     0,            0, -(far - near) * inv_nf2, -(near + far) * inv_nf2);
}

////////////////////////////////////////////////////////
//! @brief 透視射影変換行列の逆行列を生成する関数
////////////////////////////////////////////////////////
template<class T1, class T2, class T3, class T4, class T5>
inline matrix<typename deduct5<T1, T2, T3, T4, T5>::value_type>
inverse_perspective_matrix(T1 fovy, T2 width, T3 height, T4 near, T5 far){
    typedef typename deduct1<T3>::real_type RT3;
    return inverse_perspective_matrix(fovy, RT3(height) / width, near, far);
}

////////////////////////////////////////////////////////
//! @brief 透視射影変換行列を生成する関数
////////////////////////////////////////////////////////
template<class T1, class T2, class T3, class T4, class T5, class T6>
inline matrix<typename deduct2<deduct3<T1, T2, T3>, deduct3<T4, T5, T6> >::real_type>
frustum_matrix(T1 left, T2 right, T3 bottom, T4 top, T5 near, T6 far){
    typedef typename deduct2<T1, T2>::real_type T12;
    typedef typename deduct2<T3, T4>::real_type T34;
    typedef typename deduct2<T5, T6>::real_type T56;
    typedef matrix<typename deduct3<T12, T34, T56>::real_type> result;
    T12 const inv_r_l = 1.0 / (right - left);
    T34 const inv_t_b = 1.0 / (top - bottom);
    T56 const inv_f_n = 1.0 / (far   - near);
    T5  const n2      = 2 * near;
    return result(n2 * inv_r_l, 0,  (right + left) * inv_r_l,                     0,
                  0, n2 * inv_t_b,  (top + bottom) * inv_t_b,                     0,
                  0,            0, -(far + near)   * inv_f_n, -(far * n2) * inv_f_n,
                  0,            0,                        -1,                     0);
}

////////////////////////////////////////////////////////
//! @brief 透視射影変換行列の逆行列を生成する関数
////////////////////////////////////////////////////////
template<class T1, class T2, class T3, class T4, class T5, class T6>
inline matrix<typename deduct2<deduct3<T1, T2, T3>, deduct3<T4, T5, T6> >::real_type>
inverse_frustum_matrix(T1 left, T2 right, T3 bottom, T4 top, T5 near, T6 far){
    typedef typename deduct2<T1, T2>::real_type T12;
    typedef typename deduct2<T3, T4>::real_type T34;
    typedef typename deduct2<T5, T6>::real_type T56;
    typedef matrix<typename deduct3<T12, T34, T56>::real_type> result;
    T5  const n2  = 2 * near;
    T56 const inv_n2  = 1.0 / n2;
    T56 const inv_nf2 = 1.0 / (far * n2);
    return result((right - left) * inv_n2, 0, 0, (right + left) * inv_n2,
                  0, (top - bottom) * inv_n2, 0, (top + bottom) * inv_n2,
                  0, 0,                       0,                      -1,
                  0, 0, -(far - near) * inv_nf2, (far + near) * inv_nf2);
}

////////////////////////////////////////////////////////
//! @brief 正射影変換行列を生成する関数
////////////////////////////////////////////////////////
template<class T1, class T2, class T3, class T4, class T5, class T6>
inline matrix<typename deduct2<deduct3<T1, T2, T3>, deduct3<T4, T5, T6> >::real_type>
ortho_matrix(T1 left, T2 right, T3 bottom, T4 top, T5 near, T6 far){
    typedef typename deduct2<T1, T2>::real_type T12;
    typedef typename deduct2<T3, T4>::real_type T34;
    typedef typename deduct2<T5, T6>::real_type T56;
    typedef matrix<typename deduct3<T12, T34, T56>::real_type> result;
    T12 const inv_r_l = 1.0 / (right - left);
    T34 const inv_t_b = 1.0 / (top   - bottom);
    T56 const inv_f_n = 1.0 / (far   - near);
    return result(2 * inv_r_l, 0,  0, -(right + left) * inv_r_l,
                  0, 2 * inv_t_b,  0, -(top + bottom) * inv_t_b,
                  0, 0, -2 * inv_f_n, -(far + near)   * inv_f_n,
                  0, 0,            0,                         1);
}

////////////////////////////////////////////////////////
//! @brief 正射影変換行列を生成する関数
////////////////////////////////////////////////////////
template<class T1, class T2, class T3, class T4>
inline matrix<typename deduct4<T1, T2, T3, T4>::real_type>
ortho_matrix(T1 left, T2 right, T3 bottom, T4 top){
    return ortho_matrix(left, right, bottom, top, -1, 1);
}

////////////////////////////////////////////////////////
//! @brief 正射影変換行列の逆行列を生成する関数
////////////////////////////////////////////////////////
template<class T1, class T2, class T3, class T4, class T5, class T6>
inline matrix<typename deduct2<deduct3<T1, T2, T3>, deduct3<T4, T5, T6> >::real_type>
inverse_ortho_matrix(T1 left, T2 right, T3 bottom, T4 top, T5 near, T6 far){
    typedef typename deduct2<T1, T2>::real_type T12;
    typedef typename deduct2<T3, T4>::real_type T34;
    typedef typename deduct2<T5, T6>::real_type T56;
    typedef matrix<typename deduct3<T12, T34, T56>::real_type> result;

    return result((right - left) * 0.5, 0,  0, (right + left) * 0.5,
                  0, (top - bottom) * 0.5,  0, (top + bottom) * 0.5,
                  0, 0,   -(far - near) * 0.5,  -(far + near) * 0.5,
                  0, 0,                     0,                    1);
    
}

////////////////////////////////////////////////////////
//! @brief viewport行列を生成する関数
////////////////////////////////////////////////////////
template<class T1, class T2>
inline matrix<typename deduct2<T1, T2>::value_type>
viewport_matrix(T1 width, T2 height){
    typedef typename deduct2<T1, T2>::value_type T;
    T const wh = width * 0.5, hh = height * 0.5; //width half, height half
    return matrix<T>(wh, 0, 0, wh,
                     0, hh, 0, hh,
                     0,  0, 1,  0,
                     0,  0, 0,  1);
}

////////////////////////////////////////////////////////
//! @brief viewport行列を生成する関数
////////////////////////////////////////////////////////
template<class E>
inline typename boost::enable_if<
    dimension_equal_to_c<E, 2>, matrix<typename E::value_type> >::type
viewport_matrix(vector_expression<E> const& v){
    return transpose(viewport_matrix(get<0>(v), get<1>(v)));
}

////////////////////////////////////////////////////////
//! @brief viewport行列の逆行列を生成する関数
////////////////////////////////////////////////////////
template<class T1, class T2>
inline matrix<typename deduct2<T1, T2>::real_type>
inverse_viewport_matrix(T1 width, T2 height){
    typedef typename deduct2<T1, T2>::real_type T;
    T const iw = 2.0 / width, ih = 2.0 / height;
    return matrix<T>(iw, 0, 0, -1,
                     0, ih, 0, -1,
                     0,  0, 1,  0,
                     0,  0, 0,  1);
}



__NOGARA_EXPRESSION_END

__NOGARA_BEGIN
using expression::get;
using expression::abs;
using expression::ternary;
using expression::transpose;
using expression::determinant;
using expression::inverse;
using expression::rotate_matrix;
using expression::translate_matrix;
using expression::look_at;
using expression::perspective_matrix;
using expression::inverse_perspective_matrix;
using expression::frustum_matrix;
using expression::inverse_frustum_matrix;
using expression::ortho_matrix;
using expression::inverse_ortho_matrix;
using expression::viewport_matrix;

using expression::to_quaternion;
using expression::to_matrix;

__NOGARA_END

#endif
