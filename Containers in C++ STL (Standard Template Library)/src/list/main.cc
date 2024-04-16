#include <list>

#include "list.h"
template <class Type>
bool container_comparison(std::list<Type> std_list, ::list<Type> list) {
  auto it_std_list = std_list.begin();
  auto it_list = list.begin();
  while (it_list != list.end()) {
    auto value = *it_list - *it_std_list;
    if ((value > 1e-7) || (value < -1e-7)) {
      return false;
    }
    it_list++;
    it_std_list++;
  }
  return true;
}

TEST(List, st_cost) {
  ::list<double> list;
  std::list<double> std_list;
  ASSERT_EQ(std_list.size(), list.size());
}

TEST(List, size) {
  ::list<double> list(35);
  std::list<double> std_list(35);
  ASSERT_EQ(std_list.size(), list.size());
  EXPECT_TRUE(container_comparison(std_list, list));
}

TEST(List, initializer_list) {
  ::list<int> list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};
  EXPECT_TRUE(container_comparison(std_list, list));
}

TEST(List, copy) {
  ::list<double> first = {3.4, 2.5, 3.4, 2.423455};
  std::list<double> std_first = {3.4, 2.5, 3.4, 2.423455};
  ::list<double> second = first;
  std::list<double> std_second = std_first;
  EXPECT_TRUE(container_comparison(std_second, second));
}

TEST(List, copy2) {
  ::list<double> first = {3.423, 2.5234, 3.4567, 2.423455};
  ::list<double> second;
  std::list<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  std::list<double> std_second;
  second = first;
  std_second = std_first;
  EXPECT_TRUE(container_comparison(std_second, second));
  EXPECT_TRUE(container_comparison(std_first, first));
}

TEST(List, move) {
  ::list<double> first = {3.423, 2.5234, 3.4567, 2.423455};
  std::list<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  ::list<double> second = std::move(first);
  std::list<double> std_second = std::move(std_first);
  EXPECT_TRUE(container_comparison(std_second, second));
}

TEST(List, move2) {
  ::list<double> first = {3.423, 2.5234, 3.4567, 2.423455};
  ::list<double> second;
  std::list<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  std::list<double> std_second;
  second = std::move(first);
  std_second = std::move(std_first);
  EXPECT_TRUE(container_comparison(std_second, second));
  EXPECT_TRUE(container_comparison(std_first, first));
}

TEST(List, front) {
  ::list<double> first = {3.423, 2.5234, 3.4567, 2.423455};
  std::list<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  ASSERT_NEAR(first.front(), std_first.front(), 1e-7);
}

TEST(List, back) {
  ::list<double> first = {3.423, 2.5234, 3.4567, 2.423455};
  std::list<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  ASSERT_DOUBLE_EQ(first.back(), std_first.back());
}

TEST(List, begin) {
  ::list<double> first = {3.423, 2.5234, 3.4567, 2.423455};
  std::list<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  ASSERT_DOUBLE_EQ(*first.begin(), *std_first.begin());
}

TEST(List, empty) {
  ::list<double> first = {3.423, 2.5234, 3.4567, 2.423455};
  std::list<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  ::list<double> second;
  std::list<double> std_second;
  EXPECT_TRUE(first.empty() == std_first.empty());
  EXPECT_TRUE(second.empty() == std_second.empty());
}

TEST(List, size2) {
  ::list<double> first = {3.423, 2.5234, 3.4567, 2.423455};
  std::list<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  EXPECT_TRUE(first.size() == std_first.size());
}

TEST(List, clear) {
  ::list<double> first = {3.423, 2.5234, 3.4567, 2.423455};
  std::list<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  EXPECT_TRUE(container_comparison(std_first, first));
}

TEST(List, insert) {
  ::list<double> first = {3.423, 2.5234, 3.4567, 2.423455};
  std::list<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  auto it_std_list = std_first.begin();
  auto it_list = first.begin();
  first.insert(it_list, 345.345634);
  std_first.insert(it_std_list, 345.345634);
  EXPECT_TRUE(container_comparison(std_first, first));
  ++it_std_list;
  ++it_std_list;
  ++it_list;
  ++it_list;
  first.insert(it_list, 4325.3456);
  std_first.insert(it_std_list, 4325.3456);
  EXPECT_TRUE(container_comparison(std_first, first));
}

