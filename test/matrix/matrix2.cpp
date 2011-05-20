#include <nogara/vector.hpp>
#include <nogara/matrix.hpp>
#include <nogara/expression/io.hpp>
#include <nogara/utility.hpp>
#include <iostream>

template<class E>
nogara::matrixf mul_inverse(nogara::expression::matrix_expression<E> const& m){
    return m * nogara::inverse(m);
}

template<class E>
bool identity_check(nogara::expression::matrix_expression<E> const& m){
    return m == nogara::matrixf::identity;
}

int main(){
    nogara::matrixf viewport = nogara::viewport_matrix(800, 600);
    nogara::matrixf perspective = nogara::perspective_matrix<float>(nogara::to_radian(90), 800, 600, 1, 100);
    nogara::matrixf look_at = nogara::look_at(nogara::vector3f(0, 0, 20), nogara::vector3f::zero, nogara::vector3f::unit_y);

    std::cout << viewport << std::endl;
    std::cout << look_at << std::endl;
    std::cout << perspective << std::endl;

    std::cout << viewport * perspective * look_at << std::endl;


    std::cout << viewport * perspective * look_at * nogara::vector3f(0, 0, 0)<< std::endl;
    std::cout << nogara::vector4f(533.333333, 300, 0, 1) * nogara::inverse(look_at) * nogara::inverse(perspective) * nogara::inverse(viewport) << std::endl;
}
