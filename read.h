#ifndef READ_H
#define READ_H

#include <jsoncpp/json/json.h>
#include <fstream>
#include "graph.h"

/**
 * Clase de ayuda para leer el grafo desde un archivo,
 * no es necesario que la utilicen, podrían implementar su lector
 * desde su grafo o algún otro lado
 **/
template <typename G>
class Read {
	typedef typename G::N N;
	typedef typename G::E E;
		
	public:
		Read(char* file) {
		    ifstream data("airports.json");
		    Json::Value root;
		    Json::Reader reader;
		    reader.parse(data,root);
        }
		
		graph& getGraph() {
            // TODO
        }
};

#endif