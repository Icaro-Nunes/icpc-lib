#include <bits/stdc++.h>
using namespace std;

// Hash 7f4616
//
// Returns v, an array of int for which
// v[i] = the extended size of the biggest
// palindrome centered in s[i], where
// s = #str[0]#str[1]#...#str[n-1]#
// 
// the odd positions of v account for 
// the correct size of the biggest odd 
// length palindromes in str, while the 
// even positions of v account for the
// correct size of the biggest even 
// length palindromes in str
//
// Runs in O(n)
vector<int> manacher(const string& str) {
	string s = "#";
	for(int i=0; i<str.size(); i++) s += str[i], s += "#";

	int n = s.size();
	vector<int> d(n, 0);
	int l=0, r=1;

	for(int i=1; i<n; i++) {
		if(i < r) {
			int center = (r+l)/2;
			int mirror = center - (i - center);
			d[i] = min(d[mirror], r - i);
		}
		
		while(i - d[i] - 1 >= 0
			and i + d[i] + 1 < n
			and s[i - d[i] - 1] == s[i+d[i]+1]
		) d[i]++;

		if(i+d[i] > r)
			r = i+d[i], l=i-d[i];
	}
	return d;
}


