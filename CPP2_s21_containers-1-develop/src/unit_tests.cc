#include <gtest/gtest.h>

#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#include "s21_containers.h"
#include "s21_containersplus.h"

// Vector
class VectorTest : public ::testing::Test {
 public:
  s21::Vector<int> int_vector = {1, 2, 3, 4, 5, 6};
  s21::Vector<int> const const_vector = {1, 2, 3, 4, 5, 6};
  s21::Vector<float> float_vector = {1.342, 2.123, 3.978, 4.43, 5.3, 0};
  s21::Vector<double> double_vector = {4.34, 42.1123, 23.123, 6.43, 5.31, 0.02};
  s21::Vector<char> char_vector = {'a', 'b', 'c', 'd'};
  s21::Vector<std::string> string_vector = {"one", "two", "three"};
  s21::Vector<int> empty_vector;

  std::vector<int> int_vector_std = {1, 2, 3, 4, 5, 6};
  std::vector<int> const const_vector_std = {1, 2, 3, 4, 5, 6};
  std::vector<float> float_vector_std = {1.342, 2.123, 3.978, 4.43, 5.3, 0};
  std::vector<double> double_vector_std = {4.34, 42.1123, 23.123,
                                           6.43, 5.31,    0.02};
  std::vector<char> char_vector_std = {'a', 'b', 'c', 'd'};
  std::vector<std::string> string_vector_std = {"one", "two", "three"};
  std::vector<int> empty_vector_std;
};

TEST_F(VectorTest, TestAt) {
  int_vector.At(4) = 256;
  int_vector_std.at(4) = 256;
  ASSERT_EQ(int_vector.At(4), int_vector_std.at(4));
}

TEST_F(VectorTest, TestAtConst) {
  ASSERT_EQ(const_vector.At(4), const_vector_std.at(4));
}

TEST_F(VectorTest, TestReferenceOperator) {
  int_vector[3] = 123;
  int_vector_std[3] = 123;
  ASSERT_EQ(int_vector[3], int_vector_std[3]);
}

TEST_F(VectorTest, TestReferenceOperatorConst) {
  ASSERT_EQ(const_vector[3], const_vector_std[3]);
}

TEST_F(VectorTest, TestFront) {
  ASSERT_EQ(float_vector.Front(), float_vector_std.front());
}

TEST_F(VectorTest, TestBack) {
  ASSERT_EQ(float_vector.Back(), float_vector_std.back());
}

TEST_F(VectorTest, TestData) {
  s21::Vector<int>::iterator it;
  it = int_vector.Begin();
  std::vector<int>::iterator it_std;
  it_std = int_vector_std.begin();
  ASSERT_EQ(it[3], it_std[3]);
}

TEST_F(VectorTest, TestBegin) {
  s21::Vector<int>::iterator it;
  it = int_vector.Begin();
  std::vector<int>::iterator it_std;
  it_std = int_vector_std.begin();
  ASSERT_EQ(*it, *it_std);
}

TEST_F(VectorTest, TestBeginConst) {
  s21::Vector<int>::const_iterator it;
  it = const_vector.Begin();
  std::vector<int>::const_iterator it_std;
  it_std = const_vector_std.begin();
  ASSERT_EQ(*it, *it_std);
}

TEST_F(VectorTest, TestEnd) {
  s21::Vector<int>::iterator it;
  it = int_vector.End() - 1;
  std::vector<int>::iterator it_std;
  it_std = int_vector_std.end() - 1;
  ASSERT_EQ(*it, *it_std);
}

TEST_F(VectorTest, TestEndConst) {
  s21::Vector<int>::const_iterator it;
  it = const_vector.End() - 1;
  std::vector<int>::const_iterator it_std;
  it_std = const_vector_std.end() - 1;
  ASSERT_EQ(*it, *it_std);
}

TEST_F(VectorTest, TestEmpty) { ASSERT_TRUE(empty_vector.Empty()); }
TEST_F(VectorTest, TestEmpty2) { ASSERT_FALSE(string_vector.Empty()); }
TEST_F(VectorTest, TestEmptyConst) { ASSERT_FALSE(const_vector.Empty()); }
TEST_F(VectorTest, TestSize) {
  ASSERT_EQ(string_vector_std.size(), string_vector.Size());
}
TEST_F(VectorTest, TestMaxSize) {
  ASSERT_EQ(string_vector_std.max_size(), string_vector.MaxSize());
}
TEST_F(VectorTest, TestReserve) {
  double_vector.Reserve(14);
  double_vector_std.reserve(14);
  ASSERT_EQ(double_vector.Size(), double_vector_std.size());
  ASSERT_EQ(double_vector.Capacity(), double_vector_std.capacity());
}
TEST_F(VectorTest, TestCapacity) {
  ASSERT_EQ(string_vector_std.capacity(), string_vector.Capacity());
}
TEST_F(VectorTest, TestShrinkToFit) {
  double_vector.Reserve(20);
  double_vector_std.reserve(20);
  double_vector.ShrinkToFit();
  double_vector_std.shrink_to_fit();
  ASSERT_EQ(double_vector.Size(), double_vector_std.size());
  ASSERT_EQ(double_vector.Capacity(), double_vector_std.capacity());
}

TEST_F(VectorTest, TestClear) {
  double_vector.Clear();
  double_vector_std.clear();
  ASSERT_EQ(double_vector.Size(), double_vector_std.size());
  ASSERT_EQ(double_vector.Capacity(), double_vector_std.capacity());
}

TEST_F(VectorTest, TestInsert) {
  char_vector.Insert(char_vector.End(), 't');
  char_vector_std.insert(char_vector_std.end(), 't');
  ASSERT_EQ(char_vector.Back(), char_vector_std.back());
  ASSERT_EQ(char_vector.Size(), char_vector_std.size());
  ASSERT_EQ(char_vector.Capacity(), char_vector_std.capacity());
}

TEST_F(VectorTest, TestInsert2) {
  int_vector.Insert(int_vector.Begin() + 1, 444);
  int_vector_std.insert(int_vector_std.begin() + 1, 444);
  s21::Vector<int>::iterator it = int_vector.Begin();
  std::vector<int>::iterator it_std = int_vector_std.begin();
  while (it != int_vector.End() || it_std != int_vector_std.end()) {
    ASSERT_EQ(*it, *it_std);
    ++it;
    ++it_std;
  }
  ASSERT_EQ(int_vector.Size(), int_vector_std.size());
  ASSERT_EQ(int_vector.Capacity(), int_vector_std.capacity());
}

TEST_F(VectorTest, TestErase) {
  char_vector.Erase(char_vector.End() - 1);
  char_vector_std.erase(char_vector_std.end() - 1);
  ASSERT_EQ(char_vector.Back(), char_vector_std.back());
  ASSERT_EQ(char_vector.Size(), char_vector_std.size());
  ASSERT_EQ(char_vector.Capacity(), char_vector_std.capacity());
}

TEST_F(VectorTest, TestErase2) {
  int_vector.Erase(int_vector.Begin() + 1);
  int_vector_std.erase(int_vector_std.begin() + 1);
  s21::Vector<int>::iterator it = int_vector.Begin();
  std::vector<int>::iterator it_std = int_vector_std.begin();
  while (it != int_vector.End() || it_std != int_vector_std.end()) {
    ASSERT_EQ(*it, *it_std);
    ++it;
    ++it_std;
  }
  ASSERT_EQ(int_vector.Size(), int_vector_std.size());
  ASSERT_EQ(int_vector.Capacity(), int_vector_std.capacity());
}

TEST_F(VectorTest, TestPushBack) {
  int_vector.PushBack(481223);
  int_vector_std.push_back(481223);
  ASSERT_EQ(int_vector.Back(), int_vector_std.back());
  ASSERT_EQ(int_vector.Size(), int_vector_std.size());
  ASSERT_EQ(int_vector.Capacity(), int_vector_std.capacity());
}

