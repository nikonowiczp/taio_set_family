#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "SetParser.h"

int main (int argc, char *argv[]){
    std::cout << "Hello world";
    auto parser = SetParser();
    parser.ParseFile("Test path");
    return EXIT_SUCCESS;
}