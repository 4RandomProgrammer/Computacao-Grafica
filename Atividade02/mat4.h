#ifndef MAT4_H
#define MAT4_H

#include <cmath>
#include <iostream>

using std::sqrt;

class mat4 {
    
  public:
    double e[4][4];
    
    //!Construtor base: inicializa a função com zeros.
    mat4() : e{{0,0,0,0}, {0,0,0,0}, {0,0,0,0}} {}

    //!Construtor com params:
    //\@params: e0 elemento 0,0 da matriz
    //\@params: e1 elemento 0,1 da matriz
    //\@params: e2 elemento 0,2 da matriz
    //\@params: e3 elemento 0,3 da matriz
    //\@params: f0 elemento 1,0 da matriz
    //\@params: f1 elemento 1,1 da matriz
    //\@params: f2 elemento 1,2 da matriz
    //\@params: f3 elemento 1,3 da matriz
    //\@params: g0 elemento 2,0 da matriz
    //\@params: g1 elemento 2,1 da matriz
    //\@params: g2 elemento 2,2 da matriz
    //\@params: g3 elemento 2,3 da matriz
    //\@params: h0 elemento 3,0 da matriz
    //\@params: h1 elemento 3,1 da matriz
    //\@params: h2 elemento 3,2 da matriz
    //\@params: h3 elemento 3,3 da matriz
    mat4(double e0, double e1, double e2, double e3,  double f0, double f1, double f2, double f3 , double g0, double g1, double g2, double g3,  double h0, double h1, double h2, double h3) : e{{e0, e1, e2, e3}, {f0, f1, f2, f3}, {g0, g1, g2, g3}, {h0, h1, h2, h3}} {}

    //!Função de coordenada: retorna elemento 0,0 da matriz
    double x1() const { return e[0][0]; }
    //!Função de coordenada: retorna elemento 0,1 da matriz
    double y1() const { return e[0][1]; }
    //!Função de coordenada: retorna elemento 0,2 da matriz
    double z1() const { return e[0][2]; }
    //!Função de coordenada: retorna elemento 1,0 da matriz
    double x2() const { return e[1][0]; }
    //!Função de coordenada: retorna elemento 1,1 da matriz
    double y2() const { return e[1][1]; }
    //!Função de coordenada: retorna elemento 1,2 da matriz
    double z2() const { return e[1][2]; }
    //!Função de coordenada: retorna elemento 2,0 da matriz
    double x3() const { return e[2][0]; }
    //!Função de coordenada: retorna elemento 2,1 da matriz
    double y3() const { return e[2][1]; }
    //!Função de coordenada: retorna elemento 2,2 da matriz
    double z3() const { return e[2][2]; }
    //!Função de coordenada: retorna elemento 2,3 da matriz
    double w3() const { return e[2][3]; }
    //!Função de coordenada: retorna elemento 3,0 da matriz
    double x4() const { return e[3][0]; }
    //!Função de coordenada: retorna elemento 3,1 da matriz
    double y4() const { return e[3][1]; }
    //!Função de coordenada: retorna elemento 3,2 da matriz
    double z4() const { return e[3][2]; }
    //!Função de coordenada: retorna elemento 3,3 da matriz
    double w4() const { return e[3][3]; }

    //!Operação de -: Realização a inversão dos valores guardados na matrix
    mat4 operator-() const { 
        return mat4(-e[0][0], -e[0][1], -e[0][2], -e[0][3],
                    -e[1][0], -e[1][1], -e[1][2], -e[1][3],
                    -e[2][0], -e[2][1], -e[2][2], -e[2][3],
                    -e[3][0], -e[3][1], -e[3][2], -e[3][3]); 
    }
        
    //!Operação de +: Realiza a soma entre duas matrizes do mesmo tipo e guarda o resultado na mesma matriz
    //\@params: v corresponde a outra matriz da soma.
    mat4& operator+=(const mat4 &v) {

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                e[i][j] += v.e[i][j];
            }
        }

        return *this;
    }

    //!Operação de *: Realiza a multiplicação entre a matriz e um escalar
    //@params: t é o escalar que irá multiplicar os elementos da matriz
    mat4& operator*=(double t) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                e[i][j] *= t;
            }
        }

        return *this;
    }

    //!Operação de /: Realiza a divisão de todos os elementos da matriz por um escalar.
    //\@params: t: corresponde ao escalar que irá dividir toda a matriz
    mat4& operator/=(double t) {
        return *this *= 1/t;
    }
};

