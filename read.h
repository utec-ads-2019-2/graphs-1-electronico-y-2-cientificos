#ifndef READ_H
#define READ_H

#include <fstream>
#include <jsoncpp/json/json.h>
#include "graph.h"

using namespace std;

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
		    ifstream data(file);
		    Json::Value airports;
		    Json::Reader reader;
		    reader.parse(data,airports);
        }
		
		graph& getGraph() {
            // TODO
        }
};

#endif