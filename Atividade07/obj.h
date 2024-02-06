#ifndef OBJREADER_H
#define OBJREADER_H

#include <iostream>
#include<fstream>
#include "hittable.h"
#include <vector>
#include <sstream>
#include <array>
#include "utils.h"
#include "vec3.h"
#include "triangle.h"

using namespace std;

class DotObj : public hittable {
    private:

        int* allocate(int int1,int int2,int int3) {
            int *teste;
            teste = new int [3];

            teste[0] = int1;
            teste[1] = int2;
            teste[2] = int3;

            return teste;
        }

    public:
        std::vector<vec3> vertices;
        std::vector<triangle> triangles;
        std::vector<vec3> normals;
        shared_ptr<material> mat;
        vec3 mass_center;

        //! Construtor da classe de leitura de .Obj. Parametros: file_reader: nome do arquivo a ser lido. File writer: nome do arquivo a ser escrito.
        DotObj(std::vector<vec3> _vertices, std::vector<triangle> _triangles, std::vector<vec3> _normals, vec3 _mass_center, shared_ptr<material> _material): vertices(_vertices), triangles(_triangles),normals(_normals), mass_center(_mass_center),mat(_material){}

        void disloc(vec3 disloc) {
            int size = triangles.size();
            for (int i = 0; i < size; i++){
                triangles[i].disloc(disloc);
            }
        }

        bool hit( const ray& r, interval ray_t, hit_record& rec) const override {
        
            int size = triangles.size();
            for(int i = 0; i < size; i++) {
                if (triangles[i].hit(r, ray_t,rec)){
                    return true;
                }
            }

            return false;

        }


        void object_center(){

            int size = vertices.size();
            double avg_x,avg_y,avg_z;
            avg_x = 0;
            avg_y = 0;
            avg_z = 0;

            for(int i = 0; i < size; i++) {
                

                avg_x += vertices[i].x();
                avg_y += vertices[i].y();
                avg_z += vertices[i].z();

            }

            avg_x /= size;
            avg_y /= size;
            avg_z /= size;

            mass_center = vec3(avg_x,avg_y,avg_z);

            disloc(-mass_center);
        }
};


#endif