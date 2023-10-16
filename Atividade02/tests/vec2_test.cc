#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../vec2.h"

TEST_CASE("Basic Functions") {
    vec2 vec_two_zeros = vec2();
    vec2  vec_two_numbers = vec2(2,3);
    vec2 vec_one_n_one = vec2(1,1);
    vec2 result = vec2();
    double t = 2;

    //sum between 2 vectors
    CHECK((vec_two_zeros + vec_two_numbers)[0] == vec_two_numbers[0]);
    CHECK((vec_two_zeros + vec_two_numbers)[1] == vec_two_numbers[1]);

    CHECK((vec_two_zeros - vec_two_numbers)[0] == -vec_two_numbers[0]);
    CHECK((vec_two_zeros - vec_two_numbers)[1] == -vec_two_numbers[1]);

    //Multi 
    CHECK((vec_two_zeros * vec_two_numbers)[0] ==  0);
    CHECK((vec_two_zeros * vec_two_numbers)[1] == 0);
    //Multi num and vector
    result = vec_one_n_one * t;
    CHECK(result[0] ==  2);
    CHECK(result[0] ==  2);
    
    //Div
    result /= 2;
    CHECK(result[0] == 1);
    CHECK(result[1] == 1);

}

TEST_CASE("Helper Functions") {
    vec2  vec_two_numbers = vec2(2,3);
    vec2 vec_two_numbers2 = vec2(3,17);
    vec2 vec_unit = vec2(4,2);
    vec2 result = unit_vector(vec_unit);

    CHECK(dot(vec_two_numbers,vec_two_numbers2) == 57);
    CHECK(result[0] ==  doctest::Approx(0.9).epsilon(0.01));
    CHECK(result[1] == doctest::Approx(0.45).epsilon(0.01));

}
