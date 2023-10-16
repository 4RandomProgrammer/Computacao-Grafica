#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../vec4.h"

TEST_CASE("Basic Functions") {
    vec4 vec_two_zeros = vec4();
    vec4  vec_two_numbers = vec4(2,3,4,6);
    vec4 vec = vec4(3,12,4,5);
    vec4 result = vec4();
    double t = 3;

    //sum between 2 vectors
    CHECK((vec_two_zeros + vec_two_numbers)[0] == vec_two_numbers[0]);
    CHECK((vec_two_zeros + vec_two_numbers)[1] == vec_two_numbers[1]);
    CHECK((vec_two_zeros + vec_two_numbers)[2] == vec_two_numbers[2]);
    CHECK((vec_two_zeros + vec_two_numbers)[3] == vec_two_numbers[3]);

    //Minus between 2 vectors
    CHECK((vec_two_zeros - vec_two_numbers)[0] == -vec_two_numbers[0]);
    CHECK((vec_two_zeros - vec_two_numbers)[1] == -vec_two_numbers[1]);
    CHECK((vec_two_zeros - vec_two_numbers)[2] == -vec_two_numbers[2]);
    CHECK((vec_two_zeros - vec_two_numbers)[3] == -vec_two_numbers[3]);

    //Multi 
    CHECK((vec * vec_two_numbers)[0] ==  6);
    CHECK((vec * vec_two_numbers)[1] == 36);
    CHECK((vec * vec_two_numbers)[2] ==  16);
    CHECK((vec * vec_two_numbers)[3] == 30);

    //Multi num and vector
    result = vec * t;
    CHECK(result[0] ==  9);
    CHECK(result[1] ==  36);
    CHECK(result[2] ==  12);
    CHECK(result[3] ==  15);
    
    //Div
    result /= 4;
    CHECK(result[0] == 2.25);
    CHECK(result[1] == 9);
    CHECK(result[2] == 12);
    CHECK(result[3] == 3.75);

}

TEST_CASE("Helper Functions") {
    vec4  vec_two_numbers = vec4(2,3,4,5);
    vec4 vec_two_numbers2 = vec4(3,17,1,3);
    vec4 vec_unit = vec4(4,2,6,8);
    vec4 result = unit_vector(vec_unit);

    CHECK(dot(vec_two_numbers,vec_two_numbers2) == 76);
    CHECK(result[0] ==  doctest::Approx(0.36).epsilon(0.01));
    CHECK(result[1] == doctest::Approx(0.18).epsilon(0.01));
    CHECK(result[2] ==  doctest::Approx(0.54).epsilon(0.01));
    CHECK(result[3] == doctest::Approx(0.73).epsilon(0.01));

}
