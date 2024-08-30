
template<typename T>
T gcd(T a, T b) {
  if(a == b)
    return a;

  if(b > a)
    return gcd(b, a);

  if(!b) return a;
  return gcd(b, a%b);
}

template<typename T>
T lcm(T a, T b) {
  return a*b/gcd(a, b);
}

