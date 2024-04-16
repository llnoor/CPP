#include "queue.h"

class QueueTest : public ::testing::Test {
 protected:
  void SetUp() override {}
  ::queue<int> my_queue_empty_;
  ::queue<int> my_queue_full_{2, 5, 7, 10};
  struct new_type {
    char a_char = 'd';
    double a_double = 2.3;
  };
  new_type buff;
};

TEST_F(QueueTest, default_constructor) {
  ASSERT_EQ(my_queue_empty_.size(), 0);
  ASSERT_TRUE(my_queue_empty_.empty());
}

TEST_F(QueueTest, list_constructor) {
  ASSERT_FALSE(my_queue_full_.empty());
  ASSERT_EQ(my_queue_full_.size(), 4);
  ASSERT_EQ(my_queue_full_.front(), 10);
}

TEST_F(QueueTest, copy_constructor) {
  ::queue<int> new_stack(my_queue_full_);
  ASSERT_FALSE(new_stack.empty());
  ASSERT_EQ(new_stack.size(), 4);
  ASSERT_EQ(new_stack.front(), 10);
  new_stack.pop();
  ASSERT_EQ(new_stack.size(), 3);
  ASSERT_EQ(new_stack.back(), 5);
}

TEST_F(QueueTest, move_contructor) {
  ::queue<int> new_stack(std::move(my_queue_full_));
  ASSERT_EQ(new_stack.front(), 10);
  ASSERT_EQ(new_stack.size(), 4);
  ASSERT_FALSE(new_stack.empty());
  ::queue<int> new_stack_empty(std::move(my_queue_empty_));
  ASSERT_TRUE(new_stack_empty.empty());
  ASSERT_EQ(new_stack_empty.size(), 0);
}

TEST_F(QueueTest, over_operator_move) {
  ::queue<int> new_stack_empty;
  new_stack_empty = std::move(my_queue_full_);
  ASSERT_EQ(new_stack_empty.size(), 4);
  ASSERT_FALSE(new_stack_empty.empty());
  ASSERT_EQ(new_stack_empty.front(), 10);
  ::queue<int> temp_stack{1, 2, 3, 4, 5};
  new_stack_empty = std::move(temp_stack);
  ASSERT_EQ(new_stack_empty.size(), 5);
  ASSERT_FALSE(new_stack_empty.empty());
  ASSERT_EQ(new_stack_empty.front(), 5);
  new_stack_empty = std::move(my_queue_empty_);
  ASSERT_EQ(new_stack_empty.size(), 0);
  ASSERT_TRUE(new_stack_empty.empty());
}

TEST_F(QueueTest, over_operator_copy) {
  my_queue_full_ = my_queue_full_;
  ASSERT_FALSE(my_queue_full_.empty());
  ASSERT_EQ(my_queue_full_.front(), 10);
  ASSERT_EQ(my_queue_full_.size(), 4);
  ::queue<int> new_stack_full{10, 20, 30};
  new_stack_full = my_queue_full_;
  ASSERT_FALSE(my_queue_full_.empty());
  ASSERT_EQ(my_queue_full_.front(), 10);
  ASSERT_EQ(my_queue_full_.size(), 4);
  new_stack_full = my_queue_empty_;
  ASSERT_FALSE(my_queue_full_.empty());
  ASSERT_EQ(my_queue_full_.front(), 10);
  ASSERT_EQ(my_queue_full_.size(), 4);
}

TEST_F(QueueTest, empty_function) {
  ASSERT_FALSE(my_queue_full_.empty());
  ASSERT_TRUE(my_queue_empty_.empty());
}

TEST_F(QueueTest, size_function) {
  ASSERT_EQ(my_queue_full_.size(), 4);
  ASSERT_EQ(my_queue_empty_.size(), 0);
}

TEST_F(QueueTest, push_functin) {
  my_queue_full_.push(32);
  my_queue_empty_.push(2);
  ASSERT_EQ(my_queue_full_.front(), 32);
  ASSERT_EQ(my_queue_empty_.front(), 2);
}

TEST_F(QueueTest, pop_function) {
  my_queue_full_.pop();
  ASSERT_EQ(my_queue_full_.front(), 10);
  my_queue_full_.pop();
  ASSERT_EQ(my_queue_full_.back(), 7);
}

TEST_F(QueueTest, swap_function) {
  new_type buff_1;
  buff_1.a_char = 's';
  buff_1.a_double = 100.12;
  ::queue<new_type> buff_new_type{buff, buff};
  ::queue<new_type> buff_new_type_1{buff_1, buff_1, buff_1};
  buff_new_type.swap(buff_new_type_1);
  ASSERT_EQ(buff_new_type.front().a_double, 100.12);
  ASSERT_EQ(buff_new_type.front().a_char, 's');
  ASSERT_EQ(buff_new_type_1.front().a_double, 2.3);
  ASSERT_EQ(buff_new_type_1.front().a_char, 'd');
}
TEST_F(QueueTest, emplace_function) {
  my_queue_full_.emplace_back(1);
  my_queue_full_.pop();
  my_queue_full_.pop();
  my_queue_full_.pop();
  my_queue_full_.pop();
  ASSERT_EQ(my_queue_full_.back(), 1);
}

TEST_F(QueueTest, emplace_many_arg_function) {
  my_queue_empty_.emplace_back(1, 2, 3, 4);
  for (int i = 1; i != 4; i += 1) {
    ASSERT_EQ(my_queue_empty_.back(), i);
    my_queue_empty_.pop();
  }
}

TEST(QueueFrontTest, EmptyQueue) {
  ::queue<int> q;
  EXPECT_EQ(q.front(), 0);
}

TEST(QueueBackTest, EmptyQueue) {
  ::queue<int> q;
  EXPECT_EQ(q.back(), 0);
}
