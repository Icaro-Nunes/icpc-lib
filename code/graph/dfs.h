#include <vector>

auto dfs(const int& node, const std::vector<int>* graph, bool* visited) {
	if(visited[node])
		return;
	
	visited[node] = true;

	const std::vector<int>& adj = graph[node];

	for(const int& child: adj) {
		if(visited[child])
			continue;
		
		dfs(child, graph, visited);
	}
}

