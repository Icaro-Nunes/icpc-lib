using namespace std;


template<typename T, class Op>
struct SparseTable {
	const static int LOG = 23;
	vector<T> st[LOG];
	Op op;

	SparseTable(const vector<T>& f) {
		const int& n = f.size();

		st[0] = f;

		int cursor = 1;
		for(int l=1; l<LOG; l++) {
			if((cursor << 1) > n) break;

			st[l].resize(n);

			for(int i=0; i<n; i++)
				st[l][i] = (i+cursor<n) ? op(st[l-1][i], st[l-1][i+cursor]) : st[l-1][i];

			cursor <<= 1;
		}
	}

	virtual T query(int l, int r) {
		T res = op.neutral;

		while(l<=r) {
			int len = r-l+1;
			int log = 32 - __builtin_clz(len) - 1;
			res = op(res, st[log][l]);
			l += (1 << log);
		}

		return res;
	}
};


// RMQ struct
// - range queries in O(1)
// - works for Operations that allow juxtaposition,
//   like min, max and gcd
template<typename T, class Op>
struct RMQ {
	T query(int l, int r) override {
		int len = r-l+1;
		int log = 32 - __builtin_clz(len) - 1;
		T res = this->st[log][l];
		res = this->op(res, st[log][r-(1 << log)+1]);
		return res;
	}
};

// example maximizer for numeric types
template<typename T>
struct Max {
	T neutral = 0;
	T operator()(const T& a, const T& b) {
		return max(a, b);
	}
};

// example minimizer for numeric types
template<typename T>
struct Min {
	T neutral = numeric_limits<T>::max();
	T operator()(const T& a, const T& b) {
		return min(a, b);
	}
};


