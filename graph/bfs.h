#include <vector>
#include <queue>

auto bfs(const int& root, bool* visited, const std::vector<int>* graph, const int& target) {
	std::queue<int> q;

	q.push(root);

	while(!q.empty()) {
    // avoid using const& here,
    // since pop() will change the value
		int node = q.front();
		q.pop();

    if(node == target)
      break;

		if(visited[node])
			continue;

		visited[node] = true;

		const std::vector<int>& adj = graph[node];

		for(const int& child: adj) {
			if(visited[child])
				continue;

			q.push(child);
		}
	}
}