TEST_F(VectorTest, TestPushBack2) {
  int_vector.Reserve(20);
  int_vector_std.reserve(20);
  int_vector.PushBack(20);
  int_vector_std.push_back(20);
  ASSERT_EQ(int_vector.Size(), int_vector_std.size());
  ASSERT_EQ(int_vector.Capacity(), int_vector_std.capacity());
  ASSERT_EQ(int_vector.Back(), int_vector_std.back());
}

TEST_F(VectorTest, TestPopBack) {
  int_vector.PopBack();
  int_vector_std.pop_back();
  ASSERT_EQ(int_vector.Back(), int_vector_std.back());
  ASSERT_EQ(int_vector.Size(), int_vector_std.size());
  ASSERT_EQ(int_vector.Capacity(), int_vector_std.capacity());
}

TEST_F(VectorTest, TestSwap) {
  int_vector.Swap(empty_vector);
  int_vector_std.swap(empty_vector_std);
  ASSERT_EQ(int_vector.Size(), int_vector_std.size());
  ASSERT_EQ(int_vector.Capacity(), int_vector_std.capacity());
  ASSERT_EQ(empty_vector.Size(), empty_vector_std.size());
  ASSERT_EQ(empty_vector.Capacity(), empty_vector_std.capacity());
  while (!empty_vector.Empty() && !empty_vector_std.empty()) {
    ASSERT_EQ(empty_vector.Back(), empty_vector_std.back());
    empty_vector.PopBack();
    empty_vector_std.pop_back();
  }
  ASSERT_EQ(int_vector.Empty(), int_vector_std.empty());
  ASSERT_TRUE(int_vector.Empty());
}

TEST_F(VectorTest, TestInsertMany) {
  int_vector.InsertMany(int_vector.Begin() + 1, 162342);
  int_vector_std.emplace(int_vector_std.begin() + 1, 162342);
  ASSERT_EQ(int_vector.Size(), int_vector_std.size());
  ASSERT_EQ(int_vector.Capacity(), int_vector_std.capacity());
  while (!int_vector.Empty() && !int_vector_std.empty()) {
    ASSERT_EQ(int_vector.Back(), int_vector_std.back());
    int_vector.PopBack();
    int_vector_std.pop_back();
  }
}

TEST_F(VectorTest, TestInsertMany2) {
  int_vector.InsertMany(int_vector.Begin() + 1, 4234, 23423, 234234, 432,
                        2423423, 234242, 4234234, 4234234, 4324234, 42342342,
                        2342342, 234234, 234234, 234, 23, 2, 11);
  s21::Vector<int> result{1,      4234,    23423,   234234,  432,      2423423,
                          234242, 4234234, 4234234, 4324234, 42342342, 2342342,
                          234234, 234234,  234,     23,      2,        11,
                          2,      3,       4,       5,       6};
  s21::Vector<int>::iterator it = int_vector.Begin();
  s21::Vector<int>::iterator it_res = result.Begin();
  while (it != int_vector.End() || it_res != result.End()) {
    ASSERT_EQ(*it, *it_res);
    ++it;
    ++it_res;
  }
}

TEST_F(VectorTest, TestInsertManyBack) {
  int_vector.InsertManyBack(162342);
  int_vector_std.emplace_back(162342);
  ASSERT_EQ(int_vector.Size(), int_vector_std.size());
  ASSERT_EQ(int_vector.Capacity(), int_vector_std.capacity());
  while (!int_vector.Empty() && !int_vector_std.empty()) {
    ASSERT_EQ(int_vector.Back(), int_vector_std.back());
    int_vector.PopBack();
    int_vector_std.pop_back();
  }
}

TEST_F(VectorTest, TestInsertManyBack2) {
  int_vector.InsertManyBack(1, 2, 3, 4, 5, 6, 7, 8);
  for (int i = 1; i <= 8; i++) {
    int_vector_std.push_back(i);
  }
  ASSERT_EQ(int_vector.Size(), int_vector_std.size());
  ASSERT_EQ(int_vector.Capacity(), int_vector_std.capacity());
  while (!int_vector.Empty() && !int_vector_std.empty()) {
    ASSERT_EQ(int_vector.Back(), int_vector_std.back());
    int_vector.PopBack();
    int_vector_std.pop_back();
  }
}

// Stack

class StackTest : public ::testing::Test {
 public:
  s21::Stack<int> empty_stack;
  std::stack<int> empty_stack_original;
  s21::Stack<int> *int_stack;
  std::stack<int> *int_stack_original;
  s21::Stack<int> *my_stack;
  std::stack<int> *original_stack;
  void SetUp() override {
    int_stack = new s21::Stack<int>;
    int_stack_original = new std::stack<int>;
    int_stack->Push(324);
    int_stack->Push(768678);
    int_stack->Push(54342);
    int_stack->Push(6563);
    int_stack_original->push(324);
    int_stack_original->push(768678);
    int_stack_original->push(54342);
    int_stack_original->push(6563);
    my_stack = new s21::Stack<int>;
    original_stack = new std::stack<int>;
    for (int i = 0; i <= 5; i++) {
      my_stack->Push(i);
      original_stack->push(i);
    }
  }
  void TearDown() override {
    delete int_stack;
    delete int_stack_original;
    delete my_stack;
    delete original_stack;
  }
};

TEST_F(StackTest, TestDefaultConstructor) {
  ASSERT_EQ(empty_stack.Size(), empty_stack_original.size());
}

TEST_F(StackTest, TestCopyConstructor) {
  s21::Stack<int> my_stack_copy(*my_stack);
  std::stack<int> original_stack_copy(*original_stack);
  while (!my_stack_copy.Empty() && !original_stack_copy.empty()) {
    ASSERT_EQ(my_stack_copy.Top(), original_stack_copy.top());
    my_stack_copy.Pop();
    original_stack_copy.pop();
  }
  ASSERT_EQ(my_stack_copy.Empty(), original_stack_copy.empty());
}

TEST_F(StackTest, TestMoveConstructor) {
  s21::Stack<int> my_stack_copy(std::move(*my_stack));
  std::stack<int> original_stack_copy(std::move(*original_stack));
  while (!my_stack_copy.Empty() && !original_stack_copy.empty()) {
    ASSERT_EQ(my_stack_copy.Top(), original_stack_copy.top());
    my_stack_copy.Pop();
    original_stack_copy.pop();
  }
  ASSERT_EQ(my_stack_copy.Empty(), original_stack_copy.empty());
}

TEST_F(StackTest, TestCopyOperator) {
  s21::Stack<int> my_stack_copy = *my_stack;
  std::stack<int> original_stack_copy = *original_stack;
  while (!my_stack_copy.Empty() && !original_stack_copy.empty()) {
    ASSERT_EQ(my_stack_copy.Top(), original_stack_copy.top());
    my_stack_copy.Pop();
    original_stack_copy.pop();
  }
  ASSERT_EQ(my_stack_copy.Empty(), original_stack_copy.empty());
}

TEST_F(StackTest, TestMoveOperator) {
  s21::Stack<int> my_stack_copy = std::move(*my_stack);
  std::stack<int> original_stack_copy = std::move(*original_stack);
  while (!my_stack_copy.Empty() && !original_stack_copy.empty()) {
    ASSERT_EQ(my_stack_copy.Top(), original_stack_copy.top());
    my_stack_copy.Pop();
    original_stack_copy.pop();
  }
  ASSERT_EQ(my_stack_copy.Empty(), original_stack_copy.empty());
}

TEST_F(StackTest, TestTop) {
  ASSERT_EQ(my_stack->Top(), original_stack->top());
}

TEST_F(StackTest, TestSize) {
  ASSERT_EQ(my_stack->Size(), original_stack->size());
}

