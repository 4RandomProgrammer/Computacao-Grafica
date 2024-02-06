# Trabalho de Computação Gráfica

Nesta pasta encontra-se os arquivos necessários para a execução do trabalho final da matéria de Computação Gráfica que foi ministrada pelo professor Mário Lizier.
Aluno:                          RA:
Luís Felipe Dobner Henriques            771036


## Descrição do projeto:

O objetivo desta atividade é o desenvolvimento de uma animação utilizando as implementações desenvolvidas em aula.

O grupo poderá ser formado por até 4 pessoas. Peço que um dos membros do grupo faça um comentário nesta postagem com a composição e o link do github do projeto.

O projeto deve gerar uma animação com pelo menos 5 segundos. Como a implementação não é otimizada e não temos muito poder de processamento, a animação pode ter uma baixa resolução e poucos quadros por segundo. A composição dos quadros pode ser realizada com ferramenta externa (exportando em um formato avi/mp4/etc), mas a geração das imagens deve utilizar as implementações dos membros do grupo.

Utilize pelo menos 3 objetos, sendo pelo menos um deles formado por triângulos. Utilize materiais difusos e reflexivos. Faça pelo menos um movimento com a câmera e outro com pelo menos um dos objetos.

O projeto será avaliado considerando os seguinte requisitos:
- Atendimento aos requisitos;
- Documentação do código e de apesentação do projeto;
- Qualidade visual final da animação

## Animação realizada:
A animação criada pelo aluno contém 4 objetos diferentes. Um cubo de cor sólida, uma esfera metálica e um cubo com textura de vidro. Há também uma esfera grande embaixo desses objetos simulando o chão. A animação começa com o circulo se mexendo em direção ao cubo mais distante e a visão da camera o acompanha o obeto em seu movimento. Após isso, a camera se desloca para ficar perpendicular as cubos e ao final a esfera realiza o movimento de volta.

## Atendimento dos requisitos:

O projeto deve gerar uma animação com pelo menos 5 segundos:
A geração das imagens deve utilizar as implementações dos membros do grupo: a implementação foi criada por mim, como pode ser conferida nas pastas de outras atividades. Algumas adaptações foram feitas baseadas nessas implementações com o intuito de facilitar o uso e a leitura do código.
Utilize pelo menos 3 objetos sendo pelo menos um deles formado por triângulos: foram usados dois cubos e duas esferas (totalizando quatro objetos). O cubo é um objeto formado por triângulos (cada face do cubo é formada por dois triângulos)
Utilize materiais difusos e reflexivos: uma esfera e um cubo utilizam materiais difusos e enquaunto os outros objetos utilizam de material reflexivo (metálico e vidro)
Faça pelo menos um movimento com a câmera e outro com pelo menos um dos objetos: As esferas faz o movimento de ida e volta e a camera move tanto de posição quanto o ponto focal do qual olha.

## Como executar:

É necessário compilar o código através do comando:
```Shell
g++ reduced_main.cc -o nome_desejado -lpng
```
E depois executa-lo:
```Shell
./nome_desejado
```

## Documentação:
Para uma visão mais detalhada do código pode-se baixar essas pasta e utilizar a ferramenta do Doxygen para a ver todas as classes documentadas. 