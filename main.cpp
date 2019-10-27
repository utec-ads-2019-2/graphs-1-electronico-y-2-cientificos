#include "iostream"
#include "read.h"
#include "graph.h"
#include "edge.h"
using namespace std;

int main(int argc, char *argv[]) {
    graph test(true);
    char file[]="airports.json";
    Read<graph> r(test,file);
   	graph afterKruskal = test.kruskal();
    if(test.bipartito()){cout<<"es bipartito"<<endl;}
   	else{cout<<"no es bipartito"<<endl;}
    cout<<test.isConnected()<<endl;
   	/*for(auto ni=test.nodes.begin();ni!=test.nodes.end();++ni){
   	    cout << (*ni).second->data << ": ";
   	    for(auto ei=(*ni).second->edges.begin();ei!=(*ni).second->edges.end();++ei){
   	        cout << (*ei)->nodes[1]->data << " ";
   	    }
   	    cout << endl;
   	}*/
    cout<<test.removeNode("4199")<<endl;
    cout<<test.removeNode("4199")<<endl;
    return EXIT_SUCCESS;
}