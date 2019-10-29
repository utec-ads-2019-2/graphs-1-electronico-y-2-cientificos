#include "iostream"
#include "read.h"
#include "graph.h"
#include "edge.h"
using namespace std;

int main(int argc, char *argv[]) {
    graph test(true);
    char file[]="pruebas.json";
    Read<graph> r(test,file);
   	graph afterKruskal = test.kruskal();
    if(test.bipartito()){cout<<"es bipartito"<<endl;}
   	else{cout<<"no es bipartito"<<endl;}
    cout<<test.isConnected()<<endl;
    return EXIT_SUCCESS;
}