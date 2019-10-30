<<<<<<< HEAD
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#ifndef CATCH_CONFIG_MAIN
int main()
{
    return 0;
}
#endif
=======
#include "iostream"
#include "read.h"
#include "graph.h"
#include "edge.h"
#include "write.h"
using namespace std;

int main(int argc, char *argv[]) {
    graph test(false);
    char file[]="pruebas.json";
    Read<graph> r(test,file);

    //graph MSTKruskal = test.kruskal();

    //graph kruskal = test.kruskal();
    graph prim = test.primMST("2");

    if(test.bipartito()){cout<<"es bipartito"<<endl;}
    else{cout<<"no es bipartito"<<endl;}
    cout<<test.isConnected()<<endl;
    test.print_graph();
    cout<<"Ahora vamos a printear el kruskal "<<endl;

    //MSTKruskal.print_graph();
    //char file2[]="escritura.json";
    //CWrite<graph> w(MSTKruskal,file2);

    //kruskal.print_graph();
    prim.print_graph();

    return EXIT_SUCCESS;
}
>>>>>>> 39e8a4ecdfbacadd78d3c94569cef4ed80f981fd
