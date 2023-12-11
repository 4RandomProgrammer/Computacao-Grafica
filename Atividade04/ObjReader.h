#ifndef OBJREADER_H
#define OBJREADER_H

#include <iostream>
#include<fstream>
#include "ObjReader.h"
#include <vector>
#include <sstream>
#include <array>
using namespace std;

class ObjReader {
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

    public:
        std::vector<vec3> vertices;
        std::vector<int*> triangles = std::vector<int*>();
        std::vector<float[3]> normals;
        string full_file;
        //! Construtor da classe de leitura de .Obj. Parametros: file_reader: nome do arquivo a ser lido. File writer: nome do arquivo a ser escrito.
        ObjReader(string file_reader, string file_writer) {
            file_name_reader = file_reader;
            file_name_writer = file_writer;
            file_initiated = 0;
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
                    int A,B,C;
                    teste >> A >> B >> C;
                    int* numbers = allocate(A,B,C);
                    // std::clog << A << B << C << '\n';
                    triangles.push_back(numbers);

                }

                if( file_to_read.eof() ) break;
            }

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
};


#endif