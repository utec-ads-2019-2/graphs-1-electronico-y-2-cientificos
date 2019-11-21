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
#include "write.h"

using namespace std;

int main(int argc, char *argv[]) {
    //graph test(true);
    //char file[]="pruebas.json";
    graph test(false);
    char file[]="airports.json";
    Read<graph> r(test,file);
    //cout<<test.isConnected()<<endl;
    //test.print_graph();
    //graph MSTKruskal = test.kruskal();
    graph prueba = test.AStar("7252","5501");
    //auto prueba = test.dijkstra("3");
    //cout<<"estoy vivo"<<endl;
    //prueba.print_graph();
    //MSTKruskal.print_graph();
    CWrite<graph> w(prueba,"impreso.json");
    /*
   	graph MSTKruskal = test.kruskal();
   	//graph MSTKruskal = test.kruskal();
    if(test.bipartito()){cout<<"es bipartito"<<endl;}
=======
using namespace std;

int main(int argc, char *argv[]) {

    graph test(true);
    char file[]="pruebas.json";
    Read<graph> r(test,file);
    //cout<<test.isConnected()<<endl;
    test.print_graph();
    graph prueba = test.AStar("1","1");
    graph d = test.dijkstra("3");
    d.print_graph();
   	//graph MSTKruskal = test.kruskal();
   	//graph MSTKruskal = test.kruskal();
    /*if(test.bipartito()){cout<<"es bipartito"<<endl;}
>>>>>>> 1d1a94738ea7940586d9746b91e277f7250e2866
   	else{cout<<"no es bipartito"<<endl;}
    cout<<test.isConnected()<<endl;
    test.print_graph();
    cout<<"Ahora vamos a printear el kruskal "<<endl;
    MSTKruskal.print_graph();
    MSTKruskal.removeNode("1");
    cout<<"after remove"<<endl;
<<<<<<< HEAD
    MSTKruskal.print_graph();
    //MSTKruskal.print_graph();*/

    //MSTKruskal.print_graph();
    //MSTKruskal.print_graph();

    return EXIT_SUCCESS;
} 