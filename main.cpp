#include <iostream>

#include "read.h"
#include "graph.h"

using namespace std;

int main(int argc, char *argv[]) {
    graph test(false);
    char file[]="airports.json";
    Read<graph> r(test,file);
   	graph afterKruskal = test.kruskal();
   	if(test.bipartito()){cout<<"es bipartito"<<endl;}
   	else{cout<<"no es bipartito"<<endl;}
    return EXIT_SUCCESS;
}