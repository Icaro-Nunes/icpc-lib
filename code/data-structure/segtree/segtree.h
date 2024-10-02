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

	// treesize -> smallest power
  	// of 2 that is >= size
  	// (the actual space taken by
  	// the tree is 2*treesize)
	int ts; 

	// items -> pointer to the 
  	// start of the leaves of
  	// the segtree (implemented
  	// as a perfect binary tree)
	T* it;

	// nodes -> pointer to the 
  	// whole tree, with an extra
  	// unused node (nd[0])
	T* nd;

	// operation struct, must be
  	// implemented as:
  	// struct Op {
  	//  T neutral;
  	//  T operator()(const T& a, const T& b) {}
  	// }
	Op op;

	STree(const std::vector<T>& from) {
		ts=1;

		while(ts < from.size())
			ts <<=1;

		this->size = from.size();
		nd = new T[2*ts];
		it = nd+ts;

		for(int i=0; i<2*ts; i++)
			nd[i] = op.neutral;

		for(int i=0; i<size; i++)
			it[i] = from[i];

		for(int i=2*ts-1; i>1; i--)
			nd[i>>1] = op(nd[i], nd[i>>1]);
	}

	void update(int idx, T val) {
		int i = ts+idx;

		nd[i] = val;
		i = i>>1;

		while(i>0) {
			nd[i] = op(nd[i>>1], nd[(i>>1)+1]);
			i>>=1;
		}
	}

	T query(int l, int r) {
		T resl = op.neutral;
		T resr = op.neutral;
		
		r++;

		for(l += ts, r += ts; l<r; l>>=1, r>>=1) {
			if(l&1) resl = op(resl, nd[l++]);
			if(r&1) resr = op(nd[--r], resr);
		}

		return op(resl, resr);
	}

	~STree() {
		delete nd;
	}

	// search for first ocurrence to the right of strt
	// of a value greater than or equal to v
	int lower_boundr(int strt, T v) {
		int i=ts+strt;

		// accumulated value
		T acc=nd[i];

		while(i>1 and !(acc >= v)) {
			if(!(i&1) and op(acc, nd[i+1])>=v) break;
			if(!(i&1)) acc = op(acc, nd[i+1]);
			i>>=1;
		}

		if(i==1) return size;
		if(!(acc >= v)) i++;

		while(i<ts) {
			if(op(acc, nd[i<<1])>=v) i <<= 1;
			else acc = op(acc, nd[i<<1]), i = (i<<1) + 1;
		}

		return i-ts;
	}
};



