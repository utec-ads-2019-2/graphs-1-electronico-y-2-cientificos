#include "iostream"
#include "read.h"
#include "graph.h"
#include "edge.h"
using namespace std;

int main(int argc, char *argv[]) {
    graph test(false);
    char file[]="pruebas.json";
    Read<graph> r(test,file);
    //graph kruskal = test.kruskal();
    graph prim = test.primMST("1");
    if(test.bipartito()){cout<<"es bipartito"<<endl;}
   	else{cout<<"no es bipartito"<<endl;}
    cout<<test.isConnected()<<endl;
   // test.print_graph();
    cout<<"Ahora vamos a printear el kruskal "<<endl;
    //kruskal.print_graph();
    return EXIT_SUCCESS;
}