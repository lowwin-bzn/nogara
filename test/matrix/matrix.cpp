#include <iostream>
#include <nogara/vector.hpp>
#include <nogara/matrix.hpp>
#include <nogara/quaternion.hpp>
#include <nogara/model/transformation.hpp>
#include <nogara/camera.hpp>
#include <nogara/expression/io.hpp>
#include <nogara/typedef.hpp>
#include <sys/time.h>

typedef nogara::vector2<float> vector2;

int main(){
    nogara::transformation<float> transform(nogara::vector3<float>(6, 6, 3),
                                            nogara::quaternion<float>(3.14, 1, 0, 0),
                                            nogara::vector3<float>(1.0f, 1.0f, 1.0f));

    nogara::vector3<float> v(0, 1, 0);

    nogara::camera c(nogara::vector3<float>(0, 20, 20),
                     nogara::vector3<float>(0, 0, 0),
                     nogara::vector3<float>(0, 1, 0));

    nogara::matrix33<float> r = rotate_matrix(nogara::normalize(nogara::quaternion<float>(M_PI * 0.5, 4, 1, 0)));
    nogara::vector2<float> _v(nogara::minor<0>(v));

    //nogara::matrix<float> modelview = c.get_matrix() * transform.to_matrix();
    nogara::matrix33<float> t = nogara::matrix33<float>::identity;
    timeval start, end;
    gettimeofday(&start, NULL);
    for(int i = 0; i < 10000000; ++i){
        t = r * inverse(r);
        t = t * r + t * inverse(r) + t + t;
        t = inverse(t);
    }
    gettimeofday(&end, NULL);
    std::cout << end.tv_sec - start.tv_sec + (end.tv_usec - start.tv_usec) / 10000000.0 << "sec" << std::endl; 
    std::cout << t << std::endl;

    //std::cout << r << std::endl;
    //std::cout << inverse(r) << std::endl;
    //std::cout << inverse(r) * r << std::endl;
    //std::cout << inverse(r) * r * r<< std::endl;
    //std::cout << transform.to_matrix() << std::endl;
    //std::cout << transform.to_matrix() << std::endl;
    std::cout << nogara::inverse(transform.to_matrix()) << std::endl;
    std::cout << transform.to_matrix() * nogara::inverse(transform.to_matrix()) << std::endl;
    //std::cout << std::boolalpha << (transform.to_matrix() * nogara::inverse(transform.to_matrix()) * transform.to_matrix() == transform.to_matrix()) << std::endl;
    //std::cout << std::boolalpha << (r * nogara::inverse(r) == nogara::rotate_matrix<float>::identity) << std::endl;
    //std::cout << v * modelview << std::endl;
}

