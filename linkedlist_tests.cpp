#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "linkedlist.h"

using namespace std;
using namespace testing;

// Core
TEST(LinkedListCore, ListIsEmpty) {
  LinkedList<int> ll;
  EXPECT_THAT(ll.empty(), Eq(true));
  EXPECT_THAT(ll.size(), Eq(0));
}
TEST(LinkedListCore, atGivesThrow) {
  LinkedList<int> ll;
  EXPECT_THROW(ll.at(0), out_of_range);
  EXPECT_THROW(ll.at(10), out_of_range);
}
TEST(LinkedListCore, emptyListPopBack) {
  LinkedList<int> ll;
  EXPECT_THROW(ll.pop_back(), runtime_error);
}
TEST(LinkedListCore, oneElementListPushBackPopBack) {
  LinkedList<int> ll;
  ll.push_back(7);
  EXPECT_THAT(ll.pop_back(), Eq(7));
}
TEST(LinkedListCore, emptyPopFront) {
  LinkedList<int> ll;
  EXPECT_THROW(ll.pop_front(), runtime_error);
}
TEST(LinkedListCore, oneElementPopFront) {
  LinkedList<int> ll;
  ll.push_back(1);
  ll.pop_front();
  EXPECT_THAT(ll.empty(), Eq(true));
  EXPECT_THAT(ll.size(), Eq(0));
}
TEST(LinkedListCore, normalListPopFront) {
  LinkedList<int> ll;
  ll.push_back(1);
  ll.push_back(2);
  ll.push_back(3);
  ll.pop_front();
  
  EXPECT_THAT(ll.at(0), Eq(2));
  EXPECT_THAT(ll.at(1), Eq(3));
}
TEST(LinkedListCore, pushBackPopBackManyElements) {
  LinkedList<int> ll;
  ll.push_back(1);
  ll.push_back(2);
  ll.push_back(3);
  EXPECT_THAT(ll.size(), Eq(3));

  ll.pop_back();
  EXPECT_THROW(ll.at(2), out_of_range);
  EXPECT_THAT(ll.at(0), Eq(1));
  EXPECT_THAT(ll.size(), Eq(2));

  ll.pop_back();
  ll.pop_back();

  EXPECT_THAT(ll.empty(), Eq(true));
  EXPECT_THAT(ll.size(), Eq(0));
}
TEST(LinkedListCore, emptyListPushFront) {
  LinkedList<int> ll;

  EXPECT_THAT(ll.empty(), Eq(true));
  EXPECT_THAT(ll.size(), Eq(0));

  ll.push_front(9);

  EXPECT_THAT(ll.at(0), Eq(9));
}
TEST(LinkedListCore, normalListPushFront) {
  LinkedList<int> ll;

  EXPECT_THAT(ll.empty(), Eq(true));
  EXPECT_THAT(ll.size(), Eq(0));

  ll.push_back(2);
  ll.push_back(3);
  ll.push_back(4);
  ll.push_back(5);
  ll.push_front(1);

  EXPECT_THAT(ll.at(0), Eq(1));
}
TEST(LinkedListCore, clearList) {
  LinkedList<int> ll;

  ll.push_back(2);
  ll.push_back(3);
  ll.push_back(4);
  ll.push_back(5);

  ll.clear();

  EXPECT_THAT(ll.empty(), Eq(true));
  EXPECT_THAT(ll.size(), Eq(0));
}

