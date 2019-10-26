#include "iostream"
#include "read.h"
#include "graph.h"
#include "edge.h"
using namespace std;

int main(int argc, char *argv[])
{
    graph test(false);
    char file[]="airports.json";
    Read<graph> r(test, file);
    graph afterPrim =test.primMST("Cherry Capital Airport");


    return EXIT_SUCCESS;
}