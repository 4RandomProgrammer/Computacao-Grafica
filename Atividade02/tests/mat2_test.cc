#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../mat2.h"

TEST_CASE("Basic Functions") {
    mat2 mat_two_zeros = mat2();
    mat2  mat_two_numbers = mat2(2,3,3,4);
    mat2 mat_one_n_one = mat2(1,1,1,1);
    mat2 result = mat2();
    double t = 4;

    //sum between 2 matrix
    CHECK((mat_two_zeros + mat_two_numbers).e[0][0] == mat_two_numbers.e[0][0]);
    CHECK((mat_two_zeros + mat_two_numbers).e[0][1] == mat_two_numbers.e[0][1]);
    CHECK((mat_two_zeros + mat_two_numbers).e[1][0] == mat_two_numbers.e[1][0]);
    CHECK((mat_two_zeros + mat_two_numbers).e[1][1] == mat_two_numbers.e[1][1]);

    //Minus between 2 matrix
    CHECK((mat_two_zeros - mat_two_numbers).e[0][0] == -mat_two_numbers.e[0][0]);
    CHECK((mat_two_zeros - mat_two_numbers).e[0][1] == -mat_two_numbers.e[0][1]);
    CHECK((mat_two_zeros - mat_two_numbers).e[1][0] == -mat_two_numbers.e[1][0]);
    CHECK((mat_two_zeros - mat_two_numbers).e[1][1] == -mat_two_numbers.e[1][1]);

    //Multi 
    CHECK((mat_one_n_one * mat_two_numbers).e[0][0] == 2);
    CHECK((mat_one_n_one * mat_two_numbers).e[0][1] == 3);
    CHECK((mat_one_n_one * mat_two_numbers).e[1][0] == 3);
    CHECK((mat_one_n_one * mat_two_numbers).e[1][1] == 4);
    //Multi num and vector
    result = mat_two_numbers * t;
    CHECK(result.e[0][0] ==  8);
    CHECK(result.e[0][1] ==  12);
    CHECK(result.e[1][0] ==  12);
    CHECK(result.e[1][1] ==  16);
    
    //Div
    result /= 2;
    CHECK(result.e[0][0] ==  4);
    CHECK(result.e[0][1] ==  6);
    CHECK(result.e[1][0] ==  6);
    CHECK(result.e[1][1] ==  8);

}

TEST_CASE("Helper Functions") {
    mat2 mat_two_numbers = mat2(2,3,4,5);
    mat2 mat_two_numbers2 = mat2(3,17,1,1);
    mat2 result = dot(mat_two_numbers,mat_two_numbers2);

    CHECK(result.e[0][0] == 9);
    CHECK(result.e[0][1] == 37);
    CHECK(result.e[1][0] == 17);
    CHECK(result.e[1][1] == 73);

}
