# Atividade 2

Desenvolver classes para manipulação de vet2,vet4,mat2,mat3,mat4 e desenvolver testes para essas classes.

As classes desenvolvidas para esse projeto foram:

- vec2
- vec4
- mat2
- mat3
- mat4

A classe vec3 apesar de constar no repositório, não foi implementada por mim, pois ela é fornecida nos tutoriais que estamos seguindo para as atividades. Apesar disso, essa classe foi base para as implementações de todas as outras. Utilizei ela como modelo para a criação das outras classes.
Com isso, cada classe possui funções para manipulação para matrizes e vetores. E operações entre esses elementos.
Então cada classes possui as seguintes funções:

- Construtor:
- Seleções de coordenadas especifica(Ex:x1(),y1()): retorna o elemento especifico daquela coordenada.
- operador de menos: realiza a subtração entre matrizes e também realiza a inversão dos valores colocados na estrutura em questão;
- operador de +: Essa função soma dois objetos da mesma classe, sendo ela responsável ou por alterar a estrtura que recebe a soma ou por criar uma nova estrutura com o resultado da soma;
- operador de *: A multiplicação pode ser feito vide elemento a elemento da estrura, contanto que sejam do mesmo tipo, ou um escalar multiplicando a estrutura.
- operador de /: Realiza a divisão de todos os elementos da estrutura por um escalar.
- dot product: para o caso de vetores é o resultado da mutiplicação entre os elementos dos vetores e a soma ao final. Para matrizes, é essa função que realiza a multiplicação entre matrizes.

Além disso, na pasta "tests" conta com testes unitários para as funções implementadas em cada classe, assim como as auxiliares contidas em cada uma. A biblioteca de testes utilizada foi a "[Doctests](https://github.com/doctest/doctest)". Essa biblioteca permite fazer assertions básicos para verificar se os valores obtidos estão corretos. As funções utilizadas dela são as mais básicas para verificações de resultados, portanto, ainda há a necessidade de ao longo do curso da matéria explorar mais a biblioteca com o fim de entender toda as funções fornecidads para teste.