// Augmented
TEST(LinkedListAugmented, copyConstructorEmpty) {
  LinkedList<int> l1;
  LinkedList<int> l2(l1);

  EXPECT_THAT(l2.empty(), Eq(true));

}
TEST(LinkedListAugmented, copyConstructorValues) {
  LinkedList<int> l1;

  l1.push_back(1);
  l1.push_back(2);

  LinkedList<int> l2(l1);

  EXPECT_THAT(l2.size(), Eq(2));

  EXPECT_THAT(l2.at(0), Eq(1));
  EXPECT_THAT(l2.at(1), Eq(2));
}
TEST(LinkedListAugmented, copyConstructorIndependency) {
  LinkedList<int> l1;
  LinkedList<int> l2(l1);

  l1.push_back(1);
  l1.push_back(2);

  EXPECT_THAT(l2.size(), Eq(0));
  EXPECT_THAT(l1.size(), Eq(2));

  l2.push_back(3);
  l2.push_back(4);
  l2.push_back(5);

  EXPECT_THAT(l2.size(), Eq(3));
  EXPECT_THAT(l1.size(), Eq(2));

  l1.pop_back();
  EXPECT_THAT(l2.size(), Eq(3));
  l2.pop_front();
  EXPECT_THAT(l1.at(0), Eq(1));
  EXPECT_THAT(l2.at(0), Eq(4));
  EXPECT_THAT(l2.at(1), Eq(5));
}
TEST(LinkedListAugmented, listToString) {
  LinkedList<int> ll;

  ll.push_back(1);
  ll.push_back(2);

  EXPECT_THAT(ll.to_string(), Eq("[1, 2]"));

  ll.pop_back();

  EXPECT_THAT(ll.to_string(), Eq("[1]"));
}
TEST(LinkedListAugmented, findElementFound) {
  LinkedList<int> ll;

  ll.push_back(1);
  ll.push_back(2);
  ll.push_back(9);
  ll.push_back(7);
  ll.push_back(3);

  EXPECT_THAT(ll.find(7), Eq(3));
}
TEST(LinkedListAugmented, findFirstElementFound) {
  LinkedList<int> ll;

  ll.push_back(1);
  ll.push_back(2);
  ll.push_back(9);
  ll.push_back(7);
  ll.push_back(3);
  ll.push_back(7);

  EXPECT_THAT(ll.find(7), Eq(3));
}
TEST(LinkedListAugmented, findElementNotFound) {
  LinkedList<int> ll;

  ll.push_back(1);
  ll.push_back(2);
  ll.push_back(9);
  ll.push_back(7);
  ll.push_back(3);

  EXPECT_THAT(ll.find(4), Eq(-1));
}
TEST(LinkedListAugmented, removeAtEmptyList) {
  LinkedList<int> ll;

  EXPECT_THROW(ll.remove_at(2), out_of_range);
}
TEST(LinkedListAugmented, removeAtNormalList) {
  LinkedList<int> ll;

  ll.push_back(1);
  ll.push_back(2);
  ll.push_back(9);
  ll.push_back(7);
  ll.push_back(3);

  ll.remove_at(1);

  EXPECT_THAT(ll.at(1), Eq(9));
}
TEST(LinkedListAugmented, removeAtOutOfRange) {
  LinkedList<int> ll;

  ll.push_back(1);
  ll.push_back(2);
  ll.push_back(9);
  ll.push_back(7);
  ll.push_back(3);

  EXPECT_THROW(ll.remove_at(10), out_of_range);
}
TEST(LinkedListAugmented, operatorCreatesEmpty) {
  LinkedList<int> l1;

  l1.push_back(1);
  l1.push_back(2);
  l1.push_back(9);

  LinkedList<int> l2;
  l2 = l1;

  EXPECT_THAT(l2.empty(), Eq(false));
  EXPECT_THAT(l2.size(), Eq(3));
  EXPECT_THAT(l2.at(0), Eq(1));
  EXPECT_THAT(l2.at(1), Eq(2));
  EXPECT_THAT(l2.at(2), Eq(9));
}
TEST(LinkedListAugmented, assignOfEmpty) {
  LinkedList<int> l1;

  l1.push_back(1);
  l1.push_back(2);

  LinkedList<int> l2;
  l1 = l2;

  EXPECT_THAT(l1.empty(), Eq(true));
  EXPECT_THAT(l1.size(), Eq(0));
  EXPECT_THROW(l1.at(0), out_of_range);
}
TEST(LinkedListAugmented, assignSelf) {
  LinkedList<int> l1;

  l1.push_back(1);
  l1.push_back(2);

  LinkedList<int>& l2 = l1;
  l1 = l2;

  EXPECT_THAT(l1.size(), Eq(2));
  EXPECT_THAT(l1.at(0), Eq(1));
  EXPECT_THAT(l1.at(1), Eq(2));

  l1.pop_front();
  EXPECT_THAT(l1.size(), Eq(1));
  EXPECT_THAT(l1.at(0), Eq(2));
}
TEST(LinkedListAugmented, assignMissingElem) {
  LinkedList<int> l1;

  l1.push_back(1);
  l1.push_back(2);
  l1.push_back(3);
  l1.push_back(4);

  LinkedList<int> l2;
  l2 = l1;

  EXPECT_THAT(l2.size(), Eq(4));

  EXPECT_THAT(l2.at(0), Eq(1));
  EXPECT_THAT(l2.at(1), Eq(2));
  EXPECT_THAT(l2.at(2), Eq(3));
  EXPECT_THAT(l2.at(3), Eq(4));
}
TEST(LinkedListAugmented, findOutOfBounds) {
  LinkedList<int> ll;

  ll.push_back(1);
  ll.push_back(2);
  ll.push_back(9);
  ll.push_back(7);
  ll.push_back(3);

  EXPECT_THAT(ll.find(1), Eq(0));
  EXPECT_THAT(ll.find(9), Eq(2));

  EXPECT_THAT(ll.find(15), Eq(-1));

  LinkedList<int> l2;
  EXPECT_THAT(l2.find(155), Eq(-1));
}

//Extras
TEST(LinkedListExtras, insertAfterValueAndSize) {
  LinkedList<int> ll;

  ll.push_back(1);
  ll.push_back(3);
  EXPECT_THAT(ll.size(), Eq(2));
  ll.insert_after(0,2);
  EXPECT_THAT(ll.size(), Eq(3));

  EXPECT_THAT(ll.at(0), Eq(1));
  EXPECT_THAT(ll.at(1), Eq(2));
  EXPECT_THAT(ll.at(2), Eq(3));
}
TEST(LinkedListExtras, insertAfterOutOfRange) {
  LinkedList<int> ll;

  ll.push_back(1);
  ll.push_back(3);

  EXPECT_THROW(ll.insert_after(4,2), out_of_range);
}
TEST(LinkedListExtras, insertAfterEmpty) {
  LinkedList<int> ll;
  EXPECT_THROW(ll.insert_after(0,2), out_of_range);
}
TEST(LinkedListExtras, removeEvensValuesAndSize) {
  LinkedList<int> ll;

  ll.push_back(1);
  ll.push_back(2);
  ll.push_back(3);
  ll.push_back(4);
  ll.push_back(5);
  ll.push_back(6);

  EXPECT_THAT(ll.size(), Eq(6));
  ll.remove_evens();
  EXPECT_THAT(ll.size(), Eq(3));
  EXPECT_THAT(ll.at(0), Eq(2));
  EXPECT_THAT(ll.at(1), Eq(4));
  EXPECT_THAT(ll.at(2), Eq(6));
}
TEST(LinkedListExtras, removeEvensEmpty) {
  LinkedList<int> ll;

  EXPECT_THAT(ll.empty(), Eq(true));
  ll.remove_evens();
  EXPECT_THAT(ll.empty(), Eq(true));
}


