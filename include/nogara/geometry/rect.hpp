#ifndef NOGARA_RECT_HPP
#define NOGARA_RECT_HPP

//////////////////////////////////
//! @file nogara/geometry/rect.hpp
//! @brief 矩形クラス
//////////////////////////////////

#include <nogara/vector.hpp>

__NOGARA_BEGIN

/////////////////////
//! @brief 矩形クラス
/////////////////////
template<typename T>
class rect{
    typedef rect<T>    self_type;
public:
    typedef vector2<T> vector2_type;
    typedef T          value_type;

    //! @brief コンストラクタ
    rect(){}
    //! @brief コンストラクタ
    //! @param ax 始点X座標
    //! @param ay 始点Y座標
    //! @param w 矩形の横幅
    //! @param h 矩形の縦幅
    rect(value_type ax, value_type ay, value_type w, value_type h):
        x(ax), y(ay), width(w), height(h){}

    //! @brief コンストラクタ
    //! @param origin 始点座標
    //! @param size   矩形の大きさ
    rect(vector2_type const& origin, vector2_type const& size):
        x(origin.x), y(origin.y), width(size.x), height(size.y){}

    //! @brief コピーコンストラクタ 
   rect(self_type const& rhs):x(rhs.x), y(rhs.y), width(rhs.width), height(rhs.height){}

    //! @brief コピーコンストラクタ
    template<class U>
    rect(rect<U> const& rhs):x(rhs.x), y(rhs.y), width(rhs.width), height(rhs.height){}

    //! @brief 代入演算
    self_type &operator =(self_type const& rhs){
        if(&rhs == this){
            return *this;
        }

        x = rhs.x; y = rhs.y;
        width = rhs.width; height = rhs.height;
        return *this;
    }

    //! @brief 代入演算
    template<class U>
    self_type &operator =(rect<U> const& rhs){
        x = rhs.x; y = rhs.y;
        width = rhs.width; height = rhs.height;
        return *this;
    }

    //! @brief 矩形の始点座標
    vector2_type origin() const {return vector2_type(x, y);}
    //! @brief 矩形の大きさ
    vector2_type size()   const {return vector2_type(width, height);}

    //! @brief 他の矩形が矩形に含まれるかを返す
    bool contains(self_type const& rect) const {
        return contains(rect.x, rect.y, rect.width, rect.height);
    }

    //! @brief 指定した座標が矩形に含まれるかを返す
    bool contains(vector2_type const& point) const {
        return contains(point.x, point,y);
    }

    //! @brief 指定した座標が矩形に含まれるかを返す
    bool contains(value_type x, value_type y) const {
        return contains(x, y, 0, 0);
    }

    //! @brief 他の矩形が含まれるかを返す
    bool contains(value_type x, value_type y, value_type width, value_type height) const {
        return this->x <= x && this->y <= y &&
            this->x + this->width >= width &&
            this->y + this->height >= height;        
    }
    
    //! @brief 他の矩形と共通部分があるかを返す
    bool intersects(value_type x, value_type y, value_type width, value_type height) const {
        return this->x < width  && x < this->width &&
               this->y < height && y < this->height;
    }
    
    //! @brief 他の矩形と共通部分があるかを返す
    bool intersects(self_type const& rect) const {
        return intersects(rect.x, rect.y, rect.width, rect.height);
    }

    //! @brief 他の矩形と共通部分を返す
    self_type intersection(value_type x, value_type y, value_type width, value_type height) const {
        if(!intersects(x, y, width, height)){
            return zero;
        }

        value_type const dx = (this->x > x) ? this->x : x;
        value_type const dy = (this->y > y) ? this->y : y;
        value_type const dw = (dx == x) ? (x + width)  - this->x : (this->x + this->width)  - x;
        value_type const dh = (dy == y) ? (y + height) - this->y : (this->x + this->height) - y;
        return self_type(dx, dy, dw, dh);
    }

    //! @brief 他の矩形と共通部分を返す
    self_type intersection(self_type const& rect) const {
        return intersection(rect.x, rect.y, rect.width, rect.height);
    }

public:
    static self_type const zero;

    value_type x, y, width, height;
};

template<typename T>
rect<T> const rect<T>::zero(T(0), T(0), T(0), T(0));

__NOGARA_END

#endif
