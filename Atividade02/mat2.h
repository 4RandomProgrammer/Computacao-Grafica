#ifndef MAT2_H
#define MAT2_H

#include <cmath>
#include <iostream>


using std::sqrt;

class mat2 {
  public:
    double e[2][2];
    //!Construtor base: inicializa a função com zeros.
    mat2() : e{{0,0}, {0,0}} {}
    //!Construtor com params:
    //\@params: e0 elemento 0,0 da matriz
    //\@params: e1 elemento 0,1 da matriz
    //\@params: f0 elemento 1,0 da matriz
    //\@params: f1 elemento 1,1 da matriz
    mat2(double e0, double e1, double f0, double f1) : e{{e0, e1}, {f0, f1}} {}
    //!Função de coordenada: retorna elemento 0,0 da matriz
    double x1() const { return e[0][0]; }
    //!Função de coordenada: retorna elemento 0,1 da matriz
    double y1() const { return e[0][1]; }
    //!Função de coordenada: retorna elemento 1,0 da matriz
    double x2() const { return e[1][0]; }
    //!Função de coordenada: retorna elemento 1,1 da matriz
    double y2() const { return e[1][1]; }

    //!Operação de -: Realização a inversão dos valores guardados na matrix
    mat2 operator-() const { return mat2(-e[0][0], -e[0][1],-e[1][0], -e[1][1]); }

    //!Operação de +: Realiza a soma entre duas matrizes do mesmo tipo e guarda o resultado na mesma matriz
    //\@params: v corresponde a outra matriz da soma. 
    mat2& operator+=(const mat2 &v) {
        e[0][0] += v.e[0][0];
        e[0][1] += v.e[0][1];
        e[1][0] += v.e[1][0];
        e[1][1] += v.e[1][1];
        return *this;
    }

    //!Operação de *: Realiza a multiplicação entre a matriz e um escalar
    //@params: t é o escalar que irá multiplicar os elementos da matriz
    mat2& operator*=(double t) {
        e[0][0] *= t;
        e[0][1] *= t;
        e[1][0] *= t;
        e[1][1] *= t;
        return *this;
    }
    //!Operação de /: Realiza a divisão de todos os elementos da matriz por um escalar.
    //\@params: t: corresponde ao escalar que irá dividir toda a matriz
    mat2& operator/=(double t) {
        return *this *= 1/t;
    }
};

// point3 is just an alias for mat2, but useful for geometric clarity in the code.
using point2x2 = mat2;


// Vector Utility Functions

inline std::ostream& operator<<(std::ostream &out, const mat2 &v) {
    return out << v.e[0][0] << ' ' << v.e[0][1] << ' ' << v.e[1][0] << ' ' << v.e[1][1];
}

//!Operação de +: Realiza a soma  elemento a elemento entre duas matrizes resultando numa terceira com os valores correspondentes da soma.
//\@params: u corresponde a primeira matriz da soma. 
//\@params: v corresponde a segunda matriz da soma. 
inline mat2 operator+(const mat2 &u, const mat2 &v) {
    return mat2(u.e[0][0] + v.e[0][0], u.e[0][1] + v.e[0][1], u.e[1][0] + v.e[1][0], u.e[1][1] + v.e[1][1]);
}

//!Operação de -: Realiza a subtração  elemento a elemento entre duas matrizes resultando numa terceira com os valores correspondentes da subtração.
//\@params: u corresponde a primeira matriz da subtração. 
//\@params: v corresponde a segunda matriz da subtração. 
inline mat2 operator-(const mat2 &u, const mat2 &v) {
    return mat2(u.e[0][0] - v.e[0][0], u.e[0][1] - v.e[0][1], u.e[1][0] - v.e[1][0], u.e[1][1] - v.e[1][1]);
}

//!Operação de *: Realiza a multiplicação  elemento a elemento entre duas matrizes resultando numa terceira com os valores correspondentes da multiplicação.
//\@params: u corresponde a primeira matriz da multiplicação. 
//\@params: v corresponde a segunda matriz da multiplicação. 
inline mat2 operator*(const mat2 &u, const mat2 &v) {
    return mat2(u.e[0][0] * v.e[0][0], u.e[0][1] * v.e[0][1], u.e[1][0] * v.e[1][0], u.e[1][1] * v.e[1][1]);
}

//!Operação de *: Realiza a multiplicação de todos os elementos da matriz por um escalar.
//\@params: t corresponde ao escalar que irá multiplicar os elementos da matriz. 
//\@params: v corresponde a matriz a ser multiplicada. 
inline mat2 operator*(double t, const mat2 &v) {
    return mat2(t*v.e[0][0], t*v.e[0][1], t*v.e[1][0], t*v.e[1][1]);
}

//!Operação de *: Realiza a multiplicação de todos os elementos da matriz por um escalar.
//\@params: v corresponde a matriz a ser multiplicada. 
//\@params: t corresponde ao escalar que irá multiplicar os elementos da matriz. 
inline mat2 operator*(const mat2 &v, double t) {
    return t * v;
}

//!Operação de /: Realiza a divisão de todos os elementos da matriz por um escalar.
//\@params: v corresponde a matriz a ser multiplicada. 
//\@params: t corresponde ao escalar que irá multiplicar os elementos da matriz. 
inline mat2 operator/(mat2 v, double t) {
    return (1/t) * v;
}

//!dot product: Realiza a multiplicação entre as matrizes resultando em uma nova com o resultado dessa multiplicação.
//\@params: u corresponde a primeira matriz da multiplicação matricial. 
//\@params: v corresponde a segunda matriz da multiplicação matricial. 
inline mat2 dot(const mat2& u, const mat2& v) {
    return mat2(
        u.e[0][0] * v.e[0][0] + u.e[0][1] * v.e[1][0],
        u.e[0][0] * v.e[0][1] + u.e[0][1] * v.e[1][1],
        u.e[1][0] * v.e[0][0] + u.e[1][1] * v.e[1][0],
        u.e[1][0] * v.e[0][1] + u.e[1][1] * v.e[1][1]
        );
}


#endif