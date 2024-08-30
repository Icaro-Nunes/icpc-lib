#include <cstddef>


template<typename T, std::size_t N>
using Matrix = T[N][N];

template<typename T, std::size_t N>
void cp(const Matrix<T, N>& src, Matrix<T, N>& tgt) {
  for(int i=0; i<N; i++)
    for(int j=0; j<N; j++)
      tgt[i][j] = src[i][j];
}

template<typename T, std::size_t N>
void matmul(const Matrix<T, N>& a, const Matrix<T, N>& b, Matrix<T, N>& dst, const int MOD) {
  Matrix<T, N> tmp;

  for(int i=0; i<N; i++) {
    for(int j=0; j<N; j++) {
      T sum = 0;

      for(int l=0; l<N; l++) {
        sum += (a[i][l]*b[l][j])%MOD;
        sum %= MOD;
      }

      tmp[i][j] = sum;
    }
  }

  cp(tmp, dst);
}


