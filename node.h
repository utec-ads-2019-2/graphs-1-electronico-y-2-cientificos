#ifndef NODE_H
#define NODE_H

template <typename G>
class Node {
public:
    typedef typename G::N N;
    typedef typename G::EdgeSeq EdgeSeq;

    N data;
    EdgeSeq edges;
    double x, y;
public:
    Node(N data):data(data){};
    Node(N data, double x, double y):data(data),x(x),y(y){};
    N getData() {return data;}
    void setData(N newData) {data = newData;}

    double getX(){return x;}
    void setX(double X){x = X;}

    double getY(){return y;}
    void setY(double Y){y = Y;}

};

#endif