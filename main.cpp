#include <iostream>

#include "graph.h"
#include "read.h"

using namespace std;

int main(int argc, char *argv[]) {
    graph test;
    char file[]="airports.json";
    Read<graph> r(file);
    return EXIT_SUCCESS;
}