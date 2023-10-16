#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../mat4.h"

TEST_CASE("Basic Functions") {
    mat4 mat_two_zeros = mat4();
    mat4  mat_two_numbers = mat4(2,3,3,9,4,4,13,21,3,2,1,90,-1,-9,45,100);
    mat4 mat_one_n_one = mat4(2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2);
    mat4 result = mat4();
    double t = 10;

    //sum between 2 matrix
    CHECK((mat_two_zeros + mat_two_numbers).e[0][0] == mat_two_numbers.e[0][0]);
    CHECK((mat_two_zeros + mat_two_numbers).e[0][1] == mat_two_numbers.e[0][1]);
    CHECK((mat_two_zeros + mat_two_numbers).e[0][2] == mat_two_numbers.e[0][2]);
    CHECK((mat_two_zeros + mat_two_numbers).e[0][3] == mat_two_numbers.e[0][3]);
    CHECK((mat_two_zeros + mat_two_numbers).e[1][0] == mat_two_numbers.e[1][0]);
    CHECK((mat_two_zeros + mat_two_numbers).e[1][1] == mat_two_numbers.e[1][1]);
    CHECK((mat_two_zeros + mat_two_numbers).e[1][2] == mat_two_numbers.e[1][2]);
    CHECK((mat_two_zeros + mat_two_numbers).e[1][3] == mat_two_numbers.e[1][3]);
    CHECK((mat_two_zeros + mat_two_numbers).e[2][0] == mat_two_numbers.e[2][0]);
    CHECK((mat_two_zeros + mat_two_numbers).e[2][1] == mat_two_numbers.e[2][1]);
    CHECK((mat_two_zeros + mat_two_numbers).e[2][2] == mat_two_numbers.e[2][2]);
    CHECK((mat_two_zeros + mat_two_numbers).e[2][3] == mat_two_numbers.e[2][3]);
    CHECK((mat_two_zeros + mat_two_numbers).e[3][0] == mat_two_numbers.e[3][0]);
    CHECK((mat_two_zeros + mat_two_numbers).e[3][1] == mat_two_numbers.e[3][1]);
    CHECK((mat_two_zeros + mat_two_numbers).e[3][2] == mat_two_numbers.e[3][2]);
    CHECK((mat_two_zeros + mat_two_numbers).e[3][3] == mat_two_numbers.e[3][3]);

    //Minus between 2 matrix
    CHECK((mat_two_zeros - mat_two_numbers).e[0][0] == -mat_two_numbers.e[0][0]);
    CHECK((mat_two_zeros - mat_two_numbers).e[0][1] == -mat_two_numbers.e[0][1]);
    CHECK((mat_two_zeros - mat_two_numbers).e[0][2] == -mat_two_numbers.e[0][2]);
    CHECK((mat_two_zeros - mat_two_numbers).e[0][3] == -mat_two_numbers.e[0][3]);
    CHECK((mat_two_zeros - mat_two_numbers).e[1][0] == -mat_two_numbers.e[1][0]);
    CHECK((mat_two_zeros - mat_two_numbers).e[1][1] == -mat_two_numbers.e[1][1]);
    CHECK((mat_two_zeros - mat_two_numbers).e[1][2] == -mat_two_numbers.e[1][2]);
    CHECK((mat_two_zeros - mat_two_numbers).e[1][3] == -mat_two_numbers.e[1][3]);
    CHECK((mat_two_zeros - mat_two_numbers).e[2][0] == -mat_two_numbers.e[2][0]);
    CHECK((mat_two_zeros - mat_two_numbers).e[2][1] == -mat_two_numbers.e[2][1]);
    CHECK((mat_two_zeros - mat_two_numbers).e[2][2] == -mat_two_numbers.e[2][2]);
    CHECK((mat_two_zeros - mat_two_numbers).e[2][3] == -mat_two_numbers.e[2][3]);
    CHECK((mat_two_zeros - mat_two_numbers).e[3][0] == -mat_two_numbers.e[3][0]);
    CHECK((mat_two_zeros - mat_two_numbers).e[3][1] == -mat_two_numbers.e[3][1]);
    CHECK((mat_two_zeros - mat_two_numbers).e[3][2] == -mat_two_numbers.e[3][2]);
    CHECK((mat_two_zeros - mat_two_numbers).e[3][3] == -mat_two_numbers.e[3][3]);

    //Multi 
    CHECK((mat_one_n_one * mat_two_numbers).e[0][0] == 4);
    CHECK((mat_one_n_one * mat_two_numbers).e[0][1] == 6);
    CHECK((mat_one_n_one * mat_two_numbers).e[0][2] == 6);
    CHECK((mat_one_n_one * mat_two_numbers).e[0][3] == 18);
    CHECK((mat_one_n_one * mat_two_numbers).e[1][0] == 8);
    CHECK((mat_one_n_one * mat_two_numbers).e[1][1] == 8);
    CHECK((mat_one_n_one * mat_two_numbers).e[1][2] == 26);
    CHECK((mat_one_n_one * mat_two_numbers).e[1][3] == 42);
    CHECK((mat_one_n_one * mat_two_numbers).e[2][0] == 6);
    CHECK((mat_one_n_one * mat_two_numbers).e[2][1] == 4);
    CHECK((mat_one_n_one * mat_two_numbers).e[2][2] == 2);
    CHECK((mat_one_n_one * mat_two_numbers).e[2][3] == 180);
    CHECK((mat_one_n_one * mat_two_numbers).e[3][0] == -2);
    CHECK((mat_one_n_one * mat_two_numbers).e[3][1] == -18);
    CHECK((mat_one_n_one * mat_two_numbers).e[3][2] == 90);
    CHECK((mat_one_n_one * mat_two_numbers).e[3][3] == 200);

    //Multi num and vector
    result = mat_two_numbers * t;
    CHECK(result.e[0][0] ==  20);
    CHECK(result.e[0][1] ==  30);
    CHECK(result.e[0][2] ==  30);
    CHECK(result.e[0][3] ==  90);
    CHECK(result.e[1][0] ==  40);
    CHECK(result.e[1][1] ==  40);
    CHECK(result.e[1][2] ==  130);
    CHECK(result.e[1][3] ==  210);
    CHECK(result.e[2][0] ==  30);
    CHECK(result.e[2][1] ==  20);
    CHECK(result.e[2][2] ==  10);
    CHECK(result.e[2][3] ==  900);
    CHECK(result.e[3][0] ==  -10);
    CHECK(result.e[3][1] ==  -90);
    CHECK(result.e[3][2] ==  450);
    CHECK(result.e[3][3] ==  1000);
    
    //Div
    result /= 1000;
    CHECK(result.e[0][0] ==  0.02);
    CHECK(result.e[0][1] ==  0.03);
    CHECK(result.e[0][2] ==  0.03);
    CHECK(result.e[0][3] ==  0.09);
    CHECK(result.e[1][0] ==  0.04);
    CHECK(result.e[1][1] ==  0.04);
    CHECK(result.e[1][2] ==  0.13);
    CHECK(result.e[1][3] ==  0.21);
    CHECK(result.e[2][0] ==  0.03);
    CHECK(result.e[2][1] ==  0.02);
    CHECK(result.e[2][2] ==  0.01);
    CHECK(result.e[2][3] ==  0.9);
    CHECK(result.e[3][0] ==  -0.01);
    CHECK(result.e[3][1] ==  -0.09);
    CHECK(result.e[3][2] ==  0.45);
    CHECK(result.e[3][3] ==  1);

}

TEST_CASE("Helper Functions") {
    mat4 mat_two_numbers = mat4(2,3,4,5,6,7,8,9,10,30,20,100,40,450,12,-1);
    mat4 mat_two_numbers2 = mat4(3,17,1,1,4,6,12,40,2,3,7,450,1000,21,23,27);
    mat4 result = dot(mat_two_numbers,mat_two_numbers2);

    CHECK(result.e[0][0] ==  5026);
    CHECK(result.e[0][1] ==  169);
    CHECK(result.e[0][2] ==  181);
    CHECK(result.e[0][3] ==  2057);
    CHECK(result.e[1][0] ==  9062);
    CHECK(result.e[1][1] ==  357);
    CHECK(result.e[1][2] ==  353);
    CHECK(result.e[1][3] ==  4129);
    CHECK(result.e[2][0] ==  100190);
    CHECK(result.e[2][1] ==  2510);
    CHECK(result.e[2][2] ==  2810);
    CHECK(result.e[2][3] ==  12910);
    CHECK(result.e[3][0] ==  944);
    CHECK(result.e[3][1] ==  3395);
    CHECK(result.e[3][2] ==  5501);
    CHECK(result.e[3][3] ==  23413);

}
