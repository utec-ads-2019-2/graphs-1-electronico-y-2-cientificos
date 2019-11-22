#ifndef NODE_H
#define NODE_H
#include <cmath>
#include <iostream>
template <typename G>
class Node {
public:
    typedef typename G::N N;
    typedef typename G::EdgeSeq EdgeSeq;

    N data;
    EdgeSeq edges,edges_from;
    double x, y;
    double heuristic_value;

public:
    Node(N data):data(data){};
    Node(N data, double x, double y):data(data),x(x),y(y){};
    Node(Node* node):data(node->get_data()),x(node->get_posx()),y(node->get_posy()){};

    ~Node(){
    	for(auto ed : edges){
    		delete ed;
    	}
    	
    }

    N& get_data(){return data;}
    EdgeSeq& get_edges(){return edges;}
    EdgeSeq& get_edges_from(){return edges_from;}
    void setData(N newData) {data = newData;}

    double get_posx(){return x;}
    void setX(double X){x = X;}

    double get_posy(){return y;}
    void setY(double Y){y = Y;}


    void set_heuristic(Node* to){
        heuristic_value = sqrt(pow(this->x-(to)->get_posx())+pow(this->y-(to)->get_posy()));
    }


};

#endif