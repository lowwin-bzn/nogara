#ifndef NOGARA_TRANSFORMATION_HPP
#define NOGARA_TRANSFORMATION_HPP

///////////////////////////////////////////
//! @file  nogara/model/transformation.hpp
//! @brief アフィン変換行列クラス
///////////////////////////////////////////

#include <nogara/matrix.hpp>
__NOGARA_BEGIN

//! @brief 移動、回転、スケーリングを行う変換行列
template<class T>
class transformation{
    typedef expression::vector3<T>    vector3_type;
    typedef expression::quaternion<T> quaternion_type;
    typedef expression::matrix<T>     matrix_type;
    typedef expression::matrix33<T>   rotate_matrix_type;
public:
    //! @brief コンストラクタ
    transformation():
        translate_(vector3_type::zero), rotate_(quaternion_type::identity), scale_(T(1), T(1), T(1)){}
    //! @brief コピーコンストラクタ
    transformation(transformation const& rhs):
        translate_(rhs.translate_), rotate_(rhs.rotate_), scale_(rhs.scale_){}
    //! @brief コンストラクタ
    transformation(vector3_type const& t, quaternion_type const& r, vector3_type const& s):
        translate_(t), rotate_(r), scale_(s){}
    //! @brief コンストラクタ
    transformation(vector3_type const& t, vector3_type const& r, vector3_type const& s):
        translate_(t), rotate_(to_quaternion(r)), scale_(s){}
    //! @brief コンストラクタ
    transformation(vector3_type const& t, rotate_matrix_type const& r, vector3_type const& s):
        translate_(t), rotate_(to_quaternion(r)), scale_(s){}

    //! @brief 平行移動
    vector3_type const& translate() const {return translate_;}
    //! @brief 平行移動の設定
    void translate(vector3_type const& v){translate_ = v;}
    //! @brief 平行移動の設定
    void translate(T const& x, T const& y, T const& z){
        translate_(0) = x; translate_(1) = y; translate_(2) = z;
    }

    //! @brief 回転
    quaternion_type const& rotate() const {return rotate_;}
    //! @brief 回転の設定
    void rotate(quaternion_type const& q){rotate_ = q;}
    //! @brief 回転の設定
    void rotate(vector3_type const& v){rotate(to_quaternion(v));}
    //! @brief 回転の設定
    void rotate(T const& x, T const& y, T const& z){rotate(to_quaternion(x, y, z));}
    //! @brief 回転の設定
    void rotate(rotate_matrix_type const& m){rotate(to_quaternion(m));}

    //! @brief スケーリング
    vector3_type const& scale() const {return scale_;}
    //! @brief スケーリングの設定
    void scale(vector3_type const& v){scale_ = v;}
    //! @brief スケーリングの設定
    void scale(T const& x, T const& y, T const& z){
        scale_(0) = x; scale_(1) = y; scale_(2) = z;
    }
    void scale(T const& v){
        scale_(0) = v; scale_(1) = v; scale_(2) = v;
    }

    //! @brief 行列化
    operator matrix_type() const{return to_matrix();}

    //! @brief 行列化
    matrix_type to_matrix() const {
        return extend<4, 4>(scale_matrix(scale_) * 
                            rotate_matrix(rotate_)) *
            translate_matrix(translate_);
    }

    //! @brief 逆行列
    matrix_type inverse() const {
        return translate_matrix(-translate_) *
            extend<4, 4>(nogara::transpose(rotate_matrix(rotate_))) *
            extend<4, 4>(scale_matrix(nogara::inverse(scale_)));
    }

    //! @brief 転置行列
    expression::transpose_matrix<matrix_type> transpose() const {
        return nogara::transpose(to_matrix());
    }
    
private:
    vector3_type    translate_;
    quaternion_type rotate_;
    vector3_type    scale_;
};


//! @brief 逆行列
template<class T>
inline matrix<T> inverse(transformation<T> const& t){
    return t.inverse();
}

//! @brief 転置行列
template<class T>
expression::transpose_matrix<expression::matrix<T> >
inline transpose(transformation<T> const& t){
    return t.transpose();
}

__NOGARA_END



#endif
