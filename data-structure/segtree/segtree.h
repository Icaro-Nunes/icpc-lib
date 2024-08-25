#include <vector>
#include <optional>

// segment tree - 0 indexed !
// space: 4n
// time:
// - range query: O(logn)
// - lower_bound: O(logn)
// - update: O(logn)
template<typename T, class Op>
struct STree {
	int size;
	int treesize;
	T* items;
	T* nodes;
	Op op;

	STree(const std::vector<T>& from) {
		treesize=1;

		while(treesize < from.size())
			treesize <<=1;

		this->size = from.size();
		nodes = new T[2*treesize];
		items = nodes+treesize;

		for(int i=0; i<2*treesize; i++)
			nodes[i] = op.neutral;

		for(int i=0; i<size; i++)
			items[i] = from[i];

		for(int i=2*treesize-1; i>1; i--)
			nodes[i>>1] = op(nodes[i>>1], nodes[i]);
	}

	void update(int index, T value) {
		int i = treesize+index;

		nodes[i] = value;
		i = i>>1;

		while(i>0) {
			nodes[i] = op(nodes[2*i], nodes[2*i+1]);
			i>>=1;
		}
	}

	T query(int l, int r) {
		T res = op.neutral;
		r++;

		for(l += treesize, r += treesize; l<r; l>>=1, r>>=1) {
			if(l&1) res = op(res, nodes[l++]);
			if(r&1) res = op(res, nodes[--r]);
		}

		return res;
	}

	~STree() {
		delete nodes;
	}

	// search for first ocurrence to the right of strt
	// of a value greater than or equal to v
  	// REQUIRES TESTING ON STRT != 0
	int lower_boundr(int strt, T v) {
		int i=treesize+strt;
		T accum=nodes[i];

		while(i>1 and !(accum >= v)) {
			if(!(i&1) and op(accum, nodes[i+1])>=v) break;
			if(!(i&1)) accum = op(accum, nodes[i+1]);
			i>>=1;
		}

		if(i==1) return size;
		if(!(accum >= v)) i++;

		while(i<treesize) {
			if(op(accum, nodes[i<<1])>=v) i <<= 1;
			else accum = op(accum, nodes[i<<1]), i = (i<<1) + 1;
		}

		return i-treesize;
	}
};



