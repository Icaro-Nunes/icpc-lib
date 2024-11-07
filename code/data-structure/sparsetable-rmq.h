using namespace std;


// Hash 5a9566
// SparseTable:
// - construction O(nlogn)
// - query O(logn)
template<typename T, class Op>
struct SparseTable {
	const static int LOG = 23;
	vector<T> st[LOG];
	Op op;

	SparseTable(const vector<T>& f) {
		const int& n = f.size();

		st[0] = f;

		for(int c=1,l=1; (c << 1) <= n; c<<=1, l++) {
			st[l].resize(n);

			for(int i=0; i<n; i++)
				st[l][i] = (i+c<n) ? op(st[l-1][i], st[l-1][i+c]) : st[l-1][i];
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


// Hash 501b00
// RMQ struct
// - range queries in O(1)
// - works for Operations that allow juxtaposition,
//   like min, max and gcd (idempotent functions)
template<typename T, class Op>
struct RMQ: SparseTable<T,Op> {
	RMQ(const vector<T>& f): SparseTable<T,Op> (f) {}

	T query(int l, int r) override {
		int len = r-l+1;
		int log = 32 - __builtin_clz(len) - 1;
		auto& opp = this->op; auto& stt = this->st;
		return opp(stt[log][l], stt[log][r-(1 << log)+1]);
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


