#ifndef GRAPH_H
#define GRAPH_H

#include <algorithm>
#include <vector>
#include <list>

#include "node.h"
#include "edge.h"

using namespace std;

struct Traits {
	typedef string N;
	typedef float E;
};

template <typename Tr>
class Graph {
public:
    typedef Graph<Tr> self;
    typedef Node<self> node;
    typedef Edge<self> edge;
    typedef vector<node*> NodeSeq;
    typedef list<edge*> EdgeSeq;

    typedef typename Tr::N N;
    typedef typename Tr::E E;
    typedef typename NodeSeq::iterator NodeIte;
    typedef typename EdgeSeq::iterator EdgeIte;

    NodeSeq nodes;
    NodeIte ni;
    EdgeIte ei;

    node *getNode(N name)
    {

        auto *tmp = new node(name);

        if(nodes.size()>0) {
            ni = find_if(nodes.begin(), nodes.end(), [&tmp](node* x) {return x->getData() == tmp->getData();});
            if(ni != nodes.end())  return *ni;
            else return nullptr;
        }

        else return nullptr;
    }
    bool insertNode(N name, E xAxis = 0, E yAxis = 0)
    {
        //auto tempNode = getNode(name);

        //if(tempNode) return false;

        //else {
            auto newNode = new node(name, xAxis, yAxis);
            nodes.push_back(newNode);
            //mapa.insert({name,name});
            return true;
        //}
    }
};

typedef Graph<Traits> graph;

#endif