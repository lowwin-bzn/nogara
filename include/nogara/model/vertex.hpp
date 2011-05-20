#ifndef NOGARA_VERTEX_HPP
#define NOGARA_VERTEX_HPP

//////////////////////////////////
//! @file  nogara/model/vertex.hpp
//! @brief 頂点情報
//////////////////////////////////

#include <boost/mpl/size_t.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/if.hpp>
#include <nogara/vector.hpp>
#include <nogara/color/color.hpp>
#include <nogara/gl_traits.hpp>

__NOGARA_BEGIN

namespace vertices{
//! @brief 頂点位置要素タグ
struct position_tag{};
//! @brief 法線要素タグ
struct normal_tag{};
//! @brief 頂点色要素タグ
struct color_tag{};
//! @brief テクスチャ座標要素タグ
struct uv_tag{};
//! @brief null要素タグ
struct null_tag{};

//! @brief 頂点情報が扱わない要素であれば作用しないようにするための構造体
struct null_type{
    typedef null_tag  tag;
    typedef null_type value_type;
    typedef boost::mpl::size_t<0> Size;
    static unsigned int apply(unsigned int pos, std::size_t /*vertex_size*/){return pos;}
};

//! @brief 頂点位置要素
struct position_type{
    typedef position_tag             tag;
    typedef vector3<float>           value_type;
    typedef boost::mpl::sizeof_<value_type> Size;
    position_type(value_type const& v):position(v){}
    static unsigned int apply(std::size_t pos, std::size_t vertex_size){
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(expression::get_dimension<value_type>::value,
                        type_to_gl_type<value_type::value_type>::value,
                        vertex_size, reinterpret_cast<GLbyte *>(pos));
        return pos + Size::value;
    }
    value_type position;
};

//! @brief 法線要素
struct normal_type{
    typedef normal_tag               tag;
    typedef vector3<float>           value_type;
    typedef boost::mpl::sizeof_<value_type> Size;
    normal_type(value_type const& v):normal(v){}
    static unsigned int apply(std::size_t pos, std::size_t vertex_size){
        glEnableClientState(GL_NORMAL_ARRAY);
        glNormalPointer(type_to_gl_type<float>::value, vertex_size, reinterpret_cast<GLbyte *>(pos));
        return pos + Size::value;
    }
    value_type normal;
};

//! @brief テクスチャ座標要素
struct uv_type{
    typedef uv_tag                   tag;
    typedef vector2<float>           value_type;
    typedef boost::mpl::sizeof_<value_type> Size;
    uv_type(value_type const& v):uv(v){}

    static unsigned int apply(std::size_t pos, std::size_t vertex_size){
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(2, type_to_gl_type<float>::value, vertex_size, reinterpret_cast<GLbyte *>(pos));
        return pos + Size::value;
    }
    value_type uv;
};

//! @brief 頂点色要素
template<class Color>
struct color_type{
    typedef color_tag                tag;
    typedef Color                    value_type;
    typedef boost::mpl::sizeof_<value_type> Size;

    color_type(value_type const& c):color(c){}
    static unsigned int apply(std::size_t pos, std::size_t vertex_size){
        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(Color::Size::value, type_to_gl_type<typename Color::value_type>::value,
                       vertex_size, reinterpret_cast<GLbyte *>(pos));
        return pos + Size::value;
    }
    value_type color;
};

//! @brief リストアクセスの為の要素
template<class T, class N>
struct cons{
    typedef T type;
    typedef N next;
};

//! @brief タグが等しい要素を見つけるメタ関数
template<class cons, class tag>
struct find_from_tag{
    typedef typename boost::mpl::eval_if<
        boost::is_same<typename cons::type::tag, tag>,
        cons, find_from_tag<typename cons::next, tag> >::type type;
};

//! @brief タグが等しい要素を見つけるメタ関数 存在しない場合はnull_type
template<class tag>
struct find_from_tag<null_type, tag>{
    typedef null_type type;
};

//! @brief 頂点情報より頂点位置要素を抜き出す
template<class v>
struct get_position_type : find_from_tag<typename v::first_element, position_tag>{};

//! @brief 頂点情報より法線要素を抜き出す
template<class v>
struct get_normal_type   : find_from_tag<typename v::first_element, normal_tag>{};

//! @brief 頂点情報より頂点色要素を抜き出す
template<class v>
struct get_color_type    : find_from_tag<typename v::first_element, color_tag>{};

//! @brief 頂点情報よりテクスチャ座標要素を抜き出す
template<class v>
struct get_uv_type       : find_from_tag<typename v::first_element, uv_tag>{};

}

