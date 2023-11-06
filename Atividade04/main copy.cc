#include "color.h"
#include "vec3.h"
#include "ray.h"

#include <iostream>
#include <math.h>

bool hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    return (discriminant >= 0);
}


bool hit_triangle(const point3& center, const point3& v0, const point3& v1, const point3& v2, const ray& r) {
    vec3 v0v1 = v1 - v0;
    vec3 v0v2 = v2 - v0;

    constexpr double kEpsilon = std::numeric_limits<double>::epsilon();

    vec3 N = cross(v0v1,v0v2);

    double area2 = N.length();
    
    double NdotRayDirection = dot(N,unit_vector(r.direction()));

    if (fabs(NdotRayDirection) < kEpsilon) // almost 0
        return false; // they are parallel, so they don't intersect! 

    double d = dot(-N, v0);

    double t = -(dot(N,center) + d) / NdotRayDirection;

    if (t < 0) return false;    
    std::clog << "AQUI1" << '\n';
    vec3 P = center + t * unit_vector(r.direction());

    vec3 C;

    vec3 edge0 = v1 - v0; 
    vec3 vp0 = P - v0;
    C = cross(edge0,vp0);

    if (dot(N,C) < 0) return false;
    std::clog << "AQUI2" << '\n';

    vec3 edge1 = v2 - v1; 
    vec3 vp1 = P - v1;
    C = cross(edge1,vp1);

    if (dot(N,C) < 0) return false;
    std::clog << "AQUI3" << '\n';

    return true;

}

color ray_color(const ray& r) {
    //Além de verificar a intersecção com o triangulo, tenho que verificar com o plano.
    point3 v0(-1, -1, -1);
    point3 v1(1,-1,-1);
    point3 v2(0,1,-1);

    if (hit_triangle(point3(0,0,-1),v0,v1,v2, r)){
        return color(1,0,0);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}


int main() {

    // Image

    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 800;

    // Calculate the image height, and ensure that it's at least 1.
    int image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera

    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);
    auto camera_center = point3(1000000000000, 0, 1000000000000);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center
                             - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Render

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                 \n";
}