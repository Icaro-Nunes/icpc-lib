#include <cstddef>
#include <limits>

template<typename T, std::size_t N, std::size_t M> 
using Matrix = T[N][M];

// the adjacency matrix passed to floyd-warshall must contain
// weight of INF (numeric_limits<T>::max()) on pairs of nodes
// that are not adjacent, and 0 on the main diagonal
template<typename T, std::size_t N, std::size_t M>
void floydWarshall(const Matrix<T, N, M>& graph, Matrix<T, N, M>& dist, int n) {
  const T INF = std::numeric_limits<T>::max();

  for(int i=1; i<=n; i++)
    for(int j=1; j<=n; j++)
      dist[i][j] = graph[i][j];

  // k -> intermediate node
  for(int k=1; k<=n; k++) {
    // i -> source
    for(int i=1; i<=n; i++) {
      // j -> target
      for(int j=1; j<=n; j++) {
        T newdist;

        if(dist[i][k] == INF || dist[k][j] == INF)
          newdist = INF;
        else 
          newdist = dist[i][k] + dist[k][j];

        dist[i][j] = min(dist[i][j], newdist);
      }
    }
  }
}

