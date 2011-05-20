#ifndef NOGARA_OPENGL_TRAITS_HPP
#define NOGARA_OPENGL_TRAITS_HPP

///////////////////////////////////////
//! @file  nogara/gl_traits.hpp
//! @brief OpenGLの情報を統一するヘッダ
///////////////////////////////////////

#include <nogara/nogara_define.hpp>
#include <boost/mpl/size_t.hpp>

#if defined(NG_MSC)
#include <windows.h>
#endif

#if defined(__APPLE__)
#define GL_DIR OpenGL
#else
#define GL_DIR GL
#endif

#if defined(NG_MSC)
#define GLUT_DIR gl
#elif defined(__linux__)
#define GLUT_DIR GL
#else
#define GLUT_DIR GLUT
#endif

#define GL_PATH <GL_DIR/gl.h>
#define GLU_PATH <GL_DIR/glu.h>
#define GLEW_PATH <GL_DIR/glew.h>
#define GLUT_PATH <GLUT_DIR/glut.h>

#include GL_PATH

__NOGARA_BEGIN

//! @brief draw用GL_...定義の名前変更
enum draw_enum{
    NG_POINTS         = GL_POINTS,
    NG_LINES          = GL_LINES,
    NG_LINE_STRIP     = GL_LINE_STRIP,
    NG_LINE_LOOP      = GL_LINE_LOOP,
    NG_TRIANGLES      = GL_TRIANGLES,
    NG_TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
    NG_TRIANGLE_FAN   = GL_TRIANGLE_FAN,
    NG_QUADS          = GL_QUADS,
    NG_QUAD_STRIP     = GL_QUAD_STRIP,
    NG_POLYGON        = GL_POLYGON,
};

//! @brief 組み込み型をOpenGLの型を示す数値に変換するメタ関数
template<typename T>
struct type_to_gl_type : boost::mpl::size_t<0>{};

#define SP_GL_TRAITS(type, N)\
template<> struct type_to_gl_type<type> : boost::mpl::size_t<N>{}

SP_GL_TRAITS(int,            GL_INT);
SP_GL_TRAITS(unsigned int,   GL_UNSIGNED_INT);
SP_GL_TRAITS(short,          GL_SHORT);
SP_GL_TRAITS(unsigned short, GL_UNSIGNED_SHORT);
SP_GL_TRAITS(char,           GL_BYTE);
SP_GL_TRAITS(unsigned char,  GL_UNSIGNED_BYTE);
SP_GL_TRAITS(float,          GL_FLOAT);
SP_GL_TRAITS(double,         GL_DOUBLE);

#undef SP_GL_TRAITS

//! @brief マテリアル情報をメタ整数化
namespace material_enums{
    typedef boost::mpl::size_t<GL_DIFFUSE>   diffuse;
    typedef boost::mpl::size_t<GL_AMBIENT>   ambient;
    typedef boost::mpl::size_t<GL_SPECULAR>  specular;
    typedef boost::mpl::size_t<GL_EMISSION>  emission;
    typedef boost::mpl::size_t<GL_SHININESS> shininess;
}

//! @brief ライト情報をメタ整数化
namespace light_enums{
    typedef boost::mpl::size_t<GL_POSITION>              position;
    typedef boost::mpl::size_t<GL_SPOT_DIRECTION>        spot_direction;
    typedef boost::mpl::size_t<GL_SPOT_EXPONENT>         spot_exponent;
    typedef boost::mpl::size_t<GL_SPOT_CUTOFF>           spot_cutoff;
    typedef boost::mpl::size_t<GL_CONSTANT_ATTENUATION>  constant_attenuation;
    typedef boost::mpl::size_t<GL_LINEAR_ATTENUATION>    linear_attenuation;
    typedef boost::mpl::size_t<GL_QUADRATIC_ATTENUATION> quadratic_attenuation;
    typedef boost::mpl::size_t<GL_MAX_LIGHTS>            max_lights;
    typedef boost::mpl::size_t<GL_LIGHTING>              lighting;

    //! @brief 整数をライトの番号に変換するメタ関数
    template<std::size_t> struct get_light    : public boost::mpl::size_t<-999999>{};
    template<>            struct get_light<0> : public boost::mpl::size_t<GL_LIGHT0>{};
    template<>            struct get_light<1> : public boost::mpl::size_t<GL_LIGHT1>{};
    template<>            struct get_light<2> : public boost::mpl::size_t<GL_LIGHT2>{};
    template<>            struct get_light<3> : public boost::mpl::size_t<GL_LIGHT3>{};
    template<>            struct get_light<4> : public boost::mpl::size_t<GL_LIGHT4>{};
    template<>            struct get_light<5> : public boost::mpl::size_t<GL_LIGHT5>{};
    template<>            struct get_light<6> : public boost::mpl::size_t<GL_LIGHT6>{};
    template<>            struct get_light<7> : public boost::mpl::size_t<GL_LIGHT7>{};

}

__NOGARA_END

#endif
