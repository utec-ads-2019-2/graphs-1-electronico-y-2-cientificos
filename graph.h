#ifndef GRAPH_H
#define GRAPH_H

#include <algorithm>
#include <unordered_map>
#include <vector>
#include <list>
#include <set>
#include <utility>
#include "node.h"
#include "edge.h"
#include "disjointset.h"
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

    void kruskal(){
        
        multimap<E,edge> map_edge;
        self *graph_kruskal = new self(false); 
        disjointset<N> disjoin;
        int k=0;
        for(auto nodes_value : nodes){
            disjoin[nodes_value.first] = nodes_value.first;
            if((nodes_value.second->edges).size()==0){
                std::cout<<nodes_value.first<<endl;
                std::cout<<"No se conecta"<<endl;
                
            }
            k++;
            graph_kruskal->insertNode(nodes_value.second->data,nodes_value.second->get_posx(),nodes_value.second->get_posy());
            for( auto edges_value : ((nodes_value).second)->edges){

                map_edge.insert(std::make_pair<E,edge>((E)(edges_value->data),(edge)(*edges_value)));

                
            }
        }
        int contador=0;

        for(auto valores : map_edge){
            N a1 = disjoin.find_node_root((valores.second).nodes[0]->data);
            N a2 = disjoin.find_node_root((valores.second).nodes[1]->data);

            if(disjoin.same_root(a1,a2)==false){
                disjoin.Union(a1,a2); 
                contador++;
                graph_kruskal->insertEdge((valores.second).nodes[0]->data,(valores.second).nodes[1]->data);  
                //cout<<(valores.second).nodes[0]->data<<" "<<(valores.second).nodes[1]->data<<endl;    
            }

        }
        std::cout<<contador<<" "<<k<<std::endl;

    }

    /*bool conexo(set<node*> nds,node* n){
        if(nds.size()<nodes.size()){
            EdgeSeq edges=n->edges;
            for(ei=edges.begin();ei!=edges.end();++ei){
                nds.insert((*ei)->nodes[1]);
                conexo(nds,(*ei)->nodes[1]);
            }
            return false;
        }
`        return true;
    }
    bool conexo(){
        set<node*> nds;
        EdgeSeq edges;
        int size=nodes.size();
        if(direccionado){
        }else{
            for(ni=nodes.begin();ni!=nodes.end();++ni){
                edges=(*ni).second->edges;
                for(ei=edges.begin();ei!=edges.end();++ei){
                    nds.insert((*ei)->nodes[1]);
                }
            }
        }
    }*/
};

typedef Graph<Traits> graph;

#endif