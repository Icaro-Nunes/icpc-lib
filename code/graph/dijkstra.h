#include <algorithm>
#include <limits>
#include <queue>
#include <stack>
#include <vector>


template<typename T>
void dijkstra(const std::vector<std::pair<T, int>>* graph, bool* visited, T* dist, int* parent, int root, int n) {
  for(int i=1; i<=n; i++)
    dist[i] = std::numeric_limits<T>::max();

  std::priority_queue<std::pair<T, int>, std::vector<std::pair<T, int>>, std::greater<std::pair<T, int>>> pq;

  pq.push({ 0, root });
  dist[root] = 0;
  parent[root] = root;

  while(!pq.empty()) {
    auto [dst, node] = pq.top();
    pq.pop();

    if(visited[node])
      continue;

    visited[node] = true;

    const std::vector<std::pair<T, int>>& adj = graph[node];

    for(const auto& [c_dst, child]: adj) {
      if(visited[child])
        continue;

      T newdst = dist[node] + c_dst;

      if(dist[child] > newdst) {
        dist[child] = newdst;
        pq.push({ newdst, child });
      }
    }
  }
}


// retrieve_path SEEMS TO BE NOT WORKING
//
// std::vector<int> retrieve_path(int tgt, int* parent) {
//   std::vector<int> ans;
//   int curr = tgt;
//   ans.push_back(tgt);
// 
//   while(curr != parent[curr]) {
//     ans.push_back(parent[curr]);
//     curr = parent[curr];
//   }
// 
//   std::reverse(ans.begin(), ans.end());
// 
//   return ans;
// }

