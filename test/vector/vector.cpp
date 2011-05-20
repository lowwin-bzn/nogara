#include <iostream>
//#include <algorithm>
//#include <nogara/matrix.hpp>
#include <nogara/vector.hpp>
#include <nogara/expression/io.hpp>
#include <nogara/expression/vector/scalar_vector.hpp>
#include <nogara/quaternion.hpp>

#include <boost/ref.hpp>

typedef nogara::vector3<nogara::vector3f> vv;

struct add{
    template<class T, class U>
    typename nogara::deduct2<T, U>::value_type
    operator()(T const& t, U const& u) const {
        return t + u;
    }
};

float minus(float x, float y){
    return x - y;
}

template<class T>
struct vector1{
    explicit vector1(T const& v):value(v){}
    operator T() const {return value;}
    T value;
};

template<class X>
class is_convertible_to_arithmetic : public nogara::sfinae_check{
    static yes_type check(long long);
    static yes_type check(unsigned long long);
    static yes_type check(long);
    static yes_type check(unsigned long);
    static yes_type check(int);
    static yes_type check(unsigned int);
    static yes_type check(short);
    static yes_type check(unsigned short);
    static yes_type check(char);
    static yes_type check(unsigned char);
    static yes_type check(signed char);
    static yes_type check(float);
    static yes_type check(double);
    static yes_type check(long double);

    static no_type check(...);
    static X v;
public:
    static bool const value = (sizeof(check(v)) == sizeof(yes_type));
};


int main(){
    nogara::vector4f v1(2, 3, 4, 9);

    /*
    std::cout << is_convertible_to_arithmetic<vector1<float> >::value << std::endl;
    std::cout << is_convertible_to_arithmetic<vector1<int> >::value << std::endl;
    std::cout << is_convertible_to_arithmetic<double>::value << std::endl;
    std::cout << is_convertible_to_arithmetic<nogara::vector3f>::value << std::endl;
    */

    std::cout << nogara::swizzle<nogara::swizzle_xzzw>(nogara::reverse(v1)) << std::endl;

    /*
    std::cout << nogara::fold_right(v1, 3, minus) << std::endl;
    std::cout << nogara::reduce_right(v1, minus) << std::endl;
    std::cout << nogara::reduce(v1, add()) << std::endl;
    std::cout << nogara::sum(v1) << std::endl;
    std::cout << nogara::dot(v1, nogara::scalar_vector<float, 4>(2)) << std::endl;
    std::cout << nogara::pow(v1, 3) << std::endl;
    std::cout << nogara::max(v1) << std::endl;
    std::cout << nogara::lerp(v1, nogara::vector4f::zero, 0.5) << std::endl;
    std::cout << nogara::lerp(v1, nogara::vector4f::zero, 0.4) << std::endl;
    */
}
