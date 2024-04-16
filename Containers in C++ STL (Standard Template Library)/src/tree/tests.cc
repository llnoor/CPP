#include <gtest/gtest.h>

#include "tree.h"

TEST(TreeIteratorTest, DereferenceOperatorConstEmptyTree) {
  ::Tree<std::string> tree;
  EXPECT_EQ(*tree.begin(), "");
}