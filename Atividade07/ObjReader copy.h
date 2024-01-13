#ifndef OBJREADER2_H
#define OBJREADER2_H

#include <iostream>
#include<fstream>
#include "hittable.h"
#include <vector>
#include <sstream>
#include <array>
#include "utils.h"
#include "vec3.h"

using namespace std;

class ObjReader : public hittable {
    private:
        string file_name_reader;
        string file_name_writer;
        string fileRead;
        fstream file_to_read;
        int file_initiated;

        int* allocate(int int1,int int2,int int3) {
            int *teste;
            teste = new int [3];

            teste[0] = int1;
            teste[1] = int2;
            teste[2] = int3;

            return teste;
        }

        int* allocate_one_int(int value) {
            int* teste;
            teste = new int;

            teste[0] = value;

            return teste;
        }

        float* allocate_float(float int1,float int2,float int3) {
            float *teste;
            teste = new float[3];

            teste[0] = int1;
            teste[1] = int2;
            teste[2] = int3;

            return teste;
        }

      

        bool hit_triangle( const point3& v0, const point3& v1, const point3& v2, const ray& r, hit_record& rec) const {
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
            
            int normal_sizes = normals_idx.size();

            rec.t = t;
            rec.p = P;
            rec.normal = N;
            vec3 outward_normal = N;
            rec.set_face_normal(r, outward_normal);

            // if( normal_sizes > 0) {
            //     float d00 = dot(edge0,edge0);
            //     float d01 = dot(edge0,edge1);
            //     float d11 = dot(edge1,edge1);
            //     float d20 = dot(vp1,edge0);
            //     float d21 = dot(vp1,edge1);

            //     float denominador = d00 * d11 - d01 * d01;

            //     float u,w,v;

            //     v = (d11 * d20 - d01 * d21) / denominador;
            //     w = (d00 * d21 - d01 * d20) / denominador;
            //     u = 1.0 - v - w;
            //     vec3 normal = get_normal(v0,v1,v2);
            //     vec3 new_normal = u * normal + v * normal + w * normal;

            //     rec.normal = new_normal;
            //     vec3 outward_normal = new_normal;
            //     rec.set_face_normal(r, outward_normal);
            // }
            // else {
                
            //     rec.normal = N;
            //     vec3 outward_normal = N;
            //     rec.set_face_normal(r, outward_normal);
            // }

            return true;

    }

      vec3 get_normal(const point3& r1, const point3& r2, const point3& r3) const {
            std::clog << "waaa";
            int size = triangles.size();
            bool c1,c2, c3;
            c1 = c2 = c3 = false;
            
            for(int i = 0; i < size; i++) {
                int t0,t1,t2;

                t0 = triangles[i][0] - 1;
                t1 = triangles[i][1] - 1;
                t2 = triangles[i][2] - 1;

                vec3 v0 = vertices[t0];
                vec3 v1 = vertices[t1];
                vec3 v2 = vertices[t2];
                
                int normal_idx = normals_idx[i][0] - 1;
 
                c1 = v0.x() == r1.x() && v0.y() == r1.y() && v0.z() == r1.z();
                c2 = v1[0] == r2[0] && v1[1] == r2[1] && v1[2] == r2[2];
                c3 = v2[0] == r3[0] && v2[1] == r3[1] && v2[2] == r3[2];
                
                if (c1 && c2 && c3) {
  
                    return obj_normals[normal_idx];
                }
            }

            return vec3(0,0,0);
        }
        

    public:
        std::vector<vec3> vertices;
        std::vector<vec3> obj_normals;
        std::vector<int*> triangles = std::vector<int*>();
        std::vector<int*> normals_idx = std::vector<int*>();
        shared_ptr<material> mat;
        string full_file;
        vec3 mass_center;

        //! Construtor da classe de leitura de .Obj. Parametros: file_reader: nome do arquivo a ser lido. File writer: nome do arquivo a ser escrito.
        ObjReader(string file_reader, string file_writer, vec3 move, shared_ptr<material> _material) {
            file_name_reader = file_reader;
            file_name_writer = file_writer;
            file_initiated = 0;
            open_file();
            read_file();
            close_file();
            mat = _material;
            disloc(move);
        }

