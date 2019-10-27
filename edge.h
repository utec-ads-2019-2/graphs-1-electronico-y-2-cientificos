#ifndef EDGE_H
#define EDGE_H

#include <cmath>

template <typename G>
class Edge {
public:
    typedef typename G::E E;
    typedef typename G::node node;

    E data;
    node* nodes[2];

    Edge(node* from, node* to){
        nodes[0]=from;
        nodes[1]=to;
        data=pow(pow(from->x-to->x,2)+pow(from->y-to->y,2),0.5);
    };

    Edge(node* from, node* to, E d){
        nodes[0] = from;
        nodes[1] = to;
        data = d;
    }

    E getData()
    {
        return data;
    }
};

#endif