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
        

    public:
        std::vector<vec3> vertices;
        std::vector<int*> triangles = std::vector<int*>();
        std::vector<triangle> t; 
        std::vector<int> normals_idx = std::vector<int>();
        std::vector<float*> normals = std::vector<float*>();;
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
            int size = t.size();
            for (int i = 0; i < size; i++){
                t[i].disloc(disloc);
            }
        }


        bool hit( const ray& r, interval ray_t, hit_record& rec) const override {
        
            int size = t.size();

            for(int i = 0; i < size; i++) {
                if (t[i].hit(r, ray_t, rec)){
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
                    string maybe;
                    teste >> A >> maybe >> B >> maybe >>  C ;
                    int* numbers = allocate(A,B,C);
                    // std::clog << A << B << C << id1 << id2 << id3 << '\n';
                    // std::clog << A << B << C << maybe[2] << '\n';
                    
                    triangle t_new(vertices[A - 1], vertices[B - 1],vertices[C - 1],vec3(0,0,0), mat, false);
                    t.push_back(t_new);
                    value = (int)maybe[2];
                    normals_idx.push_back(value);
                    triangles.push_back(numbers);

                }

                else if (type == "vn") {
                    double x,y,z;
                    teste >> x >> y >> z;
                    float* number = allocate_float(x,y,z);
                    normals.push_back(number);
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