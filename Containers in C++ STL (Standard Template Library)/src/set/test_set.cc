#include "set.h"

TEST(SET, Insert1) {
  ::set<double> number1 = {19, 23, 43, 12, 33, 44, 32, 21, 10, 0};
  std::set<double> number2 = {19, 23, 43, 12, 33, 44, 32, 21, 10, 0};
  EXPECT_EQ(number1.size(), number2.size());
  auto it1 = number1.begin();
  for (auto it2 = number2.begin(); it2 != number2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(number1.size(), number2.size());
}

TEST(SET, Insert2) {
  ::set<double> number1 = {19, 23, 43, 12, 33, 44, 32, 21, 10, 0};
  std::set<double> number2 = {19, 23, 43, 12, 33, 44, 32, 21, 10, 0};
  EXPECT_EQ(number1.size(), number2.size());
  EXPECT_EQ(number1.insert(-1).second, number2.insert(-1).second);
  auto it1 = number1.begin();
  for (auto it2 = number2.begin(); it2 != number2.end(); ++it1, ++it2) {
    EXPECT_EQ(*it1, *it2);
  }
  EXPECT_EQ(number1.size(), number2.size());
}

TEST(SET, Insert3) {
  ::set<double> number1 = {13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  std::set<double> number2 = {13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  EXPECT_EQ(number1.size(), number2.size());
  auto it1 = number1.begin();
  for (auto it2 = number2.begin(); it2 != number2.end(); ++it1, ++it2) {
    EXPECT_EQ(*it1, *it2);
  }
  EXPECT_EQ(number1.size(), number2.size());
}

TEST(SET, Constructor1) {
  ::set<int> number1 = {19, 23, 43, 12, 33, 44, 32, 21, 10, 0};
  std::set<int> number2 = {19, 23, 43, 12, 33, 44, 32, 21, 10, 0};
  ::set<int>::iterator it1 = number1.begin();
  for (auto it2 = number2.begin(); it2 != number2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(SET, Constructor2) {
  ::set<int> number1 = {19, 23, 43, 12, 33, 44, 32, 21, 10, 0};
  std::set<int> number2 = {19, 23, 43, 12, 33, 44, 32, 21, 10, 0};
  auto it1 = number1.begin();
  for (auto it2 = number2.begin(); it2 != number2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(SET, Constructor3) {
  ::set<int> number1;
  std::set<int> number2;
  EXPECT_EQ(number1.size(), number2.size());
}

TEST(SET, Constructor4) {
  ::set<int> number1 = {19, 23, 43};
  std::set<int> number2 = {19, 23, 43};
  auto number11 = std::move(number1);
  auto number22 = std::move(number2);
  auto it1 = number11.begin();
  for (auto it2 = number22.begin(); it2 != number22.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(number1.size(), number2.size());
  EXPECT_EQ(number11.size(), number22.size());
}

TEST(SET, Constructor5) {
  ::set<int> number1 = {19, 23, 43};
  std::set<int> number2 = {19, 23, 43};
  auto number11 = number1;
  auto number22 = number2;
  auto it1 = number11.begin();
  for (auto it2 = number22.begin(); it2 != number22.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(number1.size(), number2.size());
  EXPECT_EQ(number11.size(), number22.size());
}

TEST(SET, Constructor6) {
  ::set<int> number1 = {-19, -23, -43};
  std::set<int> number2 = {-19, -23, -43};
  auto it1 = number1.begin();
  for (auto it2 = number2.begin(); it2 != number2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(number1.size(), number2.size());
}

TEST(SET, Constructor7) {
  ::set<int> number1 = {19, 23, 43};
  std::set<int> number2 = {19, 23, 43};
  ::set<int> number11;
  std::set<int> number22;
  number11 = std::move(number1);
  number22 = std::move(number2);
  auto it1 = number11.begin();
  for (auto it2 = number22.begin(); it2 != number22.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(number1.size(), number2.size());
  EXPECT_EQ(number11.size(), number22.size());
}

TEST(SET, Size1) {
  ::set<int> number1;
  std::set<int> number2;
  number1.insert(1);
  number2.insert(1);
  EXPECT_EQ(number1.size(), number2.size());
}

TEST(SET, Size2) {
  ::set<int> number1 = {19, 23, 43, 12, 33, 44, 32, 21, 10, 0};
  std::set<int> number2 = {19, 23, 43, 12, 33, 44, 32, 21, 10, 0};
  EXPECT_EQ(number1.size(), number2.size());
}

TEST(SET, Size3) {
  ::set<int> number1 = {19, 23, 43, 12, 33, 44, 32, 21, 10, 0};
  std::set<int> number2 = {19, 23, 43, 12, 33, 44, 32, 21, 10, 0};
  number1.clear();
  number2.clear();
  EXPECT_EQ(number1.size(), number2.size());
}

TEST(SET, Clear1) {
  ::set<double> number1 = {19, 23, 43, 12, 33, 44, 32, 21, 10, 0};
  std::set<double> number2 = {19, 23, 43, 12, 33, 44, 32, 21, 10, 0};
  number1.clear();
  number2.clear();
  EXPECT_EQ(number1.size(), number2.size());
  EXPECT_EQ(number1.empty(), number2.empty());
}

TEST(SET, Clear2) {
  ::set<double> number1;
  std::set<double> number2;
  number1.clear();
  number2.clear();
  EXPECT_EQ(number1.size(), number2.size());
  EXPECT_EQ(number1.empty(), number2.empty());
}

TEST(SET, Clear3) {
  ::set<double> number1 = {19, 23, 43, 12, 33, 44, 32, 21, 10, 0};
  std::set<double> number2 = {19, 23, 43, 12, 33, 44, 32, 21, 10, 0};
  number1.clear();
  number2.clear();
  EXPECT_EQ(number1.size(), number2.size());
  EXPECT_EQ(number1.empty(), number2.empty());
  number1.clear();
  number2.clear();
  EXPECT_EQ(number1.size(), number2.size());
  EXPECT_EQ(number1.empty(), number2.empty());
}

TEST(SET, Begin) {
  ::set<int> number1 = {19, 23, 43};
  std::set<int> number2 = {19, 23, 43};
  auto it1 = number1.begin();
  auto it2 = number2.begin();
  EXPECT_EQ(*it1, *it2);
}

TEST(SET, Empty) {
  ::set<int> number1 = {19, 23, 43};
  std::set<int> number2 = {19, 23, 43};
  EXPECT_EQ(number1.empty(), number2.empty());
}

TEST(SET, Empty2) {
  ::set<int> number1 = {19, 23, 43};
  std::set<int> number2 = {19, 23, 43};
  number1.clear();
  number2.clear();
  EXPECT_EQ(number1.empty(), number2.empty());
}

TEST(SET, Erase0) {
  ::set<double> number1;
  std::set<double> number2;
  EXPECT_EQ(number1.size(), number2.size());
  number1.erase(0.1);
  number2.erase(0.1);
  EXPECT_EQ(number1.size(), number2.size());
  ::set<double> number11;
  ::set<double> number22;
  EXPECT_EQ(number11.max_size(), number22.max_size());
  EXPECT_EQ(number11.Rotation(), 1);
  number11.erase(0.1);
  EXPECT_EQ(number11.size(), number22.size());
}

TEST(SET, Erase1) {
  ::set<double> number1 = {13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  std::set<double> number2 = {13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  EXPECT_EQ(number1.size(), number2.size());
  number1.erase(number1.begin());
  number2.erase(number2.begin());
  EXPECT_EQ(number1.size(), number2.size());
}

TEST(SET, Erase2) {
  ::set<double> number1 = {13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  std::set<double> number2 = {13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  number1.erase(number1.begin());
  number2.erase(number2.begin());
  auto it1 = number1.begin();
  auto it2 = number2.begin();
  EXPECT_EQ(number1.size(), number2.size());
  EXPECT_EQ(*it1, *it2);
}

TEST(SET, Erase3) {
  ::set<double> number1 = {13, 29, 34, 44, 56, 667, 24, 31, 0,  10, 5,
                              34, 0,  1,  2,  3,  4,   5,  6,  7,  8,  9,
                              10, 11, 12, 13, 14, 15,  16, 17, 18, 19, 20,
                              21, 22, 23, 24, 25, 26,  27, 28, 29, 30};
  std::set<double> number2 = {13, 29, 34, 44, 56, 667, 24, 31, 0,  10, 5,
                              34, 0,  1,  2,  3,  4,   5,  6,  7,  8,  9,
                              10, 11, 12, 13, 14, 15,  16, 17, 18, 19, 20,
                              21, 22, 23, 24, 25, 26,  27, 28, 29, 30};
  number1.erase(29);
  number2.erase(29);
  for (double i = 0; i < 20; i++) {
    number1.erase(i);
    number2.erase(i);
  }
  auto it1 = number1.begin();
  auto it2 = number2.begin();
  EXPECT_EQ(number1.size(), number2.size());
  EXPECT_EQ(*it1, *it2);
}

TEST(SET, Swap1) {
  ::set<int> number1 = {13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  std::set<int> number2 = {13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  ::set<int> number11;
  std::set<int> number22;
  number1.swap(number11);
  number2.swap(number22);
  EXPECT_EQ(number1.size(), number2.size());
  EXPECT_EQ(number11.size(), number22.size());
  auto it1 = number11.begin();
  for (auto it2 = number22.begin(); it2 != number22.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(SET, Swap2) {
  ::set<int> number1 = {13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  std::set<int> number2 = {13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  ::set<int> number11 = {138, 3, 101, 1, 67};
  std::set<int> number22 = {138, 3, 101, 1, 67};
  number1.swap(number11);
  number2.swap(number22);
  EXPECT_EQ(number1.size(), number2.size());
  EXPECT_EQ(number11.size(), number22.size());
  auto it1 = number11.begin();
  for (auto it2 = number22.begin(); it2 != number22.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(SET, Find1) {
  ::set<int> number1 = {13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  std::set<int> number2 = {13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  EXPECT_EQ(*(number1.find(31)), *(number2.find(31)));
}

TEST(Set, Find2) {
  std::set<int> std_temp{551, 843, 745, 263, 456, 142, -1123, 9};
  ::set<int> temp{551, 843, 745, 263, 456, 142, -1123, 9};
  auto std_it = std_temp.find(9);
  auto it = temp.find(9);
  EXPECT_EQ(*std_it, *it);
}

TEST(Set, Contains0) {
  std::set<int> std_temp{51, 43, 75, 13, 506, 2, -53, -1};
  ::set<int> temp{51, 43, 75, 13, 506, 2, -53, -1};
  EXPECT_EQ(true, temp.contains(-53));
  EXPECT_EQ(false, temp.contains(12345));
}

TEST(SET, Contains1) {
  ::set<int> number1 = {13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  EXPECT_EQ(number1.contains(5), true);
}

TEST(SET, Contains2) {
  ::set<int> number1 = {13, 29, 34, 44, 56, 667, 24, 31, 1, 10, 5};
  EXPECT_EQ(number1.contains(0), false);
}

TEST(Set, Insert11) {
  std::set<int> std_temp{13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  ::set<int> temp{13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  auto std_insert_pair = std_temp.insert(4530);
  auto insert_pair = temp.insert(4530);
  EXPECT_EQ(std_insert_pair.second, insert_pair.second);
  auto std_it = std_temp.begin();
  auto it = temp.begin();
  for (; std_it != std_temp.end(); ++std_it, ++it)
    EXPECT_EQ(*std_it, *it);
}

TEST(Set, Erase11) {
  std::set<int> std_temp{13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  ::set<int> temp{13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  auto std_it = std_temp.begin();
  auto it = temp.begin();
  std_temp.erase(std_it);
  temp.erase(it);
  std_it = std_temp.begin();
  it = temp.begin();
  for (; std_it != std_temp.end(); ++std_it, ++it)
    EXPECT_EQ(*std_it, *it);
}

TEST(Set, Swap11) {
  std::set<int> std_temp{13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  ::set<int> temp{13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  std::set<int> std_temp_2{551, 843, 745, 263, 456, 142, -1123};
  ::set<int> temp_2{551, 843, 745, 263, 456, 142, -1123};
  std_temp.swap(std_temp_2);
  temp.swap(temp_2);
  auto std_it = std_temp.begin();
  auto it = temp.begin();
  for (; std_it != std_temp.end(); ++std_it, ++it)
    EXPECT_EQ(*std_it, *it);
  std_it = std_temp_2.begin();
  it = temp_2.begin();
  for (; std_it != std_temp_2.end(); ++std_it, ++it)
    EXPECT_EQ(*std_it, *it);
}

TEST(Set, Merge11) {
  std::set<int> std_temp{3, 2, 0, 5, 3, 2, 9, -10, 9, 0};
  ::set<int> temp{3, 2, 0, 5, 3, 2, 9, -10, 9, 0};
  std::set<int> std_temp_2{551, 843, 745, 263, 456, 142, -1123};
  ::set<int> temp_2{551, 843, 745, 263, 456, 142, -1123};
  std_temp.merge(std_temp_2);
  temp.merge(temp_2);
  auto std_it = std_temp.begin();
  auto it = temp.begin();
  for (; std_it != std_temp.end(); ++std_it, ++it)
    EXPECT_EQ(*std_it, *it);
}

TEST(SET, Iterator1) {
  ::set<int> number1 = {13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  std::set<int> number2 = {13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  auto it1 = number1.begin();
  auto it2 = number2.begin();
  for (int i = 0; i < 9; i++) ++it1, ++it2;
  EXPECT_EQ(*it1, *it2);
}

TEST(SET, Iterator2) {
  ::set<int> number1 = {13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  std::set<int> number2 = {13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  auto it01 = number1.rbegin();
  auto it02 = number2.rbegin();
  EXPECT_EQ(*it01, *it02);
  auto it1 = number1.begin();
  auto it2 = number2.begin();
  for (int i = 0; i < 9; i++) ++it1, ++it2;
  EXPECT_EQ(*it1, *it2);
}

TEST(SET, Iterator3) {
  ::set<int> number1 = {13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  auto it1 = number1.end();
  auto it2 = number1.end();
  EXPECT_EQ(it1 == it2, true);
}

TEST(SET, Iterator4) {
  ::set<int> number1 = {13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  auto it1 = number1.end();
  auto it2 = number1.end();
  EXPECT_EQ(it1 != it2, false);
}

TEST(SET, Iterator5) {
  ::set<int> number1 = {13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  auto it1 = number1.end();
  auto it2 = number1.end();
  EXPECT_EQ(it1 == it2, true);
}

TEST(Set, Iterator6) {
  std::set<int> std_temp{13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  ::set<int> temp{13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};

  EXPECT_EQ(*(std_temp.begin()), *(temp.begin()));
}

TEST(Set, Iterator7) {
  std::set<int> std_temp{13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  ::set<int> temp{13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  auto std_it = --std_temp.end();
  auto it = temp.rbegin();
  --std_it;
  --it;
  EXPECT_EQ(*std_it, *it);
}

TEST(SET, Merge1) {
  ::set<int> number1 = {13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  std::set<int> number2 = {13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  ::set<int> number11 = {12, 41, 19, 109, 1234567};
  std::set<int> number22 = {12, 41, 19, 109, 1234567};
  number1.merge(number11);
  number2.merge(number22);
  EXPECT_EQ(number1.size(), number2.size());
  auto it1 = number1.begin();
  for (auto it2 = number2.begin(); it2 != number2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
}

TEST(Set, Emplase2) {
  ::set<int> temp = {13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  std::set<int> std_temp = {13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  auto temp_it = temp.insert_many(100, 300, 142, 400);
  auto std_temp_it = std_temp.emplace(142);
  EXPECT_EQ(*(temp_it[2].first), *(std_temp_it.first));
  EXPECT_EQ(temp_it[2].second, std_temp_it.second);
}

TEST(Set, Initializer_list) {
  std::set<int> std_temp{13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  ::set<int> temp{13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  EXPECT_EQ(std_temp.size(), temp.size());
  std::set<int, char> std_empty_temp{};
  std::set<int, char> empty_temp{};
  EXPECT_EQ(std_empty_temp.size(), empty_temp.size());
}

TEST(Set, Copy) {
  std::set<int> std_copy_temp{13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  std::set<int> std_temp = std_copy_temp;
  ::set<int> copy_temp{13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  ::set<int> temp = copy_temp;
  auto std_it = std_temp.begin();
  auto it = temp.begin();
  for (; std_it != std_temp.end(); ++std_it, ++it)
    EXPECT_EQ(*std_it, *it);
}

TEST(Set, Move) {
  std::set<int> std_moving_temp{13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  std::set<int> std_temp = std::move(std_moving_temp);
  ::set<int> moving_temp{13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  ::set<int> temp = std::move(moving_temp);
  auto std_it = std_temp.begin();
  auto it = temp.begin();
  for (; std_it != std_temp.end(); ++std_it, ++it)
    EXPECT_EQ(*std_it, *it);
  std::set<int> std_null_temp;
  std::set<int> std_temp_2 = std::move(std_null_temp);
  ::set<int> null_temp;
  ::set<int> temp_2 = std::move(null_temp);
  EXPECT_EQ(std_null_temp.size(), null_temp.size());
  EXPECT_EQ(std_temp_2.size(), temp_2.size());
}

TEST(Set, Move2) {
  std::set<int> std_temp{13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  ::set<int> temp{13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  std::set<int> std_temp_other{855, 743, 645, 523, 446, 132, -1123};
  ::set<int> temp_other{855, 743, 645, 523, 446, 132, -1123};
  std_temp_other = std::move(std_temp);
  temp_other = std::move(temp);
  auto std_it = std_temp_other.begin();
  auto it = temp_other.begin();
  for (; std_it != std_temp_other.end(); ++std_it, ++it)
    EXPECT_EQ(*std_it, *it);
}

TEST(Set, Empty) {
  std::set<int> std_temp{13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  ::set<int> temp{13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  EXPECT_EQ(std_temp.empty(), temp.empty());
  std::set<int, char> std_empty_temp{};
  std::set<int, char> empty_temp{};
  EXPECT_EQ(std_empty_temp.empty(), empty_temp.empty());
}

TEST(Set, Size) {
  std::set<int> std_temp{13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  ::set<int> temp{13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  EXPECT_EQ(std_temp.size(), temp.size());
  std::set<int, char> std_empty_temp{};
  std::set<int, char> empty_temp{};
  EXPECT_EQ(std_empty_temp.size(), empty_temp.size());
}

TEST(Set, Size2) {
  std::set<int, char> std_empty_temp{};
  std::set<int, char> empty_temp{};
  EXPECT_EQ(std_empty_temp.max_size(), empty_temp.max_size());
}

TEST(Set, Clear) {
  std::set<int> std_temp{13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  ::set<int> temp{13, 29, 34, 44, 56, 667, 24, 31, 0, 10, 5};
  std_temp.clear();
  temp.clear();
  std::set<int, char> std_empty_temp{};
  std::set<int, char> empty_temp{};
  EXPECT_EQ(std_temp.size(), std_empty_temp.size());
  EXPECT_EQ(temp.size(), empty_temp.size());
}

TEST(SET, Addition1) {
  ::set<double> number1 = {354, -100, 50,   1, 2, 3, 124, 5,
                              4,   6,    -199, 7, 8, 9, 0,   10};
  std::set<double> number2 = {354, -100, 50,   1, 2, 3, 124, 5,
                              4,   6,    -199, 7, 8, 9, 0,   10};
  EXPECT_EQ(number1.size(), number2.size());
  auto it1 = number1.begin();
  for (auto it2 = number2.begin(); it2 != number2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(number1.size(), number2.size());
}

TEST(SET, Addition2) {
  ::set<double> number1;
  std::set<double> number2;
  for (double i = 0; i < 100; i++) {
    number1.insert(i);
    number2.insert(i);
  }
  number1.erase(43);
  number2.erase(43);
  number1.erase(24);
  number2.erase(24);
  number1.erase(64);
  number2.erase(64);
  number1.erase(23);
  number2.erase(23);
  number1.erase(6);
  number2.erase(6);
  for (double i = 10; i < 40; i++) {
    number1.erase(i);
    number2.erase(i);
  }
  auto it1 = number1.begin();
  auto it2 = number2.begin();
  EXPECT_EQ(number1.size(), number2.size());
  EXPECT_EQ(*it1, *it2);
}

TEST(SET, Addition3) {
  ::set<double> number1 = {354, -100, 50,   1, 2, 3, 124, 5,
                              4,   6,    -199, 7, 8, 9, 0,   10};
  std::set<double> number2 = {354, -100, 50,   1, 2, 3, 124, 5,
                              4,   6,    -199, 7, 8, 9, 0,   10};
  EXPECT_EQ(number1.size(), number2.size());
  auto it1 = number1.begin();
  for (auto it2 = number2.begin(); it2 != number2.end(); ++it1, ++it2)
    EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(number1.size(), number2.size());
}

TEST(SET, Addition4) {
  ::set<double> number1 = {354, -100, 50,   1, 2, 3, 124, 5,
                              4,   6,    -199, 7, 8, 9, 0,   10};
  std::set<double> number2 = {354, -100, 50,   1, 2, 3, 124, 5,
                              4,   6,    -199, 7, 8, 9, 0,   10};
  EXPECT_EQ(number1.size(), number2.size());
  auto it1 = number1.begin();
  ++it1;
  it1++;
  --it1;
  it1--;
  ::set<double>::const_iterator it2 = number1.begin();
  ++it2;
  it2++;
  --it2;
  it2--;
  ::set<double>::const_iterator it3 = --number1.end();
  for (int i = 0; i < 100; i++) {
    if (it3 != number1.begin()) break;
  }
  EXPECT_EQ(number1.size(), number2.size());
  ::set<double>::const_iterator it4 = number1.rbegin();
  while (it4 != number1.begin()) {
    it4--;
  }
  EXPECT_EQ(number1.size(), number2.size());
}
