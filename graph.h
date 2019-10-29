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
#include <queue>
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

    typedef typename NodeSeq::iterator NodeIte ;
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
        for(ei=nodes[name_from]->get_edges().begin();ei!=nodes[name_from]->get_edges().end();++ei)
            if((*ei)->get_nodes()[1]->get_data()==name_to) return false;
        edge* newEdge = new edge(nodes[name_from],nodes[name_to]);
        nodes[name_from]->get_edges().push_back(newEdge);
        if(!direccionado){
            edge* newEdge1 = new edge(nodes[name_to],nodes[name_from]);
            nodes[name_to]->get_edges().push_back(newEdge1);
        }
        return true;
    }

    node* searchNode(N name){
        return nodes[name];
    }
    edge* searchEdge(N name_from, N name_to){
        EdgeSeq e = nodes[name_from]->get_edges();
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

    bool bipartito(){
        
        queue<node*> Priority_queue;
        if(nodes.size()>0){
            node *temporal = nullptr;
            map<node*,int> map_bipartito;
            NodeIte iteMap = nodes.begin();
            Priority_queue.push(iteMap->second);
            map_bipartito[iteMap->second] = 1;
            while(Priority_queue.size()>0){
                temporal = Priority_queue.front();
                Priority_queue.pop();
                if(map_bipartito[temporal]==1){              
                    for(edge* valor : temporal->get_edges()){
                        if(map_bipartito[(valor->get_nodes())[1]]==1){return false;}
                        if(map_bipartito[(valor->get_nodes())[1]]==2){continue;}
                        map_bipartito[(valor->get_nodes())[1]]=2;
                        Priority_queue.push((valor->get_nodes())[1]);
                    }
                }
                else if(map_bipartito[temporal]==2){
                    for(edge* valor : temporal->get_edges()){
                        if(map_bipartito[(valor->get_nodes())[1]]==2){return false;}
                        if(map_bipartito[(valor->get_nodes())[1]]==1){continue;}
                        map_bipartito[(valor->get_nodes())[1]]=1;
                        Priority_queue.push((valor->get_nodes())[1]);
                    }
                }
                
                
            }   
            return true;
        }
        
    }


    self& kruskal(){
        
        multimap<E,edge,greater<E>> map_edge;
        self *graph_kruskal = new self(false); 
        disjointset<N> disjoin;
        
        for(auto nodes_value : nodes){

            disjoin[nodes_value.first] = nodes_value.first; 

            for(auto edges_value : ((nodes_value).second)->get_edges()){
                map_edge.insert(make_pair<E,edge>((E)(edges_value->get_data()),(edge)(*edges_value)));
            }
        }

        for(auto valores = map_edge.begin(); valores != map_edge.end();++valores,++valores){

            N a1 = disjoin.find_node_root((valores->second).get_nodes()[0]->get_data());
            N a2 = disjoin.find_node_root((valores->second).get_nodes()[1]->get_data());

            if(disjoin.same_root(a1,a2)==false){

                disjoin.Union(a1,a2); 
                graph_kruskal->insertNode((valores->second).get_nodes()[0]->get_data(),((valores->second).get_nodes())[0]->get_posx(),((valores->second).get_nodes())[0]->get_posy());
                graph_kruskal->insertNode((valores->second).get_nodes()[1]->get_data(),((valores->second).get_nodes())[1]->get_posx(),((valores->second).get_nodes())[1]->get_posy());         
                graph_kruskal->insertEdge((valores->second).get_nodes()[0]->get_data(),((valores->second).get_nodes())[1]->get_data());
            }

            ++valores;
        }

        int k=0,contador=0;
        for(auto nodes_value : graph_kruskal->nodes){
            k++;
            contador += (nodes_value).second->get_edges().size();
        }


/*
        for(auto valores : map_edge){
            cout<<(valores.first)<<" - "<<(valores.second).nodes[0]->data<<" - "<<(valores.second).nodes[1]->data<<endl;
        }
        std::cout<<nodes_value.first<<" ("<<k<<" "<<contador<<") - "<<nodes_value.second->edges.size()<<" - ";
        for(auto edgees : nodes_value.second->edges){
            std::cout<<edgees->nodes[1]->data<<" ";
        }
        //std::cout<<contador<<endl;
*/
        std::cout<<k<<" "<<contador/2<<endl;
        return *graph_kruskal;

    }
};

typedef Graph<Traits> graph;

#endif