#include <utility>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Hash dc9083
struct SuffixArray {
	int n;
	vector<int> p, lcp;
	string v;

	SuffixArray(const string& s) {
		n=s.size()+1, v=s+'\0';
		build();
		build_lcp();
	}

	// build suffix array of s
	// complexity: O(n*logn)
	void build() {
		p = vector<int>(n);
		vector<int> b(n),bp(n),bc(n),g(n),g_(n);

		for(int i=0; i<n; i++) p[i] = i;

		auto cmp=[&](int a, int b) {
			return v[a] < v[b];
		};
		sort(begin(p), end(p), cmp);

		g[p[0]]=0, bc[0]=1;
		for(int i=1,ct=0; i<n; i++)
			if(v[p[i]] == v[p[i-1]]) g[p[i]]=ct, bc[ct]++;
			else g[p[i]]=++ct, bc[ct]=1;

		for(int c=1,k=0; c<n; c<<=1,k++) {
			auto& gg = (k&1) ? g_ : g;
			auto& gg_ = (k&1) ? g : g_;

			for(int i=0,sum=0; i<n; i++) bp[i]=sum,sum+=bc[i],bc[i]=bp[i];
			for(int i=0; i<n; i++) b[bc[gg[(p[i]+c)%n]]++] = p[i];
			for(int i=0; i<n; i++) p[bp[gg[b[i]]]++] = b[i];

			gg_[p[0]]=0, bc[0]=1;
			for(int i=1,ct=0; i<n; i++)
				if(make_pair(gg[p[i]], gg[(p[i]+c)%n]) == make_pair(gg[p[i-1]], gg[(p[i-1]+c)%n]))
					gg_[p[i]]=ct, bc[ct]++;
				else
					gg_[p[i]]=++ct, bc[ct]=1;
		}
	}

	void build_lcp() {
		lcp = vector<int>(n);
		vector<int> pos(n);
		for(int i=0; i<n; i++) pos[p[i]] = i;
		int k=0;
		for(int i=0, len=n-1; len>0; i++,len--,k=max(0,k-1)) {
			int prv=p[pos[i]-1];
			while(k<len)
				if(v[i+k] == v[(prv+k)%n]) k++;
				else break;
			lcp[pos[i]] = k;
		}
	}

};


