#ifndef GRAPH_H
#define GRAPH_H

#include <algorithm>
#include <vector>
#include <unordered_map>
#include <list>
#include <queue>

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
    bool directed = false;
    bool weighted = false;

    Graph() = default;
    explicit Graph(bool directed) : directed(directed) {};
    bool findNode(N name){
        return nodes.find(name) != nodes.end();
    }

    bool findEdge(N a, N b){
        return findEdge(nodes[a], nodes[b]);
    }

    bool findEdge(node *node1, node *node2){
        for(edge* edg : node1->edges){
            if(edg->nodes[1] == node2) return true;
        }
        return false;
    }
    void insertNode(N name){
        node* newNode = new node(name);
        nodes[name] = newNode;
    }
    void insertNode(node* prevNode)
    {
        node* newNode = new node(prevNode);
        nodes[prevNode->data]= newNode;
    }
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
                if(flag) break;
            }
            if(!flag)
                return false;
            (*ni)->edges.erase(ei);
            return true;
        }
        return false;
    }
    self& primMST(N start){
        unordered_map<N, N> parent;
        unordered_map<N, bool> vis;
        unordered_map<N, E> weight;
        priority_queue<pair<E, N>, vector<pair<E, N>>, greater<pair<E, N>>> pq;

        self* MST = new self(false, weighted);

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

        return MST;
    }


};

typedef Graph<Traits> graph;

#endif