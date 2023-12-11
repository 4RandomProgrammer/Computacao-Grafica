#include "color.h"
#include "vec3.h"
#include "ray.h"
#include "ObjReader.h"

#include <iostream>
#include <math.h>

string file_name = "teste.obj";
ObjReader obj = ObjReader(file_name,"");;

bool hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    return (discriminant >= 0);
}


bool hit_triangle( const point3& v0, const point3& v1, const point3& v2, const ray& r) {
    vec3 v0v1 = v1 - v0;
    vec3 v0v2 = v2 - v0;

    constexpr double kEpsilon = std::numeric_limits<double>::epsilon();

    vec3 N = cross(v0v1,v0v2);

    double area2 = N.length();
    
    double NdotRayDirection = dot(N,r.direction());

    if (fabs(NdotRayDirection) < kEpsilon) // almost 0
        return false; // they are parallel, so they don't intersect! 

    double d = dot(N, v0);

    double t = (d - dot(N,r.origin())) / NdotRayDirection;

    if (t < 0) return false;    

    vec3 P = r.origin() + t * r.direction();

    vec3 C;

    vec3 edge0 = v1 - v0; 
    vec3 vp0 = P - v0;
    C = cross(edge0,vp0);

    if (dot(N,C) < 0) return false;

    vec3 edge1 = v2 - v1; 
    vec3 vp1 = P - v1;
    C = cross(edge1,vp1);

    if (dot(N,C) < 0) return false;

    vec3 edge2 = v0 - v2; 
    vec3 vp2 = P - v2;
    C = cross(edge2,vp2);

    if (dot(N,C) < 0) return false;

    return true;

}

color ray_color(const ray& r) {
    //Além de verificar a intersecção com o triangulo, tenho que verificar com o plano.
    // Pegar os triangulos do objeto aqui
    // Como que eu faço isso?
    // Eu tenho que passar por todos os triangulos do meu objeto e fazer com que ele veja se foi hitado ou n.
    

    

    int size = obj.triangles.size();

    for(int i = 0; i < size; i++) {
        int t0,t1,t2;

        t0 = obj.triangles[i][0] - 1;
        t1 = obj.triangles[i][1] - 1;
        t2 = obj.triangles[i][2] - 1;

        vec3 v0 = obj.vertices[t0];
        vec3 v1 = obj.vertices[t1];
        vec3 v2 = obj.vertices[t2];

        if (hit_triangle(v0,v1,v2, r)){
                return color(1,0,0);
        }
    }
    
    //Para cada raio iterar sobre todos os triangulos.
    // if (hit_triangle(v0,v1,v2, r)){
    //     return color(1,0,0);
    // }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}


int main() {

    
    obj.open_file();
    obj.read_file();

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
    auto camera_center = point3(0, 0, 0);

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