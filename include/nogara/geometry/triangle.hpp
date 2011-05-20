#ifndef NOGARA_GEOMETRY_TRIANGLE_HPP
#define NOGARA_GEOMETRY_TRIANGLE_HPP

////////////////////////////////////////
//! @file  /nogara/geometry/triangle.hpp
//! @brief 三角形について取り扱うクラス
////////////////////////////////////////


#include <nogara/vector.hpp>
#include <nogara/geometry/line.hpp>
#include <utility>

__NOGARA_BEGIN

//! @brief 三角形クラス
template<class Vector>
class triangle{
    typedef line<Vector> line_type;
    typedef expression::expression_container<Vector, 3> container_type;
    typedef std::pair<unsigned, unsigned> index_pair;
public:
    //! @brief ベクトル型
    typedef Vector                      vector_type;
    //! @brief ベクトルの要素の型
    typedef typename Vector::value_type value_type;
    //! @brief 実数型
    typedef typename deduct1<Vector>::real_type  real_type;
    //! @brief 実数ベクトル型
    typedef typename expression::vector_type<
        real_type, Vector::Dimension::value>::type real_vector_type;

    //! @brief コンストラクタ
    //! @param _1 一番目の頂点
    //! @param _2 二番目の頂点
    //! @param _3 三番目の頂点
    triangle(vector_type const& _1, vector_type const& _2, vector_type const& _3):
        vertices(_1, _2, _3){}

    //! @brief コピーコンストラクタ
    triangle(triangle const& t):vertices(t.vertices){}
    //! @brief コピーコンストラクタ
    template<class U>
    triangle(triangle<U> const& t):vertices(t.vertices){}

    //! @brief 面積
    real_type S() const {
        return real_type(0.5) * nogara::length(surface_normal());
    }

    //! @brief 面積
    real_type area() const {return S();}

    //! @brief 重心の座標
    real_vector_type centroid() const {
        return (vertex(0) + vertex(1) + vertex(2)) / real_type(3);
    }

    //! @brief 内接円の中心座標
    real_vector_type incircle_center() const {
        real_vector_type lens(edge_length(0), edge_length(1), edge_length(2));
        return (lens(0) * vertex(0) + lens(1) * vertex(1) + lens(2) * vertex(2)) / nogara::sum(lens);
    }

    //! @brief 内接円の半径
    real_type incircle_radius() const {
        return 2 * S() / sum_edge_length();
    }

    //! @brief 外接円の中心座標
    real_vector_type circum_center() const {
        real_type const sqS16 = std::pow(S(), 2) * 16;
        if(std::abs(sqS16) < std::numeric_limits<real_type>::epsilon()){
            return real_vector_type::zero;
        }

        real_type const invS = 1 / sqS16;
        vector_type const len_sq(nogara::length_sq(edge(0).vector()),
                                 nogara::length_sq(edge(1).vector()),
                                 nogara::length_sq(edge(2).vector()));
        real_vector_type const k = invS * 
            nogara::multiply(len_sq, swizzle<swizzle_yzx>(len_sq) + swizzle<swizzle_zxy>(len_sq) - len_sq);
        return k(0) * vertex(0) + k(1) * vertex(1) + k(2) * vertex(2);
    }

    //! @brief 外接円の半径
    real_type circum_radius() const {
        return real_type(0.5) * edge_length(0) / std::sin(angle(0));
    }

    //! @brief 引数で示した2頂点からなる辺
    //! @param from 始点の頂点番号
    //! @param to   終点の頂点番号
    line_type edge(unsigned from, unsigned to) const {
        return line_type(vertex(from), vertex(to));
    }

    //! @brief indexが示す頂点の対角にある辺
    //! @param index 頂点番号
    line_type edge(unsigned index) const {
        index_pair const other = other_index_pair(index);
        return edge(other.first, other.second);
    }
    //! @brief indexが示す頂点の対角にある辺(edgeとは始点、終点の順が違う)
    //! @param index 頂点番号
    line_type edge_reverse(unsigned index) const {
        index_pair const other = other_index_pair(index);
        return line_type(vertex(other.second), vertex(other.first));
    }

    //! @brief indexが示す頂点の対角にある辺の長さ
    //! @param index 頂点番号
    real_type edge_length(unsigned index) const {
        return edge(index).length();
    }

    //! 各辺の長さの合計
    real_type sum_edge_length() const {
        return edge_length(0) + edge_length(1) + edge_length(2);
    }

    //! @brief indexの示す頂点の角度
    //! @param index 頂点番号
    real_type angle(unsigned index) const {
        index_pair const other = other_index_pair(index);
        return nogara::angle(edge(index, other.first).normalize(),
                             edge(index, other.second).normalize());
    }

    //! @brief 頂点
    //! @param index 頂点番号
    vector_type const& vertex(unsigned index) const {return vertices(index);}

    //! @brief 面法線
    vector_type surface_normal() const {
        return nogara::cross(edge(0, 1).vector(), edge(0, 2).vector());
    }

    //! @brief 標準化された面法線
    vector_type normalize_surface_normal() const {
        return nogara::normalize(surface_normal());
    }

private:
    index_pair other_index_pair(unsigned index) const {
        return index_pair((1 + index) % 3, (2 + index) % 3);
    }

private:
    container_type vertices;
};





__NOGARA_END

#endif
