#include <string>
#include <pair>
using namespace std;

struct SuffixArray {
	int n;
	vector<int> p;
	string v;

	SuffixArray(const string& s) {
		build(s);
	}

	// build suffix array of s
	// complexity: O(n*logn)
	void build(const string& s) {
		n = s.size();
		v = s; v+=char(0);
		p = vector<int>(n+1);

		vector<int> b, bp, bc, g, g_;
		b = bp = bc = g = g_ = p;

		for(int i=0; i<=n; i++) p[i] = i;

		auto cmp=[&](int a, int b) {
			return v[a]<v[b];
		};
		sort(begin(p), end(p), cmp);

		g[p[0]] = 0, bc[0]=1;
		for(int i=1, ct=0; i<=n; i++)
			if(v[p[i]] == v[p[i-1]])
				g[p[i]] = ct, bc[ct]++;
			else
				g[p[i]] = ++ct, bc[ct]=1;

		for(int c=1; c<n; c<<=1) {
			for(int i=0, sum=0; i<=n; i++) bp[i]=sum, sum+=bc[i];
			for(int i=0; i<=n; i++) b[bp[g[(p[i]+c)%(n+1)]]++] = p[i];
			p = b;

			for(int i=0, sum=0; i<=n; i++) bp[i]=sum, sum+=bc[i];
			for(int i=0; i<=n; i++) b[bp[g[p[i]]]++] = p[i];
			p = b;

			g_[p[0]] = 0, bc[0]=1;
			for(int i=1,ct=0; i<=n; i++)
				if(make_pair(g[p[i]], g[(p[i]+c)%(n+1)]) == make_pair(g[p[i-1]], g[(p[i-1]+c)%(n+1)]))
					g_[p[i]] = ct, bc[ct]++;
				else
					g_[p[i]] = ++ct, bc[ct]=1;
			g = g_;
		}
	}

	// check if suffix starting at p[b] is lexicographically
	// greater than or equal to s
	// complexity: O(|s|)
	bool ge(const string& s, int b) {
		for(int i=0; i<s.size(); i++)
			if(v[(p[b]+i)%(n+1)] > s[i]) return true;
			else if(v[(p[b]+i)%(n+1)] < s[i]) return false;
		return true;
	}

	// check if suffix starting at p[b] is lexicographically
	// greater than s
	// complexity: O(|s|)
	bool gt(const string& s, int b) {
		for(int i=0; i<s.size(); i++)
			if(v[(p[b]+i)%(n+1)] > s[i]) return true;
			else if(v[(p[b]+i)%(n+1)] < s[i]) return false;
		return false;
	}


	// counts occurrences of substring s
	// complexity: O(|s|*logn)
	int count(const string& s) {
		int l=0, r=n, fgt=n+1, fge=n+1;

		while(l<=r) {
			int mid = l+(r-l)/2;
			if(ge(s, mid))
				r=mid-1, fge=mid;
			else
				l=mid+1;
		}

		l=fge, r=n;
		while(l<=r) {
			int mid = l+(r-l)/2;
			if(gt(s, mid))
				r=mid-1, fgt=mid;
			else
				l=mid+1;
		}

		return fgt-fge;
	}


	// to find the first occurence of a substring
	// it is necessary to have a Sparse Table or
	// any RMQ DS
};


