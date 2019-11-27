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

    graph test(false);
    char file[]="pruebas.json";
    Read<graph> r(test,file);
    //cout<<test.isConnected()<<endl;
    //test.print_graph();
    //graph MSTKruskal = test.kruskal();
    //graph prueba = test.AStar("7252","3199");
    graph prueba = test.dijkstra("1");
    //graph prueba = test.Bellman("1");
    //auto prueba = test.dijkstra("3");
    //MSTKruskal.print_graph();
    CWrite<graph> w(prueba,"impreso.json");


    return EXIT_SUCCESS;
} 