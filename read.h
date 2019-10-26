
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
    Read(G &g,char* file):g(g) {
        ifstream data(file);
        Json::Value obj;
        Json::Reader reader;
        reader.parse(data, obj);
        const Json::Value &airports = obj["airports"];
        for (unsigned int i = 0; i < airports.size(); ++i) {
            g.insertNode(airports[i]["Id"].asString(), stod(airports[i]["Longitude"].asString()),
                         stod(airports[i]["Latitude"].asString()));
        }
        for (unsigned int i = 0; i < airports.size(); ++i) {
            auto from = airports[i]["Id"].asString();
            for (unsigned int j = 0; j < airports[i]["destinations"].size(); ++j) {
                auto to = airports[i]["destinations"][j].asString();
                g.insertEdge(from, to);
            }
        }
    }

    graph& getGraph() {
        return g;
    }
};

#endif
