#ifndef GRAPH_H
#define GRAPH_H
#include <iomanip>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <stack>
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
    typedef float  E;
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

    typedef typename NodeSeq::iterator NodeIte ;
    typedef typename EdgeSeq::iterator EdgeIte;

    NodeSeq nodes;
    NodeIte ni;
    EdgeIte ei;
    bool direccionado = false;


    Graph() = default;

    Graph(bool d):direccionado(d){};

    ~Graph();

    void print_graph();
        
    bool findNode(N name);

    bool findEdge(N a, N b);

    bool findEdge(node *node1, node *node2);

    void insertNode(N name);

    void insertNode(node* prevNode);

    bool insertNode(N name, E xAxis = 0, E yAxis = 0);

    bool insertEdge(N name_from, N name_to);

    node* searchNode(N name);

    edge* searchEdge(N name_from, N name_to);

    E graphDensity();

    Graph<Tr> transpose();

    bool bipartito();

    void isVisit(node* n,unordered_map<node*,bool> &visit);

    void fillDfs(node* n,unordered_map<node*,bool> &visit,stack<node*> &s);

    void fillDfs(node* n,unordered_map<node*,bool> &visit,Graph<Tr> &s);

    template <typename D>
    void setMap(unordered_map<node*,D> &visit,D n);

    bool isConnected();

    bool removeNode(N name);

    bool removeEdge(N from, N to);

    self& kruskal();

    self& primMST(N start);

    Graph<Tr> bfs(N name){
        Graph<Tr> bfs(direccionado); bfs.insertNode(nodes[name]); 
        queue<node*> qnode; qnode.push(nodes[name]);
        unordered_map<node*,bool> visit; setMap(visit,false); visit[nodes[name]]=1;
        while(!qnode.empty()){
            for(auto e:qnode.front()->get_edges()){
                if(!visit[e->get_nodes()[1]]){
                    bfs.insertNode(e->get_nodes()[1]); 
                    bfs.insertEdge(qnode.front()->get_data(),e->get_nodes()[1]->get_data()); 
                    visit[e->get_nodes()[1]]=1;
                    qnode.push(e->get_nodes()[1]);
                } 
            }
            qnode.pop();
        }
        return bfs;
    };

    Graph<Tr> dfs(N name){
        Graph<Tr> dfs(direccionado); dfs.insertNode(nodes[name]); 
        unordered_map<node*,bool> visit; setMap(visit,false); visit[nodes[name]]=1;
        fillDfs(nodes[name],visit,dfs);
        return dfs;
    };

    node* findMin(unordered_map<node*,bool> visit, unordered_map<node*,E> distance, node* min){
        for(auto d:distance)
            if(!visit[d.first])
                if(distance[min]>d.second) min=d.first;
        return min;
    }

    Graph<Tr> dijkstra(N name){
        Graph<Tr> dij(direccionado); auto minNode=nodes[name]; dij.insertNode(minNode);
        unordered_map<node*,bool> visit; setMap(visit,false); 
        unordered_map<node*,E> distance; setMap(distance,numeric_limits<E>::max()); 
        distance[minNode]=0; node *newNode, *tempNode=0; distance[newNode]=numeric_limits<E>::max();
        while(minNode!=newNode){
            visit[minNode] = 1;
            dij.insertNode(minNode);
            if(tempNode) dij.insertEdge(tempNode->get_data(),minNode->get_data());
            for(auto e:minNode->get_edges()){
                if(!visit[e->get_nodes()[1]]){
                    if((distance[minNode]+e->get_data())<distance[e->get_nodes()[1]]){
                        distance[e->get_nodes()[1]]=distance[minNode]+e->get_data();
                    }
                }
            }
            tempNode = minNode;
            distance.erase(minNode);
            minNode = findMin(visit,distance,newNode);
        }
        return dij;
        //Lista con las distancias
        /*unordered_map<node*,bool> visit; setMap(visit,false); auto minNode=nodes[name];
        unordered_map<node*,E> distance; setMap(distance,numeric_limits<E>::max()); 
        distance[nodes[name]]=0; node* newNode; distance[newNode]=numeric_limits<E>::max();
        auto minNode = nodes[name];
        for(int i=0;i<nodes.size();++i){
            visit[minNode] = 1;
            dfs.insertNode(minNode);
            for(auto e:minNode->get_edges()){
                if(!visit[e->get_nodes()[1]]){
                    if((distance[minNode]+e->get_data())<distance[e->get_nodes()[1]]){
                        distance[e->get_nodes()[1]]=distance[minNode]+e->get_data();
                    }
                }
            }
            minNode = findMin(visit,distance,newNode);
            if(minNode==newNode) break; 
        }
        distance.erase(newNode); return distance;*/
    };

    Graph<Tr>& AStar(N from, N to);
    
};

