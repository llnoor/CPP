#include "multiset.h"

TEST(Multiset, EqualRange) {
  ::multiset<double> multiset = {-1, -6, 45, -34, 54, 23, -5, -6, -5, 0};
  auto x = multiset.equal_range(-5);
  ASSERT_EQ(*x.first, -5);
  ASSERT_EQ(*x.second, -1);
}

TEST(Multiset, LowerBound) {
  ::multiset<double> multiset = {-1, -6, 45, -34, 54, 23, -5, -6, -5, 0};
  ::multiset<double>::iterator x = multiset.lower_bound(-5);
  --x;
  ASSERT_EQ(*x, -6);
}

TEST(Multiset, UpperBound) {
  ::multiset<double> multiset = {-1, -6, 45, -34, 54, 23, -5, -6, -5, 0};
  auto x = multiset.upper_bound(45);
  --x;
  ASSERT_EQ(*x, 45);
}

TEST(Multiset, Constructor1) {
  ::multiset<double> multiset = {-1, -6, 45, -34, 54, 23, -5, -6, -5, 0};
  std::multiset<double> std_multiset = {-1, -6, 45, -34, 54, 23, -5, -6, -5, 0};

  ASSERT_EQ(*multiset.begin(), *std_multiset.begin());
  ASSERT_EQ(multiset.empty(), std_multiset.empty());
  ASSERT_EQ(multiset.size(), std_multiset.size());
}

TEST(Multiset, Constructor2) {
  ::multiset<double> multiset = {-1, -6, 45, -34, 54, 23, -5, -6, -5, 0};
  std::multiset<double> std_multiset = {-1, -6, 45, -34, 54, 23, -5, -6, -5, 0};
  auto x = multiset.begin();
  auto y = std_multiset.begin();

  for (; x != multiset.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }
}

TEST(Multiset, Insert) {
  ::multiset<double> multiset = {-1, -6, 45, -34, 54, 23, -5, -6, -5, 0};
  std::multiset<double> std_multiset = {-1, -6, 45, -34, 54, 23, -5, -6, -5, 0};
  multiset.insert(15);
  std_multiset.insert(15);
  multiset.erase(multiset.begin());
  std_multiset.erase(std_multiset.begin());
  auto x = multiset.begin();
  auto y = std_multiset.begin();
  for (; x != multiset.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }
}

TEST(Multiset, Swap) {
  ::multiset<double> multiset = {-1, -6, 45, -34, 54, 23, -5, -6, -5, 0};
  std::multiset<double> std_multiset = {-1, -6, 45, -34, 54, 23, -5, -6, -5, 0};
  ::multiset<double> multiset1 = {10, 20, 30, 40, 50};
  std::multiset<double> std_multiset1 = {10, 20, 30, 40, 50};
  multiset.swap(multiset1);
  std_multiset.swap(std_multiset1);
  auto x = multiset.begin();
  auto y = std_multiset.begin();
  for (; x != multiset.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }
}

TEST(Multiset, Merge) {
  ::multiset<double> multiset = {-1, -6, 45, -34, 54, 23, -5, -6, -5, 0};
  ::multiset<double> multiset1 = {543, 345, 654, 35, 65};
  multiset.merge(multiset1);

  ::multiset<double> std_multiset = {-1, -6, 45,  -34, 54,  23, -5, -6,
                                        -5, 0,  543, 345, 654, 35, 65};

  auto x = multiset.begin();
  auto y = std_multiset.begin();
  for (; x != multiset.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }
}

TEST(Multiset, Find) {
  ::multiset<double> multiset = {-1, -6, 45,  -34, 54,  23, -5, -6,
                                        -5, 0,  543, 345, 654, 35, 65};
  std::multiset<double> std_multiset = {-1, -6, 45,  -34, 54,  23, -5, -6,
                                        -5, 0,  543, 345, 654, 35, 65};
  ASSERT_EQ(*multiset.find(45), *std_multiset.find(45));
}

TEST(Multiset, Contains) {
  ::multiset<double> multiset = {-1, -6, 45,  -34, 54,  23, -5, -6,
                                        -5, 0,  543, 345, 654, 35, 65};
  multiset.count(-6);
  ASSERT_EQ(multiset.contains(200), false);
}
