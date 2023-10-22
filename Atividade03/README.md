# Atividade 03

Nessa atividade o professor deu a tarefa ao aluno de criar uma classe faz a leitura de arquivos .obj. Para isso a classe ObjReader foi criada e seu conteúdos se encontram no arquivo ObjReader.h.

Essa classe possui as seguintes funções:
 - Construtor,
 - get_file_read,
 - open_file,
 - read_file,
 - write_file,
 - close_file.

Detalhando agora cada uma das funções criadas acima:
### Construtor:
Params: file_reader: (string) Nome do arquivo a ser lido. file_writer: (string) Nome do arquivo a ser escrito. 
Essa função é responsavel por instanciar um objeto da classe ObjReader e recebe os nomes dos arquivos que o objeto vai tratar durante o uso.

### get_file_read:
Retorna o valor de uma variavel interna do código, que é responsavel por armazenar os conteúdos lidos de um arquivo especificado.

### open_file:
Função responsável por fazer a abertura do arquivo a ser lido. É necessário executar esta função antes das outras, pois através dela que é possivel realizar operações de leitura e escrita.
### read_file:
Função responsável fazer a leitura do arquivo especificado no construturor e armazenar em uma variavel interna da classe.
### write_file:
Função responsável por fazer a escrita do arquivo lido em outro arquivo cujo nome fora fornecido no construtor.
### close_file:
Função responsável por realizar o fechamento do arquivo de leitura.