template <typename Tr>
Graph<Tr>& Graph<Tr>::AStar(N from, N to){
    self* graphAstar = new self(false);
    queue<node *> Cola;
    Cola.push(nodes[from]);
    graphAstar->insertNode(nodes[from]);
    while(Cola.front()!=nodes[to]){
        //cout<<"buscando"<<endl;
    }
    return *graphAstar;
}


template <typename Tr>
Graph<Tr>::~Graph(){
    for(auto nod : nodes){
        delete nod.second;
    }
    nodes.clear();
}


template <typename Tr>
void Graph<Tr>::print_graph(){
    for(NodeIte ni = nodes.begin();ni!=nodes.end();++ni){
        cout<<"Node "<<setw(5)<<(*ni).second->get_data()<<" : "<<endl;
        for(EdgeIte ei = (*ni).second->get_edges().begin();ei != (*ni).second->get_edges().end();ei++){
            cout<<"          "<<setw(6)<<(*ei)->get_nodes()[1]->get_data()<<" - "<<(*ei)->get_data()<<endl;
        }
    }
    cout << "\n\n";
}



template <typename Tr>
bool Graph<Tr>::findNode(N name){
    return nodes.find(name) != nodes.end();
}



template <typename Tr>
bool Graph<Tr>::findEdge(N a, N b){
    return findEdge(nodes[a], nodes[b]);
}



template <typename Tr>
bool Graph<Tr>::findEdge(node *node1, node *node2){
    for(edge* edg : node1->edges){
        if(edg->nodes[1] == node2) return true;
    }
    return false;
}



template <typename Tr>
void Graph<Tr>::insertNode(N name){
    node* newNode = new node(name);
    nodes[name] = newNode;
}



template <typename Tr>
void Graph<Tr>::insertNode(node* prevNode){
    node* newNode = new node(prevNode);
    nodes[prevNode->data]= newNode;
}



template <typename Tr>
bool Graph<Tr>::insertNode(N name, E xAxis, E yAxis) {
    if(nodes.find(name)!=nodes.end()) return false;
    else {
        auto newNode = new node(name, xAxis, yAxis);
        nodes[name]=newNode;
        return true;
    }
}



template <typename Tr>
bool Graph<Tr>::insertEdge(N name_from, N name_to){
    if(!(nodes.find(name_from)!=nodes.end() && nodes.find(name_to)!=nodes.end())) return false;
    for(ei=nodes[name_from]->get_edges().begin();ei!=nodes[name_from]->get_edges().end();++ei)
        if((*ei)->get_nodes()[1]->get_data()==name_to) return false;
    edge* newEdge = new edge(nodes[name_from],nodes[name_to]);
    nodes[name_from]->get_edges().push_back(newEdge);
    nodes[name_from]->get_edges_from().push_back(newEdge);
    if(!direccionado){
        edge* newEdge1 = new edge(nodes[name_to],nodes[name_from]);
        nodes[name_to]->get_edges().push_back(newEdge1);
        nodes[name_from]->get_edges_from().push_back(newEdge1);
    }
    return true;
}



template <typename Tr>
typename Graph<Tr>::node* Graph<Tr>::searchNode(N name){
    if(nodes.empty()) return nullptr;
    return nodes[name];
}




template <typename Tr>
typename Graph<Tr>::edge* Graph<Tr>::searchEdge(N name_from, N name_to){
    if(nodes.empty()) return nullptr;
    EdgeSeq* e = &(nodes[name_from]->edges);
    if(e->empty()) return nullptr;
    node* n = nodes[name_to];
    for(ei=e->begin();ei!=e->end();++ei){
        if((*ei)->nodes[1]==n) return *ei;
    }
    return nullptr;
}



template <typename Tr>
typename Tr::E Graph<Tr>::graphDensity(){
    E numEdges=0;
    E numNodes=nodes.size();
    for(ni=nodes.begin();ni!=nodes.end();++ni)
        numEdges+=(*ni).second->edges.size();
        return (numEdges)/(numNodes*(numNodes-1));
    }



template <typename Tr>
Graph<Tr> Graph<Tr>::transpose(){
    Graph<Tr> newGraph(direccionado);
    for(ni=nodes.begin();ni!=nodes.end();++ni)
        newGraph.insertNode((*ni).second->get_data(),(*ni).second->get_posx(),(*ni).second->get_posy());

    for(ni=nodes.begin();ni!=nodes.end();++ni)
        for(ei=(*ni).second->get_edges().begin();ei!=(*ni).second->get_edges().end();++ei){
            edge* e=new edge((*ei)->get_nodes()[1],(*ei)->get_nodes()[0]);
            newGraph.nodes[(*ei)->get_nodes()[1]->get_data()]->get_edges().push_back(e);
        }
    return newGraph;
}



template <typename Tr>
bool Graph<Tr>::bipartito(){
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
return false;
}


template <typename Tr>
void Graph<Tr>::isVisit(node* n,unordered_map<node*,bool> &visit){
    visit[n]=1;
    for(EdgeIte it=n->get_edges().begin();it!=n->get_edges().end();++it)
        if(!visit[(*it)->get_nodes()[1]]) isVisit((*it)->get_nodes()[1],visit);
}


