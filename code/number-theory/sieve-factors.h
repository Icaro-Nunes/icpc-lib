#include <cmath>
#include <vector>

void sieve(bool* prime, std::vector<int>& primes, const int MAX_V) {
	for(int i=2; i<MAX_V; i++) {
		prime[i] = true;
	}

	int root = std::sqrt(MAX_V);

	for(int i=2; i<=root; i++) {
		if(!prime[i])
			continue;

		primes.push_back(i);

		for(int j=i; j <= MAX_V; j+=i) {
			prime[j] = false;
		}
	}

	for(int i=root; i<MAX_V; i++) {
		if(prime[i])
			primes.push_back(i);
	}
}

std::vector<std::pair<int, int>> factors(const int& x, const std::vector<int>& primes) {
  std::vector<std::pair<int, int>> res;

	int rem = x;

	for(const int& p: primes) {
		if(p > rem)
			break;

		if(rem % p != 0)
			continue;

		int amt = 0;

		while(rem % p == 0) {
			rem /= p;
			amt++;
		}

		res.push_back(std::make_pair(p, amt));
	}

	return res;
}
