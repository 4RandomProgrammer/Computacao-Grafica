#include<png.h>
#include <iostream>
#include <cmath>
using namespace std;

class png_processor {
  private:
        int width = 256;
        int height = 256;
        png_byte color_type = PNG_COLOR_TYPE_RGBA;
        png_byte bit_depth = 8;
        png_byte **rows = NULL;
        void init_png();
        int process_png_file_gradient();
        int process_png_file_circle();
        int process_png_file_triangle();
        int write_png_file(char *filename);
        bool is_inside(int x1, int y1, int x2, int y2, int x3, int y3, int x, int y);
        float triangle_area(int x1, int y1, int x2, int y2, int x3, int y3);

    public:
        void render_gradient(char *filename);
        void render_circle(char *filename);
        void render_triangle(char *filename);
};
// Função não foi criada por mim! Retirada do seguinte local: https://www.geeksforgeeks.org/check-whether-a-given-point-lies-inside-a-triangle-or-not/
float png_processor::triangle_area(int x1, int y1, int x2, int y2, int x3, int y3) {
   return abs((x1*(y2-y3) + x2*(y3-y1)+ x3*(y1-y2))/2.0);
}

// Função não foi criada por mim! Retirada do seguinte local: https://www.geeksforgeeks.org/check-whether-a-given-point-lies-inside-a-triangle-or-not/
bool png_processor::is_inside(int x1, int y1, int x2, int y2, int x3, int y3, int x, int y) {   
   /* Calculate area of triangle ABC */
   float A = area (x1, y1, x2, y2, x3, y3);
  
   /* Calculate area of triangle PBC */ 
   float A1 = area (x, y, x2, y2, x3, y3);
  
   /* Calculate area of triangle PAC */ 
   float A2 = area (x1, y1, x, y, x3, y3);
  
   /* Calculate area of triangle PAB */  
   float A3 = area (x1, y1, x2, y2, x, y);
    
   /* Check if sum of A1, A2 and A3 is same as A */
   return (A == A1 + A2 + A3);
}

void png_processor::render_triangle(char *filename){ 
  init_png();
  process_png_file_triangle();
  write_png_file(filename);
}

void png_processor::render_circle(char *filename){ 
  init_png();
  process_png_file_circle();
  write_png_file(filename);
}

void png_processor::render_gradient(char *filename){ 
  init_png();
  process_png_file_gradient();
  write_png_file(filename);
}

void png_processor::init_png() {
    
    rows = new png_byte *[height];

    for (auto i = 0; i < height; i++)
        rows[i] = new png_byte[width * 4];


}

int png_processor::process_png_file_triangle() {

  float point1_y = 127;
  float point1_x = 127;
  
  float point2_y = 2;
  float point2_x = 55;

  float point3_y = 127;
  float point3_x = 2;

	for (auto i = 0; i < height; i++) {
        for (auto j = 0; j < width; j++) {
          if (isInside(point1_x, point1_y, point2_x, point2_y, point3_x, point3_y, j, i)){
            // Red channel
            rows[i][j * 4 + 0] = 0;
            // Green channel
            rows[i][j * 4 + 1] = 255;
            // Blue channel
            rows[i][j * 4 + 2] = 0;
            // Alpha channel
            rows[i][j * 4 + 3] = 255;
          } else {
            // Red channel
            rows[i][j * 4 + 0] = 0;
            // Green channel
            rows[i][j * 4 + 1] = 0;
            // Blue channel
            rows[i][j * 4 + 2] = 0;
            // Alpha channel
            rows[i][j * 4 + 3] = 255;
          }
      }
  }

  return 0;
}

int png_processor::process_png_file_circle() {

  float center_x = 127;
  float center_y = 127;
  float radius = 20;

	for (auto i = 0; i < height; i++) {
        for (auto j = 0; j < width; j++) {
          float pow_x = pow((j - center_x), 2.0);
          float pow_y = pow((i - center_y), 2.0);
          float result = sqrt(pow_x + pow_y);
          if (result > radius){
            // Red channel
            rows[i][j * 4 + 0] = 0;
            // Green channel
            rows[i][j * 4 + 1] = 0;
            // Blue channel
            rows[i][j * 4 + 2] = 0;
            // Alpha channel
            rows[i][j * 4 + 3] = 255;
          } else {
            // Red channel
            rows[i][j * 4 + 0] = 255;
            // Green channel
            rows[i][j * 4 + 1] = 0;
            // Blue channel
            rows[i][j * 4 + 2] = 0;
            // Alpha channel
            rows[i][j * 4 + 3] = 255;
          }
            
        }
    }
	
  return 0;
}

int png_processor::process_png_file_gradient() {

	for (auto i = 0; i < height; i++) {
        for (auto j = 0; j < width; j++) {
            // Red channel
            rows[i][j * 4 + 0] = (j * 127.) / width;
            // Green channel
            rows[i][j * 4 + 1] = 0;
            // Blue channel
            rows[i][j * 4 + 2] = (i * 127.) / height;
            // Alpha channel
            rows[i][j * 4 + 3] = 255;
        }
    }
	
  return 0;
}

int png_processor::write_png_file(char *filename) {
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
    width, height,
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

}

int main() {
    
  png_processor png;

  char img[] = "gradient.png";
  char img2[] = "circle.png";
  char img3[] = "triangle.png";

  png.render_gradient(img);
  png.render_circle(img2);
  png.render_triangle(img3);

  return 0;


}