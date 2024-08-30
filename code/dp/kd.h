
template<typename T>
T kadane(T* arr, int n) {
  T curr = arr[0];
  T best = curr;

  for(int i=1; i<n; i++) {
    curr = max(arr[i], curr + arr[i]);
    best = max(best, curr);
  }

  return best;
}
