#include <nogara/vector.hpp>
#include <nogara/matrix.hpp>
#include <nogara/expression/io.hpp>
#include <nogara/utility.hpp>
#include <iostream>

typedef nogara::vector3<float> vector3;
typedef nogara::rotate_matrix<float> rotate_matrix;

int main(){
    std::cout << nogara::cross(vector3::unit_x, vector3::unit_y) << std::endl;

    vector3 v(2, -2, 2);
    vector3 v2 = nogara::normalize(v);
    float rad = std::acos(dot(vector3::unit_z, v2));
    std::cout << nogara::to_degree(rad) << std::endl;
    std::cout << v2 << std::endl;

    rotate_matrix rmat = nogara::quaternion_rotate_axis(v2, rad);

    std::cout << rmat << std::endl;
    std::cout << nogara::cross(vector3::unit_z, v2) << std::endl;
    std::cout << nogara::cross(vector3::unit_z, v2) * rmat << std::endl;
    vector3 rot_vector = nogara::normalize(rmat * nogara::cross(vector3::unit_z, v2));
    std::cout << rot_vector << std::endl;

    std::cout << nogara::lerp(vector3::zero, v, 0.5f) << std::endl;
    std::cout << nogara::lerp(vector3::zero, v, 0.5f) + rot_vector << std::endl;
}
