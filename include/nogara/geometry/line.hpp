#ifndef NOGARA_GEOMETRY_LINE_HPP
#define NOGARA_GEOMETRY_LINE_HPP

//! @file  nogara/geometry/line.hpp
//! @brief 線分を表すオブジェクト

#include <nogara/interval.hpp>
#include <nogara/vector.hpp>

__NOGARA_BEGIN

template<class Vector>
class line{
    typedef expression::vector_binary<
        Vector, Vector, expression::scalar_sub<Vector, Vector> > edge_vector;
public:
    typedef Vector                           vector_type;
    typedef typename vector_type::value_type value_type;
    typedef typename vector_type::real_type  real_type;

    //! @brief コンストラクタ
    //! @param s 始点
    //! @param e 終点
    line(vector_type const& s, vector_type const& e):start_(s), end_(e){}
    //! @brief コピーコンストラクタ
    line(line const& l):start_(l.start_), end_(l.end_){}

    //! @brief 線分の長さ
    real_type   length()    const {return nogara::length(vector());}
    //! @brief 標準化された線分ベクトル
    vector_type normalize() const {return nogara::normalize(vector());}
    //! @brief 線分のベクトル
    edge_vector vector()    const {return end_ - start_;}

    //! @brief 線分の始点
    vector_type const& start() const {return start_;}
    //! @brief 線分の終点
    vector_type const&   end() const {return end_;}
private:
    vector_type start_;
    vector_type end_;
};

//! @brief 3次元単精度浮動小数の線分
typedef line<nogara::vector3f> line3D;
//! @brief 2次元単精度浮動小数の線分
typedef line<nogara::vector2f> line2D;

__NOGARA_END

#endif
