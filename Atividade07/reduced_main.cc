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

    point3 start( 0.0, 0.0, -1.0 );
    point3 middle( 3.0, 0.0, -1.0 );
    point3 end( 6.0,0.0, -1.0 );
    point3 sub(0,0,0);
    point3 camera_start(-2,2,1);
    point3 camera_end(-8,2,-1);
    sphere moving_sphere(start, 0.5, material_center);
    sphere ground(point3( 0.0, -100.5, -1.0), 100.0, material_ground);
    shared_ptr<ObjReader> quadrado1 = make_shared<ObjReader>(file_name,"",vec3(-1,0,-1.0),material_left);
    shared_ptr<ObjReader> quadrado2 = make_shared<ObjReader>(file_name,"",vec3(8,0,-1), material_right);
    
    world.add(make_shared<sphere>(ground));
    world.add(make_shared<sphere>(moving_sphere));
    world.add(quadrado1);
    world.add(quadrado2);
    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width  = 1280;
    cam.samples_per_pixel = 50;
    cam.max_depth = 50;

    cam.vfov     = 45;
    cam.lookfrom = camera_start;
    cam.lookat   = point3(0,0,-1);
    cam.vup      = vec3(0,1,0);

    double frames = 23;
    double time = 1;

    std::clog << time / frames << '\n';
    // cam.render(world);
    // Loop de renderização

    // Como a função funiona de 1 em 1 segundo preciso criar um sistema que deixa a animação mais fácil de ocorrer.
    for (double i = 0; i <= time; i += time / frames ) {
    
        cam.anim_frame += 1;
        cam.lerp_look_at(start,middle,i);
        world.clear();
        moving_sphere.lerp(start,middle,i);
        world.add(make_shared<sphere>(ground));
        world.add(quadrado2);
        world.add(make_shared<sphere>(moving_sphere));
        world.add(quadrado1);
        cam.render(world);
    }

    for (double i = 0; i <= time; i += time / frames ) {
    
        cam.anim_frame += 1;
        cam.lerp_look_at(middle,end,i);
        world.clear();
        moving_sphere.lerp(middle,end,i);
        world.add(make_shared<sphere>(ground));
        world.add(quadrado2);
        world.add(make_shared<sphere>(moving_sphere));
        world.add(quadrado1);

        cam.render(world);
    }

    // bola para e camera mexe
    for (double i = 0; i <= time; i += time / frames ) {
    
        cam.anim_frame += 1;
        cam.lerp_look_from(camera_start,camera_end,i);
        cam.render(world);
    }

    // Movimento da voltando.
    sub = start;
    start = end;
    end = sub;
    for (double i = 0; i <= time; i += time / frames ) {
    
        cam.anim_frame += 1;
        world.clear();

        moving_sphere.lerp(start,middle,i);
        std::clog << i << '\n' << moving_sphere.center << '\n';
        world.add(make_shared<sphere>(ground));
        world.add(quadrado2);
        world.add(make_shared<sphere>(moving_sphere));
        world.add(quadrado1);

        cam.render(world);
    }
    
    for (double i = 0; i <= time; i += time / frames ) {
    
        cam.anim_frame += 1;
        world.clear();

        moving_sphere.lerp(middle,end,i);
        std::clog << i << '\n' << moving_sphere.center << '\n';
        world.add(make_shared<sphere>(ground));
        world.add(quadrado2);
        world.add(make_shared<sphere>(moving_sphere));
        world.add(quadrado1);

        cam.render(world);
    }
    

}