#include "utils.h"

#include "camera.h"
#include "hittable_list.h"
// #include "sphere.h"
#include "ObjReader.h"

string file_name = "cube.obj";


int main() {
    hittable_list world;
    
    auto R = cos(pi/4);

    auto material_left  = make_shared<lambertian>(color(0,0,1));
    auto material_right = make_shared<lambertian>(color(1,0,0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));


    world.add(make_shared<ObjReader>(file_name,"",vec3(0,0,-1.5),material_center));
    world.add(make_shared<ObjReader>(file_name,"",vec3(0,-1.5,-1.75), material_right));
    world.add(make_shared<ObjReader>(file_name,"",vec3(0,1.5,-1.75), material_left));

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