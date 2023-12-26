#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>
#include <algorithm>


typedef std::map<std::string, std::vector<std::string>> AdjacencyList;
typedef std::map<std::string, int> SetSizes;

AdjacencyList graph;
std::vector<std::string> vertices;
SetSizes sizes;


void absorbNode(const std::string& absorbing, const std::string& newParent) {
    auto& adjFromAbsorbedNode = graph[absorbing];

    adjFromAbsorbedNode.erase(
        std::remove(adjFromAbsorbedNode.begin(), adjFromAbsorbedNode.end(), newParent),
        adjFromAbsorbedNode.end()
    );

    auto& adjFromNewParent = graph[newParent];
    adjFromNewParent.erase(
        std::remove(adjFromNewParent.begin(), adjFromNewParent.end(), absorbing),
        adjFromNewParent.end()
    );

    adjFromNewParent.insert(
        adjFromNewParent.end(),
        std::make_move_iterator(adjFromAbsorbedNode.begin()),
        std::make_move_iterator(adjFromAbsorbedNode.end())
    );

    for (auto& pair : graph)
        for (auto& s : pair.second)
            if (s == absorbing)
                s = newParent;

    graph.erase(absorbing);
    vertices.erase(std::remove(vertices.begin(), vertices.end(), absorbing), vertices.end());

    sizes[newParent] += sizes[absorbing] + 1;
}


bool kargerAlgorithm() {
    int size = graph.size();
    int vel = size;

    while (vel > 2) {
        int n = rand() % vertices.size();
        int i = rand() % graph[vertices[n]].size();

        if (vertices[n] == graph[vertices[n]][i]) 
            continue;

        absorbNode(graph[vertices[n]][i], vertices[n]);
        vel--;
    }

    int cuts = 0;
    long long setSizeTotal = 1;

    for (const auto& pair : graph) {
        if (!pair.second.empty()) 
            setSizeTotal *= sizes[pair.first] + 1;
        for (const std::string& ed : pair.second)
            if (ed != pair.first) 
                cuts++;
    }

    return (cuts / 2 == 3);
}

int main(){
    std::ifstream inputFile("../input/day25.txt");
	std::string u, v, inputLine;
	std::set<std::string> nodesToAdd;
	
	while (getline(inputFile, inputLine)){
		std::stringstream linestream(inputLine);
		linestream >> u;
		u = u.substr(0, u.length() - 1);
		nodesToAdd.insert(u);
		while (linestream >> v){
			graph[u].push_back(v);
			graph[v].push_back(u);
			nodesToAdd.insert(v);
		}
	}

	vertices.resize(nodesToAdd.size());
	std::copy(nodesToAdd.begin(), nodesToAdd.end(), vertices.begin());
	nodesToAdd.clear(); //clean up

	std::map<std::string, std::vector<std::string>> graph_copy = graph;
	std::vector<std::string> vertices_copy = vertices;
	std::map<std::string, int> set_sizes_copy = sizes;

	while (!kargerAlgorithm()){
		srand(time(0));

		graph = graph_copy;
		vertices = vertices_copy;
		sizes = set_sizes_copy;
	}
    
    return 0;
}
