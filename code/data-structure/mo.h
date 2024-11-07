#include <vector>
using namespace std;

const int BLKSIZE=1e2;


// Hash 319b09
// OPTIONAL
inline int64_t hilbertOrder(int x, int y, int pow, int rotate) {
	if (pow == 0) {
		return 0;
	}
	int hpow = 1 << (pow-1);
	int seg = (x < hpow) ? (
		(y < hpow) ? 0 : 3
	) : (
		(y < hpow) ? 1 : 2
	);
	seg = (seg + rotate) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	int64_t subSquareSize = int64_t(1) << (2*pow - 2);
	int64_t ans = seg * subSquareSize;
	int64_t add = hilbertOrder(nx, ny, pow-1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
}
//-------------

// Hash d56199
struct Query {
	int l, r, idx;
	int64_t ord;

	Query(int l, int r, int idx) : l(l), r(r), idx(idx) {
		ord = hilbertOrder(l, r, 21, 0);
	}

	bool operator < (const Query& other) const {
		// return ord < other.ord;
		int i1 = l/BLKSIZE, i2 = other.l/BLKSIZE;
		if(i1 == i2) return (i1%2 ? r > other.r : r < other.r);
		return i1 < i2;
	}
};

int add(int i) {
	// TODO
}


int remove(int i) {
	// TODO
}


void process(const vector<Query>& queries) {
	vector<int> res(queries.size());

	for(const auto& query: queries) {
		while(l > query.l)
			add(--l);

		while(r < query.r)
			add(++r);

		while(l < query.l)
			remove(l++);

		while(r > query.r)
			remove(r--);

		res[query.idx] = ans;
	}
}



