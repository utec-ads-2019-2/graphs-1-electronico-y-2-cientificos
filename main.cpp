/*
#include "node.h"
#include "iostream"
#include "read.h"
#include "graph.h"
#include "edge.h"
int main()
{
    return 0;
}
*/

#include "iostream"
#include "read.h"
#include "graph.h"
#include "edge.h"
#include "write.h"
using namespace std;

int main(int argc, char *argv[]) {
    graph test(true);
    char file[]="pruebas.json";
    Read<graph> r(test,file);

    //graph MSTKruskal = test.kruskal();

    //graph kruskal = test.kruskal();
    //graph prim = test.primMST("2");

    //if(test.bipartito()){cout<<"es bipartito"<<endl;}
    //else{cout<<"no es bipartito"<<endl;}
    //cout<<test.isConnected()<<endl;

    test.floyd();
    //test.print_graph();

    //cout<<"Ahora vamos a printear el kruskal "<<endl;

    //MSTKruskal.print_graph();
    //char file2[]="escritura.json";
    //CWrite<graph> w(MSTKruskal,file2);

    //kruskal.print_graph();
    //prim.print_graph();

    return EXIT_SUCCESS;
}
