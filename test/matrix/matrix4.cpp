#include <nogara/matrix.hpp>
#include <nogara/vector.hpp>
#include <nogara/expression/sse/traits.hpp>
#include <nogara/expression/io.hpp>
#include <ctime>

nogara::matrixf mul(nogara::matrixf const& x, nogara::matrixf const& y){
    using nogara::sse::load;

    __m128 y1 = load(y.pointer());
    __m128 y2 = load(&y.pointer()[4]);
    __m128 y3 = load(&y.pointer()[8]);
    __m128 y4 = load(&y.pointer()[12]);
    nogara::sse::to_sse_type<float>::align_type value[4];
    for(int i = 0; i < 4; ++ i){
        __m128 x1 = load(x(0, i), x(1, i), x(2, i), x(3, i));
        __m128 mul1 = _mm_mul_ps(x1, y1);
        __m128 mul2 = _mm_mul_ps(x1, y2);
        __m128 inter1 = _mm_add_ps(_mm_unpackhi_ps(mul1, mul2), _mm_unpacklo_ps(mul1, mul2));
        mul1 = _mm_mul_ps(x1, y3);
        mul2 = _mm_mul_ps(x1, y4);
        __m128 inter2 = _mm_add_ps(_mm_unpackhi_ps(mul1, mul2), _mm_unpacklo_ps(mul1, mul2));
        __m128 result = _mm_add_ps(_mm_unpackhi_ps(inter1, inter2), _mm_unpacklo_ps(inter1, inter2));
        result = _mm_shuffle_ps(result, result, 0xD8);
        _mm_store_ps(&value[i][0], result);
    }

    return nogara::matrixf(value[0][0], value[0][1], value[0][2], value[0][3],
                           value[1][0], value[1][1], value[1][2], value[1][3],
                           value[2][0], value[2][1], value[2][2], value[2][3],
                           value[3][0], value[3][1], value[3][2], value[3][3]);
}

nogara::matrixf add(nogara::matrixf const& x, nogara::matrixf const& y){
    using nogara::sse::load;
    NG_ALIGN16 float value[16];
    for(int i = 0; i < 4; ++i){
        _mm_store_ps(&value[4 * i], _mm_add_ps(load(&x.pointer()[4 * i]), load(&y.pointer()[4 * i])));
    }
    return nogara::matrixf(value[0], value[4], value[8],  value[12],
                           value[1], value[5], value[9],  value[13],
                           value[2], value[6], value[10], value[14],
                           value[3], value[7], value[11], value[15]);
}

int main(){
    nogara::matrixf x(1,   2,  3,  4,
                      5,   6,  7,  8,
                      9,  10, 11, 12,
                      13, 14, 15, 16);
    nogara::matrixf y(1,   2,  3,  4,
                      5,   6,  7,  8,
                      9,  10, 11, 12,
                      13, 14, 15, 16);

    nogara::matrixf adder(0.5, 0.5, 0.5, 0.5,
                          0.5, 0.5, 0.5, 0.5,
                          0.5, 0.5, 0.5, 0.5,
                          0.5, 0.5, 0.5, 0.5);
    nogara::matrixf addee = nogara::matrixf(0, 0, 0, 0,
                                            0, 0, 0, 0,
                                            0, 0, 0, 0,
                                            0, 0, 0, 0);
    clock_t start, end;

    start = clock();
    for(int i = 0; i < 10000000; ++i){
        addee = add(addee, adder);
    }
    end = clock();
    std::cout << static_cast<double>(end - start) / CLOCKS_PER_SEC << "sec" << std::endl; 

    addee = nogara::matrixf(0, 0, 0, 0,
                            0, 0, 0, 0,
                            0, 0, 0, 0,
                            0, 0, 0, 0);

    start = clock();
    for(int i = 0; i < 10000000; ++i){
        addee = addee + adder;
    }
    end = clock();
    std::cout << static_cast<double>(end - start) / CLOCKS_PER_SEC << "sec" << std::endl; 

    nogara::matrixf result;
    start = clock();
    for(int i = 0; i < 10000000; ++i){
        result = mul(mul(x, y), result);
    }
    end = clock();
    std::cout << static_cast<double>(end - start) / CLOCKS_PER_SEC << "sec" << std::endl; 
    nogara::matrixf result2;
    start = clock();
    for(int i = 0; i < 10000000; ++i){
        result2 = x * y * result2;
    }
    end = clock();
    std::cout << static_cast<double>(end - start) / CLOCKS_PER_SEC << "sec" << std::endl; 

    std::cout << result << std::endl;
    std::cout << result2 << std::endl;
 
}
