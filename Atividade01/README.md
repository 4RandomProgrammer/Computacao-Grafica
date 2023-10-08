# Atividade 1

A atividade foi se familiarizar com alguns conceitos da parte computação gráfica e gerar imagens base para isso.

Portanto, a classe criada foi a "png_processor" que esta responsável pela geração de imagens.

## Png_processor:
Dentro dessa classe houve a criações de métodos internos como por exemplo, criação de um método para entender se um ponto especifico esta dentro de um triângulo e um método para ajudar no calculo de área de triangulos. Além da criação de um método que inicia as imagens com tamanho especificados dentro da classe(init_png) e também uma função que realiza a escrita da imagem(write_png_file).

### Métodos:
 - render_circle: recebe o nome do arquivo e renderiza um circulo vermelho com centro no ponto 127,127
 - render_gradient: Recebe o nome do arquivo e renderiza um gradiente entre vermelho e azul.
 - render_triangle: Recebe o nome do arquivo do qual a imagem deve ser salva. Renderiza um triângulo verde com base em pontos especificado dentro da função.

 O processo de renderização é igual para todas as imagens e funcionam da seguinte forma: realiza-se a incialização da imagem como uma matriz de altura height e largura width. Depois, dentro dessa matriz é realizada a operação de desenhar a imagem, portanto dentro de cada campo da imagem se coloca um valor que determina a cor daquele pixel. Por fim, converte a matriz para uma imagem png através da utilização de método da biblioteca libpng.