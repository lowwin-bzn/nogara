#ifndef NOGARA_SHAPE_H
#define NOGARA_SHAPE_H

/////////////////////////////////////////
//! @file  nogara/model/shape.hpp
//! @brief モデル生成関数群
/////////////////////////////////////////

#include <cassert>
#include <vector>
#include <utility>
#include <functional>
#include <boost/mpl/greater_equal.hpp>
#include <nogara/typedef.hpp>
#include <nogara/array.hpp>
#include <nogara/color/color.hpp>
#include <nogara/model/model.hpp>
#include <nogara/model/material.hpp>
#include <nogara/model/make_normals.hpp>
#if defined(NG_MSC)
#define _USE_MATH_DEFINES
#endif
#include <nogara/utility.hpp>

__NOGARA_BEGIN

namespace invisible{

typedef nogara::array<nogara::vector3f const, 8> BoxPosArray;
typedef nogara::array<uint16_t const, 36> BoxIndices;

#define BOX_VECTORS(wd2, hd2, dd2) {\
        nogara::vector3f(-wd2,  hd2, dd2),\
        nogara::vector3f( wd2,  hd2, dd2),\
        nogara::vector3f(-wd2, -hd2, dd2),\
        nogara::vector3f( wd2, -hd2, dd2),\
        nogara::vector3f(-wd2,  hd2, -dd2),\
        nogara::vector3f( wd2,  hd2, -dd2),\
        nogara::vector3f(-wd2, -hd2, -dd2),\
        nogara::vector3f( wd2, -hd2, -dd2),\
   }

#define BOX_INDICES { \
        0, 2, 1, \
        3, 1, 2, \
        4, 5, 6, \
        7, 6, 5, \
\
        1, 3, 5, \
        7, 5, 3, \
        0, 4, 2, \
        6, 2, 4, \
\
        4, 0, 5, \
        1, 5, 0, \
        2, 6, 3, \
        7, 3, 6, \
   }
        
static BoxPosArray boxPosArray(float width, float height, float depth){
    float const wd2 = width / 2;
    float const hd2 = height / 2;
    float const dd2 = depth / 2;
    BoxPosArray posAry = {BOX_VECTORS(wd2, hd2, dd2)};
    return posAry;
}

static BoxIndices boxIndices(){
    BoxIndices posAry = {BOX_INDICES};
    return posAry;
}

#undef BOX_VECTORS
#undef BOX_INDICES

template<class Vertex>
struct make_buffer_functor_base{
    std::vector<Vertex> vb;
};

template<class Vertex>
struct make_box_functor : public make_buffer_functor_base<Vertex>{
    typedef make_buffer_functor_base<Vertex> base_type;
    std::vector<Vertex>& operator()(BoxPosArray const& pos, BoxIndices const& ib){
        std::vector<vector3<float> > normals = make_normals(pos, ib);
        for(std::size_t i = 0; i < normals.size(); ++i){
            base_type::vb.push_back(Vertex(pos[i], normals[i]));
        }
        return base_type::vb;
    }
};

template<class Vertex, class ColorPack>
class make_colorBox_functor : public make_buffer_functor_base<Vertex>{
    typedef make_buffer_functor_base<Vertex> base_type;
public:
    make_colorBox_functor(ColorPack const& cp):color(cp){}
    std::vector<Vertex>& operator()(BoxPosArray const& pos, BoxIndices const&){
        for(std::size_t i = 0; i < pos.size(); ++i){
            base_type::vb.push_back(Vertex(pos[i], color[i]));
        }
        return base_type::vb;
    }

private:
    ColorPack color;
};

template<class Vertex, class ColorPack>
class make_normal_colorBox_functor : public make_buffer_functor_base<Vertex>{
    typedef make_buffer_functor_base<Vertex> base_type;
public:
    make_normal_colorBox_functor(ColorPack const& cp):color(cp){}
    std::vector<Vertex>& operator()(BoxPosArray const& pos, BoxIndices const& ib){
        std::vector<vector3<float> > const normals = make_normals(pos, ib);
        for(std::size_t i = 0; i < pos.size(); ++i){
            base_type::vb.push_back(Vertex(pos[i], normals[i], color[i]));
        }
        return base_type::vb;
    }

private:
    ColorPack const& color;
};

}

template<class Color>
struct color_pack{
    color_pack(Color const& c):color(c){}
    Color const& operator[](unsigned) const{return color;}
    Color const& color;
};

