#include "stack.h"

class StackTest : public ::testing::Test {
 protected:
  void SetUp() override {}
  ::stack<int> my_stack_empty_;
  ::stack<int> my_stack_full_{2, 5, 7, 10};
  struct new_type {
    char a_char = 'd';
    double a_double = 2.3;
  };
  new_type buff;
};

TEST_F(StackTest, default_constructor) {
  ASSERT_EQ(my_stack_empty_.size(), 0);
  ASSERT_TRUE(my_stack_empty_.empty());
}

TEST_F(StackTest, list_constructor) {
  ASSERT_FALSE(my_stack_full_.empty());
  ASSERT_EQ(my_stack_full_.size(), 4);
  ASSERT_EQ(my_stack_full_.top(), 10);
}

TEST_F(StackTest, copy_constructor) {
  ::stack<int> new_stack(my_stack_full_);
  ASSERT_FALSE(new_stack.empty());
  ASSERT_EQ(new_stack.size(), 4);
  ASSERT_EQ(new_stack.top(), 2);
  new_stack.pop();
  ASSERT_EQ(new_stack.size(), 3);
  ASSERT_EQ(new_stack.top(), 5);
}

TEST_F(StackTest, move_contructor) {
  ::stack<int> new_stack(std::move(my_stack_full_));
  ASSERT_EQ(new_stack.top(), 10);
  ASSERT_EQ(new_stack.size(), 4);
  ASSERT_FALSE(new_stack.empty());
  ::stack<int> new_stack_empty(std::move(my_stack_full_));
  ASSERT_TRUE(new_stack_empty.empty());
  ASSERT_EQ(new_stack_empty.size(), 0);
}

TEST_F(StackTest, over_operator_move) {
  ::stack<int> new_stack_empty;
  new_stack_empty = std::move(my_stack_full_);
  ASSERT_EQ(new_stack_empty.size(), 4);
  ASSERT_FALSE(new_stack_empty.empty());
  ASSERT_EQ(new_stack_empty.top(), 10);
  ::stack<int> temp_stack{1, 2, 3, 4, 5};
  new_stack_empty = std::move(temp_stack);
  ASSERT_EQ(new_stack_empty.size(), 5);
  ASSERT_FALSE(new_stack_empty.empty());
  ASSERT_EQ(new_stack_empty.top(), 5);
  new_stack_empty = std::move(my_stack_empty_);
  ASSERT_EQ(new_stack_empty.size(), 0);
  ASSERT_TRUE(new_stack_empty.empty());
}

TEST_F(StackTest, over_operator_copy) {
  my_stack_full_ = my_stack_full_;
  ASSERT_FALSE(my_stack_full_.empty());
  ASSERT_EQ(my_stack_full_.top(), 10);
  ASSERT_EQ(my_stack_full_.size(), 4);
  ::stack<int> new_stack_full{10, 20, 30};
  new_stack_full = my_stack_full_;
  ASSERT_FALSE(my_stack_full_.empty());
  ASSERT_EQ(my_stack_full_.top(), 10);
  ASSERT_EQ(my_stack_full_.size(), 4);
  new_stack_full = my_stack_empty_;
  ASSERT_FALSE(my_stack_full_.empty());
  ASSERT_EQ(my_stack_full_.top(), 10);
  ASSERT_EQ(my_stack_full_.size(), 4);
}

TEST_F(StackTest, empty_function) {
  ASSERT_FALSE(my_stack_full_.empty());
  ASSERT_TRUE(my_stack_empty_.empty());
}

TEST_F(StackTest, size_function) {
  ASSERT_EQ(my_stack_full_.size(), 4);
  ASSERT_EQ(my_stack_empty_.size(), 0);
}

TEST_F(StackTest, push_functin) {
  my_stack_full_.push(32);
  my_stack_empty_.push(2);
  ASSERT_EQ(my_stack_full_.top(), 32);
  ASSERT_EQ(my_stack_empty_.top(), 2);
}

TEST_F(StackTest, pop_function) {
  my_stack_full_.pop();
  ASSERT_EQ(my_stack_full_.top(), 7);
  my_stack_full_.pop();
  ASSERT_EQ(my_stack_full_.top(), 5);
}

TEST_F(StackTest, swap_function) {
  new_type buff_1;
  buff_1.a_char = 's';
  buff_1.a_double = 100.12;
  ::stack<new_type> buff_new_type{buff, buff};
  ::stack<new_type> buff_new_type_1{buff_1, buff_1, buff_1};
  buff_new_type.swap(buff_new_type_1);
  ASSERT_EQ(buff_new_type.top().a_double, 100.12);
  ASSERT_EQ(buff_new_type.top().a_char, 's');
  ASSERT_EQ(buff_new_type_1.top().a_double, 2.3);
  ASSERT_EQ(buff_new_type_1.top().a_char, 'd');
}

TEST_F(StackTest, emplace_function) {
  my_stack_full_.emplace_front(48);
  ASSERT_EQ(my_stack_full_.top(), 48);
}

TEST_F(StackTest, emplace_many_arg_function) {
  my_stack_full_.emplace_front(1, 2, 3, 4, 5, 6, 7, 8, 9);
  for (int i = 9; i != 0; --i) {
    ASSERT_EQ(my_stack_full_.top(), i);
    my_stack_full_.pop();
  }
}