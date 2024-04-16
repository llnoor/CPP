#include "tree/tests.cc"

#include <gtest/gtest.h>

#include "array/test.cc"
#include "list/main.cc"
#include "map/test_map.cc"
#include "multiset/test_multiset.cc"
#include "queue/main.cc"
#include "set/test_set.cc"
#include "stack/main.cc"
#include "vector/test.cc"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}