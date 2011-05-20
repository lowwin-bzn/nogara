#ifndef NOGARA_GEOMETRY_RAY_HPP
#define NOGARA_GEOMETRY_RAY_HPP

//////////////////////////////////
//! @file  nogara/geometry/ray.hpp
//! @brief 無限光線を表すクラス
//////////////////////////////////

#include <nogara/geometry/line.hpp>

__NOGARA_BEGIN

template<class V>
class ray{
public:
    //! ベクトル型
    typedef V                              vector_type;
    //! ベクトルの要素の型
    typedef typename V::value_type         value_type;
    //! ベクトル要素型から推論した実数型
    typedef typename deduct1<V>::real_type real_type;
    //! 線分型
    typedef line<V>                        line_type;

    //! @brief コンストラクタ
    //! @param o 始点
    //! @param d 方向ベクトル
    ray(V const& o, V const& d):org(o), dir(d){}
    //! @brief コピーコンストラクタ
    ray(ray const& r):org(r.org), dir(r.dir){}

    //! @brief 始点から大きさtまでの線分を返す
    //! @param t 線分の大きさ
    line_type get_line(real_type const& t) const {
        return line_type(org, t * dir);
    }

    //! @brief 始点
    V const& origin()    const {return org;}
    //! @brief 方向ベクトル
    V const& direction() const {return dir;}

private:
    vector_type org, dir;
    
};

//! @brief 3次元単精度浮動小数光線
typedef ray<nogara::vector3f> ray3D;
//! @brief 2次元単精度浮動小数光線
typedef ray<nogara::vector2f> ray2D;

__NOGARA_END

#endif