        void disloc(vec3 disloc) {
            int size = vertices.size();
            for (int i = 0; i < size; i++){
                vertices[i] += disloc;
            }
        }


        bool hit( const ray& r, interval ray_t, hit_record& rec) const override {
        
            int size = triangles.size();
            
            for(int i = 0; i < size; i++) {
                int t0,t1,t2;

                t0 = triangles[i][0] - 1;
                t1 = triangles[i][1] - 1;
                t2 = triangles[i][2] - 1;

                vec3 v0 = vertices[t0];
                vec3 v1 = vertices[t1];
                vec3 v2 = vertices[t2];

                if (hit_triangle(v0,v1,v2, r, rec)){
                    std::clog << i;
                    return true;
                }
                
                

            }
            return false;
            //hit record aqui, n?
                    

        }

        //! Getter da variavel que armazena os conteúdos do arquivo lido. Retorna o valor dele apenas
        string get_file_read(){
            return fileRead;
        }

        //! Função de abertura de arquivo. É necessário executa-la antes de qualquer operação. Ela verfica se o arquivo com nome indicado pode ser aberto e retorna 0 sim e -1 indicando erro.
        int open_file(){
            file_to_read.open(file_name_reader.c_str(), ios::in);

            if(!file_to_read) {
                cout << "No file found!";
                return -1;
            }
            file_initiated = 1;
            return 0;

        }
        //! Função de leitura de arquivo. Ela lê um arquivo aberto. Ela verfica se o arquivo ja foi aberto para fazer a leitura, caso não tenha retorna erro. Em caso do arquivo estar aberto le o arquivo e guarda o seu valor em uma variavel interna. Se tudo ocorrer bem retorna 0.
        int read_file() {
            if (!file_initiated) return -1;

            while (1) {
                std::getline(file_to_read,fileRead);
                std::stringstream teste(fileRead);
                std::string type;
                teste >> type;

                // if (type == "vn"){
                //     std::clog << fileRead;
                if (type == "v"){
                    double x,y,z;
                    teste >> x >> y >> z;
                    vec3 teste(x,y,z);
                    vertices.push_back(teste);
                    // std::clog << x << y << z << '\n';
                }
                else if (type == "f") {
                    int A,B,C,value;

                    value = 0;
                    string maybe, maybe2;

                    teste >> A >> maybe >> B >> maybe2 >>  C ;
  
                    int* numbers = allocate(A,B,C);

                    stringstream ss;
                    ss << maybe[2];
                    ss >> value;

                    int *values = allocate_one_int(value);
                    normals_idx.push_back(values);
                    triangles.push_back(numbers);

                }

                else if (type == "vn") {
                    double nx,ny,nz;
                    teste >> nx >> ny >> nz;
                    vec3 normal(nx,ny,nz);
                    obj_normals.push_back(normal);
                }

                if( file_to_read.eof() ) break;
            }

            
            object_center();

            return 0;
        }

        //! Função de leitura de escrita. Ela escreve os conteudos de um arquivo aberto. Ela verfica se o arquivo ja foi aberto para fazer a escrita, caso não tenha retorna erro. Em caso do arquivo estar aberto escreve em outro arquivo com o nome fornecido. Se tudo ocorrer bem retorna 0.
        int write_file(){
            if (!file_initiated) return -1;

            ofstream test_file(file_name_writer);
            
            if (!test_file) return -1;

            test_file  << full_file;

            return 0;

        }

        //! Função de fechamento de arquivo. É necessário a abertura do arquivo antes do fechamento. Ela verfica se o arquivo com nome indicado ja foi aberto, se não retornar erro. Caso contrário, fecha o arquivo e retorna 0.
        int close_file(){
            if ( !file_initiated ) return -1;
            file_to_read.close();
            return 0;
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