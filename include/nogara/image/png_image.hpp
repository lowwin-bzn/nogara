#ifndef NOGARA_PNG_IMAGE_HPP
#define NOGARA_PNG_IMAGE_HPP

////////////////////////////////////////////////////////////
//! @file  nogara/image/png_image.hpp
//! @brief png画像クラス
//!  -- このクラスを使用するにはlibpng, zlibが必要です --
////////////////////////////////////////////////////////////

#include <cstdio>
#include <string>
#include <nogara/image/image.hpp>
#include <nogara/gl_traits.hpp>
#include <nogara/file_cover.hpp>

#include <png.h>

__NOGARA_BEGIN

class png_image : public image{
public:
    typedef smart_ptr::shared_ptr<png_image> shared_ptr;

    static int pixel_format_from_png_color_type(int color_t){
        switch(color_t){
        case PNG_COLOR_TYPE_RGB_ALPHA:
            return GL_RGBA;
        case PNG_COLOR_TYPE_RGB:
            return GL_RGB;
        case PNG_COLOR_TYPE_GRAY:
            return GL_LUMINANCE;
        case PNG_COLOR_TYPE_GRAY_ALPHA:
            return GL_LUMINANCE_ALPHA;
        }
        return GL_RGBA;
    }

    png_image(int width, int height, int depth, int size,
              int color, int interlace, int compression, int filter):
        image(width, height, size, pixel_format_from_png_color_type(color),
              pixel_format_from_png_color_type(color)),
        depth_(depth), color_type_(color), interlace_type_(interlace),
        compression_type_(compression), filter_type_(filter){}

    static png_image* load(char const* filename){
        file_ptr fp(make_file_ptr(filename, "rb"));
        if(!fp){return NULL;}

        png_structp png_s = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        png_infop   info  = png_create_info_struct(png_s);
        png_init_io(png_s, fp.get());
        png_read_info(png_s, info);
        png_uint_32 width, height;
        int depth, color, interlace, compression, filter;

        png_get_IHDR(png_s, info,
                     &width, &height, &depth, &color,
                     &interlace, &compression, &filter);

        int row_bytes = png_get_rowbytes(png_s, info);
        png_image* image = new png_image(width, height, depth, row_bytes * height,
                                         color, interlace, compression, filter);

        std::vector<byte_t*> recv;
        recv.reserve(height);
        for(png_uint_32 i = 0; i < height; ++i){
            recv.push_back(&image->data()[i * row_bytes]);
        }

        png_read_image(png_s, &recv[0]);
        png_read_end(png_s, info);
        png_destroy_read_struct(&png_s, &info, NULL);

        return image;
    }

    static png_image* load(std::string const& filename){return load(filename.c_str());}

    int depth()            const {return depth_;}
    int color_type()       const {return color_type_;}
    int interlace_type()   const {return interlace_type_;}
    int compression_type() const {return compression_type_;}
    int filter_type()      const {return filter_type_;}

private:
    int depth_;
    int color_type_;
    int interlace_type_;
    int compression_type_;
    int filter_type_;
};

inline png_image::shared_ptr make_png_image(char const* filename){
    return png_image::shared_ptr(png_image::load(filename));
}

inline png_image::shared_ptr make_png_image(std::string const& filename){
    return png_image::shared_ptr(png_image::load(filename));
}

__NOGARA_END

#endif
