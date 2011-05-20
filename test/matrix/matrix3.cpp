#include <iostream>
#include <nogara/expression/io.hpp>
#include <nogara/camera.hpp>
#include <nogara/collisions.hpp>
#include <nogara/geometry/ray.hpp>

int main(){
    nogara::ray<nogara::vector3f>      r1(nogara::vector3f(0, 5, -2), nogara::vector3f::unit_z);
    nogara::ray<nogara::vector3f>      r2(nogara::vector3f(0, 5,  2), -nogara::vector3f::unit_z);
    nogara::ray<nogara::vector3f>      r3(nogara::vector3f(0, 25,  2), -nogara::vector3f::unit_z);
    nogara::triangle<nogara::vector3f> tri(nogara::vector3f(-10, -10, 0),
                                           nogara::vector3f( 10, -10, 0),
                                           nogara::vector3f(  0,  10, 0));
    std::cout << std::boolalpha << nogara::collide_triangle(tri, r1) << std::endl;
    std::cout << std::boolalpha << nogara::collide_triangle(tri, r2) << std::endl;
    std::cout << std::boolalpha << nogara::collide_triangle(tri, r3) << std::endl;
}