// point3 is just an alias for mat4, but useful for geometric clarity in the code.
using point3 = mat4;


// Vector Utility Functions

inline std::ostream& operator<<(std::ostream &out, const mat4 &v) {
    return out << v.e[0][0] << ' ' << v.e[0][1] << ' ' << v.e[0][2] << ' ' << v.e[0][3] << ' ' 
               << v.e[1][0] << ' ' << v.e[1][1] << ' ' << v.e[1][2] << ' ' << v.e[1][3] << ' '
               << v.e[2][0] << ' ' << v.e[2][1] << ' ' << v.e[2][2] << ' ' << v.e[2][3];
}

//!Operação de +: Realiza a soma  elemento a elemento entre duas matrizes resultando numa terceira com os valores correspondentes da soma.
//\@params: u corresponde a primeira matriz da soma. 
//\@params: v corresponde a segunda matriz da soma. 
inline mat4 operator+(const mat4 &u, const mat4 &v) {
    return mat4(u.e[0][0] + v.e[0][0], u.e[0][1] + v.e[0][1],
                u.e[0][2] + v.e[0][2], u.e[0][3] + v.e[0][3],
                u.e[1][0] + v.e[1][0], u.e[1][1] + v.e[1][1],
                u.e[1][2] + v.e[1][2], u.e[1][3] + v.e[1][3],
                u.e[2][0] + v.e[2][0], u.e[2][1] + v.e[2][1],
                u.e[2][2] + v.e[2][2], u.e[2][3] + v.e[2][3],
                u.e[3][0] + v.e[3][0], u.e[3][1] + v.e[3][1],
                u.e[3][2] + v.e[3][2], u.e[3][3] + v.e[3][3]);
}

//!Operação de -: Realiza a subtração  elemento a elemento entre duas matrizes resultando numa terceira com os valores correspondentes da subtração.
//\@params: u corresponde a primeira matriz da subtração. 
//\@params: v corresponde a segunda matriz da subtração. 
inline mat4 operator-(const mat4 &u, const mat4 &v) {
    return mat4(u.e[0][0] - v.e[0][0], u.e[0][1] - v.e[0][1],
                u.e[0][2] - v.e[0][2], u.e[0][3] - v.e[0][3],
                u.e[1][0] - v.e[1][0], u.e[1][1] - v.e[1][1],
                u.e[1][2] - v.e[1][2], u.e[1][3] - v.e[1][3],
                u.e[2][0] - v.e[2][0], u.e[2][1] - v.e[2][1],
                u.e[2][2] - v.e[2][2], u.e[2][3] - v.e[2][3],
                u.e[3][0] - v.e[3][0], u.e[3][1] - v.e[3][1],
                u.e[3][2] - v.e[3][2], u.e[3][3] - v.e[3][3]);
}

//!Operação de *: Realiza a multiplicação  elemento a elemento entre duas matrizes resultando numa terceira com os valores correspondentes da multiplicação.
// \@params: u corresponde a primeira matriz da multiplicação. 
// \@params: v corresponde a segunda matriz da multiplicação. 
inline mat4 operator*(const mat4 &u, const mat4 &v) {
    return mat4(u.e[0][0] * v.e[0][0], u.e[0][1] * v.e[0][1],
                u.e[0][2] * v.e[0][2], u.e[0][3] * v.e[0][3],
                u.e[1][0] * v.e[1][0], u.e[1][1] * v.e[1][1],
                u.e[1][2] * v.e[1][2], u.e[1][3] * v.e[1][3],
                u.e[2][0] * v.e[2][0], u.e[2][1] * v.e[2][1],
                u.e[2][2] * v.e[2][2], u.e[2][3] * v.e[2][3],
                u.e[3][0] * v.e[3][0], u.e[3][1] * v.e[3][1],
                u.e[3][2] * v.e[3][2], u.e[3][3] * v.e[3][3]);
}

