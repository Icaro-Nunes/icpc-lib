

template<typename T>
T fexp(T x, T exp, const T MOD) {
  T cursor = 1;
  T ans = 1;
  T currpow = x;

  while(cursor <= exp) {
    if(cursor & exp)
      ans = (ans%MOD) * (currpow%MOD) %MOD;

    cursor <<= 1;
    currpow = currpow%MOD;
    currpow = (currpow*currpow)%MOD;
  }

  return ans;
}

template<typename T>
T inv(T x, const T MOD) {
  return fexp(x, MOD-2, MOD);
}
