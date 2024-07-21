#include <vector>
#include <optional>

template<typename T, class Op>
struct STree {
	int size;
	int treesize;
	T* items;
	T* nodes;
	Op op;

	STree(const std::vector<T>& from) {
		treesize = 1;

		while(treesize < from.size())
			treesize <<= 1;

		this->size = from.size();
		nodes = new T[2*treesize];
		items = nodes+treesize;

		for(int i=0; i < 2*treesize; i++)
			nodes[i] = op.neutral;

		for(int i=0; i<size; i++)
			items[i] = from[i];

		for(int i=2*treesize-1; i>1; i--) {
			nodes[i/2] = op(nodes[i/2], nodes[i]);
		}
	}

	void update(int index, T value) {
		int i = treesize + index;

		nodes[i] = value;
		i = i/2;

		while(i > 0) {
			nodes[i] = op(nodes[2*i], nodes[2*i+1]);
			i = i/2;
		}
	}

	T query(int l, int r) {
    T res = op.neutral;

    r++;

    for (l += treesize, r += treesize; l < r; l >>= 1, r >>= 1) {
      if (l&1) res = op(res, nodes[l++]);
      if (r&1) res = op(res, nodes[--r]);
    }

    return res;
	}

	~STree() {
		delete nodes;
	}

};



