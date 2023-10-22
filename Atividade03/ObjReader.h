#ifndef OBJREADER_H
#define OBJREADER_H

#include <iostream>
#include<fstream>
using namespace std;

class ObjReader {
    private:
        string file_name_reader;
        string file_name_writer;
        string fileRead;
        string full_file;
        fstream file_to_read;
        int file_initiated;

    public:
        ObjReader(string file_reader, string file_writer) {
            file_name_reader = file_reader;
            file_name_writer = file_writer;
            file_initiated = 0;
        }
        
        string get_file_read(){
            return fileRead;
        }

        int open_file(){
            file_to_read.open(file_name_reader.c_str(), ios::in);

            if(!file_to_read) {
                cout << "No file found!";
                return -1;
            }
            file_initiated = 1;
            return 0;

        }
        int read_file() {
            if (!file_initiated) return -1;

            while (1) {
                std::getline(file_to_read,fileRead);
                full_file += fileRead + '\n';
                if( file_to_read.eof() ) break;
            }

            return 0;
        }

        int write_file(){
            if (!file_initiated) return -1;

            ofstream test_file(file_name_writer);
            
            if (!test_file) return -1;

            test_file  << full_file;

            return 0;

        }

        int close_file(){
            if ( !file_initiated ) return -1;
            file_to_read.close();
            return 0;
        }
};


#endif