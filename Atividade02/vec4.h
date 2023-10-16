#ifndef VEC4_H
#define VEC4_H

#include <cmath>
#include <iostream>

using std::sqrt;

class vec4 {

  public:
    double e[4];
    //!Construtor base: inicializa a função com zeros.
    vec4() : e{0,0,0,0} {}
    //!Construtor com params:
    //  \@params: e0 elemento 0 da matriz
    //  \@params: e1 elemento 1 da matriz
    //  \@params: e2 elemento 2 da matriz
    //  \@params: e3 elemento 3 da matriz
    vec4(double e0, double e1,double e2, double e3) : e{e0, e1,e2, e3} {}

    //!Função de coordenada: retorna elemento 0 do vetor
    double x() const { return e[0]; }
    //!Função de coordenada: retorna elemento 1 do vetor
    double y() const { return e[1]; }
    //!Função de coordenada: retorna elemento 2 do vetor
    double z() const { return e[2]; }
    //!Função de coordenada: retorna elemento 3 do vetor
    double w() const { return e[3]; }

    //!Operação de -: Realização a inversão dos valores guardados no vetor
    vec4 operator-() const { return vec4(-e[0], -e[1],-e[2], -e[3]); }
    //!retorna o elemento na posição i do vetor, não previne contra violação de memória, ou seja, pode acessar fora do vetor
    double operator[](int i) const { return e[i]; }
    //!retorna o elemento na posição i do vetor, não previne contra violação de memória, ou seja, pode acessar fora do vetor
    double& operator[](int i) { return e[i]; }

    //!Operação de +: Realiza a soma entre dois vetores do mesmo tipo e guarda o resultado no mesmo vetor
    //  \@params: v corresponde a outro vetor da soma.
    vec4& operator+=(const vec4 &v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        e[3] += v.e[3];
        return *this;
    }

    //!Operação de *: Realiza a multiplicação entre o vetor e um escalar
    //  \@params: t é o escalar que irá multiplicar os elementos do vetor
    vec4& operator*=(double t) {
        e[0] *= t;
        e[1] *= t;
        e[3] *= t;
        e[4] *= t;
        return *this;
    }

    //!Operação de /: Realiza a divisão de todos os elementos do vetor por um escalar.
    // \@params: t: corresponde ao escalar que irá dividir todo o vetor
    vec4& operator/=(double t) {
        return *this *= 1/t;
    }

    //!Operação que faz a raiz  dos elementos de um vetor, necessária para a normalização de vetores
    double length() const {
        return sqrt(length_squared());
    }

    //!Operação que calcula a soma dos quadrados dos elementos de um vetor, necessária para a normalização de vetores
    double length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2] + e[3]*e[3];
    }
};

// point3 is just an alias for vec4, but useful for geometric clarity in the code.
using point4 = vec4;


// Vector Utility Functions

inline std::ostream& operator<<(std::ostream &out, const vec4 &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2] << ' ' << v.e[3];
}

//!Operação de +: Realiza a soma  elemento a elemento entre duois vetores resultando em um terceiro com os valores correspondentes da soma.
// \@params: u corresponde a primeiro vetor da soma. 
// \@params: v corresponde a segundo vetor da soma.
inline vec4 operator+(const vec4 &u, const vec4 &v) {
    return vec4(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2], u.e[3] + v.e[3]);
}

//!Operação de -: Realiza a subtração  elemento a elemento de dois vetores resultando em um terceiro com os valores correspondentes da subtração.
// \@params: u corresponde a primeiro vetor da subtração. 
// \@params: v corresponde a segundo vetor da subtração. 
inline vec4 operator-(const vec4 &u, const vec4 &v) {
    return vec4(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2], u.e[3] - v.e[3]);
}

//!Operação de *: Realiza a multiplicação  elemento a elemento de dois vetores resultando em um terceiro com os valores correspondentes da multiplicação.
// \@params: u corresponde a primeiro vetor da multiplicação. 
// \@params: v corresponde a segundo vetor da multiplicação. 
inline vec4 operator*(const vec4 &u, const vec4 &v) {
    return vec4(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2], u.e[3] * v.e[3]);
}

//!Operação de *: Realiza a multiplicação de todos os elementos de um vetor por um escalar.
// \@params: t corresponde ao escalar que irá multiplicar os elementos do vetor. 
// \@params: v corresponde a vetor a ser multiplicado.
inline vec4 operator*(double t, const vec4 &v) {
    return vec4(t*v.e[0], t*v.e[1], t*v.e[2], t*v.e[3]);
}

//!Operação de *: Realiza a multiplicação de todos os elementos de um vetor por um escalar.
// \@params: v corresponde a vetor a ser multiplicado.
// \@params: t corresponde ao escalar que irá multiplicar os elementos do vetor.
inline vec4 operator*(const vec4 &v, double t) {
    return t * v;
}

//!Operação de /: Realiza a divisão de todos os elementos de um vetor por um escalar.
// \@params: v corresponde ao vetor a ser dividido. 
// \@params: t corresponde ao escalar que irá multiplicar os elementos do vetor.
inline vec4 operator/(vec4 v, double t) {
    return (1/t) * v;
}

//!dot product: realiza a operação de multiplicação de vetores, resultando no módulo dos mesmos.
// \@params: u corresponde ao primeiro vetor da operação. 
// \@params: v corresponde ao segundo vetor da operação. 
inline double dot(const vec4 &u, const vec4 &v) {
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2] + u.e[3] * v.e[3];
}

//!Operação de normalização: faz a normalização de um vetor para que ele fique com valores entre 1 e -1
// \@params: v o vetor em questão para ser normalizado.
inline vec4 unit_vector(vec4 v) {
    return v / v.length();
}

#endif