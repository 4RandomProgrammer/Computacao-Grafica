#include<iostream>

using namespace std;

class vec_manipulator {
    public:
        int create_vec(int size);
        int create_mat(int x, int y);
        int remove_mat( int y);
        int remove_vet();
        float* vet_operator-();
        float* vet_operator+(float *v, float size);

    private:
        float *vec = NULL;
        float **mat = NULL;
        int vec_size = 0;
};

//Função para a criação de vetor 
//Recebe size correspondente ao tamanho do vetor
//Retorna -1 caso erro, caso de certo retorna 0
int vec_manipulator::create_vec(int size){
    if (vec != NULL) return -1;

    vec = new float[size]();

    if (!vec) return -1;

    vec_size = size; 

    return 0;
}

//Função para criação de matrizes,
//Recebe colunhas e linhas para inicializar o vetor
// Caso de erro retorna -1, caso de certo 0
int vec_manipulator::create_mat(int x, int y){
    if (mat != NULL) return -1;

    mat = new int*[rows];

    if (!mat) return -1;

    for (int i = 0; i < y; ++i)
        mat[i] = new int[x];
    
    if (!mat) return -1;

    return 0;
}

float* vet_operator-(){
    float op_vec = new float[size];

    for(int i = 0; i < vec_size; i++) {
        op_vec[i] = 0 - vec[i];
    }

    return op_vec;
}

float vet_operator+(float *v, float size){
    float op_vec = new float[size];

    for(int i = 0; i < vec_size; i++) {
        op_vec[i] =  v[i] - vec[i];
    }

    return op_vec;
}

int vec_manipulator::remove_mat(int y) {
    for (int i = 0; i < y; ++i)
        delete [] mat[i];

    delete [] mat;

    return 0;
}

int vec_manipulator::remove_vet() {
    delete [] vec;
    return 0;
}


int main(){

}