TEST(List, earse) {
  ::list<double> first = {3.423,     2.5234,       3.4567,   2.423455,
                                 42545.123, 4563456.7564, 6543.6436};
  std::list<double> std_first = {3.423,     2.5234,       3.4567,   2.423455,
                                 42545.123, 4563456.7564, 6543.6436};
  auto it_std_list = std_first.begin();
  auto it_list = first.begin();
  std_first.erase(it_std_list);
  first.erase(it_list);
  EXPECT_TRUE(container_comparison(std_first, first));
  it_std_list = std_first.begin();
  it_list = first.begin();
  --it_std_list;
  --it_std_list;
  it_list--;
  it_list--;
  std_first.erase(it_std_list);
  first.erase(it_list);
  EXPECT_TRUE(container_comparison(std_first, first));
}

TEST(List, push_back) {
  ::list<double> first = {3.423, 2.5234, 3.4567, 2.423455};
  std::list<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  first.push_back(534.532);
  first.push_back(0.432456);
  std_first.push_back(534.532);
  std_first.push_back(0.432456);
  EXPECT_TRUE(container_comparison(std_first, first));
}

TEST(List, pop_back) {
  ::list<double> first = {3.423,     2.5234,       3.4567,   2.423455,
                                 42545.123, 4563456.7564, 6543.6436};
  std::list<double> std_first = {3.423,     2.5234,       3.4567,   2.423455,
                                 42545.123, 4563456.7564, 6543.6436};
  first.pop_back();
  first.pop_back();
  std_first.pop_back();
  std_first.pop_back();
  EXPECT_TRUE(container_comparison(std_first, first));
}

TEST(List, push_front) {
  ::list<double> first = {3.423, 2.5234, 3.4567, 2.423455};
  std::list<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  first.push_front(534.532);
  first.push_front(0.432456);
  std_first.push_front(534.532);
  std_first.push_front(0.432456);
  EXPECT_TRUE(container_comparison(std_first, first));
}

TEST(List, pop_front) {
  ::list<double> first = {3.423,     2.5234,       3.4567,   2.423455,
                                 42545.123, 4563456.7564, 6543.6436};
  std::list<double> std_first = {3.423,     2.5234,       3.4567,   2.423455,
                                 42545.123, 4563456.7564, 6543.6436};
  first.pop_front();
  first.pop_front();
  std_first.pop_front();
  std_first.pop_front();
  EXPECT_TRUE(container_comparison(std_first, first));
}

TEST(List, swap) {
  ::list<double> first = {3.423, 2.5234, 3.4567, 2.423455};
  ::list<double> second = {53.543, 234.543, 436.543, 6436.435};
  std::list<double> std_first = {3.423, 2.5234, 3.4567, 2.423455};
  std::list<double> std_second = {53.543, 234.543, 436.543, 6436.435};
  first.swap(second);
  std_first.swap(std_second);
  EXPECT_TRUE(container_comparison(std_first, first));
  EXPECT_TRUE(container_comparison(std_second, second));
}

TEST(List, reverce) {
  ::list<double> first = {3.423,     2.5234,       3.4567,   2.423455,
                                 42545.123, 4563456.7564, 6543.6436};
  std::list<double> std_first = {3.423,     2.5234,       3.4567,   2.423455,
                                 42545.123, 4563456.7564, 6543.6436};
  first.reverse();
  std_first.reverse();
  EXPECT_TRUE(container_comparison(std_first, first));
}

TEST(List, unique) {
  ::list<double> first = {1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4,
                                 5, 6, 6, 6, 7, 7, 8, 8, 8, 9};
  std::list<double> std_first = {1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4,
                                 5, 6, 6, 6, 7, 7, 8, 8, 8, 9};
  first.unique();
  std_first.unique();
  EXPECT_TRUE(container_comparison(std_first, first));
}

TEST(List, sort) {
  ::list<double> first = {3.423,     2.5234,       3.4567,   2.423455,
                                 42545.123, 4563456.7564, 6543.6436};
  std::list<double> std_first = {3.423,     2.5234,       3.4567,   2.423455,
                                 42545.123, 4563456.7564, 6543.6436};
  first.sort();
  std_first.sort();
  EXPECT_TRUE(container_comparison(std_first, first));
}

