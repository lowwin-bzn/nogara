#include <nogara/vector.hpp>
#include <nogara/expression/accessor.hpp>
#include <nogara/expression/io.hpp>

int main(){
    namespace accessor = nogara::expression::accessor;

    nogara::vector3f v1(1, 2, 3);
    std::cout << v1 << std::endl;
    std::cout << accessor::x(v1) << std::endl;
    std::cout << accessor::y(v1) << std::endl;
    std::cout << accessor::z(v1) << std::endl;
    //std::cout << accessor::w(v1) << std::endl; //error!!
    accessor::z(v1) = 4;
    std::cout << v1 << std::endl;

    nogara::vector4f const v2(2, 3, 4, 9);
    std::cout << accessor::x(v2) << std::endl;
    std::cout << accessor::w(v2) << std::endl;
    std::cout << accessor::y(v1 + nogara::minor<2>(v2)) << std::endl;
    //accessor::z(v2) = 6; //error!!
}
