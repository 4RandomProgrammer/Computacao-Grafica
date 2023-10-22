#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../ObjReader.h"

//! Função de teste, verifica se a leitura de um arquivo funciona corretamente e compara com o arquivo de mesmo conteúdo.
TEST_CASE("Only Read") {
    ObjReader teste("../FinalBaseMesh.obj","onlyRead.txt");

    CHECK(teste.open_file() == 0);
    CHECK(teste.read_file() == 0);
    
    CHECK(teste.write_file() == 0);

    ObjReader checker("onlyRead.txt","");

    CHECK(checker.open_file() == 0);
    CHECK(checker.read_file() == 0);

    CHECK(teste.get_file_read() == checker.get_file_read());


    CHECK (teste.close_file() == 0);

}

//! Função de teste, verifica se a leitura  e escrita de um arquivo funciona corretamente e compara com o arquivo de mesmo conteúdo.
TEST_CASE("Read and Write") {
   ObjReader teste("../FinalBaseMesh.obj","teste.txt");

   CHECK (teste.open_file() == 0);
   CHECK(teste.read_file() == 0);
   CHECK(teste.write_file() == 0);
   CHECK(teste.close_file() == 0);

    ObjReader checker("teste.txt","");

    CHECK(checker.open_file() == 0);
    CHECK(checker.read_file() == 0);

    CHECK(teste.get_file_read() == checker.get_file_read());
}

// Testa os casos de erros de leitura, que caso um arquivo fornecido com nome incorreto é impossibilita-se de realizer qualquer operação
TEST_CASE("Read with Errors") {
    ObjReader teste("ASDUIHASDIHUISDA.obj","onlyRead.txt");
    CHECK(teste.open_file() == -1);
    CHECK(teste.close_file() == -1);
    CHECK(teste.write_file() == -1);
    CHECK(teste.read_file() == -1);
}

// Testa os casos de erros de escrita, que caso um arquivo fornecido com nome incorreto é impossibilita-se de realizer qualquer operação
TEST_CASE("Write with Errors") {
    ObjReader teste("ASDUIHASDIHUISDA.obj","onlyRead.txt");
    teste.open_file();
    CHECK(teste.write_file() == -1);
}
