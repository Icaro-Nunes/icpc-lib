#include <vector>
#include <string>

std::vector<int> zstring(const std::string& s) {
	std::vector<int> z(s.size(), 0);

	int left = 0, right = 0;

	for(int k=1; k < s.size(); k++) {
		if(k > right) {
			left = right = k;

			while(right < s.size() && s[right] == s[right - left])
				right++;

			z[k] = right - left;

			right--;
		} else /* k <= right */ {
			int k1 = k - left;

			if(z[k1] < right - k) {
				z[k] = z[k1];
			} else {
				left = k;

				while(right < s.size() && s[right] == s[right - left])
					right++;

				z[k] = right - left;
				right--;
			}
		}
	}

	return z;
}

std::vector<int> match(const std::string& s, const std::string& pattern) {
	std::string pt = pattern + "$" + s;
	std::vector<int> z = zstring(pt);
	std::vector<int> res;

	for(int i=pattern.size() + 1; i < pt.size(); i++) {
		if(z[i] == pattern.size())
			res.push_back(i - pattern.size() - 1);
	}

	return res;
}

