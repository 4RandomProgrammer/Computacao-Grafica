#ifndef VEC2_H
#define VEC2_H

#include <cmath>
#include <iostream>

using std::sqrt;

class vec2 {

  public:
    double e[2];
    //!Construtor base: inicializa a função com zeros.
    vec2() : e{0,0} {}
    //!Construtor com params:
    //! \@params: e0 elemento 0 da matriz
    //! \@params: e1 elemento 1 da matriz
    vec2(double e0, double e1) : e{e0, e1} {}
    
    //!Função de coordenada: retorna elemento 0 do vetor
    double x() const { return e[0]; }
    //!Função de coordenada: retorna elemento 1 do vetor
    double y() const { return e[1]; }

    //!Operação de -: Realização a inversão dos valores guardados no vetor
    vec2 operator-() const { return vec2(-e[0], -e[1]); }
    //!retorna o elemento na posição i do vetor, não previne contra violação de memória, ou seja, pode acessar fora do vetor
    double operator[](int i) const { return e[i]; }
    //!retorna o elemento na posição i do vetor, não previne contra violação de memória, ou seja, pode acessar fora do vetor
    double& operator[](int i) { return e[i]; }

    //!Operação de +: Realiza a soma entre dois vetores do mesmo tipo e guarda o resultado no mesmo vetor
    // \@params: v corresponde a outro vetor da soma. 
    vec2& operator+=(const vec2 &v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        return *this;
    }

    //!Operação de *: Realiza a multiplicação entre o vetor e um escalar
    //@params: t é o escalar que irá multiplicar os elementos do vetor
    vec2& operator*=(double t) {
        e[0] *= t;
        e[1] *= t;
        return *this;
    }

    //!Operação de /: Realiza a divisão de todos os elementos do vetor por um escalar.
    // \@params: t: corresponde ao escalar que irá dividir todo o vetor
    vec2& operator/=(double t) {
        return *this *= 1 / t;
    }
    
    //!Operação que faz a raiz  dos elementos de um vetor, necessária para a normalização de vetores
    double length() const {
        return sqrt(length_squared());
    }

    //!Operação que calcula a soma dos quadrados dos elementos de um vetor, necessária para a normalização de vetores
    double length_squared() const {
        return e[0]*e[0] + e[1]*e[1];
    }
};

// point3 is just an alias for vec2, but useful for geometric clarity in the code.
using point2 = vec2;


// Vector Utility Functions

inline std::ostream& operator<<(std::ostream &out, const vec2 &v) {
    return out << v.e[0] << ' ' << v.e[1];
}

//!Operação de +: Realiza a soma  elemento a elemento entre duois vetores resultando em um terceiro com os valores correspondentes da soma.
// \@params: u corresponde a primeiro vetor da soma. 
// \@params: v corresponde a segundo vetor da soma.
inline vec2 operator+(const vec2 &u, const vec2 &v) {
    return vec2(u.e[0] + v.e[0], u.e[1] + v.e[1]);
}

//!Operação de -: Realiza a subtração  elemento a elemento de dois vetores resultando em um terceiro com os valores correspondentes da subtração.
// \@params: u corresponde a primeiro vetor da subtração. 
// \@params: v corresponde a segundo vetor da subtração. 
inline vec2 operator-(const vec2 &u, const vec2 &v) {
    return vec2(u.e[0] - v.e[0], u.e[1] - v.e[1]);
}

//!Operação de *: Realiza a multiplicação  elemento a elemento de dois vetores resultando em um terceiro com os valores correspondentes da multiplicação.
// \@params: u corresponde a primeiro vetor da multiplicação. 
// \@params: v corresponde a segundo vetor da multiplicação. 
inline vec2 operator*(const vec2 &u, const vec2 &v) {
    return vec2(u.e[0] * v.e[0], u.e[1] * v.e[1]);
}

//!Operação de *: Realiza a multiplicação de todos os elementos de um vetor por um escalar.
// \@params: t corresponde ao escalar que irá multiplicar os elementos do vetor. 
// \@params: v corresponde a vetor a ser multiplicado.
inline vec2 operator*(double t, const vec2 &v) {
    return vec2(t*v.e[0], t*v.e[1]);
}

//!Operação de *: Realiza a multiplicação de todos os elementos de um vetor por um escalar.
// \@params: v corresponde a vetor a ser multiplicado.
// \@params: t corresponde ao escalar que irá multiplicar os elementos do vetor. 
inline vec2 operator*(const vec2 &v, double t) {
    return t * v;
}

//!Operação de /: Realiza a divisão de todos os elementos de um vetor por um escalar.
// \@params: v corresponde ao vetor a ser dividido. 
// \@params: t corresponde ao escalar que irá multiplicar os elementos do vetor.
inline vec2 operator/(vec2 v, double t) {
    return (1/t) * v;
}

//!dot product: realiza a operação de multiplicação de vetores, resultando no módulo dos mesmos.
// \@params: u corresponde ao primeiro vetor da operação. 
// \@params: v corresponde ao segundo vetor da operação. 
inline double dot(const vec2 &u, const vec2 &v) {
    return u.e[0] * v.e[0] + u.e[1] * v.e[1];
}


//!Operação de normalização: faz a normalização de um vetor para que ele fique com valores entre 1 e -1
// \@params: v o vetor em questão para ser normalizado.
inline vec2 unit_vector(vec2 v) {
    return v / v.length();
}

#endif