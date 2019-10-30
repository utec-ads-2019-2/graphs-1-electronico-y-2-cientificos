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
    char file[]="pruebas.json";
    Read<graph> r(test,file);
    test.print_graph();
}
/*
TEST_CASE("GIVEN A GRAPH TO GET DENSITY")
{



}
TEST_CASE("GIVEN A GRAPH TO FIND EDGES AND NODES")
{


}
TEST_CASE("GIVE A GRAPH TO GET A MST BY KRUSKAL ALGORITHM")
{



}
TEST_CASE("GIVEN A GRAPH TO GET A MST BY PRIM ALGORITHM ")
{


}
 */