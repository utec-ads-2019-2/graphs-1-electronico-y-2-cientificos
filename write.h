
#ifndef WRITE_H
#define WRITE_H

#include <fstream>
#include <string>
#include <jsoncpp/json/json.h>
#include "graph.h"

using namespace std;

template <typename G>
class CWrite {
    typedef typename G::N N;
    typedef typename G::E E;
    G g;

public:
    /*
    CWrite(G &g,char* file):g(g) {
        
        Json::Value output;
        Json::Value airports(Json::arrayValue);

        for(NodeIte ni = g->nodes.begin();ni!=g->nodes.end();++ni){
            
            airports["Id"]=(*ni).second->get_data();
            airports["Longitude"]=(*ni).second->get_posx();
            airports["Latitude"]=(*ni).second->get_posy();
            for(EdgeIte ei = (*ni).second->get_edges().begin();ei != (*ni).second->get_edges().end();ei++){
                //cout<<"          "<<setw(6)<<(*ei)->get_nodes()[1]->get_data()<<" - "<<(*ei)->get_data()<<endl;
                     
            }

        }
    }


"Longitude": "-93.7931",
    "Latitude": "51.0669",
    for(NodeIte ni = nodes.begin();ni!=nodes.end();++ni){
        cout<<"Node "<<setw(5)<<(*ni).second->get_data()<<" : "<<endl;
        for(EdgeIte ei = (*ni).second->get_edges().begin();ei != (*ni).second->get_edges().end();ei++){
            cout<<"          "<<setw(6)<<(*ei)->get_nodes()[1]->get_data()<<" - "<<(*ei)->get_data()<<endl;
        }
    }
*/
    graph& getGraph() {
        return g;
    }
};

#endif
