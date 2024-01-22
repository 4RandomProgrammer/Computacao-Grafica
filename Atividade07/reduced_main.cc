#include "utils.h"

#include "camera.h"
#include "hittable_list.h"
#include "sphere.h"
#include "ObjReader.h"
#include "triangle.h"

string file_name = "cube.obj";


int main() {
    hittable_list world;
    
    auto R = cos(pi/4);

    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_left  = make_shared<lambertian>(color(1,0,0));
    auto material_right = make_shared<dielectric>(1.5);
    auto material_center = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<ObjReader>(file_name,"",vec3(0,0,-1.5),material_center));
    world.add(make_shared<ObjReader>(file_name,"",vec3(0,-1.5,-1.75), material_right));
    world.add(make_shared<ObjReader>(file_name,"",vec3(0,1.5,-1.75), material_left));
    // world.add(make_shared<triangle>(vec3(0.0,0.0,0.0),vec3(1.0,1.0,0.0),vec3(1.0,0.0,0.0), vec3(0.0,0.0,-1.0), material_left, true));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width  = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;

    cam.vfov     = 45;
    cam.lookfrom = point3(-2,2,1);
    cam.lookat   = point3(0,0,-1);
    cam.vup      = vec3(0,1,0);


    cam.render(world);
}