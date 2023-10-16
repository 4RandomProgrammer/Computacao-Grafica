#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../mat3.h"

TEST_CASE("Basic Functions") {
    mat3 mat_two_zeros = mat3();
    mat3  mat_two_numbers = mat3(2,3,3,4,4,13,3,2,1);
    mat3 mat_one_n_one = mat3(2,2,2,2,2,2,2,2,2);
    mat3 result = mat3();
    double t = 5;

    //sum between 2 matrix
    CHECK((mat_two_zeros + mat_two_numbers).e[0][0] == mat_two_numbers.e[0][0]);
    CHECK((mat_two_zeros + mat_two_numbers).e[0][1] == mat_two_numbers.e[0][1]);
    CHECK((mat_two_zeros + mat_two_numbers).e[0][2] == mat_two_numbers.e[0][2]);
    CHECK((mat_two_zeros + mat_two_numbers).e[1][0] == mat_two_numbers.e[1][0]);
    CHECK((mat_two_zeros + mat_two_numbers).e[1][1] == mat_two_numbers.e[1][1]);
    CHECK((mat_two_zeros + mat_two_numbers).e[1][2] == mat_two_numbers.e[1][2]);
    CHECK((mat_two_zeros + mat_two_numbers).e[2][0] == mat_two_numbers.e[2][0]);
    CHECK((mat_two_zeros + mat_two_numbers).e[2][1] == mat_two_numbers.e[2][1]);
    CHECK((mat_two_zeros + mat_two_numbers).e[2][2] == mat_two_numbers.e[2][2]);

    //Minus between 2 matrix
    CHECK((mat_two_zeros - mat_two_numbers).e[0][0] == -mat_two_numbers.e[0][0]);
    CHECK((mat_two_zeros - mat_two_numbers).e[0][1] == -mat_two_numbers.e[0][1]);
    CHECK((mat_two_zeros - mat_two_numbers).e[0][2] == -mat_two_numbers.e[0][2]);
    CHECK((mat_two_zeros - mat_two_numbers).e[1][0] == -mat_two_numbers.e[1][0]);
    CHECK((mat_two_zeros - mat_two_numbers).e[1][1] == -mat_two_numbers.e[1][1]);
    CHECK((mat_two_zeros - mat_two_numbers).e[1][2] == -mat_two_numbers.e[1][2]);
    CHECK((mat_two_zeros - mat_two_numbers).e[2][0] == -mat_two_numbers.e[2][0]);
    CHECK((mat_two_zeros - mat_two_numbers).e[2][1] == -mat_two_numbers.e[2][1]);
    CHECK((mat_two_zeros - mat_two_numbers).e[2][2] == -mat_two_numbers.e[2][2]);

    //Multi 
    CHECK((mat_one_n_one * mat_two_numbers).e[0][0] == 4);
    CHECK((mat_one_n_one * mat_two_numbers).e[0][1] == 6);
    CHECK((mat_one_n_one * mat_two_numbers).e[0][2] == 6);
    CHECK((mat_one_n_one * mat_two_numbers).e[1][0] == 8);
    CHECK((mat_one_n_one * mat_two_numbers).e[1][1] == 8);
    CHECK((mat_one_n_one * mat_two_numbers).e[1][2] == 26);
    CHECK((mat_one_n_one * mat_two_numbers).e[2][0] == 6);
    CHECK((mat_one_n_one * mat_two_numbers).e[2][1] == 4);
    CHECK((mat_one_n_one * mat_two_numbers).e[2][2] == 2);

    //Multi num and vector
    result = mat_two_numbers * t;
    CHECK(result.e[0][0] ==  10);
    CHECK(result.e[0][1] ==  15);
    CHECK(result.e[0][2] ==  15);
    CHECK(result.e[1][0] ==  20);
    CHECK(result.e[1][1] ==  20);
    CHECK(result.e[1][2] ==  65);
    CHECK(result.e[2][0] ==  15);
    CHECK(result.e[2][1] ==  10);
    CHECK(result.e[2][2] ==  5);
    
    //Div
    result /= 2;
    CHECK(result.e[0][0] ==  5);
    CHECK(result.e[0][1] ==  7.5);
    CHECK(result.e[0][2] ==  7.5);
    CHECK(result.e[1][0] ==  10);
    CHECK(result.e[1][1] ==  10);
    CHECK(result.e[1][2] ==  32.5);
    CHECK(result.e[2][0] ==  7.5);
    CHECK(result.e[2][1] ==  5);
    CHECK(result.e[2][2] ==  2.5);

}

TEST_CASE("Helper Functions") {
    mat3 mat_two_numbers = mat3(2,3,4,5,6,7,8,9,10);
    mat3 mat_two_numbers2 = mat3(3,17,1,1,4,6,12,40,2);
    mat3 result = dot(mat_two_numbers,mat_two_numbers2);

    CHECK(result.e[0][0] ==  57);
    CHECK(result.e[0][1] ==  206);
    CHECK(result.e[0][2] ==  28);
    CHECK(result.e[1][0] ==  105);
    CHECK(result.e[1][1] ==  389);
    CHECK(result.e[1][2] ==  55);
    CHECK(result.e[2][0] ==  153);
    CHECK(result.e[2][1] ==  572);
    CHECK(result.e[2][2] ==  82);

}
