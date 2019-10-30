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

    typedef typename NodeSeq::iterator NodeIte ;
    typedef typename EdgeSeq::iterator EdgeIte;

    NodeSeq nodes;
    NodeIte ni;
    EdgeIte ei;
    bool direccionado = false;


    Graph() = default;
    Graph(bool d):direccionado(d){};

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

    self& kruskal();

    void dfs(node* n,unordered_map<node*,bool> &visit);

    void fillOrder(node* n,unordered_map<node*,bool> &visit,stack<node*> &s);

    void setMap(unordered_map<node*,bool> &visit,bool n);

    bool isConnected();

    bool removeNode(N name);

    bool removeEdge(N from, N to);

    self& primMST(N start);
};




template <typename Tr>
void Graph<Tr>::print_graph(){
    for(NodeIte ni = nodes.begin();ni!=nodes.end();++ni){
        cout<<"Node "<<setw(5)<<(*ni).second->get_data()<<" : "<<endl;
        for(EdgeIte ei = (*ni).second->get_edges().begin();ei != (*ni).second->get_edges().end();ei++){
            cout<<"          "<<setw(6)<<(*ei)->get_nodes()[1]->get_data()<<" - "<<(*ei)->get_data()<<endl;
        }
    }
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
Graph<Tr> & Graph<Tr>::kruskal(){
    if(!isConnected()) throw out_of_range("Graph is not connected");
    if(direccionado) throw out_of_range("Graph is not ");
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
    }

/*
    int k=0,contador=0;
    for(auto nodes_value : graph_kruskal->nodes){
        k++;
        contador += (nodes_value).second->get_edges().size();
    }

    std::cout<<k<<" "<<contador/2<<endl;
*/

    return *graph_kruskal;
}



template <typename Tr>
void Graph<Tr>::dfs(node* n,unordered_map<node*,bool> &visit){
    visit[n]=1;
    for(EdgeIte it=n->get_edges().begin();it!=n->get_edges().end();++it)
        if(!visit[(*it)->get_nodes()[1]]) dfs((*it)->get_nodes()[1],visit);
}



template <typename Tr>
void Graph<Tr>::fillOrder(node* n,unordered_map<node*,bool> &visit,stack<node*> &s){
    visit[n]=1;
    for(EdgeIte it=n->get_edges().begin();it!=n->get_edges().end();++it)
        if(!visit[(*it)->get_nodes()[1]]) fillOrder((*it)->get_nodes()[1],visit,s);
    s.push(n);
}



template <typename Tr>
void Graph<Tr>::setMap(unordered_map<node*,bool> &visit,bool n){
    for(NodeIte it=nodes.begin();it!=nodes.end();++it) visit[(*it).second]=n;
}



template <typename Tr>
bool Graph<Tr>::isConnected(){
    unordered_map<node*,bool> visit;
    setMap(visit,0);
    //cout << nodes.size() << endl;
    if(!direccionado) dfs((*nodes.begin()).second,visit);
    else{
        stack<node*> s;
        for(auto nni=nodes.begin();nni!=nodes.end();++nni){
            if(!visit[(*nni).second]) fillOrder((*nni).second,visit,s);
        }
        Graph g1=transpose();
        setMap(visit,0);
        node* n=s.top(); s.pop();
        if(!visit[n]) g1.dfs((*g1.nodes.begin()).second,visit);
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
    if(f){
        nodes[from]->get_edges().remove(f);
        if(!direccionado) nodes[to]->get_edges().remove(searchEdge(to,from));
        return true;
    }
    return false;
}



template <typename Tr>
typename Graph<Tr>::self& Graph<Tr>::primMST(N start){/*
    unordered_map<N, N> parent;
    unordered_map<N, bool> vis;
    unordered_map<N, E> weight;
    priority_queue<pair<E, N>, vector<pair<E, N>>, greater<pair<E, N>>> pq;

    self* MST = new self(false);

    pq.push(make_pair(0, start));
    parent[start] = start;
    while(!pq.empty()){
        N curr = pq.top().second;
        E weig = pq.top().first;
        pq.pop();

        if(vis[curr]) continue;
        vis[curr] = true;

        if(MST->nodes.find(curr) == MST->nodes.end()){
            MST->insertNode(nodes[curr]);
        }
        if(parent[curr] != curr){
            MST->insertEdge(parent[curr], curr);
        }

        for(edge* edg : nodes[curr]->edges){
            int nd = edg->nodes[1]->data;
            int w = edg->getData();
            if(vis[nd]) continue;
            if(weight.find(nd) == weight.end() || weight[nd] < w){
                parent[nd] = curr;
                weight[nd] = w;
                pq.push(make_pair(w, nd));
            }
        }
    }
    return MST;*/
}



typedef Graph<Traits> graph;

#endif