TEST(List, merge) {
  ::list<double> first = {3.423,    2.5234,  3.4567, 2.423455,
                                 4254.123, 45.7564, 65};
  std::list<double> std_first = {3.423,    2.5234,  3.4567, 2.423455,
                                 4254.123, 45.7564, 65};
  ::list<double> second = {53.543, 234.543, 436.543, 6436.435};
  std::list<double> std_second = {53.543, 234.543, 436.543, 6436.435};
  first.merge(second);
  std_first.merge(std_second);
  EXPECT_TRUE(container_comparison(std_first, first));
  EXPECT_TRUE(container_comparison(std_second, second));
}

TEST(List, splice) {
  ::list<double> first = {3.423,     2.5234,       3.4567,   2.423455,
                                 42545.123, 4563456.7564, 6543.6436};
  std::list<double> std_first = {3.423,     2.5234,       3.4567,   2.423455,
                                 42545.123, 4563456.7564, 6543.6436};
  ::list<double> second = {53.543, 234.543, 436.543, 6436.435};
  std::list<double> std_second = {53.543, 234.543, 436.543, 6436.435};
  auto it_std_list = std_first.begin();
  auto it_list = first.begin();
  it_std_list++;
  it_std_list++;
  ++it_list;
  ++it_list;
  first.splice(it_list, second);
  std_first.splice(it_std_list, std_second);
  EXPECT_TRUE(container_comparison(std_first, first));
  EXPECT_TRUE(container_comparison(std_second, second));
}

TEST(List, splice2) {
  ::list<double> first = {3.423,     2.5234,       3.4567,   2.423455,
                                 42545.123, 4563456.7564, 6543.6436};
  std::list<double> std_first = {3.423,     2.5234,       3.4567,   2.423455,
                                 42545.123, 4563456.7564, 6543.6436};
  ::list<double> second = {53.543, 234.543, 436.543, 6436.435};
  std::list<double> std_second = {53.543, 234.543, 436.543, 6436.435};
  auto it_std_list = std_first.begin();
  auto it_list = first.begin();
  first.splice(it_list, second);
  std_first.splice(it_std_list, std_second);
  EXPECT_TRUE(container_comparison(std_first, first));
  EXPECT_TRUE(container_comparison(std_second, second));
}

TEST(List, max_size) {
  ::list<double> first;
  std::list<double> std_first;
  ASSERT_EQ(first.max_size(), std_first.max_size());
}

TEST(List, list_iterator) {
  ::list<double> first = {3.423, 2.5234, 3.4567, 2.423455};
  ::list<double>::iterator it = first.begin();
  ::list<double>::iterator it_second = std::move(it);
  EXPECT_TRUE(it_second == first.begin());
}

TEST(List, list_iterator2) {
  ::list<double> first = {3.423, 2.5234, 3.4567, 2.423455};
  ::list<double>::iterator it = first.begin();
  ::list<double>::iterator it_second = std::move(it);
  EXPECT_TRUE(it_second == first.begin());
}

TEST(List, list_iterator_const) {
  ::list<double> first = {3.423, 2.5234, 3.4567, 2.423455};
  ::list<double>::const_iterator first_it = first.begin();
  ::list<double>::const_iterator second_it = first_it;
  EXPECT_TRUE(second_it == first.begin());
}

TEST(List, list_iterator_const2) {
  ::list<double> first = {3.423, 2.5234, 3.4567, 2.423455};
  ::list<double>::const_iterator first_it = first.begin();
  ::list<double>::const_iterator second_it = std::move(first_it);
  first_it = second_it;
  EXPECT_TRUE(second_it == first.begin());
}

TEST(List, list_iterator_const3) {
  ::list<double> first = {3.423, 2.5234, 3.4567, 2.423455};
  ::list<double>::const_iterator first_it = first.begin();
  ::list<double>::const_iterator second_it = first.end();
  second_it = std::move(first_it);
  EXPECT_TRUE(second_it == first.begin());
}

TEST(List, list_iterator_const4) {
  ::list<double> first = {3.423, 2.5234, 3.4567, 2.423455};
  ::list<double>::const_iterator first_it = first.begin();
  ::list<double>::const_iterator second_it = first.begin();
  first_it++;
  second_it++;
  ++first_it;
  ++second_it;
  EXPECT_FALSE(first_it != second_it);
}

