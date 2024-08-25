#include <cstdlib>
#include <gtest/gtest.h>
#include "data-structure/segtree/segtree.h"

TEST(STreeTest, RangeQueriesWork) {
  using ll = long long;

  int random_seed = (1 << 10) | 31;
  std::srand(random_seed);

  struct lladd {
    ll neutral=0;
    ll operator()(const ll& a, const ll& b) { return a+b; }
  };

  // test will involve 10 vectors with close to 1000 elements each,
  // and construct 10 segtrees on them
  for(int tc=0; tc<10; tc++) {
    std::vector<ll> inp;
    std::vector<ll> ps;

    ll sum = 0;

    auto interval_sum = [&ps](int l, int r) {
      ll disc = 0;

      if(l != 0)
        disc = ps[l-1];

      return ps[r] - disc;
    };

    for(int i=0; i<1000-(7*tc); i++) {
      ll val = rand();
      sum += val;
      inp.push_back(val);
      ps.push_back(sum);
    }

    STree<ll, lladd> tree(inp);

    int match = 0;
    int ct = 0;

    for(int i=0; i<inp.size(); i++) {
      for(int j=i; j<inp.size(); j++) {
        ct++;

        ll res_ps = interval_sum(i, j);
        ll res_seg = tree.query(i, j);

        ASSERT_EQ(res_ps, res_seg);
      }
    }
  }
}




TEST(STreeTest, BinarySearchWorks) {
  using ll = long long;

  int random_seed = (1 << 10) | 31;
  std::srand(random_seed);

  struct lladd {
    ll neutral=0;
    ll operator()(const ll& a, const ll& b) { return a+b; }
  };

  // test will involve 10 vectors with close to 1000 elements each,
  // and construct 10 segtrees on them
  for(int tc=0; tc<10; tc++) {
    std::vector<ll> inp;
    std::vector<ll> ps;

    unsigned int seed = (7 << 8) | 7;
    srand(seed);

    ll sum = 0;

    ll mx=0, mn=std::numeric_limits<ll>::max();

    for(int i=0; i<1000-(7*tc); i++) {
      ll val = rand();
      sum += val;
      inp.push_back(val);
      mx = std::max(mx, sum);
      mn = std::min(mn, val);
    }

    STree<ll, lladd> tree(inp);

    int match = 0;
    int ct = 0;
    
    for(int i=0; i<1000; i++) {
      int pos = rand()%inp.size();
      ll lb = (rand()%(mx-mn+1)) + mn;
      ll accum = 0;
      int ans = inp.size();

      for(int j=pos; j<inp.size(); j++) {
        accum += inp[j];
        if(accum >= lb) {
          ans = j;
          break;
        }
      }

      int prop = tree.lower_boundr(pos, lb);
      if(ans != prop)
        std::cout << "";
      
      ASSERT_EQ(ans, prop);
    }
  }
  
  
}



