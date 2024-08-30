#include <gtest/gtest.h>
#include "number-theory/find_divisors/find_divisors.h"

TEST(FindDivisorsTest, DivisorsOf30ShouldBe) {
  long long val = 30;

  std::vector<long long> exp = {1, 2, 3, 5, 6, 10, 15, 30};
  auto res = find_divisors(val);

  EXPECT_EQ(res, exp);
}

TEST(FindDivisorsTest, DivisorsOf20ShouldBe) {
  long long val = 20;

  std::vector<long long> exp = {1, 2, 4, 5, 10, 20};
  auto res = find_divisors(val);

  EXPECT_EQ(res, exp);
}
