#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"

#include "color.h"
#include "hittable.h"
#include "material.h"
#include <iostream>
#include <libpng/png.h>
#include <string>
#include <cstring>

using namespace std;

class camera {
    public:
        double aspect_ratio = 1.0;  // Ratio of image width over height
        int    image_width  = 100;  // Rendered image width in pixel count
        int    samples_per_pixel = 10; // Count of random samples for each pixel
        int max_depth = 10; // Maximum number of ray bounces into scene 
        int anim_frame = 0;

        double vfov = 90; // Vertical view angle (field of view)

        point3 lookfrom = point3(0,0,-1);  // Point camera is looking from
        point3 lookat   = point3(0,0,0);   // Point camera is looking at
        vec3   vup      = vec3(0,1,0);     // Camera-relative "up" direction


        void render(const hittable& world) {
            initialize();

            for (int j = 0; j < image_height; ++j) {
                std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
                for (int i = 0; i < image_width; ++i) {
                    color pixel_color(0,0,0);
                    for (int sample = 0; sample < samples_per_pixel; sample++) {
                        ray r = get_ray(i,j);
                        pixel_color += ray_color(r, max_depth, world);
                    }
                    
                    write_color(pixel_color, samples_per_pixel, j, i);
                }
            }


            // write the full png here when done
            string animation = "animation_";
            string type =  ".png";
            string file = animation + std::to_string(anim_frame) + type;
            char file_name[file.length()+1];
            strcpy(file_name, file.c_str());
            write_png_file(file_name);
            std::clog << "Image Generated!" << '\n';
        }

        void lerp_look_from(point3 start, point3 end, double time) {
            lookfrom = start * ( 1 - time ) + end * time;
        }

        void lerp_look_at(point3 start, point3 end, double time) {
            lookat = start * ( 1 - time ) + end * time;
        }

    private:
        int    image_height;   // Rendered image height
        point3 center;         // Camera center
        point3 pixel00_loc;    // Location of pixel 0, 0
        vec3   pixel_delta_u;  // Offset to pixel to the right
        vec3   pixel_delta_v;  // Offset to pixel below
        vec3   u, v, w;        // Camera frame basis vectors
        png_byte color_type = PNG_COLOR_TYPE_RGBA;
        png_byte bit_depth = 8;
        png_byte **rows = NULL;

        void initialize() {
            image_height = static_cast<int>(image_width / aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height;

            center = lookfrom;

            // Determine viewport dimensions.
            auto focal_length = (lookfrom - lookat).length();
            auto theta = degrees_to_radians(vfov);
            auto h = tan(theta/2);
            auto viewport_height = 2 * h * focal_length;
            auto viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);

            // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
            w = unit_vector(lookfrom - lookat);
            u = unit_vector(cross(vup, w));
            v = cross(w, u);

            // Calculate the vectors across the horizontal and down the vertical viewport edges.
            vec3 viewport_u = viewport_width * u;    // Vector across viewport horizontal edge
            vec3 viewport_v = viewport_height * -v;  // Vector down viewport vertical edge

            // Calculate the horizontal and vertical delta vectors from pixel to pixel.
            pixel_delta_u = viewport_u / image_width;
            pixel_delta_v = viewport_v / image_height;

            // Calculate the location of the upper left pixel.
            auto viewport_upper_left = center - (focal_length * w) - viewport_u/2 - viewport_v/2;
            pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

            init_png();
        }

        color ray_color(const ray& r, int depth, const hittable& world) const {
            hit_record rec;

            if (depth <= 0) return color(0,0,0);
            if (world.hit(r, interval(0.001, infinity), rec)) {
                ray scattered;
                color attenuation;
                if (rec.mat->scatter(r, rec, attenuation, scattered)){
                    return attenuation * ray_color(scattered, depth-1, world);
                }
                return color(0,0,0);
            }
            vec3 unit_direction = unit_vector(r.direction());
            auto a = 0.5*(unit_direction.y() + 1.0);

            return (1.0 - a) * color(1.0,1.0,1.0) + a * color(0.5,0.7,1.0);
            
        }

        ray get_ray(int i, int j) const {

            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto pixel_sample = pixel_center + pixel_sample_square();

            auto ray_origin = center;
            auto ray_direction = pixel_sample - ray_origin;

            return ray(ray_origin, ray_direction);
        }

        vec3 pixel_sample_square() const {
            auto px = -0.5 + random_double();
            auto py = -0.5 + random_double();
            return (px * pixel_delta_u) + (py * pixel_delta_v);
        }

        inline double linear_to_gamma(double linear_component)
        {
            return sqrt(linear_component);
        }

        void write_color(color pixel_color, int samples_per_pixel, int i, int j) {
            
            auto r = pixel_color.x();
            auto g = pixel_color.y();
            auto b = pixel_color.z();

            auto scale = 1.0 / samples_per_pixel;
            r *= scale;
            g *= scale;
            b *= scale;

            r = linear_to_gamma(r);
            g = linear_to_gamma(g);
            b = linear_to_gamma(b);
            
            interval intesity(0.000,0.999);
            // Red channel
            rows[i][j * 4 + 0] = static_cast<int>(256 * intesity.clamp(r));
            // Green channel
            rows[i][j * 4 + 1] = static_cast<int>(256 * intesity.clamp(g));
            // Blue channel
            rows[i][j * 4 + 2] = static_cast<int>(256 * intesity.clamp(b));
            // Alpha channel
            rows[i][j * 4 + 3] = 255;


        };


        int write_png_file(char *filename) {
            /* create file */

            FILE *fp = fopen(filename, "wb");

            png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

            if (!png) {
                std::cout << "No PNG file found";
                return -1;
            }
            png_infop info = png_create_info_struct(png);

            if (!info) {
                std::cout << "No PNG info found";
                return -1;
            }

            if (setjmp(png_jmpbuf(png)))  {
                fprintf(stderr, "Error during png creation\n");
                return -1;
            }

            png_init_io(png, fp);

            if (setjmp(png_jmpbuf(png))){
                    fprintf(stderr, "Error during png creation\n");
                    return -1;
            }

            // Output is 8bit depth, RGBA format.
            png_set_IHDR(
                png,
                info,
                image_width, image_height,
                bit_depth,
                color_type,
                PNG_INTERLACE_NONE,
                PNG_COMPRESSION_TYPE_BASE,
                PNG_FILTER_TYPE_BASE
            );

            png_write_info(png, info);

            if (setjmp(png_jmpbuf(png))){
                    return -1;
            }

            if (!rows) {
                std::cout << "No ROW Pointers initialized";
                return -1;
            } 

            png_write_image(png, rows);
            
            if (setjmp(png_jmpbuf(png))){
                    std::cout << 'f';
                    return -1;
            }

            png_write_end(png, NULL);


            fclose(fp);
            return 1;
        }

        void init_png() {
    
            rows = new png_byte *[image_height];

            for (auto i = 0; i < image_height; i++)
                rows[i] = new png_byte[image_width * 4];


        }
};

#endif