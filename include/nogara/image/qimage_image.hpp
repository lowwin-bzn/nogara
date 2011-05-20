#ifndef QIMAGE_IMAGE_HPP
#define QIMAGE_IMAGE_HPP

////////////////////////////////////////////////////////
//! @file  nogara/image/qimage_image.hpp
//! @brief Qtの画像クラスに依存した画像クラス
//! -- このクラスを使用するにはQtライブラリが必要です --
////////////////////////////////////////////////////////

#include <string>
#include <algorithm>
#include <QImage>
#include <nogara/gl_traits.hpp>
#include <nogara/image/image.hpp>

__NOGARA_BEGIN

/////////////////////////////////////////////
//! @brief Qtの画像クラスに依存した画像クラス
/////////////////////////////////////////////
class qimage_image : public image{
public:
    typedef image::shared_ptr image_ptr;
    typedef smart_ptr::shared_ptr<qimage_image> shared_ptr;
    qimage_image(int width, int height, int data_size):
        image(width, height, data_size, GL_RGBA, GL_BGRA){}

    struct send_data{
        send_data(QImage const& i):img(i){}
        template<typename T>
        void operator()(std::vector<T>& data){
            std::copy(img.bits(), img.bits() + img.byteCount(), data.begin());
        }
        QImage const& img;
    };

    /////////////////////////////////////////////
    //! @brief 画像を読み込む
    //!        対応フォーマットはQtのQImageを参照
    /////////////////////////////////////////////
    static shared_ptr load(char const* filename){
        QImage img = QImage(filename);
        shared_ptr ptr(new qimage_image(img.width(), img.height(), img.byteCount()));
        ptr->setData(send_data(img));
        return ptr;
    }
    static shared_ptr load(std::string const& filename){
        return load(filename.c_str());
    }
};

__NOGARA_END

#endif
