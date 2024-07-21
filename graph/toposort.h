#include <vector>
#include <stack>
#include <queue>

bool dfs(const std::vector<int>* graph, bool* visited, int* currtrav, std::stack<int>& ans, int node) {
	visited[node] = true;

	const std::vector<int>& adj = graph[node];

	bool poss = true;

	for(const int& child: adj) {
		if(currtrav[child] == currtrav[node]) {
			poss = false;
			break;
		}

		if(!visited[child]) {
			currtrav[child] = currtrav[node];

			if(!dfs(graph, visited, currtrav, ans, child)) {
				poss = false;
				break;
			}
		}
	}

	if(!poss)
		return false;

	currtrav[node] = -1;
	ans.push(node);
	return true;
}

// dfs-based toposort
// returns an empty vector in case it finds a cycle 
// (which means there is no valid topological order
// for the graph)
// 
// PS. the array currtrav representes the origin node
// for the current traversal,it will be useful for
// finding if there are cycles
//
// PS2. removed std::optional since it only compiles on
// C++17 above, and judges such as SPOJ only supports up 
// to C++14
std::vector<int> tarjan(const std::vector<int>* graph, bool* visited, int* currtrav, int n) {
	for(int i=1; i<=n; i++)
		currtrav[i] = -1;

	bool poss = true;

  std::stack<int> ans;

	for(int i=1; i<=n; i++) {
		if(visited[i])
			continue;

		currtrav[i] = i;

		if(!dfs(graph, visited, currtrav, ans, i)) {
			poss = false;
			break;
		}
	}

	if(poss) {
		std::vector<int> v;

		while(!ans.empty()) {
			v.push_back(ans.top());
			ans.pop();
		}
		
		return v;
	} else 
		return std::vector<int>();

}



// "bfs-based" toposort
// returns an empty vector in case it finds a cycle 
// (which means there is no valid topological order
// for the graph)
//
// PS. removed std::optional since it only compiles on
// C++17 above, and judges such as SPOJ only supports up 
// to C++14
std::vector<int> kahn(const std::vector<int>* graph, bool* visited, int* indeg, int n) {
  std::queue<int> q;

  for(int i=1; i<=n; i++) {
    if(indeg[i] == 0)
      q.push(i);
  }

  std::vector<int> ans;

  while(!q.empty()) {
    int node = q.front();
    q.pop();

    if(visited[node])
      continue;

    visited[node] = true;
    ans.push_back(node);

    const std::vector<int>& adj = graph[node];

    for(const int& child: adj) {
      indeg[child]--;

      if(indeg[child] == 0)
        q.push(child);
    }
  }

  if(ans.size() == n)
    return ans;
  else
    return std::vector<int>();
}