TEST_F(StackTest, TestSwap) {
  int_stack->Swap(empty_stack);
  int_stack_original->swap(empty_stack_original);
  while (!int_stack->Empty() && !int_stack_original->empty()) {
    ASSERT_EQ(int_stack->Top(), int_stack_original->top());
    int_stack->Pop();
    int_stack_original->pop();
  }
  ASSERT_EQ(int_stack->Empty(), int_stack_original->empty());
}

TEST_F(StackTest, TestEmplaceFront) {
  int_stack->InsertManyFront(481223);
  int_stack_original->emplace(481223);
  while (!int_stack->Empty() && !int_stack_original->empty()) {
    ASSERT_EQ(int_stack->Top(), int_stack_original->top());
    int_stack->Pop();
    int_stack_original->pop();
  }
  ASSERT_EQ(int_stack->Empty(), int_stack_original->empty());
}

// Queue

class TestQueue : public ::testing::Test {
 public:
  s21::Queue<int> empty_queue;
  std::queue<int> empty_queue_original;
  std::deque<int> numbers = {1, 2, 3, 4, 5};
  std::queue<int> std_queue{numbers};
  s21::Queue<int> s21_queue = {1, 2, 3, 4, 5};
  std::queue<int> queue_1;
  s21::Queue<int> queue_2;
  std::deque<std::string> str = {"I Love School"};
  std::queue<std::string> queue_str1{str};
  s21::Queue<std::string> queue_str2 = {"I Love School"};
  std::deque<std::string> string_deque = {"School S21", " in ", "Kazan"};
  std::queue<std::string> std_queue_str{string_deque};
  s21::Queue<std::string> s21_queue_str = {"School S21", " in ", "Kazan"};
  std::deque<std::string> string_deque_2 = {"I ", "from ", "Dagestan"};
  std::queue<std::string> std_queue_2{string_deque_2};
  s21::Queue<std::string> s21_queue_str_2 = {"I ", "from ", "Dagestan"};
};

TEST_F(TestQueue, Constructor_Default) {
  EXPECT_EQ(empty_queue.Empty(), empty_queue_original.empty());
  EXPECT_EQ(empty_queue.Size(), empty_queue_original.size());
}

TEST_F(TestQueue, Constructor_Init) {
  while (!s21_queue.Empty()) {
    EXPECT_EQ(s21_queue.Front(), std_queue.front());
    s21_queue.Pop();
    std_queue.pop();
  }
}

TEST_F(TestQueue, Constructor_Copy) {
  std::queue<int> std_queue_2(std_queue);
  std::queue<int> std_queue_3;
  std_queue_3 = std_queue_2;

  s21::Queue<int> s21_queue_2(s21_queue);
  s21::Queue<int> s21_queue_3;
  s21_queue_3 = s21_queue_2;

  EXPECT_EQ(std_queue.size(), s21_queue.Size());
  EXPECT_EQ(std_queue_2.size(), std_queue_2.size());
  EXPECT_EQ(std_queue_3.size(), s21_queue_3.Size());
  while (!s21_queue.Empty()) {
    EXPECT_EQ(s21_queue.Front(), std_queue.front());
    EXPECT_EQ(s21_queue_2.Front(), std_queue_2.front());
    EXPECT_EQ(s21_queue_3.Front(), std_queue_3.front());
    s21_queue.Pop();
    std_queue.pop();
    s21_queue_2.Pop();
    std_queue_2.pop();
    s21_queue_3.Pop();
    std_queue_3.pop();
  }
}

TEST_F(TestQueue, Constructor_Move) {
  std::queue<int> std_queue_2(std::move(std_queue));
  s21::Queue<int> s21_queue_2(std::move(s21_queue));
  EXPECT_EQ(s21_queue.Empty(), std_queue.empty());
  while (!s21_queue_2.Empty()) {
    EXPECT_EQ(s21_queue_2.Front(), std_queue_2.front());
    s21_queue_2.Pop();
    std_queue_2.pop();
  }

  std::queue<int> std_queue_3{numbers};
  std_queue_2 = std::move(std_queue_3);

  s21::Queue<int> s21_queue_3{1, 2, 3};
  s21_queue_2 = std::move(s21_queue_3);

  EXPECT_EQ(s21_queue_3.Empty(), std_queue_3.empty());
  while (!s21_queue_2.Empty()) {
    EXPECT_EQ(s21_queue_2.Front(), std_queue_2.front());
    s21_queue_2.Pop();
    std_queue_2.pop();
  }
}

TEST_F(TestQueue, Test_Push) {
  for (int i = 0; i < 5; ++i) {
    queue_1.push(i);
    queue_2.Push(i);
    EXPECT_EQ(queue_1.size(), queue_2.Size());
    EXPECT_EQ(queue_1.back(), queue_2.Back());
  }
}

TEST_F(TestQueue, Test_Push_2) {
  queue_str1.push(" S21");
  queue_str2.Push(" S21");
  EXPECT_EQ(queue_str1.size(), queue_str2.Size());
  while (!queue_2.Empty()) {
    EXPECT_EQ(queue_str1.front(), queue_str2.Front());
    queue_str1.pop();
    queue_str2.Pop();
  }
}

TEST_F(TestQueue, Test_Swap) {
  std_queue_str.swap(std_queue_2);
  s21_queue_str.Swap(s21_queue_str_2);
  while (!std_queue_str.empty()) {
    EXPECT_EQ(s21_queue_str.Front(), std_queue_str.front());
    s21_queue_str.Pop();
    std_queue_str.pop();
  }
  while (!std_queue_2.empty()) {
    EXPECT_EQ(s21_queue_str_2.Front(), std_queue_2.front());
    s21_queue_str_2.Pop();
    std_queue_2.pop();
  }
}

TEST_F(TestQueue, Test_InsertManyBack) {
  for (int i = 6; i < 8; ++i) {
    std_queue.push(i);
  }
  s21_queue.InsertManyBack(6, 7, 8);
  while (!std_queue.empty()) {
    EXPECT_EQ(s21_queue.Front(), std_queue.front());
    s21_queue.Pop();
    std_queue.pop();
  }
}

// List

class TestList : public ::testing::Test {
 public:
  std::list<int> empty_list_std;
  s21::List<int> empty_list_s21;
  std::list<int> list_std{1, 2, 3};
  std::list<int> list_std_2{5, 6, 7};
  s21::List<int> list_s21{1, 2, 3};
  s21::List<int> list_s21_2{5, 6, 7};
  std::list<int> list_std_3 = {5, 0, 2};
  s21::List<int> list_s21_3 = {5, 0, 2};
  std::list<int> list_std_4 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::List<int> list_s21_4 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::list<std::string> list_str_std = {"I Love School"};
  s21::List<std::string> list_str_s21 = {"I Love School"};
  std::list<char> list_char_std = {'D', 'A', 'G'};
  s21::List<char> list_char_s21 = {'D', 'A', 'G'};
  std::list<char> list_char_std_2 = {'a', 'b', 'b', 'a', 'c', 'x',
                                     'y', 'y', 'y', 'z', 'z'};
  s21::List<char> list_char_s21_2 = {'a', 'b', 'b', 'a', 'c', 'x',
                                     'y', 'y', 'y', 'z', 'z'};
  std::list<char> list_char_std_3 = {'y', 'c', 'z', 'a', 'a', 'x',
                                     'w', 'v', 't', 'e', 'q'};
  s21::List<char> list_char_s21_3 = {'y', 'c', 'z', 'a', 'a', 'x',
                                     'w', 'v', 't', 'e', 'q'};
  std::list<std::string> std_kazan = {"I study ", " in Kazan"};
  std::list<std::string> std_school = {" at school ", "s21"};
  s21::List<std::string> s21_kazan = {"I study ", " in Kazan"};
  s21::List<std::string> s21_school = {" at school ", "s21"};
};

