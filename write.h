
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


public:
    
    CWrite(G &g,string file) {
        
        Json::Value salida(Json::arrayValue);

        
        for(auto ni = g.nodes.begin();ni!=g.nodes.end();++ni){
            Json::Value airports;
            airports["City"]="";
            airports["Country"]="";
            airports["Id"]=(*ni).second->get_data();
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

};

#endif
