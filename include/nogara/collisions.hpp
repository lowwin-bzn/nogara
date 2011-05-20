#ifndef NOGARA_COLLISIONS_HPP
#define NOGARA_COLLISIONS_HPP

///////////////////////////////
//! @file nogara/collisions.hpp
//! @brief 衝突判定を扱う
///////////////////////////////

#include <nogara/vector.hpp>
#include <nogara/geometry/line.hpp>
#include <nogara/geometry/ray.hpp>
#include <nogara/geometry/triangle.hpp>

__NOGARA_BEGIN

//! @brief 点が衝突するかを返す
template<class E1, class E2, typename T>
inline typename boost::enable_if<
    expression::same_dimension<E1, E2>, bool>::type
collide_dot(expression::vector_expression<E1> const &v1,
            expression::vector_expression<E2> const &v2, T const& r){
    typedef expression::get_dimension<E1> size;
    typedef typename expression::vector_type<T, size::value>::type vector;
    vector const sub = v1 - v2;
    return nogara::dot(sub, sub) < r * r;
}

//! @brief 球が衝突するかを返す
template<class E1, class E2, typename T, typename U>
inline typename boost::enable_if<
    expression::same_dimension<E1, E2>, bool>::type
collide_sphere(expression::vector_expression<E1> const &v1,
               expression::vector_expression<E2> const &v2, T const& r1, U const& r2){
    return collide_dot(v1, v2, r1 + r2);
}

//! @brief 線分同士が衝突するかを返す
template<class E1, class E2, class E3, class E4>
inline typename boost::enable_if<
    boost::mpl::and_<expression::same_dimension<E1, E2>,
                     expression::same_dimension<E3, E4>,
                     expression::same_dimension<E1, E4> >, bool>::type
collide_line(expression::vector_expression<E1> const& s1,
             expression::vector_expression<E2> const& e1,
             expression::vector_expression<E3> const& s2,
             expression::vector_expression<E4> const& e2)
{
    typedef typename deduct4<E1, E2, E3, E4>::real_type real_t;
    typedef expression::get_dimension<E1> size;
    typedef typename expression::vector_type<real_t, size::value>::type vector;
    return collide_line(line<vector>(s1, e1), line<vector>(s2, e2));
}

//! @brief 線分同士が衝突するかを返す
template<class V>
inline bool collide_line(line<V> const& v1, line<V> const& v2){
    line<V> const v3(v1.start(), v2.start());
    V const n1 = nogara::cross(v3.vector(), v1.vector());
    expression::equal_test<typename V::real_type> equal;
    if(equal(nogara::length(n1), 0)){return true;}
    V const n2 = nogara::cross(v2.vector(), v1.vector());
    return nogara::length(n2) > 0 && equal(nogara::length(nogara::cross(n1, n2)), 0);
}

//! @brief 直線が三角形と衝突するかを返す
template<class V>
inline bool collide_triangle(triangle<V> const& tri, ray<V> const& r){
    typedef typename V::value_type value_type;
    typedef typename V::real_type  real_type;
    //表裏面の判定は、途中の条件式が反転するだけなので
    //条件式の切り替えだけで記述が済むように
    //関数内構造体のstatic関数を記述して
    //ポインタで切り替えが出来るようにする
    typedef bool (*cond_type)(value_type, value_type);
    struct cond_op{
        static bool _1(value_type x, value_type d){return (x < 0 || x > d);}
        static bool _2(value_type x, value_type d){return (x > 0 || x < d);}
    };

    V const edge1(tri.edge(0, 1).vector()), edge2(tri.edge(0, 2).vector());
    V const diredge_v(nogara::cross(r.direction(), edge2));
    value_type const d = nogara::dot(edge1, diredge_v);

    bool const ovep = d >  std::numeric_limits<value_type>::epsilon();
    bool const lsep = d < -std::numeric_limits<value_type>::epsilon();
    if(!(ovep || lsep)){return false;}
    cond_type const cond_f = ovep ? &cond_op::_1 : &cond_op::_2;

    V const ray_v(r.origin() - tri.vertex(0));
    value_type const u = nogara::dot(diredge_v, ray_v);
    if(cond_f(u, d)){return false;}
    V const rayedge_v(nogara::cross(ray_v, edge1));
    value_type const v = nogara::dot(r.direction(), ray_v);
    if(cond_f(v + u, d)){return false;}
    //real_type const inv_d = 1.0 / d;
    //value_type const t = dot(edge2, rayedge_v);
    //return r.get_line(t);
}

//! @brief 三角形の中に点が存在するかを判定する
template<class V>
inline bool collide_triangle(triangle<V> const& tri, V const& p){
    V const normal = tri.surface_normal();
    expression::equal_test<typename V::value_type> equal;
    //三角形の法線と点の位置の内積の結果が0でなければ
    //水平でなく、平面上に存在しないのでfalseを返す
    if(!equal(nogara::dot(p, normal), 0)){
        return false;
    }
    V const e1 = tri.vertex(0) - p, e2 = tri.vertex(1) - p;
    if(nogara::dot(nogara::cross(e1, e2), normal) < 0){
        return false;
    }
    V const e3 = tri.vertex(2) - p;
    if(nogara::dot(nogara::cross(e2, e3), normal) < 0){
        return false;
    }
    return !(nogara::dot(nogara::cross(e3, e1), normal) < 0);
}

__NOGARA_END

#endif
