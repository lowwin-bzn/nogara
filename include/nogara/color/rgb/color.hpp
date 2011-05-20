#ifndef NOGARA_RGB_COLOR_HPP
#define NOGARA_RGB_COLOR_HPP

//////////////////////////////////
//! @file  nogara/color/rgb/color.hpp
//! @brief rgbカラーライブラリ
//////////////////////////////////

#include <boost/type_traits.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/identity.hpp>

__NOGARA_BEGIN
namespace rgb{

template<typename T>
struct float_color{
    typedef T value_type;
    typedef boost::mpl::size_t<3> Size;

    float_color():r(), g(), b(){}
    float_color(float_color const& color):r(color.r), g(color.g), b(color.b){}
    float_color(value_type ar, value_type ag, value_type ab):r(ar), g(ag), b(ab){}
    explicit float_color(unsigned int value):
        r(value_type((value >> 16) & 0xFF) / 255),
        g(value_type((value >>  8) & 0xFF) / 255),
        b(value_type(value & 0xFF) / 255){}


    void set_color(value_type ar, value_type ag, value_type ab){
        r = ar; g = ag; b = ab;
    }

    void set_color(unsigned int value){
        set_color(value_type((value >> 16) & 0xFF) / 255,
                  value_type((value >>  8) & 0xFF) / 255,
                  value_type(value & 0xFF)         / 255);
    }

    void set_color(float_color const& value){
        set_color(value.r, value.g, value.b);
     }

    float_color& operator =(float_color const& value){
        set_color(value);
        return *this;
    }

    float_color& operator =(unsigned int value){
        set_color(value);
        return *this;
    }

    value_type* to_pointer(){return &r;}
    value_type const* to_pointer() const {return &r;}

    value_type r, g, b;
};

template<typename T>
struct integer_color{
    typedef T value_type;
    typedef boost::mpl::size_t<3> Size;

    integer_color():r(), g(), b(){}
    integer_color(integer_color const& color):r(color.r), g(color.g), b(color.b){}
    integer_color(T ar, T ag, T ab):r(ar), g(ag), b(ab){}

    void set_color(value_type ar, value_type ag, value_type ab){
        r = ar; g = ag; b = ab;
    }

    void set_color(integer_color const& value){
        set_color(value.r, value.g, value.b);
     }

    integer_color& operator =(integer_color const& value){
        set_color(value);
        return *this;
    }

    value_type*       to_pointer()       {return &r;}
    value_type const* to_pointer() const {return &r;}
    value_type r, g, b;
};

struct color24{
    typedef unsigned char value_type;
    typedef boost::mpl::size_t<3> Size;

    color24():r(), g(), b(){}
    color24(color24 const& color):r(color.r), g(color.g), b(color.b){}
    color24(value_type ar, value_type ag, value_type ab):r(ar), g(ag), b(ab){}
    color24(unsigned int value):r((value >> 16) & 0xFF), g((value >> 8) & 0xFF), b(value & 0xFF){}

    void set_color(value_type ar, value_type ag, value_type ab){
        r = ar; g = ag; b = ab;
    }

    void set_color(unsigned int value){
        set_color((value >> 16) & 0xFF, (value >>  8) & 0xFF, value & 0xFF);
    }

    void set_color(color24 const& value){
        set_color(value.r, value.g, value.b);
     }

    color24& operator =(color24 const& value){
        set_color(value);
        return *this;
    }

    color24& operator =(unsigned int value){
        set_color(value);
        return *this;
    }

    operator unsigned int() const {return (r << 16) + (g << 8) + b;}
    value_type*       to_pointer()       {return &r;}
    value_type const* to_pointer() const {return &r;}

    value_type r, g, b;
};

namespace invisible{
    template<typename T>
    struct color_deduct{
        typedef typename boost::lazy_enable_if<
            boost::is_arithmetic<T>,
            boost::mpl::eval_if<
                boost::is_floating_point<T>,
                boost::mpl::identity<float_color<T> >,
                boost::mpl::if_<
                    boost::mpl::equal_to<boost::mpl::sizeof_<T>, boost::mpl::size_t<1> >,
                         color24, integer_color<T> > > >::type type;
    };
}

template<class T>
struct color : public invisible::color_deduct<T>::type{
    typedef typename invisible::color_deduct<T>::type   parent_type;
    typedef typename parent_type::value_type value_type;

    color():parent_type(){}
    color(value_type r, value_type g, value_type b):parent_type(r, g, b){}
    color(unsigned int value, typename boost::enable_if<
          boost::mpl::or_<boost::is_floating_point<T>,
          boost::mpl::equal_to<boost::mpl::sizeof_<T>, boost::mpl::size_t<1> > >
          >::type* =0):parent_type(value){}
    color(parent_type const& c):parent_type(c){}

    color& operator =(parent_type const& value){
        return parent_type::operator =(value);
    }

    typename boost::enable_if<
        boost::mpl::or_<
            boost::is_floating_point<T>,
            boost::mpl::equal_to<
                boost::mpl::sizeof_<T>, boost::mpl::size_t<1> > >, color&>::type
    operator =(unsigned int value){
        return parent_type::operator =(value);
    }

    void set_color(value_type r, value_type g, value_type b){
        parent_type::set_color(r, g, b);
    }

    void set_color(parent_type const& value){
        parent_type::set_color(value);        
     }    
    
    typename boost::enable_if<
        boost::mpl::or_<
            boost::is_floating_point<T>,
            boost::mpl::equal_to<boost::mpl::sizeof_<T>,
                                 boost::mpl::size_t<1> > > >::type
    set_color(unsigned int value){
        parent_type::set_color(value);        
    }

    value_type*       to_pointer()       {return parent_type::to_pointer();}
    value_type const* to_pointer() const {return parent_type::to_pointer();}
};
}

__NOGARA_END
#endif
