#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "node.h"
#include "iostream"
#include "read.h"
#include "graph.h"
#include "edge.h"

TEST_CASE("GIVEN A GRAPH TO READ")
{
    graph test(false);
    char file[]="airports.json";
    Read<graph> r(test,file);
    THEN("PRINT GRAPH")
    {test.print_graph();};
}
TEST_CASE("GIVE A GRAPH TO GET A MST BY KRUSKAL ALGORITHM")
{
    graph test1(false);
    char file[]="pruebas.json";
    Read<graph> r(test1,file);
    graph kruskal = test1.kruskal();
    REQUIRE(test1.nodes.size()==kruskal.nodes.size());
    REQUIRE(kruskal.isConnected());
    THEN("PRINT MST KRUSKAL")
    {
        kruskal.print_graph();
    };

}
TEST_CASE("GIVEN A GRAPH TO GET DENSITY") {
    graph test2(false);
    char file[] = "airports.json";
    Read<graph> r(test2, file);
    float density = test2.graphDensity();
    REQUIRE(density == test2.graphDensity());
}
TEST_CASE("GIVEN A GRAPH TO FIND EDGES AND NODES")
{
    graph test3(false);
    char file[] = "airports.json";
    Read<graph> r(test3, file);
        REQUIRE(test3.findNode("6972"));
        REQUIRE(test3.findNode("4027"));
        REQUIRE(test3.findEdge("4026", "3448"));
        REQUIRE(test3.findEdge("4029", "6485"));
}

TEST_CASE("GIVEN A GRAPH TO GET A MST BY PRIM ALGORITHM ")
{
    graph test4(false);
    char file[]="pruebas.json";
    Read<graph> r(test4,file);
    graph prim = test4.primMST("1");
    REQUIRE(test4.nodes.size()==prim.nodes.size());
    REQUIRE(prim.isConnected());
    THEN("PRINT MST PRIM")
    {
        prim.print_graph();
    };

}
