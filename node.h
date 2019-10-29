#ifndef NODE_H
#define NODE_H

template <typename G>
class Node {
private:
    typedef typename G::N N;
    typedef typename G::EdgeSeq EdgeSeq;

    N data;
    EdgeSeq edges,edges_from;
    double x, y;
public:
    Node(N data):data(data){};
    Node(N data, double x, double y):data(data),x(x),y(y){};

    N get_data(){return data;}
    EdgeSeq& get_edges(){return edges;}
    EdgeSeq& get_edges_from(){return edges_from;}
    
    void setData(N newData) {data = newData;}

    double get_posx(){return x;}
    void setX(double X){x = X;}

    double get_posy(){return y;}
    void setY(double Y){y = Y;}

};

#endif