template<class Functor>
inline mesh_buffer make_box_buffer_impl(float width, float height, float depth, Functor func){
    invisible::BoxIndices const ib = invisible::boxIndices();
    return make_mesh_buffer(func(invisible::boxPosArray(width, height, depth), ib), ib);
};

inline mesh_buffer make_box_buffer(float width, float height, float depth){
    typedef nogara::vertex1<vertices::normal_type> Vertex;
    return make_box_buffer_impl(width, height, depth, invisible::make_box_functor<Vertex>());
};

template<class Color, class ColorPack>
inline mesh_buffer make_colorBox_buffer(float width, float height, float depth, ColorPack const& color){ 
    typedef nogara::vertex1<vertices::color_type<Color> > Vertex;
    return make_box_buffer_impl(width, height, depth,
                                invisible::make_colorBox_functor<Vertex, ColorPack>(color));
}

template<class Color, class ColorPack>
inline mesh_buffer make_normal_colorBox_buffer(float width, float height, float depth, ColorPack const& color){ 
    typedef nogara::vertex2<vertices::normal_type, vertices::color_type<Color> > Vertex;
    return make_box_buffer_impl(width, height, depth,
                                invisible::make_normal_colorBox_functor<Vertex, ColorPack>(color));
}

template<class Color>
inline mesh_buffer make_normal_colorBox_buffer(float width, float height, float depth, Color const& color){ 
    typedef nogara::vertex2<vertices::normal_type, vertices::color_type<Color> > Vertex;
    return make_box_buffer_impl(width, height, depth,
                                invisible::make_normal_colorBox_functor<Vertex, color_pack<Color> >(color));
}


inline nogara::model::shared_ptr make_box(float width, float height, float depth){
    return make_model(make_mesh(make_box_buffer(width, height, depth)));
}

inline nogara::model::shared_ptr make_box(nogara::vector3f const& whd){
    return make_box(whd(0), whd(1), whd(2));
}

template<class Color>
inline typename boost::enable_if<is_color<Color>, nogara::model::shared_ptr>::type
make_colorBox(float width, float height, float depth, Color const& color){
    return make_model(make_mesh(make_colorBox_buffer<Color>(width, height, depth,
                                                           color_pack<Color>(color))));
}

template<class Color, std::size_t SIZE>
inline typename boost::enable_if<
    boost::mpl::and_<is_color<Color>,
    boost::mpl::greater_equal<boost::mpl::size_t<SIZE>, boost::mpl::size_t<8> > >,
    nogara::model::shared_ptr>::type
make_colorBox(float width, float height, float depth, Color const (&colors)[SIZE]){
    return make_model(make_mesh(make_colorBox_buffer<Color>(width, height, depth, colors)));
}

template<class Color, std::size_t SIZE>
inline typename boost::enable_if<
    boost::mpl::and_<is_color<Color>,
                     boost::mpl::greater_equal<boost::mpl::size_t<SIZE>, boost::mpl::size_t<8> > >,
                     nogara::model::shared_ptr>::type
make_colorBox(float width, float height, float depth, array<Color, SIZE> const& colors){
    return make_model(make_mesh(make_colorBox_buffer<Color>(width, height, depth, colors)));
}

template<class Color>
inline typename boost::enable_if<is_color<Color>, nogara::model::shared_ptr>::type
make_colorBox(float width, float height, float depth, std::vector<Color> const& colors){
    if(colors.size() < 8){
        return nogara::model::shared_ptr();
    }
    return mame_model(make_mesh(make_colorBox_buffer<Color>(width, height, depth, colors)));
}


template<class Color>
inline nogara::model::shared_ptr make_colorBox(vector3<float> const& whd, Color const& color){
    return make_colorBox(whd(0), whd(1), whd(2), color);
}

template<class Color, std::size_t SIZE>
inline nogara::model::shared_ptr make_colorBox(vector3<float> const& whd, Color const (&colors)[SIZE]){
    return make_colorBox(whd(0), whd(1), whd(2), colors);
}

template<class Color, std::size_t SIZE>
inline nogara::model::shared_ptr make_colorBox(vector3<float> const& whd, array<Color, SIZE> const& colors){
    return make_colorBox(whd(0), whd(1), whd(2), colors);
}

template<class Color>
inline nogara::model::shared_ptr make_colorBox(vector3<float> const& whd, std::vector<Color> const& colors){
    return make_colorBox(whd(0), whd(1), whd(2), colors);
}



