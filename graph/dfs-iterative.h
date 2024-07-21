#include <vector>
#include <stack>

auto dfs(const int& root, const std::vector<int>* graph, bool* visited) {
	std::stack<int> s;
	s.push(root);

	while(!s.empty()) {
    // avoid using const& here,
    // since pop() will change the value
		int node = s.top();
		s.pop();

		if(visited[node])
			continue;

		visited[node] = true;

		const std::vector<int>& adj = graph[node];

		for(const int& child: adj) {
			if(visited[child])
				continue;

			s.push(child);
		}
	}
}

