#ifndef GRAPH_H
#define GRAPH_H

#include <algorithm>
#include <vector>
#include <unordered_map>
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

    typedef typename Tr::N N;
    typedef typename Tr::E E;

    typedef unordered_map<N,node*> NodeSeq;
    typedef list<edge*> EdgeSeq;

    typedef typename NodeSeq::iterator NodeIte;
    typedef typename EdgeSeq::iterator EdgeIte;

    NodeSeq nodes;
    NodeIte ni;
    EdgeIte ei;

    bool insertNode(N name, E xAxis = 0, E yAxis = 0) {
        if(nodes.find(name)!=nodes.end()) return false;
        else {
            auto newNode = new node(name, xAxis, yAxis);
            nodes[name]=newNode;
            return true;
        }
    }
    edge* insertEdge(N name_from, N name_to){
        auto newEdge = new edge(nodes[name_from],nodes[name_to]);
        return newEdge;
    }

    bool removeNode(N name) {
        bool flag = false;
        NodeIte tempIte;

        if(nodes.size()<=0) return false;
        else
        {
            for (ni = nodes.begin(); ni != nodes.end() ; ni++)
            {
                for (ei = (*ni)->edges.begin() ;  ei != (*ni)->edges.end(); ei++)
                {
                    if((*ei)->nodes[1]->getData() == name)
                    {
                        (*ni)->edges.erase(ei);
                        break;
                    }
                }
                if((*ni)->getData() == name)
                {
                    flag = true;
                    tempIte = ni;
                }
            }
            if(!flag)
                return false;
            nodes.erase(tempIte);
            mapa.erase(tempIte);
            return true;
        }
    }


    bool removeEdge(N orig, N dest)
    {
        bool flag = false;

        if(nodes.size()>0)
        {
            for (ni = nodes.begin(); ni != nodes.end(); ni++)
            {
                for (ei = (*ni)->edges.begin() ;  ei != (*ni)->edges.end(); ei++)
                {
                    if((*ei)->nodes[0]->getData() == orig && (*ei)->nodes[1]->getData() == dest)
                    {
                        flag = true;
                        break;
                    }
                }
                if(flag == true) break;
            }
            if(!flag)
                return false;
            (*ni)->edges.erase(ei);
            return true;
        }
        return false;
    }
};

typedef Graph<Traits> graph;

#endif