template<class Color>
inline typename boost::enable_if<is_color<Color>, nogara::model::shared_ptr>::type
make_normal_colorBox(float width, float height, float depth, Color const& color){
    return make_model(make_mesh(make_normal_colorBox_buffer<Color>(width, height, depth,
                                                                   color_pack<Color>(color))));
}

template<class Color, std::size_t SIZE>
inline typename boost::enable_if<
    boost::mpl::and_<is_color<Color>,
    boost::mpl::greater_equal<boost::mpl::size_t<SIZE>, boost::mpl::size_t<8> > >,
    nogara::model::shared_ptr>::type
make_normal_colorBox(float width, float height, float depth, Color const (&colors)[SIZE]){
    return make_model(make_mesh(make_normal_colorBox_buffer<Color>(width, height, depth, colors)));
}

template<class Color, std::size_t SIZE>
inline typename boost::enable_if<
        boost::mpl::and_<is_color<Color>,
        boost::mpl::greater_equal<boost::mpl::size_t<SIZE>, boost::mpl::size_t<8> > >,
        nogara::model::shared_ptr>::type
make_normal_colorBox_buffer(float width, float height, float depth, array<Color, SIZE> const& colors){
    return make_model(make_mesh(make_normal_colorBox_buffer<Color>(width, height, depth, colors)));
}

template<class Color>
inline typename boost::enable_if<is_color<Color>, nogara::model::shared_ptr>::type
make_normal_colorBox_buffer(float width, float height, float depth, std::vector<Color> const& colors){
    if(colors.size() < 8){
        return nogara::model::shared_ptr();
    }
    return make_model(make_mesh(make_normal_colorBox_buffer<Color>(width, height, depth, colors)));
}


template<class Color>
inline nogara::model::shared_ptr make_normal_colorBox_buffer(vector3<float> const& whd, Color const& color){
    return make_normal_colorBox_buffer(whd(0), whd(1), whd(2), color);
}

template<class Color, std::size_t SIZE>
inline nogara::model::shared_ptr make_normal_colorBox_buffer(vector3<float> const& whd, Color const (&colors)[SIZE]){
    return make_normal_colorBox_buffer(whd(0), whd(1), whd(2), colors);
}

template<class Color, std::size_t SIZE>
inline nogara::model::shared_ptr make_normal_colorBox_buffer(vector3<float> const& whd, array<Color, SIZE> const& colors){
    return make_normal_colorBox_buffer(whd(0), whd(1), whd(2), colors);
}

template<class Color>
inline nogara::model::shared_ptr make_normal_colorBox_buffer(vector3<float> const& whd, std::vector<Color> const& colors){
    return make_normal_colorBox_buffer(whd(0), whd(1), whd(2), colors);
}


inline nogara::model::shared_ptr make_sphire(){
    typedef nogara::vertex1<nogara::vertices::normal_type> Vertex;
    std::vector<Vertex> vb;
    vb.reserve(17 * 9);

    for(int i = 0; i <= 8; ++i){
        float const v = i / 8.0f;
        float const y = std::cos(NG_PI * v);
        float const r = std::sin(NG_PI * v);
        for(int j = 0 ; j <= 16 ; ++j) {
            float const u = j / 16.0f;
            float const x = std::cos(2 * NG_PI * u) * r;
            float const z = std::sin(2 * NG_PI * u) * r;
            nogara::vector3f v(x, y, z);
            vb.push_back(Vertex(v, v));
        }
    }

    uint16_t ib[3 * 32 * 8];
    uint16_t* index = &ib[0];
    for(int j = 0 ; j < 8 ; ++j) {
        int base = j * 17;
        for(int i = 0 ; i < 16 ; ++i) {
            *index++ = base + i;
            *index++ = base + i + 1;
            *index++ = base + i + 17;
            *index++ = base + i + 17;
            *index++ = base + i + 1;
            *index++ = base + i + 1 + 17;
        }
    }

    return make_model(nogara::make_mesh(nogara::make_mesh_buffer(vb, ib)));
}

#include "shape/cylinder.hpp"

inline nogara::model::shared_ptr make_cylinder(float radius, float height){
    return cylinder_maker::make(radius, height);
}

#include "shape/pyramid.hpp"

inline nogara::model::shared_ptr make_pyramid(float radius, float height, int num_base_vertices){
    return pyramid_maker::make(radius, height, num_base_vertices);
}

#include "shape/corn.hpp"

inline nogara::model::shared_ptr make_corn(float radius, float height){
    return corn_maker::make(radius, height);
}

__NOGARA_END

#endif
