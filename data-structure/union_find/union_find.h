// union find code
int parent[1123456];
int ranks[1123456];

int disjoint = 0;

// the use of ct and newSet()
// is useful in problems
// where the initial number
// of disjoint sets is unknown
// such as in Hoshen-Kopelman
int ct = 0;
int newSet() {
  ct++;
  disjoint++;
  parent[ct] = ct;
  ranks[ct] = 1;

  return ct;
}

// for "regular" disjoint-sets problems
// one must use this function to
// initialize the union_find
inline void init_union_find(int sz) {
  disjoint = sz;

  for(int i=1; i<=sz; i++) {
    parent[i] = i;
    ranks[i] = 1;
  }
}

// find using compression
int find(const int& v) {
  int root = parent[v];

  while(root != parent[root]) {
    parent[root] = parent[parent[root]];
    root = parent[root];
  }

  parent[v] = root;

  return root;
}

// merge using ranks
void merge(const int& a, const int& b) {
  int root_a = find(a);
  int root_b = find(b);

  if(root_a == root_b)
    return;

  if(ranks[root_b] > ranks[root_a]) {
    parent[root_a] = root_b;
    ranks[root_b] += ranks[root_a];
  } else {
    parent[root_b] = root_a;
    ranks[root_a] += ranks[root_b];
  }

  disjoint--;
}
// end union find code

