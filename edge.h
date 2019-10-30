#ifndef EDGE_H
#define EDGE_H

#include <cmath>

template <typename G>
class Edge {

    typedef typename G::E E;
    typedef typename G::node node;

    E data;
    node* nodes[2];

public:
    

    Edge(node* from, node* to){
        nodes[0]=from;
        nodes[1]=to;
        data=pow(pow(from->get_posx()-to->get_posx(),2)+pow(from->get_posy()-to->get_posy(),2),0.5);
    };


    E& get_data(){return data;}
    node** get_nodes(){return nodes;}
    
    Edge(node* from, node* to, E d){
        nodes[0] = from;
        nodes[1] = to;
        data = d;
    }
};

#endif