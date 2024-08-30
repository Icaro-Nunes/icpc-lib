#include <queue>
#include <vector>
#include "../data-structure/union_find/union_find.h"

template<typename T>
T prim(const std::vector<std::pair<T, int>>* graph, bool* visited, int root) {
  using pTi = std::pair<T, int>;
  std::priority_queue<pTi, std::vector<pTi>, std::greater<pTi>> pq;

  T total = 0;

  pq.push({0, root});

  while(!pq.empty()) {
    auto [cost, node] = pq.top();
    pq.pop();

    if(visited[node])
      continue;

    visited[node] = true;
    total += cost;

    const std::vector<pTi>& adj = graph[node];

    for(const auto& [c_dist, child]: adj) {
      if(visited[child])
        continue;

      pq.push({c_dist, child});
    }
  }

  return total;
}


// for kruskal
template<typename T>
struct edge {
  int a, b;
  T c;

  bool operator<(const edge<T>& other) const {
    return c < other.c;
  }
};

template<typename T>
T kruskal(std::vector<edge<T>>& edges, int n) {

  init_union_find(n);

  sort(edges.begin(), edges.end());

  T total = 0;

  for(const edge<T>& e: edges) {
    int root_a = find(e.a);
    int root_b = find(e.b);

    if(root_a != root_b) {
      total += e.c;
      merge(root_a, root_b);
    }
  }

  return total;
}


