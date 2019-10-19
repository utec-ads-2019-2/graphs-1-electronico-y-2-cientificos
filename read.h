#ifndef READ_H
#define READ_H

#include <fstream>
#include <string>
#include <jsoncpp/json/json.h>
#include "graph.h"

using namespace std;

template <typename G>
class Read {
	typedef typename G::N N;
	typedef typename G::E E;
    graph g;

	public:
		Read(char* file) {
		    ifstream data(file);
		    Json::Value obj;
		    Json::Reader reader;
		    reader.parse(data,obj);
		    const Json::Value& airports=obj["airports"];
		    for(int i=0;i<airports.size();++i){
		        g.insertNode(airports[i]["Id"].asString(),stod(airports[i]["Longitude"].asString()),
		                stod(airports[i]["Latitude"].asString()));
		    }
        }

		graph& getGraph() {
            return g;
        }
};

#endif