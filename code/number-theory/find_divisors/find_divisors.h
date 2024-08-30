#include <bits/stdc++.h>

// regular implementation
// - time complexity: O(sqrt(n))
// - space complexity: O(sqrt(n))
template<typename Integer>
std::vector<Integer> find_divisors(Integer val) {
  std::vector<Integer> v;
  std::stack<Integer> finals;

  Integer root = sqrt(val);

  // this less than or equal to is important
  // to avoid edge case like in find_divisors(20),
  // where sqrt(20) == 4, and therefore, in a 
  // mistake I previously made, my algorithm was
  // checking "root" separately, only to check
  // if the square root was exact. Even though 
  // 4 is not the exact square root of 20, it is
  // still a divisor of 20, and that version of
  // the algorithm would output { 1, 2, 10, 20 }
  // instead of { 1, 2, 4, 5, 10, 20 }. Another 
  // fix was to keep the separate check, but
  // using ceil-rounded (instead of floor-rounded)
  // square root.
  for(Integer i=1; i<=root; i++) {
    if(val%i == 0) {
      v.push_back(i);

      Integer div = val/i;

      if(div != i)
        finals.push(div);
    }
  }

  while(!finals.empty()) {
    v.push_back(finals.top());
    finals.pop();
  }

  return v;
}