TEST_F(TestList, Constructor_Default) {
  EXPECT_EQ(empty_list_std.empty(), empty_list_s21.Empty());
  EXPECT_EQ(empty_list_std.size(), empty_list_s21.Size());
}

TEST_F(TestList, Constructor_Size) {
  size_t count = 4;
  std::list<int> list_1(count);
  s21::List<int> list_2(count);
  EXPECT_EQ(list_1.size(), list_2.Size());
}

TEST_F(TestList, Constructor_Init) {
  auto iter_2 = list_s21.Begin();
  for (auto i = list_std.begin(); i != list_std.end(); ++i, ++iter_2) {
    EXPECT_EQ(*i, *iter_2);
  }
}

TEST_F(TestList, Constructor_Copy) {
  std::list<int> list_1(list_std);
  list_std_2 = list_1;
  s21::List<int> list_2(list_s21);
  list_s21_2 = list_2;

  EXPECT_EQ(list_1.size(), list_2.Size());
  EXPECT_EQ(list_std_2.size(), list_s21_2.Size());
  EXPECT_EQ(list_std.size(), list_s21.Size());
  auto it = list_2.Begin();
  auto it2 = list_std_2.begin();
  for (auto i = list_1.begin(); i != list_1.begin(); ++i, ++it) {
    EXPECT_EQ(*i, *it);
  }
  for (auto i = list_std_2.begin(); i != list_std_2.begin(); ++i, ++it2) {
    EXPECT_EQ(*i, *it2);
  }
}

TEST_F(TestList, Constructor_Move) {
  std::list<int> list_1(std::move(list_std));
  s21::List<int> list_2(std::move(list_s21));
  EXPECT_EQ(list_1.size(), list_2.Size());
  EXPECT_EQ(list_std.size(), list_s21.Size());
  auto it = list_2.Begin();
  for (auto i = list_1.begin(); i != list_1.begin(); ++i, ++it) {
    EXPECT_EQ(*i, *it);
  }
  list_std_2 = std::move(list_1);
  s21::List<int> list_s21_2{5, 6, 7};
  list_s21_2 = std::move(list_2);
  EXPECT_EQ(list_1.size(), list_2.Size());
  EXPECT_EQ(list_std_2.size(), list_s21_2.Size());
  auto it2 = list_s21_2.Begin();
  for (auto i = list_std_2.begin(); i != list_std_2.begin(); ++i, ++it) {
    EXPECT_EQ(*i, *it2);
  }
}

TEST_F(TestList, Test_PushFront) {
  std::list<int> list1;
  s21::List<int> list2;
  for (int i = 0; i < 5; ++i) {
    list1.push_front(i);
    list2.PushFront(i);
    EXPECT_EQ(list1.size(), list2.Size());
    EXPECT_EQ(list1.front(), list2.Front());
  }
}

TEST_F(TestList, Test_PushBack) {
  list_str_std.push_back(" S21");
  list_str_s21.PushBack(" S21");
  EXPECT_EQ(list_str_std.size(), list_str_s21.Size());
  auto it = list_str_std.begin();
  for (auto i = list_str_std.begin(); i != list_str_std.end(); ++i, ++it) {
    EXPECT_EQ(*it, *i);
  }
}

TEST_F(TestList, Test_PopFront) {
  auto it = list_std.begin();
  auto it2 = list_s21.Begin();
  EXPECT_EQ(list_std.size(), list_s21.Size());
  EXPECT_EQ(*it, *it2);
  list_std.pop_front();
  list_s21.PopFront();
  it = list_std.begin();
  it2 = list_s21.Begin();
  EXPECT_EQ(list_std.size(), list_s21.Size());
  EXPECT_EQ(*it, *it2);
}

TEST_F(TestList, Test_PopBack) {
  auto it = list_std.end();
  auto it2 = list_s21.End();
  EXPECT_EQ(list_std.size(), list_s21.Size());
  EXPECT_EQ(*(++it), *(++it2));
  list_std.pop_back();
  list_s21.PopBack();
  EXPECT_EQ(list_std.size(), list_s21.Size());
  EXPECT_EQ(*(++it), *(++it2));
}

TEST_F(TestList, Test_FrontBack) {
  EXPECT_EQ(list_char_std.front(), list_char_s21.Front());
  EXPECT_EQ(list_char_std.back(), list_char_s21.Back());
}

TEST_F(TestList, Test_Insert) {
  auto it = --list_str_std.end();
  auto it2 = --list_str_s21.End();
  list_str_std.insert(it, "School");
  list_str_s21.Insert(it2, "School");
  it = list_str_std.begin();
  for (auto i = list_str_std.begin(); i != list_str_std.end(); ++i, ++it) {
    EXPECT_EQ(*it, *i);
  }
  EXPECT_EQ(list_str_std.size(), list_str_s21.Size());
}

TEST_F(TestList, Test_Clear) {
  list_std.clear();
  list_s21.Clear();
  auto it = list_std.end();
  auto it2 = list_s21.End();
  EXPECT_EQ(*it, *it2);
  EXPECT_EQ(list_std.size(), list_s21.Size());
}

TEST_F(TestList, Test_Erase) {
  auto it = ++list_std_2.begin();
  auto it2 = ++list_s21_2.Begin();
  list_std_2.erase(it);
  list_s21_2.Erase(it2);
  EXPECT_EQ(list_std_2.size(), list_s21_2.Size());
  it2 = list_s21_2.Begin();
  for (auto i = list_std_2.begin(); i != list_std_2.end(); ++i, ++it2) {
    EXPECT_EQ(*it2, *i);
  }
}

TEST_F(TestList, Test_Swap) {
  std::list<char> list1;
  s21::List<char> list2;
  list1.swap(list_char_std);
  list2.Swap(list_char_s21);
  auto it1 = list1.begin();
  auto it2 = list2.Begin();
  auto it22 = list_char_s21.Begin();
  EXPECT_EQ(list1.size(), list2.Size());
  EXPECT_EQ(list_char_std.size(), list_char_s21.Size());
  for (auto it11 = list_char_std.begin(); it11 != list_char_std.end();
       ++it11, ++it1, ++it2, ++it22) {
    EXPECT_EQ(*it1, *it2);
    EXPECT_EQ(*it11, *it22);
  }
}

TEST_F(TestList, Test_Merge) {
  list_std_2.merge(list_std_3);
  list_s21_2.Merge(list_s21_3);
  EXPECT_EQ(list_std_3.size(), list_s21_3.Size());
  auto it = list_std_2.begin();
  for (auto i = list_std_2.begin(); i != list_std_2.end(); ++i, ++it) {
    EXPECT_EQ(*i, *it);
  }
}

