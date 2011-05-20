#ifndef NOGARA_RGBA_COLOR_HPP
#define NOGARA_RGBA_COLOR_HPP

//////////////////////////////////
//! @file  nogara/color/rgba/color.hpp
//! @brief rgbaカラーライブラリ
//////////////////////////////////

#include <boost/type_traits.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/utility/enable_if.hpp>

#include <nogara/nogara_define.hpp>
#include <nogara/vector.hpp>

__NOGARA_BEGIN
namespace rgba{

template<typename T>
struct float_color{
    typedef T                     value_type;
    typedef vector4<value_type>   vector_type;
    typedef boost::mpl::size_t<4> Size;

    float_color():rgba(0, 0, 0, 0){}
    float_color(float_color const& color):rgba(color.rgba){}
    float_color(value_type r, value_type g, value_type b, value_type a = value_type(1)):rgba(r, g, b, a){}
    template<class E>
    float_color(expression::vector_expression<E> const& v):rgba(v){}
    explicit float_color(unsigned int value):
        rgba(value_type((value >> 24) & 0xFF) / 255,
             value_type((value >> 16) & 0xFF) / 255,
             value_type((value >> 8)  & 0xFF) / 255,
             value_type(value & 0xFF) / 255){}

    void set_color(value_type r, value_type g, value_type b, value_type a = value_type(1)){
        rgba(0) = r; rgba(1) = g; rgba(2) = b; rgba(3) = a;
    }

    void set_color(unsigned int value){
        set_color(value_type((value >> 24) & 0xFF) / 255.0,
                  value_type((value >> 16) & 0xFF) / 255.0,
                  value_type((value >> 8)  & 0xFF) / 255.0,
                  value_type(value & 0xFF) / 255.0);
    }

    void set_color(float_color const& value){
        rgba = value.rgba;
    }

    template<class E>
    typename boost::enable_if<expression::dimension_equal_to_c<E, 4> >::type
    set_color(expression::vector_expression<E> const& v){
        rgba = v;
    }

    value_type*       to_pointer()       {return rgba.begin();}
    value_type const* to_pointer() const {return rgba.begin();}

    float_color& operator =(float_color const& value){
        if(&value != this){
            set_color(value);
        }
        return *this;
    }

    float_color& operator =(unsigned int value){
        set_color(value);
        return *this;
    }

    template<class E>
    float_color& operator =(expression::vector_expression<E> const& v){
        set_color(v);
        return *this;
    }

    operator vector_type&()             {return rgba;}
    operator vector_type const&() const {return rgba;}

    vector_type rgba;
};

template<typename T>
struct integer_color{
    typedef T                     value_type;
    typedef vector4<value_type>   vector_type;
    typedef boost::mpl::size_t<4> Size;

    integer_color():rgba(0, 0, 0, 0){}
    integer_color(integer_color const& color):rgba(color.rgba){}
    integer_color(value_type r, value_type g, value_type b, value_type a = 1):rgba(r, g, b, a){}
    template<class E>
    integer_color(expression::vector_expression<E> const& v):rgba(v){}

    void set_color(value_type r, value_type g, value_type b, value_type a = 1){
        rgba(0) = r; rgba(1) = g; rgba(2) = b; rgba(3) = a;
    }

    void set_color(integer_color const& value){
        rgba = value.rgba;
    }

    template<class E>
    typename boost::enable_if<expression::dimension_equal_to_c<E, 4> >::type
    set_color(expression::vector_expression<E> const& v){
        rgba = v;
    }

    value_type*       to_pointer()       {return rgba.begin();}
    value_type const* to_pointer() const {return rgba.begin();}

    integer_color& operator =(integer_color const& value){
        set_color(value);
        return *this;
    }

    template<class E>
    integer_color& operator =(expression::vector_expression<E> const& v){
        set_color(v);
        return *this;
    }

    vector_type rgba;
};

struct color32{
    typedef unsigned char value_type;
    typedef vector4<value_type>   vector_type;
    typedef boost::mpl::size_t<4> Size;

