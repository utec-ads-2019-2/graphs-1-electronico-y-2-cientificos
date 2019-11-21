
#ifndef WRITE_H
#define WRITE_H

#include <fstream>
#include <string>
#include <jsoncpp/json/json.h>
#include <iostream>
#include "graph.h"

using namespace std;

template <typename G>
class CWrite {
    typedef typename G::N N;
    typedef typename G::E E;
    G g;

public:
    
    CWrite(G &g,string file):g(g) {
        

        Json::Value salida(Json::arrayValue);
        

        
        for(auto ni = g.nodes.begin();ni!=g.nodes.end();++ni){
            Json::Value airports;
            airports["City"]="";
            airports["Country"]="";
            airports["Id"]=(*ni).second->get_data();
            cout<<(*ni).second->get_data()<<endl;
            airports["Longitude"]=(*ni).second->get_posx();
            airports["Latitude"]=(*ni).second->get_posy();
            
            Json::Value destinations(Json::arrayValue);
            for(auto ei = (*ni).second->get_edges().begin();ei != (*ni).second->get_edges().end();ei++){
                destinations.append((*ei)->get_nodes()[1]->get_data());
            }
            airports["destinations"]=destinations;
            salida.append(Json::Value(airports));

        }

        std::ofstream file_id;
        file_id.open(file);
        Json::StyledWriter styledWriter;
        file_id << styledWriter.write(salida);

        file_id.close();
   
    }

/*
    "Longitude": "-93.7931",
    "Latitude": "51.0669",
    for(NodeIte ni = nodes.begin();ni!=nodes.end();++ni){
        cout<<"Node "<<setw(5)<<(*ni).second->get_data()<<" : "<<endl;
        for(EdgeIte ei = (*ni).second->get_edges().begin();ei != (*ni).second->get_edges().end();ei++){
            cout<<"          "<<setw(6)<<(*ei)->get_nodes()[1]->get_data()<<" - "<<(*ei)->get_data()<<endl;
        }
    }*/

    graph& getGraph() {
        return g;
    }
};

#endif
