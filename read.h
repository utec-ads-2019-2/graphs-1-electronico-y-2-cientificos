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
    G g;

	public:
		Read(G g,char* file):g(g){
		    ifstream data(file);
		    Json::Value obj;
		    Json::Reader reader;
		    reader.parse(data,obj);
		    const Json::Value& airports=obj["airports"];
		    for(int i=0;i<airports.size();++i){
		        g.insertNode(airports[i]["Id"].asString(),stod(airports[i]["Longitude"].asString()),
		                stod(airports[i]["Latitude"].asString()));
		    }
            for(int i=0;i<airports.size();++i){
                auto from=airports[i]["Id"].asString();
                for(int j=0;j<airports[i]["destinations"].size();++j){
                    auto to=airports[i]["destinations"][j].asString();
                    g.insertEdge(from,to);
                }
            }
		    for(g.ni = g.nodes.begin();g.ni != g.nodes.end(); ++g.ni){
		        cout << (*g.ni).first << ' ';
		        for(g.ei = (*g.ni).second->edges.begin(); g.ei != (*g.ni).second->edges.end(); ++g.ei){
		            cout << (*g.ei)->nodes[1]->data << ' ';
		        }
		        cout << '\n';
		    }
        }

		graph& getGraph() {
            return g;
        }
};

#endif