TEST(List, list_iterator_const5) {
  ::list<double> first = {3.423, 2.5234, 3.4567, 2.423455};
  ::list<double>::const_iterator first_it = first.end();
  ::list<double>::const_iterator second_it = first.end();
  --first_it;
  --second_it;
  first_it--;
  second_it--;
  EXPECT_TRUE(*first_it == *second_it);
}

TEST(List, list_iterator_3) {
  ::list<double> first = {3.423, 2.5234, 3.4567, 2.423455};
  ::list<double>::iterator first_it = first.begin();
  ::list<double>::iterator second_it = first.begin();
  first_it++;
  second_it++;
  EXPECT_FALSE(first_it != second_it);
  EXPECT_TRUE(first_it == second_it);
}

TEST(List, list_iterator_4) {
  const ::list<double> first = {3.423, 2.5234, 3.4567, 2.423455};
  auto first_it = first.begin();
  auto second_it = first.begin();
  first_it++;
  second_it++;
  EXPECT_FALSE(first_it != second_it);
  EXPECT_TRUE(first_it == second_it);
}

TEST(List, exeptions) {
  ::list<int> first = {1, 2, 3, 4, 5};
  ::list<int>::iterator iter1;
  ASSERT_THROW(*iter1, std::invalid_argument);
  ASSERT_THROW(first.erase(first.end()), std::invalid_argument);
}

TEST(List, emplace) {
  ::list<int> first = {2, 3, 4, 5};
  std::list<int> std_first = {2, 3, 4, 5};
  std_first.emplace(std_first.begin(), 1);
  first.emplace(first.begin(), 1);
  EXPECT_TRUE(container_comparison(std_first, first));
}

TEST(List, emplace_many_args) {
  ::list<int> first = {1, 2, 8, 9, 0};
  std::list<int> std_first = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
  auto first_it = ++first.begin();
  first_it++;
  first.emplace(first_it, 3, 4, 5, 6, 7);
  EXPECT_TRUE(container_comparison(std_first, first));
}

TEST(List, emplace_front) {
  ::list<double> first = {2, 3, 4, 5};
  std::list<double> std_first = {2, 3, 4, 5};
  std_first.emplace_front(2.345);
  first.emplace_front(2.345);
  EXPECT_TRUE(container_comparison(std_first, first));
}

TEST(List, emplace_front_many_args) {
  ::list<int> first = {5, 6, 7, 8, 9, 0};
  std::list<int> std_first = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
  first.emplace_front(4, 3, 2, 1);
  EXPECT_TRUE(container_comparison(std_first, first));
}

TEST(List, emplace_back) {
  ::list<double> first = {2, 3, 4, 5};
  std::list<double> std_first = {2, 3, 4, 5};
  std_first.emplace_back(543.2345);
  first.emplace_back(543.2345);
  EXPECT_TRUE(container_comparison(std_first, first));
}

TEST(List, emplace_back_many_args) {
  ::list<int> first = {1, 2, 3, 4, 5};
  std::list<int> std_first = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
  first.emplace_back(6, 7, 8, 9, 0);
  EXPECT_TRUE(container_comparison(std_first, first));
}

TEST(ListInsertTest, InsertAtEnd) {
  ::list<int> myList;

  myList.push_back(1);
  myList.push_back(2);
  myList.push_back(3);

  auto it = myList.end();

  myList.insert(it, 4);

  EXPECT_EQ(myList.back(), 4);
  EXPECT_EQ(myList.size(), 4);
}

TEST(ListPopFrontTest, PopFrontNotEmptyNotEqual) {
  ::list<int> myList;

  myList.push_back(42);
  myList.push_back(43);
  myList.push_back(44);

  myList.pop_front();

  EXPECT_EQ(myList.front(), 43);
}

TEST(ListPopFrontTest, PopFrontOnlyOneElement) {
  ::list<int> myList;

  myList.push_back(42);

  myList.pop_front();

  EXPECT_TRUE(myList.empty());
}

TEST(ListContainerComparisonTest, WithinRange) {
  ::list<double> list = {1.0, 2.0, 3.0};
  std::list<double> std_list = {1.0, 2.0000001, 3.0};

  EXPECT_TRUE(container_comparison(std_list, list));
}

TEST(ListContainerComparisonTest, OutsideRange) {
  ::list<double> list = {1.0, 2.0, 3.0};
  std::list<double> std_list = {1.0, 2.1, 3.0};
  EXPECT_FALSE(container_comparison(std_list, list));
}