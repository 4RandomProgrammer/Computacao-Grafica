/// \file utils.h
/// \brief Arquivo que centraliza todas as coisas úteis que são mais utilizadas dentro de projeto.
/// \author Criado por Luís Felipe Dobner Henriques, porém retirado do tutorial: https://raytracing.github.io/books/RayTracingInOneWeekend.html

#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>

// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;
constexpr double kEpsilon = std::numeric_limits<double>::epsilon();

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() {
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    return min + (max - min) * random_double();
}

// Common Headers

#include "interval.h"
#include "ray.h"
#include "vec3.h"
// #include "sphere.h"
#include "color.h"


#endif