template <typename Tr>
void Graph<Tr>::fillDfs(node* n,unordered_map<node*,bool> &visit,stack<node*> &s){
    visit[n]=1;
    for(EdgeIte it=n->get_edges().begin();it!=n->get_edges().end();++it)
        if(!visit[(*it)->get_nodes()[1]]) fillDfs((*it)->get_nodes()[1],visit,s);
    s.push(n);
}


template <typename Tr>
void Graph<Tr>::fillDfs(node* n,unordered_map<node*,bool> &visit,Graph<Tr> &s){
    visit[n]=1;
    for(EdgeIte it=n->get_edges().begin();it!=n->get_edges().end();++it)
        if(!visit[(*it)->get_nodes()[1]]) {
            s.insertNode((*it)->get_nodes()[1]);
            s.insertEdge(n->get_data(),(*it)->get_nodes()[1]->get_data());
            fillDfs((*it)->get_nodes()[1],visit,s);
        }
}


template <typename Tr>
template <typename D>
void Graph<Tr>::setMap(unordered_map<node*,D> &visit,D n){
    for(NodeIte it=nodes.begin();it!=nodes.end();++it) visit[(*it).second]=n;
}



template <typename Tr>
bool Graph<Tr>::isConnected(){
    unordered_map<node*,bool> visit; setMap(visit,false);
    if(!direccionado) isVisit((*nodes.begin()).second,visit); 
    else{
        stack<node*> s;
        for(auto nni=nodes.begin();nni!=nodes.end();++nni){
            if(!visit[(*nni).second]) fillDfs((*nni).second,visit,s);
        }
        Graph g1=transpose();
        setMap(visit,false);
        node* n=s.top(); s.pop();
        if(!visit[n]) g1.isVisit((*g1.nodes.begin()).second,visit);
    }
    for(auto mi=visit.begin();mi!=visit.end();++mi){
        if(!(*mi).second) return false;
    }
    return true;
}



template <typename Tr>
bool Graph<Tr>::removeNode(N name){
    NodeIte ndIt = nodes.find(name);
    if(ndIt==nodes.end()) return false;
    for(ei=(*ndIt).second->get_edges().begin();ei!=(*ndIt).second->get_edges().end();++ei){
        nodes[(*ei)->get_nodes()[1]->get_data()]->get_edges().remove(*ei);
    }
    for(ei=(*ndIt).second->get_edges_from().begin();ei!=(*ndIt).second->get_edges_from().end();++ei){
        nodes[(*ei)->get_nodes()[0]->get_data()]->get_edges().remove(*ei);
    }
    nodes.erase(ndIt);
    return true;
}



template <typename Tr>
bool Graph<Tr>::removeEdge(N from, N to){
    if(!(nodes.find(from)!=nodes.end() && nodes.find(to)!=nodes.end())) return false;
    edge* f=searchEdge(from,to);
    edge* g=searchEdge(to,from);
    if(f){
        nodes[from]->get_edges().remove(f);nodes[to]->get_edges_from().remove(g);
        if(!direccionado) {nodes[to]->get_edges().remove(g);nodes[from]->get_edges_from().remove(f);}
        return true;
    }
    return false;
}



template <typename Tr>
Graph<Tr> & Graph<Tr>::kruskal(){
    if(!isConnected()) throw exception();
    if(direccionado) throw exception();
    multimap<E,edge> map_edge;
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
        if(graph_kruskal->nodes.size()==this->nodes.size()){
            break;
        }
    }
    return *graph_kruskal;
}



template <typename Tr>
Graph<Tr> & Graph<Tr>::primMST(N source){
    if(!isConnected()) throw exception();
    if(direccionado) throw exception();
    vector<node*> list_of_nodes;
    self* graphPRIM = new self(false);
    multimap<E,edge> list_of_edges;
    list_of_nodes.push_back(nodes[source]);
    graphPRIM->insertNode(nodes[source]);
    
    while(list_of_nodes.size()!=this->nodes.size()){
        for(auto edg : list_of_nodes[list_of_nodes.size()-1]->get_edges()){

            list_of_edges.insert(make_pair<E,edge>((E)edg->get_data(),(edge)*edg));
        }
        for(auto nod = list_of_edges.begin(); nod != list_of_edges.end();nod++){
            if(find(list_of_nodes.begin(),list_of_nodes.end(),(nod->second.get_nodes()[1]))==list_of_nodes.end()){
                list_of_nodes.push_back(nod->second.get_nodes()[1]);
                graphPRIM->insertNode(nod->second.get_nodes()[1]);
                graphPRIM->insertEdge(nod->second.get_nodes()[0]->get_data(),nod->second.get_nodes()[1]->get_data());
                break;
            }
        }

    }

    

    return *graphPRIM;
}



typedef Graph<Traits> graph;

#endif