    color32():rgba(0, 0, 0, 0){}
    color32(color32 const& color):rgba(color.rgba){}
    color32(value_type r, value_type g, value_type b, value_type a = 255):rgba(r, g, b, a){}
    color32(unsigned int value):rgba((value >> 24) & 0xFF, (value >> 16) & 0xFF, (value >> 8) & 0xFF, value & 0xFF){}
    template<class E>
    color32(expression::vector_expression<E> const& v):rgba(v){}

    void set_color(value_type r, value_type g, value_type b, value_type a = 255){
        rgba(0) = r; rgba(1) = g; rgba(2) = b; a = a;
    }

    void set_color(unsigned int value){
        set_color((value >> 24) & 0xFF, (value >> 16) & 0xFF, (value >> 8) & 0xFF, value & 0xFF);
    }

    void set_color(color32 const& value){
        set_color(value.rgba);
     }

    template<class E>
    typename boost::enable_if<expression::dimension_equal_to_c<E, 4> >::type
    set_color(expression::vector_expression<E> const& v){
        rgba = v;
    }

    color32& operator =(color32 const& value){
        set_color(value);
        return *this;
    }

    color32& operator =(unsigned int value){
        set_color(value);
        return *this;
    }

    template<class E>
    color32& operator =(expression::vector_expression<E> const& v){
        set_color(v);
        return *this;
    }

    operator unsigned int() const {return (rgba(0) << 24) | (rgba(1) << 16) | (rgba(2) << 8) | rgba(3);}
    value_type*       to_pointer()       {return rgba.begin();}
    value_type const* to_pointer() const {return rgba.begin();}

    vector_type rgba;
};

namespace invisible{
template<typename T>
struct color_deduct{
    typedef typename boost::lazy_enable_if<
        boost::is_arithmetic<T>,
        boost::mpl::eval_if<
            boost::is_floating_point<T>,
            boost::mpl::identity<float_color<T> >,
            boost::mpl::if_<boost::mpl::equal_to<boost::mpl::sizeof_<T>, boost::mpl::size_t<1> >,
                     color32, integer_color<T> > > >::type type;
};
}

template<class T>
struct color : public invisible::color_deduct<T>::type{
    typedef typename invisible::color_deduct<T>::type   parent_type;
    typedef typename parent_type::value_type value_type;
    typedef boost::mpl::size_t<4> Size;

    color():parent_type(){}
    color(parent_type const& color):parent_type(color){}
    color(value_type r, value_type g, value_type b, value_type a = value_type(1)):parent_type(r, g, b, a){}
    color(unsigned int value, typename boost::enable_if<
          boost::mpl::or_<boost::is_floating_point<T>, boost::mpl::equal_to<boost::mpl::sizeof_<T>, boost::mpl::size_t<1> > >
          >::type* =0):parent_type(value){}
    template<class E>
    color(expression::vector_expression<E> const& v):parent_type(v){}


    color& operator =(parent_type const& value){
        return parent_type::operator =(value);
    }

    typename boost::enable_if<
        boost::mpl::or_<boost::is_floating_point<T>, boost::mpl::equal_to<boost::mpl::sizeof_<T>, boost::mpl::size_t<1> > >,
        color&>::type
    operator =(unsigned int value){
        return parent_type::operator =(value);
    }

    template<class E>
    color& operator =(expression::vector_expression<E> const& v){
        return parent_type::operator =(v);
    }

    void set_color(value_type r, value_type g, value_type b, value_type alpha = value_type(1)){
        parent_type::set_color(r, g, b, alpha);
    }

    void set_color(color const& value){
        parent_type::set_color(value);        
    }    

    template<class E>
    typename boost::enable_if<expression::dimension_equal_to_c<E, 4> >::type
    set_color(expression::vector_expression<E> const& v){
        parent_type::set_color(v);
    }

    typename boost::enable_if<
        boost::mpl::or_<
            boost::is_floating_point<T>,
            boost::mpl::equal_to<
                boost::mpl::sizeof_<T>, boost::mpl::size_t<1> > > >::type
    set_color(unsigned int value){
        parent_type::set_color(value);        
    }

    value_type*       to_pointer()       {return parent_type::to_pointer();}
    value_type const* to_pointer() const {return parent_type::to_pointer();}
};

} __NOGARA_END

#endif
