
#include <unordered_map>

using namespace std;

template <typename T>
class disjointset{

	unordered_map<T,T> disjoint_map;
public:
	T &operator[](T buscar){
		return disjoint_map[buscar];
	}

	T find_node_root(T node1){

		while(node1 != disjoint_map[node1] ){
			disjoint_map[node1] = disjoint_map[disjoint_map[node1]];
			node1 = disjoint_map[node1];
		}
		return node1;
	}

	void Union(T node1, T node2){
		disjoint_map[node1] = disjoint_map[node2];
	}

	bool same_root(T node1, T node2){
		if(find_node_root(node1) == find_node_root(node2)){
			return true;
		}
		return false;
	}

};