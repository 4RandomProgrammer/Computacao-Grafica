#ifndef OBJREADER_H
#define OBJREADER_H

#include <iostream>
#include <string>
#include<fstream>
#include "hittable.h"
#include <vector>
#include <sstream>
#include <array>
#include "utils.h"
#include "vec3.h"
#include "triangle.h"

using namespace std;

class ObjReader : public hittable{
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
        std::vector<triangle> triangles;
        std::vector<vec3> normals;
        shared_ptr<material> mat;
        string full_file;
        vec3 mass_center;
        

        /**
         * @brief Construtor da classe de leitura de .Obj e criação dos respectivos triangulos lidos..
         * @param file_reader: nome do arquivo a ser lido.
         * @param file_writer writer: nome do arquivo a ser escrito.
         */  
        ObjReader(string file_reader, string file_writer, vec3 move, shared_ptr<material> _material) {
            file_name_reader = file_reader;
            file_name_writer = file_writer;
            file_initiated = 0;
            mat = _material;
            open_file();
            read_file();
            close_file();
            disloc(move);
        }

        /**
         * @brief função de acerto para um objeto que vai verificar se um raio cruza determinado objeto. Essa função foi baseada na função realizada no tutorial.
         * @param r O raio que queremos testar.
         * @param ray_t O intervalo de acerto.
         * @param rec caso o raio acerte foi indicar aonde foi acertado.
         * @return se o raio fornecido acertou ou não o objeto.
         */
        bool hit( const ray& r, interval ray_t, hit_record& rec) const override {
        
            int size = triangles.size();
            for(int i = 0; i < size; i++) {
                if (triangles[i].hit(r, ray_t,rec)){
                    return true;
                }
            }

            return false;

        }

        /**
         * @brief função com o objetivo de deslocar um objeto para uma posição desejada..
         * @param discloc Deslocamento desejado a aplicar em um objeto.
         */
        void disloc(vec3 disloc) {
            int size = triangles.size();
            for (int i = 0; i < size; i++){
                triangles[i].disloc(disloc);
            }
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
                }
                else if (type == "f") {
                    int A,B,C,value;
                    string maybe;
                    teste >> A >> maybe >> B >> maybe >>  C ;
                    int* numbers = allocate(A,B,C);

                    std::stringstream ss;
                    ss << maybe[2];
                    ss >> value;

                    value -= 1;
                    A -= 1;
                    B -= 1;
                    C -= 1;
                    triangle new_triangle(vertices[A], vertices[B], vertices[C],normals[value],normals[value],normals[value], mat,true);
                    triangles.push_back(new_triangle);
                }

                else if (type == "vn") {
                    double x,y,z;
                    teste >> x >> y >> z;

                    // std::clog << x << ' ' << y << ' ' << z << '\n' ;

                    vec3 normal(x,y,z);
                    normals.push_back(normal);
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