//! @brief 頂点位置のみを扱う頂点情報
struct position_vertex : public vertices::position_type{
    typedef vertices::cons<position_type, vertices::null_type> first_element;

    static std::size_t position_size(){
        return vertices::position_type::Size::value;
    }

    static std::size_t normal_size(){return 0;}
    static std::size_t color_size() {return 0;}
    static std::size_t uv_size()    {return 0;}

    static std::size_t size(){return position_size();}

    position_vertex(position_type::value_type const& _0):position_type(_0){}
};

//! @brief 頂点位置 + 一つの要素を扱う頂点情報
template<class T1>
struct vertex1 : public vertices::position_type, public T1{
    typedef vertex1<T1>                                self_type;
    typedef vertices::cons<T1, vertices::null_type>    end_element;
    typedef vertices::cons<position_type, end_element> first_element;

    static std::size_t position_size(){
        return vertices::get_position_type<self_type>::type::Size::value;
    }

    static std::size_t normal_size(){
        return vertices::get_normal_type<self_type>::type::Size::value;
    }

    static std::size_t color_size(){
        return vertices::get_color_type<self_type>::type::Size::value;
    }
    static std::size_t uv_size(){
        return vertices::get_uv_type<self_type>::type::Size::value;
    }

    static std::size_t size(){
        return position_size() + normal_size() + color_size() + uv_size();
    }

    vertex1(position_type::value_type const& _0, typename T1::value_type const& _1):
        position_type(_0), T1(_1){}
};

//! @brief 頂点位置 + 二つの要素を扱う頂点情報
template<class T1, class T2>
struct vertex2 : public vertices::position_type, public T1, public T2{
    typedef vertex2<T1, T2>                               self_type;
    typedef vertices::cons<T2, vertices::null_type>       end_element;
    typedef vertices::cons<T1, end_element>               second_element;
    typedef vertices::cons<position_type, second_element> first_element;

    static std::size_t position_size(){
        return vertices::get_position_type<self_type>::type::Size::value;
    }

    static std::size_t normal_size(){
        return vertices::get_normal_type<self_type>::type::Size::value;
    }

    static std::size_t color_size(){
        return vertices::get_color_type<self_type>::type::Size::value;
    }
    static std::size_t uv_size(){
        return vertices::get_uv_type<self_type>::type::Size::value;
    }

    static std::size_t size(){
        return position_size() + normal_size() + color_size() + uv_size();
    }

    vertex2(position_type::value_type const& _0,
            typename T1::value_type const& _1,
            typename T2::value_type const& _2):
        position_type(_0), T1(_1), T2(_2){}
};

//! @brief 頂点位置 + 三つの要素を扱う頂点情報
template<class T1, class T2, class T3>
struct vertex3 : public vertices::position_type, public T1, public T2, public T3{
    typedef vertex3<T1, T2, T3>                           self_type;
    typedef vertices::cons<T3, vertices::null_type>       end_element;
    typedef vertices::cons<T2, end_element>               third_element;
    typedef vertices::cons<T1, third_element>             second_element;
    typedef vertices::cons<vertices::position_type, second_element> first_element;

    static std::size_t position_size(){
        return vertices::get_position_type<self_type>::type::Size::value;
    }

    static std::size_t normal_size(){
        return vertices::get_normal_type<self_type>::type::Size::value;
    }

    static std::size_t color_size(){
        return vertices::get_color_type<self_type>::type::Size::value;
    }
    static std::size_t uv_size(){
        return vertices::get_uv_type<self_type>::type::Size::value;
    }

    static std::size_t size(){
        return position_size() + normal_size() + color_size() + uv_size();
    }

    vertex3(vertices::position_type::value_type const& _0,
           typename T1::value_type const& _1,
           typename T2::value_type const& _2,
           typename T3::value_type const& _3):
        position_type(_0), T1(_1), T2(_2), T3(_3){}
};

__NOGARA_END

#endif
