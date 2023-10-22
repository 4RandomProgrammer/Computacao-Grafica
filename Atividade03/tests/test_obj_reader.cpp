#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../ObjReader.h"

TEST_CASE("Only Read") {
    ObjReader teste("FinalBaseMesh.obj","onlyRead.txt");

    teste.read_file();

    fstream file_to_read;


    // CHECK(teste.get_file_read() == );

    teste.close_file();

}

TEST_CASE("Read and Write") {
   ObjReader teste("../FinalBaseMesh.obj","teste.txt");

   CHECK (teste.open_file() == 0);
   CHECK(teste.read_file() == 0);
   CHECK(teste.write_file() == 0);
   CHECK(teste.close_file() == 0);
}

TEST_CASE("Read with Errors") {
    ObjReader teste("ASDUIHASDIHUISDA.obj","onlyRead.txt");
    CHECK(teste.open_file() == -1);
    CHECK(teste.close_file() == -1);
    CHECK(teste.write_file() == -1);
    CHECK(teste.read_file() == -1);
}

TEST_CASE("Write with Errors") {
    ObjReader teste("ASDUIHASDIHUISDA.obj","onlyRead.txt");
    teste.open_file();
    CHECK(teste.write_file() == -1);
}
