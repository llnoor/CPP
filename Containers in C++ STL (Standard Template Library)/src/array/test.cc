#include "Array.h"

// using namespace ;

TEST(Array_constructor, default_constructor) {
  ::Array<int, 4> Array;
  std::array<int, 4> stdarray;
  ASSERT_EQ(Array.empty(), stdarray.empty());
  ASSERT_EQ(Array.size(), stdarray.size());
  ASSERT_EQ(Array.max_size(), stdarray.max_size());
}

TEST(Array, def_constructor_int) {
  ::Array<int, 5> Array;
  std::array<int, 5> std_array;

  ASSERT_EQ(Array.empty(), std_array.empty());
  ASSERT_EQ(Array.size(), std_array.size());
}

TEST(Array, def_constructor_char) {
  ::Array<char, 5> Array;
  std::array<char, 5> std_array;

  ASSERT_EQ(Array.empty(), std_array.empty());
  ASSERT_EQ(Array.size(), std_array.size());
}

TEST(Array, def_constructor_int_1) {
  ::Array<int, 5> Array{};
  std::array<int, 5> std_array{};

  ASSERT_EQ(Array.empty(), std_array.empty());
  ASSERT_EQ(Array.size(), std_array.size());
}

TEST(Array, def_constructor_int_2) {
  ::Array<int, 5> Array{1, 2, 3};
  std::array<int, 5> std_array{1, 2, 3};

  ASSERT_EQ(Array.empty(), std_array.empty());
  ASSERT_EQ(Array.size(), std_array.size());
}

TEST(Array, def_constructor_int_3) {
  ::Array<int, 5> Array{1, 2, 3, 4, 5};
  std::array<int, 5> std_array{1, 2, 3, 4, 5};

  ASSERT_EQ(Array.empty(), std_array.empty());
  ASSERT_EQ(Array.size(), std_array.size());
}

TEST(Array, def_at) {
  ::Array<int, 3> Array{1, 2, 3};
  std::array<int, 3> std_array{1, 2, 3};
  Array.at(0) = 100;
  std_array.at(0) = 100;

  ASSERT_EQ(Array.at(0), std_array.at(0));
  ASSERT_EQ(Array.at(1), std_array.at(1));
  ASSERT_EQ(Array.at(2), std_array.at(2));
  ASSERT_EQ(Array.empty(), std_array.empty());
  ASSERT_EQ(Array.size(), std_array.size());
}

TEST(Array, def_operator) {
  ::Array<int, 3> Array{1, 2, 3};
  std::array<int, 3> std_array{1, 2, 3};
  Array[0] = 100;
  std_array[0] = 100;

  ASSERT_EQ(Array.at(0), std_array.at(0));
  ASSERT_EQ(Array.at(1), std_array.at(1));
  ASSERT_EQ(Array.at(2), std_array.at(2));
  ASSERT_EQ(Array.empty(), std_array.empty());
  ASSERT_EQ(Array.size(), std_array.size());
}

TEST(Array, def_front) {
  ::Array<int, 3> Array{1, 2, 3};
  std::array<int, 3> std_array{1, 2, 3};

  ASSERT_EQ(Array.front(), std_array.front());
}

TEST(Array, def_back) {
  ::Array<int, 3> Array{1, 2, 3};
  std::array<int, 3> std_array{1, 2, 3};

  ASSERT_EQ(Array.back(), std_array.back());
}

TEST(Array, def_empty) {
  ::Array<int, 3> Array{1, 2, 3};
  std::array<int, 3> std_array{1, 2, 3};

  ASSERT_EQ(Array.empty(), std_array.empty());
}

TEST(Array, def_empty_1) {
  ::Array<int, 0> Array{};
  std::array<int, 0> std_array{};

  ASSERT_EQ(Array.empty(), std_array.empty());
}

TEST(Array, def_size) {
  ::Array<int, 3> Array{1, 2, 3};
  std::array<int, 3> std_array{1, 2, 3};

  ASSERT_EQ(Array.size(), std_array.size());
}

TEST(Array, def_max_size) {
  ::Array<int, 3> Array{1, 2, 3};
  std::array<int, 3> std_array{1, 2, 3};

  ASSERT_EQ(Array.max_size(), std_array.max_size());
}
