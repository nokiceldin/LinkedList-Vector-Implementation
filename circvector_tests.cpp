#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "circvector.h"

using namespace std;
using namespace testing;

TEST(CircVectorCore, emptyVecTrue) {
  CircVector<int> v;
  EXPECT_THAT(v.empty(), Eq(true));
  EXPECT_THAT(v.size(), Eq(0));
}

TEST(CircVectorCore, pushEmptyList) {
  CircVector<int> v;
  v.push_back(5);
  EXPECT_THAT(v.empty(), Eq(false));
  EXPECT_THAT(v.size(), Eq(1));
}
TEST(CircVectorCore, PushBackNormal) {
  CircVector<int> v;
  v.push_back(2);
  v.push_back(3);
  EXPECT_THAT(v.at(0), Eq(2));
  EXPECT_THAT(v.at(1), Eq(3));
}
TEST(CircVectorCore, PushFrontNormal) {
  CircVector<int> v;
  v.push_front(2);
  v.push_front(3);
  EXPECT_THAT(v.at(0), Eq(3));
  EXPECT_THAT(v.at(1), Eq(2));
}
TEST(CircVectorCore, PushBackResize) {
  CircVector<int> v(2);
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  EXPECT_THAT(v.size(), Eq(3));
  EXPECT_THAT(v.at(0), Eq(1));
  EXPECT_THAT(v.at(1), Eq(2));
  EXPECT_THAT(v.at(2), Eq(3));
}
TEST(CircVectorCore, PushFrontkResize) {
  CircVector<int> v(2);
  v.push_front(3);
  v.push_front(2);
  v.push_front(1);
  EXPECT_THAT(v.size(), Eq(3));
  EXPECT_THAT(v.at(0), Eq(1));
  EXPECT_THAT(v.at(1), Eq(2));
  EXPECT_THAT(v.at(2), Eq(3));
}
TEST(CircVectorCore, PopFront) {
  CircVector<int> v;
  v.push_front(2);
  v.push_front(3);
  v.pop_front();
  EXPECT_THAT(v.at(0), Eq(2));
  v.pop_front();
  EXPECT_THAT(v.empty(), Eq(true));
}
TEST(CircVectorCore, PopBack) {
  CircVector<int> v;
  v.push_front(2);
  v.push_front(3);
  v.pop_back();
  EXPECT_THAT(v.at(0), Eq(3));
  v.pop_back();
  EXPECT_THAT(v.empty(), Eq(true));
}
TEST(CircVectorCore, PopEmpty) {
  CircVector<int> v;
  EXPECT_THROW(v.pop_back(), runtime_error);
  EXPECT_THROW(v.pop_front(), runtime_error);
}
TEST(CircVectorCore, PopFrontAndBack) {
  CircVector<int> v;
  v.push_front(6);
  v.push_front(5);
  v.push_front(4);
  v.push_front(3);
  v.push_front(2);
  v.push_front(1);
  v.push_front(0);
  v.pop_front();
  EXPECT_THAT(v.at(3), Eq(4));
  v.pop_back();
  EXPECT_THROW(v.at(5), out_of_range);
}
TEST(CircVectorCore, atOutOfRange) {
  CircVector<int> v;
  v.push_front(2);
  v.push_front(3);
  EXPECT_THROW(v.at(3), out_of_range);
}
TEST(CircVectorCore, PushFrontAndBack) {
  CircVector<int> v;
  v.push_back(2);
  v.push_back(3);
  v.push_front(1);
  v.push_front(0);
  v.push_back(4);
  EXPECT_THAT(v.at(0), Eq(0));
  EXPECT_THAT(v.at(1), Eq(1));
  EXPECT_THAT(v.at(2), Eq(2));
  EXPECT_THAT(v.at(3), Eq(3));
  EXPECT_THAT(v.at(4), Eq(4));
}
TEST(CircVectorCore, emptyAfterClear) {
  CircVector<int> v;
  v.push_back(2);
  v.push_back(3);
  EXPECT_THAT(v.at(0), Eq(2));
  v.clear();
  EXPECT_THAT(v.empty(), Eq(true));
}
TEST(CircVectorCore, MixOfEverything) {
  CircVector<int> v;
  v.push_front(3);
  v.push_front(2);
  v.push_front(1);
  v.push_front(0);
  v.push_back(4);
  v.push_back(5);
  v.push_back(6);

  EXPECT_THAT(v.size(), Eq(7));
  EXPECT_THAT(v.empty(), Eq(false));
  EXPECT_THAT(v.at(4), Eq(4));

  v.pop_back();
  v.pop_back();
  v.pop_front();

  EXPECT_THAT(v.size(), Eq(4));
  EXPECT_THAT(v.at(1), Eq(2));

  v.clear();
  EXPECT_THAT(v.empty(), Eq(true));
  EXPECT_THROW(v.at(0), out_of_range);
}

