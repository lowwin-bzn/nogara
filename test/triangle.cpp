#include <iostream>
#include <nogara/geometry/triangle.hpp>
#include <nogara/utility.hpp>
#include <nogara/collisions.hpp>
#include <nogara/expression/io.hpp>
#include <nogara/expression/vector/scalar_vector.hpp>

template<class T>
nogara::triangle<nogara::vector3<typename nogara::deduct1<T>::real_type> >
equilateral_triangle(T edge){
    typedef typename nogara::deduct1<T>::real_type R;
    typedef nogara::vector3<R> vector;
    R const edge_half = edge * 0.5f;
    return nogara::triangle<vector>(vector(0, edge * std::sqrt(3) * 0.5f - edge_half, 0),
                                    vector(-edge_half, -edge_half, 0),
                                    vector(edge_half, -edge_half, 0));
}

int main(){
    nogara::triangle<nogara::vector3f> triangle = equilateral_triangle(3);
    nogara::vector3f p1(0, 0, 0);
    nogara::vector3f p2(0, 0, 1);
    nogara::vector3f p3(0, 2, 0);
    nogara::vector3f p4(0, 99, 0);
    nogara::vector3f p5(0.5, 0.23, 0);
    
    std::cout << std::boolalpha << nogara::collide_triangle(triangle, p1) << std::endl;
    std::cout << std::boolalpha << nogara::collide_triangle(triangle, p2) << std::endl;
    std::cout << std::boolalpha << nogara::collide_triangle(triangle, p3) << std::endl;
    std::cout << std::boolalpha << nogara::collide_triangle(triangle, p4) << std::endl;
    std::cout << std::boolalpha << nogara::collide_triangle(triangle, p5) << std::endl;

    std::cout << triangle.S() << std::endl;
    std::cout << triangle.centroid() << std::endl;

    std::cout << triangle.incircle_center() << std::endl;
    std::cout << triangle.incircle_radius() << std::endl;
    std::cout << triangle.circum_center() << std::endl;
    std::cout << triangle.circum_radius() << std::endl;
}
