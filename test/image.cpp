#include <iostream>
#include <nogara/image/qimage_image.hpp>

int main(){
    nogara::qimage_image::shared_ptr ptr = nogara::qimage_image::load("/Users/lowwin/Pictures/img/sporty.png");
    std::cout << std::endl << std::endl;
    nogara::qimage_image::shared_ptr ptr2 = nogara::qimage_image::load("/Users/lowwin/QtProjects/Invader/Invader.app/Contents/Resources/image.png");
}