//Augmented
TEST(CircVectorAugmented, copyConstructorEmpty) {
  CircVector<int> v1;
  CircVector<int> v2(v1);

  EXPECT_THAT(v2.empty(), Eq(true));
}
TEST(CircVectorAugmented, copyConstructorValues) {
  CircVector<int> v1;

  v1.push_back(5);
  v1.push_back(4);
  v1.push_back(3);

  CircVector<int> v2(v1);

  EXPECT_THAT(v2.empty(), Eq(false));
  EXPECT_THAT(v2.size(), Eq(3));
  EXPECT_THAT(v2.at(0), Eq(5));
  EXPECT_THAT(v2.at(1), Eq(4));
  EXPECT_THAT(v2.at(2), Eq(3));
}
TEST(CircVectorAugmented, copyConstructorIndependency) {
  CircVector<int> v1;
  CircVector<int> v2(v1);

  v1.push_back(1);
  v1.push_back(2);

  EXPECT_THAT(v2.size(), Eq(0));
  EXPECT_THAT(v1.size(), Eq(2));

  v2.push_back(3);
  v2.push_back(4);
  v2.push_back(5);

  EXPECT_THAT(v2.size(), Eq(3));
  EXPECT_THAT(v1.size(), Eq(2));

  v1.pop_back();
  EXPECT_THAT(v2.size(), Eq(3));
  v2.pop_front();
  EXPECT_THAT(v1.at(0), Eq(1));
  EXPECT_THAT(v2.at(0), Eq(4));
  EXPECT_THAT(v2.at(1), Eq(5));
}
TEST(CircVectorAugmented, listToString) {
  CircVector<int> v;

  v.push_back(1);
  v.push_back(2);

  EXPECT_THAT(v.to_string(), Eq("[1, 2]"));

  v.pop_back();

  EXPECT_THAT(v.to_string(), Eq("[1]"));
}
TEST(CircVectorAugmented, findElementFound) {
  CircVector<int> v;

  v.push_back(1);
  v.push_back(2);
  v.push_back(9);
  v.push_back(7);
  v.push_back(3);

  EXPECT_THAT(v.find(7), Eq(3));
}
TEST(CircVectorAugmented, findFirstElementFound) {
  CircVector<int> v;

  v.push_back(1);
  v.push_back(2);
  v.push_back(9);
  v.push_back(7);
  v.push_back(3);
  v.push_back(7);

  EXPECT_THAT(v.find(7), Eq(3));
}
TEST(CircVectorAugmented, findElementNotFound) {
  CircVector<int> v;

  v.push_back(1);
  v.push_back(2);
  v.push_back(9);
  v.push_back(7);
  v.push_back(3);

  EXPECT_THAT(v.find(4), Eq(-1));
}
TEST(CircVectorAugmented, findOutOfBounds) {
  CircVector<int> v;

  v.push_back(1);
  v.push_back(2);
  v.push_back(9);
  v.push_back(7);
  v.push_back(3);

  EXPECT_THAT(v.find(1), Eq(0));
  EXPECT_THAT(v.find(9), Eq(2));

  EXPECT_THAT(v.find(15), Eq(-1));

  CircVector<int> v2;
  EXPECT_THAT(v2.find(155), Eq(-1));
}
TEST(CircVectorAugmented, removeAtEmptyList) {
  CircVector<int> v;

  EXPECT_THROW(v.remove_at(2), out_of_range);
}
TEST(CircVectorAugmented, removeAtNormalList) {
  CircVector<int> v;

  v.push_back(1);
  v.push_back(2);
  v.push_back(9);
  v.push_back(7);
  v.push_back(3);

  v.remove_at(1);

  EXPECT_THAT(v.at(1), Eq(9));
}
TEST(CircVectorAugmented, removeAtOutOfRange) {
  CircVector<int> v;

  v.push_back(1);
  v.push_back(2);
  v.push_back(9);
  v.push_back(7);
  v.push_back(3);

  EXPECT_THROW(v.remove_at(10), out_of_range);
}
TEST(CircVectorAugmented, operatorCreatesEmpty) {
  CircVector<int> v1;

  v1.push_back(1);
  v1.push_back(2);
  v1.push_back(9);

  CircVector<int> v2;
  v2 = v1;

  EXPECT_THAT(v2.empty(), Eq(false));
  EXPECT_THAT(v2.size(), Eq(3));
  EXPECT_THAT(v2.at(0), Eq(1));
  EXPECT_THAT(v2.at(1), Eq(2));
  EXPECT_THAT(v2.at(2), Eq(9));
}
TEST(CircVectorAugmented, assignOfEmpty) {
  CircVector<int> v1;

  v1.push_back(1);
  v1.push_back(2);

  CircVector<int> v2;
  v1 = v2;

  EXPECT_THAT(v1.empty(), Eq(true));
  EXPECT_THAT(v1.size(), Eq(0));
  EXPECT_THROW(v1.at(0), out_of_range);
}
TEST(CircVectorAugmented, assignSelf) {
  CircVector<int> v1;

  v1.push_back(1);
  v1.push_back(2);

  CircVector<int>& v2 = v1;
  v1 = v2;

  EXPECT_THAT(v1.size(), Eq(2));
  EXPECT_THAT(v1.at(0), Eq(1));
  EXPECT_THAT(v1.at(1), Eq(2));

  v1.pop_front();
  EXPECT_THAT(v1.size(), Eq(1));
  EXPECT_THAT(v1.at(0), Eq(2));
}
TEST(CircVectorAugmented, assignMissingElem) {
  CircVector<int> v1;

  v1.push_back(1);
  v1.push_back(2);
  v1.push_back(3);
  v1.push_back(4);

  CircVector<int> v2;
  v2 = v1;

  EXPECT_THAT(v2.size(), Eq(4));

  EXPECT_THAT(v2.at(0), Eq(1));
  EXPECT_THAT(v2.at(1), Eq(2));
  EXPECT_THAT(v2.at(2), Eq(3));
  EXPECT_THAT(v2.at(3), Eq(4));
}

