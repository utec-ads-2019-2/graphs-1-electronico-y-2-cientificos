#ifndef GRAPH_H
#define GRAPH_H

#include <algorithm>
#include <unordered_map>
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
    bool direccionado;
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

    Graph(bool d):direccionado(d){};
    bool insertNode(N name, E xAxis = 0, E yAxis = 0) {
        if(nodes.find(name)!=nodes.end()) return false;
        else {
            auto newNode = new node(name, xAxis, yAxis);
            nodes[name]=newNode;
            return true;
        }
    }
    bool insertEdge(N name_from, N name_to){
        if(!(nodes.find(name_from)!=nodes.end() && nodes.find(name_to)!=nodes.end())) return false;
        for(ei=nodes[name_from]->edges.begin();ei!=nodes[name_from]->edges.end();++ei)
            if((*ei)->nodes[1]->data==name_to) return false;
        edge* newEdge = new edge(nodes[name_from],nodes[name_to]);
        nodes[name_from]->edges.push_back(newEdge);
        if(!direccionado){
            edge* newEdge1 = new edge(nodes[name_to],nodes[name_from]);
            nodes[name_to]->edges.push_back(newEdge1);
        }
        return true;
    }
    node* searchNode(N name){
        return nodes[name];
    }
    edge* searchEdge(N name_from, N name_to){
        EdgeSeq e = nodes[name_from]->edges;
        node* n = nodes[name_to];
        for(ei=e.begin();ei!=e.end();++ei){
            if((*ei)->nodes[1]==n) return *ei;
        }
    }
    E graphDensity(){
        E numEdges=0;
        E numNodes=nodes.size();
        for(ni=nodes.begin();ni!=nodes.end();++ni)
            numEdges+=(*ni).second->edges.size();
        return (numEdges)/(numNodes*(numNodes-1));
    }
    void dfs(node* n,unordered_map<node*,bool> &visit){
        visit[n]=1;
        for(EdgeIte it=n->edges.begin();it!=n->edges.end();++it){
            if(!visit[(*it)->nodes[1]]){
                dfs((*it)->nodes[1],visit);
            }
        }
    }
    void setMap(unordered_map<node*,bool> visit,bool n){
        for(NodeIte it=nodes.begin();it!=nodes.end();++it) visit[(*it).second]=n;
    }
    bool isConnected(){
        unordered_map<node*,bool> visit;
        setMap(visit,0);
        for(ni=nodes.begin();ni!=nodes.end();++ni){
            dfs((*nodes.begin()).second,visit);
            for(auto mi=visit.begin();mi!=visit.end();++mi){
                if(!(*mi).second) return false;
            }
            if(!direccionado) return true;
            setMap(visit,0);
        }
        return true;
    }
};

typedef Graph<Traits> graph;

#endif