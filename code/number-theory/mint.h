const ll mod = 1e9 + 7;

ll fexp(ll a, ll b) {
	ll v=1;
	while(b) {
		if(b&1ll) v = v*a % mod;
		a = a*a % mod;
		b >>= 1;
	}
	return v;
}

ll inv(ll x) {
	return fexp(x, mod-2);
}

struct mint {
	ll x;

	mint(ll _x) { x=_x, x%=mod, x+=mod, x%=mod; }

	mint operator+(mint o) const { return (x + o.x) % mod; }
	mint operator-(mint o) const { return (mod + (x - o.x)%mod)%mod; }
	mint operator*(mint o) const { return x * o.x % mod; }
	mint operator/(mint o) const { return x * inv(o.x) % mod; }
	mint& operator=(mint o) { x = o.x; return (*this); }
	mint& operator+=(mint o) { return (*this) = (*this) + o; }
	mint& operator-=(mint o) { return (*this) = (*this) - o; }
};