//Extras
TEST(CircVectorExtras, insertAfterValueAndSize) {
  CircVector<int> v;

  v.push_back(1);
  v.push_back(3);
  EXPECT_THAT(v.size(), Eq(2));
  v.insert_after(0,2);
  EXPECT_THAT(v.size(), Eq(3));

  EXPECT_THAT(v.at(0), Eq(1));
  EXPECT_THAT(v.at(1), Eq(2));
  EXPECT_THAT(v.at(2), Eq(3));
}
TEST(CircVectorExtras, insertAfterOutOfRange) {
  CircVector<int> v;

  v.push_back(1);
  v.push_back(3);

  EXPECT_THROW(v.insert_after(4,2), out_of_range);
}
TEST(CircVectorExtras, insertAfterEmpty) {
  CircVector<int> v;
  EXPECT_THROW(v.insert_after(0,2), out_of_range);
}
TEST(CircVectorExtras, insertAfterResizing) {
  CircVector<int> v(4);
  
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.push_back(5);

  v.insert_after(2,4);

  EXPECT_THAT(v.size(), Eq(5));
  EXPECT_THAT(v.at(0), Eq(1));
  EXPECT_THAT(v.at(1), Eq(2));
  EXPECT_THAT(v.at(2), Eq(3));
}
TEST(CircVectorExtras, removeEvensValuesAndSize) {
  CircVector<int> v;

  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.push_back(4);
  v.push_back(5);
  v.push_back(6);

  EXPECT_THAT(v.size(), Eq(6));
  v.remove_evens();
  EXPECT_THAT(v.size(), Eq(3));
  EXPECT_THAT(v.at(0), Eq(2));
  EXPECT_THAT(v.at(1), Eq(4));
  EXPECT_THAT(v.at(2), Eq(6));
}