/*#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "main_test.cpp"
#ifndef CATCH_CONFIG_MAIN

int main() {   
}*/

#include "iostream"
#include "read.h"
#include "graph.h"
#include "edge.h"

using namespace std;

int main(int argc, char *argv[]) {

    graph test(true);
    char file[]="pruebas.json";
    Read<graph> r(test,file);
    //cout<<test.isConnected()<<endl;
    //test.print_graph();
    //graph prueba = test.AStar("1","1");
    test.print_graph();
    graph d = test.dijkstra("1");
    d.print_graph();
   	//graph MSTKruskal = test.kruskal();
   	//graph MSTKruskal = test.kruskal();
    /*if(test.bipartito()){cout<<"es bipartito"<<endl;}
   	else{cout<<"no es bipartito"<<endl;}
    cout<<test.isConnected()<<endl;
    test.print_graph();
    cout<<"Ahora vamos a printear el kruskal "<<endl;
    MSTKruskal.print_graph();
    MSTKruskal.removeNode("1");
    cout<<"after remove"<<endl;
    MSTKruskal.print_graph();*/
    //MSTKruskal.print_graph();
    return EXIT_SUCCESS;
}