//!Operação de *: Realiza a multiplicação de todos os elementos da matriz por um escalar.
//\@params: t corresponde ao escalar que irá multiplicar os elementos da matriz. 
//\@params: v corresponde a matriz a ser multiplicada.
inline mat4 operator*(double t, const mat4 &v) {
    return mat4(t*v.e[0][0], t*v.e[0][1],
                t*v.e[0][2], t*v.e[0][3],
                t*v.e[1][0], t*v.e[1][1],
                t*v.e[1][2], t*v.e[1][3],
                t*v.e[2][0], t*v.e[2][1],
                t*v.e[2][2], t*v.e[2][3],
                t*v.e[3][0], t*v.e[3][1],
                t*v.e[3][2], t*v.e[3][3]);
}

//!Operação de *: Realiza a multiplicação de todos os elementos da matriz por um escalar.
//\@params: v corresponde a matriz a ser multiplicada. 
//\@params: t corresponde ao escalar que irá multiplicar os elementos da matriz.
inline mat4 operator*(const mat4 &v, double t) {
    return t * v;
}

//!Operação de /: Realiza a divisão de todos os elementos da matriz por um escalar.
//\@params: v corresponde a matriz a ser multiplicada. 
//\@params: t corresponde ao escalar que irá multiplicar os elementos da matriz.
inline mat4 operator/(mat4 v, double t) {
    return (1/t) * v;
}

//!dot product: Realiza a multiplicação entre as matrizes resultando em uma nova com o resultado dessa multiplicação.
//\@params: u corresponde a primeira matriz da multiplicação matricial. 
//\@params: v corresponde a segunda matriz da multiplicação matricial.
inline mat4 dot(const mat4 &u, const mat4 &v) {
    return mat4(
        u.e[0][0] * v.e[0][0] + u.e[0][1] * v.e[1][0] + u.e[0][2] * v.e[2][0] + u.e[0][3] * v.e[3][0],
        u.e[0][0] * v.e[0][1] + u.e[0][1] * v.e[1][1] + u.e[0][2] * v.e[2][1] + u.e[0][3] * v.e[3][1],
        u.e[0][0] * v.e[0][2] + u.e[0][1] * v.e[1][2] + u.e[0][2] * v.e[2][2] + u.e[0][3] * v.e[3][2],
        u.e[0][0] * v.e[0][3] + u.e[0][1] * v.e[1][3] + u.e[0][2] * v.e[2][3] + u.e[0][3] * v.e[3][3],

        u.e[1][0] * v.e[0][0] + u.e[1][1] * v.e[1][0] + u.e[1][2] * v.e[2][0] + u.e[1][3] * v.e[3][0],
        u.e[1][0] * v.e[0][1] + u.e[1][1] * v.e[1][1] + u.e[1][2] * v.e[2][1] + u.e[1][3] * v.e[3][1],
        u.e[1][0] * v.e[0][2] + u.e[1][1] * v.e[1][2] + u.e[1][2] * v.e[2][2] + u.e[1][3] * v.e[3][2],
        u.e[1][0] * v.e[0][3] + u.e[1][1] * v.e[1][3] + u.e[1][2] * v.e[2][3] + u.e[1][3] * v.e[3][3],

        u.e[2][0] * v.e[0][0] + u.e[2][1] * v.e[1][0] + u.e[2][2] * v.e[2][0] + u.e[2][3] * v.e[3][0],
        u.e[2][0] * v.e[0][1] + u.e[2][1] * v.e[1][1] + u.e[2][2] * v.e[2][1] + u.e[2][3] * v.e[3][1],
        u.e[2][0] * v.e[0][2] + u.e[2][1] * v.e[1][2] + u.e[2][2] * v.e[2][2] + u.e[2][3] * v.e[3][2],
        u.e[2][0] * v.e[0][3] + u.e[2][1] * v.e[1][3] + u.e[2][2] * v.e[2][3] + u.e[2][3] * v.e[3][3],

        u.e[3][0] * v.e[0][0] + u.e[3][1] * v.e[1][0] + u.e[3][2] * v.e[2][0] + u.e[3][3] * v.e[3][0],
        u.e[3][0] * v.e[0][1] + u.e[3][1] * v.e[1][1] + u.e[3][2] * v.e[2][1] + u.e[3][3] * v.e[3][1],
        u.e[3][0] * v.e[0][2] + u.e[3][1] * v.e[1][2] + u.e[3][2] * v.e[2][2] + u.e[3][3] * v.e[3][2],
        u.e[3][0] * v.e[0][3] + u.e[3][1] * v.e[1][3] + u.e[3][2] * v.e[2][3] + u.e[3][3] * v.e[3][3]
        );
}


#endif