TEST_F(TestList, Test_Splice) {
  auto it1 = std_kazan.begin();
  ++it1;
  std_kazan.splice(it1, std_school);
  auto it2 = s21_kazan.Begin();
  ++it2;
  s21_kazan.Splice(it2, s21_school);
  it1 = std_kazan.begin();
  it2 = s21_kazan.Begin();
  EXPECT_EQ(std_school.size(), s21_school.Size());
  for (; it1 != std_kazan.end(); it1++, it2++) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST_F(TestList, Test_Reverse) {
  list_std_4.reverse();
  list_s21_4.Reverse();
  auto it2 = list_s21_4.Begin();
  for (auto it1 = list_std_4.begin(); it1 != list_std_4.end(); ++it2, ++it1) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST_F(TestList, Test_Unique) {
  list_char_std_2.unique();
  list_char_s21_2.Unique();
  auto it1 = list_char_std_2.begin();
  EXPECT_EQ(list_char_std_2.size(), list_char_s21_2.Size());
  for (auto it2 = list_char_s21_2.Begin(); it2 != list_char_s21_2.End();
       ++it1, ++it2) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST_F(TestList, Test_Sort) {
  list_char_std_3.sort();
  list_char_s21_3.Sort();
  auto it1 = list_char_std_3.begin();
  EXPECT_EQ(list_char_std_3.size(), list_char_s21_3.Size());
  for (auto it2 = list_char_s21_3.Begin(); it2 != list_char_s21_3.End();
       ++it1, ++it2) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST_F(TestList, Test_InsertMany) {
  std::list<int> std_lst{1, 2, 3, 4, 5};
  auto std_it = std_lst.begin();
  ++std_it;
  ++std_it;
  auto std_i = std_it;
  for (int data = 6; data < 9; ++data) {
    std_i = std_lst.insert(std_it, data);
  }
  s21::List<int> s21_lst{1, 2, 3, 4, 5};
  auto s21_it = s21_lst.Begin();
  ++s21_it;
  ++s21_it;
  auto s21_i = s21_lst.InsertMany(s21_it, 6, 7, 8);
  std_it = std_lst.begin();
  for (s21_it = s21_lst.Begin(); s21_it != s21_lst.End(); ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
  EXPECT_EQ(*s21_i, *std_i);

  for (int data = -2; data < 1; ++data) {
    std_lst.push_front(data);
  }
  s21_lst.InsertManyFront(-2, -1, 0);
  std_it = std_lst.begin();
  for (s21_it = s21_lst.Begin(); s21_it != s21_lst.End(); ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }

  for (int data = 10; data < 15; ++data) {
    std_lst.push_back(data);
  }
  s21_lst.InsertManyBack(10, 11, 12, 13, 14);
  std_it = std_lst.begin();
  for (s21_it = s21_lst.Begin(); s21_it != s21_lst.End(); ++s21_it, ++std_it) {
    EXPECT_EQ(*s21_it, *std_it);
  }
}

// Set

class SetTest : public ::testing::Test {
 public:
  s21::Set<int> empty_set;
  std::set<int> empty_set_std;
  s21::Set<int> one_set = {1};
  s21::Set<int> int_set = {4, 8, 15, 16, 23, 42};
  std::set<int> int_set_std = {4, 8, 15, 16, 23, 42};
  s21::Set<char> char_set = {'a', 'b', 'c'};
  std::set<char> char_set_std = {'a', 'b', 'c'};
  s21::Set<std::string> string_set = {"one", "two", "three"};
  std::set<std::string> string_set_std = {"one", "two", "three"};
  s21::Set<int> first = {4, 8, 15, 16, 23, 42};
  std::set<int> first_std = {4, 8, 15, 16, 23, 42};
  s21::Set<int> second = {1, 2, 3, 4};
  std::set<int> second_std = {1, 2, 3, 4};
  s21::Set<int> big = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
  std::set<int> big_std = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
};

TEST_F(SetTest, TestDefaultConstructor) { EXPECT_TRUE(empty_set.Empty()); }

TEST_F(SetTest, TestInitializerList) {
  EXPECT_EQ(int_set.Size(), int_set_std.size());
}

TEST_F(SetTest, TestCopyConstructor) {
  s21::Set<int> copy_set(int_set);
  auto i = int_set.Begin();
  auto j = copy_set.Begin();
  while (i != int_set.End() && j != copy_set.End()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
}

TEST_F(SetTest, TestMoveConstructor) {
  s21::Set<char> copy_set(std::move(char_set));
  std::set<char> copy_set_std(std::move(char_set_std));
  EXPECT_EQ(char_set.Empty(), char_set_std.empty());
  EXPECT_EQ(copy_set.Size(), copy_set_std.size());
}

TEST_F(SetTest, TestCopyOperator) {
  s21::Set<int> copy_set = int_set;
  auto i = int_set.Begin();
  auto j = copy_set.Begin();
  while (i != int_set.End() && j != copy_set.End()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
}

TEST_F(SetTest, TestMoveOperator) {
  s21::Set<char> copy_set = std::move(char_set);
  std::set<char> copy_set_std = std::move(char_set_std);
  EXPECT_EQ(char_set.Empty(), char_set_std.empty());
  EXPECT_EQ(copy_set.Size(), copy_set_std.size());
}

TEST_F(SetTest, TestEmpty) { EXPECT_TRUE(empty_set.Empty()); }

TEST_F(SetTest, TestSize) {
  EXPECT_EQ(string_set.Size(), string_set_std.size());
}

TEST_F(SetTest, TestMaxSize) {
  EXPECT_EQ(int_set.MaxSize(), int_set_std.max_size());
}

TEST_F(SetTest, TestClear) {
  string_set.Clear();
  string_set_std.clear();
  EXPECT_EQ(string_set.Empty(), string_set_std.empty());
  EXPECT_EQ(string_set.Size(), string_set_std.size());
}

TEST_F(SetTest, TestInsert) {
  int_set.Insert(36);
  int_set_std.insert(36);
  auto i = int_set.Begin();
  std::set<int>::iterator j = int_set_std.begin();
  while (i != int_set.End() && j != int_set_std.end()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
}

TEST_F(SetTest, TestErase) {
  int_set.Erase(int_set.Begin());
  int_set_std.erase(int_set_std.begin());
  auto i = int_set.Begin();
  std::set<int>::iterator j = int_set_std.begin();
  while (i != int_set.End() && j != int_set_std.end()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
  EXPECT_EQ(int_set.Size(), int_set_std.size());
}

TEST_F(SetTest, TestSwap) {
  int_set.Swap(empty_set);
  int_set_std.swap(empty_set_std);
  auto i = empty_set.Begin();
  std::set<int>::iterator j = empty_set_std.begin();
  while (i != empty_set.End() && j != empty_set_std.end()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
  EXPECT_EQ(int_set.Size(), int_set_std.size());
  EXPECT_EQ(empty_set.Size(), empty_set_std.size());
  EXPECT_TRUE(int_set.Empty());
}

TEST_F(SetTest, TestMerge) {
  first.Merge(second);
  first_std.merge(second_std);
  auto i = first.Begin();
  std::set<int>::iterator j = first_std.begin();
  while (i != first.End() && j != first_std.end()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
  EXPECT_EQ(first.Size(), first_std.size());
}

TEST_F(SetTest, TestFind) {
  for (int i = 1; i < 5; i++) {
    EXPECT_EQ(*(second.Find(i)), *(second_std.find(i)));
  }
}

TEST_F(SetTest, TestContains) {
  for (int i = 1; i < 5; i++) {
    EXPECT_TRUE(second.Contains(i));
  }
}

TEST_F(SetTest, TestIteratorOperator) {
  auto iter_begin = int_set.Begin();
  auto iter_end = int_set.End();
  iter_end--;
  --iter_begin;
  ++iter_begin;
  iter_begin++;
  ++iter_begin;
  --iter_begin;
  --iter_begin;
  EXPECT_EQ(*iter_begin, 4);
  EXPECT_EQ(*iter_end, 42);
}

TEST_F(SetTest, TestInsertMany) {
  empty_set.InsertMany(50, 100, 150, 250, 300, 220, 450, 500, 510, 550, 410,
                       200, 700, 123, 4789, 20, 10, 698, 444, 26, 79, 4861, 476,
                       236, 948, 333, 486, 93, 766);
  empty_set.Erase(empty_set.Find(250));
  empty_set.Erase(empty_set.Find(300));
  empty_set.Erase(empty_set.Find(220));
  empty_set.Erase(empty_set.Find(500));
  empty_set.Erase(empty_set.Find(150));
  empty_set.Erase(empty_set.Find(510));
  empty_set.Erase(empty_set.Find(100));
  empty_set.Erase(empty_set.Find(550));
  empty_set.Erase(empty_set.Find(766));
  empty_set.Erase(empty_set.Find(444));
  empty_set.Erase(empty_set.Find(410));
  empty_set.Erase(empty_set.Find(698));
  empty_set.Erase(empty_set.Find(948));
  empty_set.Erase(empty_set.Find(700));
  empty_set.Erase(empty_set.Find(486));
  empty_set.Erase(empty_set.Find(50));
  empty_set.Erase(empty_set.Find(450));
  EXPECT_EQ(empty_set.Size(), 12);
}

TEST_F(SetTest, TestNotEqual) {
  auto iter = int_set.Begin();
  auto iter_std = int_set.End();
  EXPECT_FALSE(iter == iter_std);
}

// Multiset

class MultisetTest : public ::testing::Test {
 public:
  s21::Multiset<int> empty_set;
  std::multiset<int> empty_set_std;
  s21::Multiset<int> int_set = {4, 8, 15, 16, 23, 42};
  std::multiset<int> int_set_std = {4, 8, 15, 16, 23, 42};
  s21::Multiset<char> char_set = {'a', 'b', 'c'};
  s21::Multiset<std::string> string_set = {"one", "two", "three"};
  std::multiset<std::string> string_set_std = {"one", "two", "three"};
  s21::Multiset<int> first = {4, 8, 15, 16, 23, 42};
  std::multiset<int> first_std = {4, 8, 15, 16, 23, 42};
  s21::Multiset<int> second = {1, 2, 3, 4, 8};
  std::multiset<int> second_std = {1, 2, 3, 4, 8};
  s21::Multiset<int> int_set2 = {1, 2, 2, 3, 4, 5, 5, 5, 5};
  std::multiset<int> int_set2_std = {1, 2, 2, 3, 4, 5, 5, 5, 5};
};

TEST_F(MultisetTest, TestDefaultConstructor) { EXPECT_TRUE(empty_set.Empty()); }

TEST_F(MultisetTest, TestInitializerList) {
  EXPECT_EQ(int_set.Size(), int_set_std.size());
}

TEST_F(MultisetTest, TestCopyConstructor) {
  s21::Multiset<int> copy_set(int_set);
  auto i = int_set.Begin();
  auto j = copy_set.Begin();
  while (i != int_set.End() && j != copy_set.End()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
}

TEST_F(MultisetTest, TestMoveConstructor) {
  s21::Multiset<char> copy_set(std::move(char_set));
  EXPECT_TRUE(char_set.Empty());
  EXPECT_EQ(copy_set.Size(), 3);
}

TEST_F(MultisetTest, TestCopyOperator) {
  s21::Multiset<int> copy_set = int_set;
  auto i = int_set.Begin();
  auto j = copy_set.Begin();
  while (i != int_set.End() && j != copy_set.End()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
}

TEST_F(MultisetTest, TestMoveOperator) {
  s21::Multiset<char> copy_set = std::move(char_set);
  EXPECT_TRUE(char_set.Empty());
  EXPECT_EQ(copy_set.Size(), 3);
}

TEST_F(MultisetTest, TestEmpty) { EXPECT_TRUE(empty_set.Empty()); }

TEST_F(MultisetTest, TestSize) {
  EXPECT_EQ(string_set.Size(), string_set_std.size());
}

TEST_F(MultisetTest, TestMaxSize) {
  EXPECT_EQ(int_set.MaxSize(), int_set_std.max_size());
}

TEST_F(MultisetTest, TestClear) {
  string_set.Clear();
  string_set_std.clear();
  EXPECT_EQ(string_set.Empty(), string_set_std.empty());
  EXPECT_EQ(string_set.Size(), string_set_std.size());
}

TEST_F(MultisetTest, TestInsert) {
  int_set.Insert(16);
  int_set_std.insert(16);
  auto i = int_set.Begin();
  std::multiset<int>::iterator j = int_set_std.begin();
  while (i != int_set.End() && j != int_set_std.end()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
}

TEST_F(MultisetTest, TestErase) {
  int_set.Erase(int_set.Begin());
  int_set_std.erase(int_set_std.begin());
  auto i = int_set.Begin();
  std::multiset<int>::iterator j = int_set_std.begin();
  while (i != int_set.End() && j != int_set_std.end()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
  EXPECT_EQ(int_set.Size(), int_set_std.size());
}

TEST_F(MultisetTest, TestSwap) {
  int_set.Swap(empty_set);
  int_set_std.swap(empty_set_std);
  auto i = empty_set.Begin();
  std::multiset<int>::iterator j = empty_set_std.begin();
  while (i != empty_set.End() && j != empty_set_std.end()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
  EXPECT_EQ(int_set.Size(), int_set_std.size());
  EXPECT_EQ(empty_set.Size(), empty_set_std.size());
  EXPECT_TRUE(int_set.Empty());
}

TEST_F(MultisetTest, TestMerge) {
  first.Merge(second);
  first_std.merge(second_std);
  auto i = first.Begin();
  std::multiset<int>::iterator j = first_std.begin();
  while (i != first.End() && j != first_std.end()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
  EXPECT_EQ(first.Size(), first_std.size());
}

TEST_F(MultisetTest, TestCount) {
  for (int i = 1; i <= 5; i++) {
    EXPECT_EQ(int_set2.Count(i), int_set2_std.count(i));
  }
}

TEST_F(MultisetTest, TestFind) {
  for (int i = 1; i < 5; i++) {
    EXPECT_EQ(*(second.Find(i)), *(second_std.find(i)));
  }
}

TEST_F(MultisetTest, TestContains) {
  for (int i = 1; i < 5; i++) {
    EXPECT_TRUE(second.Contains(i));
  }
}

TEST_F(MultisetTest, TestEqualRange) {
  for (int i = 1; i < 5; i++) {
    EXPECT_EQ(*(second.EqualRange(i).first),
              *(second_std.equal_range(i).first));
    EXPECT_EQ(*(second.EqualRange(i).second),
              *(second_std.equal_range(i).second));
  }
}

TEST_F(MultisetTest, TestLowerBound) {
  for (int i = 1; i < 8; i++) {
    EXPECT_EQ(*(second.LowerBound(i)), *(second_std.lower_bound(i)));
  }
  auto iter = second.End();
  ASSERT_EQ(iter, second.LowerBound(10));
}

TEST_F(MultisetTest, TestUpperBound) {
  for (int i = 1; i <= 5; i++) {
    EXPECT_EQ(*(second.UpperBound(i)), *(second_std.upper_bound(i)));
  }
  auto iter = second.End();
  ASSERT_EQ(iter, second.UpperBound(10));
}

// Map

class MapTest : public ::testing::Test {
 public:
  s21::Map<int, char> empty_map;
  std::map<int, char> std_empty_map;
  s21::Map<int, int> my_map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> std_map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::Map<int, std::string> string_map = {
      {1, "one"}, {2, "two"}, {3, "three"}};
  std::map<int, std::string> string_map_std = {
      {1, "one"}, {2, "two"}, {3, "three"}};
};

TEST_F(MapTest, TestDefaultConstructor) { EXPECT_TRUE(empty_map.Empty()); }

TEST_F(MapTest, TestInitializerList) {
  EXPECT_EQ(my_map.Size(), std_map.size());
}

TEST_F(MapTest, TestCopyConstructor) {
  s21::Map<int, char> my_map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::Map<int, char> copy_map(my_map2);
  auto i = my_map2.Begin();
  auto j = copy_map.Begin();
  EXPECT_EQ(my_map2.Size(), copy_map.Size());
  while (i != my_map2.End() && j != copy_map.End()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
}

TEST_F(MapTest, TestMoveConstructor) {
  s21::Map<int, char> my_map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::Map<int, char> copy_map(std::move(my_map2));
  EXPECT_TRUE(my_map2.Empty());
  EXPECT_EQ(copy_map.Size(), 3);
}

TEST_F(MapTest, TestCopyOperator) {
  s21::Map<int, char> my_map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::Map<int, char> copy_map = my_map2;
  auto i = my_map2.Begin();
  auto j = copy_map.Begin();
  while (i != my_map2.End() && j != copy_map.End()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
}

TEST_F(MapTest, TestMoveOperator) {
  s21::Map<int, char> my_map2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::Map<int, char> copy_map = std::move(my_map2);
  EXPECT_TRUE(my_map2.Empty());
  EXPECT_EQ(copy_map.Size(), 3);
}

TEST_F(MapTest, TestAt) {
  for (int i = 1; i <= 3; i++) {
    EXPECT_EQ(my_map.At(i), std_map.at(i));
  }
}

TEST_F(MapTest, TestReferenceOperator) {
  for (int i = 1; i <= 3; i++) {
    EXPECT_EQ(my_map[i], std_map[i]);
  }
}

TEST_F(MapTest, TestEmpty) {
  EXPECT_EQ(empty_map.Empty(), std_empty_map.empty());
}

TEST_F(MapTest, TestSize) {
  EXPECT_EQ(string_map.Size(), string_map_std.size());
}

TEST_F(MapTest, TestMaxSize) {
  EXPECT_EQ(my_map.MaxSize(), std_map.max_size());
}

TEST_F(MapTest, TestClear) {
  string_map.Clear();
  string_map_std.clear();
  EXPECT_EQ(string_map.Empty(), string_map_std.empty());
  EXPECT_EQ(string_map.Size(), string_map_std.size());
}

TEST_F(MapTest, TestInsertPair) {
  bool my_result = string_map.Insert(std::pair{4, "four"}).second;
  bool std_result = string_map_std.insert(std::pair{4, "four"}).second;
  EXPECT_EQ(my_result, std_result);
  auto i = string_map.Begin();
  auto j = string_map_std.begin();
  while (i != string_map.End() && j != string_map_std.end()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
}

TEST_F(MapTest, TestInsertKeyValue) {
  bool my_result = string_map.Insert(4, "four").second;
  bool std_result = string_map_std.insert(std::pair{4, "four"}).second;
  EXPECT_EQ(my_result, std_result);
  auto i = string_map.Begin();
  auto j = string_map_std.begin();
  while (i != string_map.End() && j != string_map_std.end()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
}

TEST_F(MapTest, TestInsertKeyValue2) {
  bool my_result = string_map.Insert(2, "two").second;
  bool std_result = string_map_std.insert(std::pair{2, "two"}).second;
  EXPECT_EQ(my_result, std_result);
  auto i = string_map.Begin();
  auto j = string_map_std.begin();
  while (i != string_map.End() && j != string_map_std.end()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
  EXPECT_EQ(string_map.Size(), string_map_std.size());
}

TEST_F(MapTest, TestInsertKeyValue3) {
  bool my_result = string_map.Insert(0, "zero").second;
  bool std_result = string_map_std.insert(std::pair{0, "zero"}).second;
  EXPECT_EQ(my_result, std_result);
  auto i = string_map.Begin();
  auto j = string_map_std.begin();
  while (i != string_map.End() && j != string_map_std.end()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
}

TEST_F(MapTest, TestInsertOrAssign) {
  bool my_result = string_map.InsertOrAssign(3, "assign").second;
  bool std_result = string_map_std.insert_or_assign(3, "assign").second;
  EXPECT_EQ(my_result, std_result);
  my_result = string_map.InsertOrAssign(4, "four").second;
  std_result = string_map_std.insert_or_assign(4, "four").second;
  EXPECT_EQ(my_result, std_result);
  auto i_right = string_map.Begin();
  auto j_right = string_map_std.begin();
  while (i_right != string_map.End() && j_right != string_map_std.end()) {
    EXPECT_EQ(*i_right, *j_right);
    i_right++;
    j_right++;
  }
  my_result = string_map.InsertOrAssign(0, "zero").second;
  std_result = string_map_std.insert_or_assign(0, "zero").second;
  EXPECT_EQ(my_result, std_result);
  auto i_left = string_map.Begin();
  auto j_left = string_map_std.begin();
  while (i_left != string_map.End() && j_left != string_map_std.end()) {
    EXPECT_EQ(*i_left, *j_left);
    i_left++;
    j_left++;
  }
}

TEST_F(MapTest, TestErase) {
  s21::Map<int, char> my_map_2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> std_map_2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  auto it = my_map_2.Begin();
  it++;
  auto it_std = std_map_2.begin();
  it_std++;
  my_map_2.Erase(it);
  std_map_2.erase(it_std);
  s21::Map<int, char>::iterator i = my_map_2.Begin();
  std::map<int, char>::iterator j = std_map_2.begin();
  while (i != my_map_2.End() && j != std_map_2.end()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
  EXPECT_EQ(my_map_2.Size(), std_map_2.size());
}

TEST_F(MapTest, TestSwap) {
  s21::Map<int, char> my_map_2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> std_map_2 = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  my_map_2.Swap(empty_map);
  std_map_2.swap(std_empty_map);
  s21::Map<int, char>::iterator i = empty_map.Begin();
  std::map<int, char>::iterator j = std_empty_map.begin();
  while (i != empty_map.End() && j != std_empty_map.end()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
  EXPECT_EQ(my_map_2.Size(), std_map_2.size());
  EXPECT_EQ(empty_map.Size(), std_empty_map.size());
  EXPECT_EQ(my_map_2.Empty(), std_map_2.empty());
}

TEST_F(MapTest, TestMerge) {
  s21::Map<int, char> first = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> first_std = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::Map<int, char> second = {{2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'f'}};
  std::map<int, char> second_std = {{2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'f'}};
  first.Merge(second);
  first_std.merge(second_std);
  s21::Map<int, char>::iterator i = first.Begin();
  std::map<int, char>::iterator j = first_std.begin();
  while (i != first.End() && j != first_std.end()) {
    EXPECT_EQ(*i, *j);
    i++;
    j++;
  }
  EXPECT_EQ(first.Size(), first_std.size());
  auto emp = empty_map.End();
  EXPECT_EQ(emp, empty_map.Begin());
  empty_map.Merge(first);
  EXPECT_EQ(empty_map.Size(), 5);
}

TEST_F(MapTest, TestContains) {
  for (int i = 1; i <= 3; i++) {
    EXPECT_TRUE(my_map.Contains(i));
  }
}

// ============Array===============================//

class s21ArrayTest {
 public:
  s21::Array<int, 10> empty_array;
  s21::Array<int, 5> arr_list_init{0, 1, 2, 3, 4};
  const s21::Array<std::string, 5> test{"School", "21", "Kazan", "Array",
                                        "Contnrs"};
  s21::Array<std::string, 5> test_move{"School", "21", "Kazan", "Array",
                                       "Contnrs"};
  s21::Array<double, 10> double_test{1.2, 2.2, 3.3, 4.4, 5.5, 6.6};
  s21::Array<double, 5> copy_array1{2.5, 3.4, 255.3, 1.2, 0.5};
  s21::Array<double, 5> copy_array2{-5.3, 1.18, -4.3, 255.34, 1.23};

  std::array<int, 10> empty_array_std;
  std::array<int, 5> arr_list_init_std{0, 1, 2, 3, 4};
  const std::array<std::string, 5> test_std{"School", "21", "Kazan", "Array",
                                            "Contnrs"};
  std::array<std::string, 5> test_move_std{"School", "21", "Kazan", "Array",
                                           "Contnrs"};
  std::array<double, 10> double_test_std{1.2, 2.2, 3.3, 4.4, 5.5, 6.6};
  std::array<double, 5> orig_array1{2.5, 3.4, 255.3, 1.2, 0.5};
  std::array<double, 5> orig_array2{-5.3, 1.18, -4.3, 255.34, 1.23};
};

TEST(Array, default_constructor) {
  s21ArrayTest arr;
  ASSERT_EQ(arr.empty_array.Size(), arr.empty_array_std.size());
  ASSERT_EQ(arr.empty_array.Empty(), arr.empty_array_std.empty());
}

TEST(Array, initializer_list_constructor) {
  s21ArrayTest arr;
  ASSERT_EQ(arr.arr_list_init.Size(), arr.arr_list_init_std.size());
  ASSERT_EQ(arr.arr_list_init.Back(), arr.arr_list_init_std.back());
  ASSERT_EQ(arr.arr_list_init.Front(), arr.arr_list_init_std.front());
  ASSERT_EQ(arr.arr_list_init.MaxSize(), arr.arr_list_init_std.max_size());
  for (std::size_t i{}; i < arr.arr_list_init.Size(); ++i) {
    ASSERT_EQ(arr.arr_list_init.At(i), arr.arr_list_init_std.at(i));
  }
}

TEST(Array, copy_constructor) {
  s21ArrayTest temp;
  s21::Array<std::string, 5> copy_array(temp.test);
  for (std::size_t i{}; i < copy_array.Size(); ++i) {
    ASSERT_EQ(copy_array[i], temp.test[i]);
  }
}

TEST(Array, move_constructor) {
  s21ArrayTest temp;
  s21::Array<std::string, 5> move_s21(std::move(temp.test_move));
  std::array<std::string, 5> move_std(std::move(temp.test_move_std));
  for (size_t i{}; i < 5; ++i) {
    ASSERT_EQ(move_s21[i], move_std[i]);
    ASSERT_EQ(temp.test_move[i], temp.test_move_std[i]);
  }
}

TEST(Array, operator_test) {
  s21ArrayTest temp;
  s21::Array<double, 10> double_array;
  std::array<double, 10> double_array_std;
  double_array = temp.double_test;
  double_array_std = temp.double_test_std;
  for (size_t i{}; i < double_array.Size(); ++i) {
    ASSERT_EQ(double_array[i], temp.double_test[i]);
    ASSERT_EQ(double_array_std[i], temp.double_test_std[i]);
  }
}

TEST(Array, at_test) {
  s21ArrayTest temp;
  for (size_t i{}; i < temp.test.Size(); ++i)
    ASSERT_EQ(temp.test.At(i), temp.test_std.at(i));
  for (size_t i = 0; i < temp.double_test.Size(); i++)
    ASSERT_DOUBLE_EQ(temp.double_test_std.at(i), temp.double_test.At(i));
}

TEST(Array, at_opertor_test) {
  s21ArrayTest temp;
  for (size_t i{}; i < temp.test.Size(); ++i)
    ASSERT_EQ(temp.test[i], temp.test_std[i]);
  for (size_t i = 0; i < temp.double_test.Size(); i++)
    ASSERT_DOUBLE_EQ(temp.double_test_std[i], temp.double_test[i]);
}

TEST(Array, data_test) {
  s21ArrayTest temp;
  ASSERT_EQ(temp.test_move.Front(), temp.test_move_std.front());
  ASSERT_EQ(temp.test_move.Back(), temp.test_move_std.back());
}

TEST(Array, front_test) {
  s21ArrayTest temp;
  ASSERT_EQ(temp.test_move.Front(), temp.test_move_std.front());
  ASSERT_EQ(temp.test_move.Back(), temp.test_move_std.back());
}

TEST(Array, iterator_test) {
  std::array<int, 5> orig_array1{234, 21, 11, 34, 999};
  s21::Array<int, 5> copy_array1{234, 21, 11, 34, 999};
  int *orig_beg = orig_array1.begin();
  int *copy_beg = copy_array1.Begin();
  int *orig_end = orig_array1.end();
  int *copy_end = copy_array1.End();
  while (orig_beg < orig_end && copy_beg < copy_end) {
    ASSERT_EQ(*orig_beg++, *copy_beg++);
  }
  ASSERT_EQ(orig_array1.size(), copy_array1.Size());
  ASSERT_EQ(orig_array1.max_size(), copy_array1.MaxSize());
  s21::Array<char, 0> copy_ar1;
  ASSERT_TRUE(copy_ar1.Begin() == copy_ar1.End());

  std::cout << copy_ar1.Begin() << std::endl;
  std::cout << copy_ar1.End() << std::endl;
  s21::Array<double, 3> my_arr{2.3, 4.5555, 6.1234};
  double *d = my_arr.Data();
  ASSERT_DOUBLE_EQ(my_arr[0], *d);
}

TEST(Array, fill_test) {
  std::array<size_t, 10> orig_array;
  s21::Array<size_t, 10> my_arr;
  orig_array.fill(555);
  my_arr.Fill(555);
  for (size_t i = 0; i < orig_array.size(); i++)
    ASSERT_EQ(orig_array[i], my_arr[i]);
  ASSERT_EQ(orig_array.size(), my_arr.Size());
}

TEST(Array, move_operator_test) {
  std::array<int, 5> orig_array1{234, 21, 11, 34, 999};
  s21::Array<int, 5> copy_array1{234, 21, 11, 34, 999};
  std::array<int, 5> orig_array2{25};
  s21::Array<int, 5> copy_array2{25};
  orig_array2 = std::move(orig_array1);
  copy_array2 = std::move(copy_array1);
  for (size_t i{}; i < copy_array2.Size(); i++) {
    ASSERT_EQ(orig_array2.at(i), copy_array2.At(i));
  }
  ASSERT_EQ(orig_array1.size(), copy_array1.Size());
  ASSERT_EQ(orig_array1.max_size(), copy_array1.MaxSize());
  ASSERT_EQ(orig_array2.size(), copy_array2.Size());
  ASSERT_EQ(orig_array2.max_size(), copy_array2.MaxSize());
  std::array<char, 0> orig_ar1;
  s21::Array<char, 0> copy_ar1;
  ASSERT_EQ(orig_ar1.empty(), copy_ar1.Empty());
}

TEST(Array, move_constructor_test) {
  std::array<int, 5> orig_array1{234, 21, 11, 34, 999};
  s21::Array<int, 5> copy_array1{234, 21, 11, 34, 999};
  std::array<int, 5> orig_array2(std::move(orig_array1));
  s21::Array<int, 5> copy_array2(std::move(copy_array1));
  for (size_t i{}; i < copy_array2.Size(); i++) {
    ASSERT_EQ(orig_array2.at(i), copy_array2.At(i));
  }
  ASSERT_EQ(orig_array1.size(), copy_array1.Size());
  ASSERT_EQ(orig_array1.max_size(), copy_array1.MaxSize());
  ASSERT_EQ(orig_array2.size(), copy_array2.Size());
  ASSERT_EQ(orig_array2.max_size(), copy_array2.MaxSize());
  std::array<char, 0> orig_ar1;
  s21::Array<char, 0> copy_ar1;
  ASSERT_EQ(orig_ar1.empty(), copy_ar1.Empty());
}

TEST(Array, swap_test) {
  s21ArrayTest logger;
  logger.orig_array1.swap(logger.orig_array2);
  logger.copy_array1.Swap(logger.copy_array2);
  for (int i{}; i < 5; i++) {
    ASSERT_DOUBLE_EQ(logger.orig_array1[i], logger.copy_array1[i]);
    ASSERT_DOUBLE_EQ(logger.orig_array2[i], logger.copy_array2[i]);
  }
  ASSERT_EQ(logger.orig_array1.size(), logger.copy_array1.Size());
  ASSERT_EQ(logger.orig_array2.max_size(), logger.copy_array2.MaxSize());
  ASSERT_EQ(logger.orig_array1.front(), logger.copy_array1.Front());
  ASSERT_EQ(logger.orig_array2.front(), logger.copy_array2.Front());
  ASSERT_EQ(logger.orig_array1.back(), logger.copy_array1.Back());
  ASSERT_EQ(logger.orig_array2.back(), logger.copy_array2.Back());
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