/*
template<class T>
class matrix{
public:
    matrix(){}
    matrix(T m11, T m21, T m31, T m41,
           T m12, T m22, T m32, T m42,
           T m13, T m23, T m33, T m43,
           T m14, T m24, T m34, T m44)
    {
        (*this)(0, 0) = m11; (*this)(1, 0) = m21; (*this)(2, 0) = m31; (*this)(3, 0) = m41;
        (*this)(0, 1) = m12; (*this)(1, 1) = m22; (*this)(2, 1) = m32; (*this)(3, 1) = m42;
        (*this)(0, 2) = m13; (*this)(1, 2) = m23; (*this)(2, 2) = m33; (*this)(3, 2) = m43;
        (*this)(0, 3) = m14; (*this)(1, 3) = m24; (*this)(2, 3) = m34; (*this)(3, 3) = m44;
    }

    matrix(matrix const& m){
        (*this)(0, 0) = m(0, 0); (*this)(1, 0) = m(1, 0); (*this)(2, 0) = m(2, 0); (*this)(3, 0) = m(3, 0);
        (*this)(0, 1) = m(0, 1); (*this)(1, 1) = m(1, 1); (*this)(2, 1) = m(2, 1); (*this)(3, 1) = m(3, 1);
        (*this)(0, 2) = m(0, 2); (*this)(1, 2) = m(1, 2); (*this)(2, 2) = m(2, 2); (*this)(3, 2) = m(3, 2);
        (*this)(0, 3) = m(0, 3); (*this)(1, 3) = m(1, 3); (*this)(2, 3) = m(2, 3); (*this)(3, 3) = m(3, 3);
    }


    matrix& operator =(matrix const& m){
        for(int x = 0; x < 4; ++x){
            for(int y = 0; y < 4; ++y){
                (*this)(x, y) = m(x, y);
            }
        }
        return *this;
    }

    matrix operator *(matrix const& m){
        matrix result(0, 0, 0, 0,
                      0, 0, 0, 0,
                      0, 0, 0, 0,
                      0, 0, 0, 0);
        for(int x = 0; x < 4; ++x){
            for(int y = 0; y < 4; ++y){
                for(int i = 0; i < 4; ++i){
                    result(x, y) += (*this)(x, i) * m(i, y);
                }
            }
        }
        return result;
    }

    matrix operator +(matrix const& m){
        matrix result(0, 0, 0, 0,
                      0, 0, 0, 0,
                      0, 0, 0, 0,
                      0, 0, 0, 0);
        for(int x = 0; x < 4; ++x){
            for(int y = 0; y < 4; ++y){
                result(x, y) = (*this)(x, y) + m(x, y);
            }
        }
        return result;
    }

    T&       operator ()(unsigned x, unsigned y)      {return data()[x + 4 * y];}
    T const& operator ()(unsigned x, unsigned y) const{return data()[x + 4 * y];}
    nogara::array<T, 16>      & data()       {return data_;}
    nogara::array<T, 16> const& data() const {return data_;}

private:
    nogara::array<T, 16> data_;
};

template<class T>
std::ostream& operator <<(std::ostream& os, matrix<T> const& m){
    os << "[";
    for(unsigned y = 0; y < 4; ++y){
        for(unsigned x = 0; x < 4; ++x){
            if(x != 0 || y != 0){
                os << ", ";
            }
            if(y != 0 && x == 0){
                os << "\n ";
            }
            os << std::setw(8) << m(x, y);
        }
    }
    os << "]";
    return os;
}


int main(){
    timeval start1, end1;
    gettimeofday(&start1, NULL);
    {
        matrix<float> x( 1,  2,  3,  4,
                         5,  6,  7,  8,
                         9, 10, 11, 12,
                        13, 14, 15, 16);

        matrix<float> r = x * x * x + x * x * x;
        for(int i = 0; i < 1000000; ++i){
            matrix<float> s = r + x + r;
            r = s * s * r * r * r * s * r * s;
        }
        gettimeofday(&end1, NULL);
        std::cout << r << std::endl;
    }
    
    timeval start2, end2;
    gettimeofday(&start2, NULL);
    {
        nogara::matrix<float> x( 1,  2,  3,  4,
                                 5,  6,  7,  8,
                                 9, 10, 11, 12,
                                13, 14, 15, 16);
        nogara::matrix<float> r = nogara::matrix<float>(x * x * x) * nogara::matrix<float>(x * x * x);
        for(int i = 0; i < 1000000; ++i){
            nogara::matrix<float> s = r + x + r;
            r = nogara::matrix<float>(nogara::matrix<float>(s * s * r) * nogara::matrix<float>(r * r * s) * r) * s;
        }
        gettimeofday(&end2, NULL);
        std::cout << r << std::endl;
    }

    timeval start3, end3;
    gettimeofday(&start3, NULL);
    {
        nogara::rotate_matrix<float> x(1, 2, 3,
                                       4, 5, 6,
                                       7, 8, 9);

        nogara::rotate_matrix<float> r = x * x * x * x * x * x;
        for(int i = 0; i < 1000000; ++i){
            nogara::rotate_matrix<float> s = nogara::rotate_matrix<float>(r + x + r);
            r = nogara::rotate_matrix<float>(nogara::rotate_matrix<float>(s * s * r) * nogara::rotate_matrix<float>(r * r * s) * r) * s;
        }
        gettimeofday(&end3, NULL);
        std::cout << r << std::endl;
    }

    timeval start4, end4;
    gettimeofday(&start4, NULL);
    {
        using nogara::expression::matrix22;
        matrix22<float> x(1, 2, 3, 4);
        matrix22<float> r = x * x * x * x * x * x;
        for(int i = 0; i < 1000000; ++i){
            matrix22<float> s =  matrix22<float>(r + x + r);
            r = matrix22<float>(matrix22<float>(s * s * r) * matrix22<float>(r * r * s) * r) * s;
        }
        gettimeofday(&end4, NULL);
        std::cout << r << std::endl;
    }

    std::cout << end1.tv_sec - start1.tv_sec + (end1.tv_usec - start1.tv_usec) / 10000000.0 << "sec" << std::endl; 
    std::cout << end2.tv_sec - start2.tv_sec + (end2.tv_usec - start2.tv_usec) / 10000000.0 << "sec" << std::endl; 
    std::cout << end3.tv_sec - start3.tv_sec + (end3.tv_usec - start3.tv_usec) / 10000000.0 << "sec" << std::endl; 
    std::cout << end4.tv_sec - start4.tv_sec + (end4.tv_usec - start4.tv_usec) / 10000000.0 << "sec" << std::endl; 
}
*/
