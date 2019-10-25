#include <iostream>

#include "read.h"
#include "graph.h"

using namespace std;

int main(int argc, char *argv[]) {
    graph test(false);
    char file[]="airports.json";
    Read<graph> r(test,file);
   	test.kruskal();
    return EXIT_SUCCESS;
}