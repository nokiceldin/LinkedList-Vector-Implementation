#pragma once

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

template <typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node *next;

    Node(T data) {
      this->data = data;
      this->next = nullptr;
    }

    Node(T data, Node *next) {
      this->data = data;
      this->next = next;
    }
  };

  size_t list_size;
  Node *list_front;

 public:
  /**
   * Default constructor. Creates an empty `LinkedList`.
   */
  LinkedList() {
    list_size = 0;
    list_front = nullptr;
  }

  /**
   * Returns whether the `LinkedList` is empty (i.e. whether its
   * size is 0).
   */
  bool empty() const {
    return list_size == 0;;
  }

  /**
   * Returns the number of elements in the `LinkedList`.
   */
  size_t size() const {
    return list_size;
  }

  /**
   * Adds the given `T` to the front of the `LinkedList`.
   */
  void push_front(T data) {
    Node* ptr = new Node(data);
    ptr->next = list_front;
    list_front = ptr;
    list_size++;
  }

  /**
   * Adds the given `T` to the back of the `LinkedList`.
   */
  void push_back(T data) {
    Node* newNode = new Node(data);

    if (list_front == nullptr) {
      list_front = newNode;
    }
    else {
      Node* ptr = list_front;
      while (ptr->next != nullptr) {
        ptr = ptr->next;
      }
      ptr->next = newNode;
    }
    list_size++;
  }

  /**
   * Removes the element at the front of the `LinkedList`.
   *
   * If the `LinkedList` is empty, throws a `runtime_error`.
   */
  T pop_front() {
    if (list_size == 0) {
      throw runtime_error("List is empty.");
    }
    
    Node* ptr = list_front;
    T deletedValue = ptr->data;
    list_front = list_front->next;
    delete ptr;
    list_size--;

    return deletedValue;
  }

  /**
   * Removes the element at the back of the `LinkedList`.
   *
   * If the `LinkedList` is empty, throws a `runtime_error`.
   */
  T pop_back() {
    if (list_size == 0) {
      throw runtime_error("List is empty.");
    }

    if (list_front->next == nullptr) {
      T deletedValue = list_front->data;
      delete list_front;
      list_front = nullptr;
      list_size--;
      return deletedValue;
    }

    Node* ptr = list_front;
    while (ptr->next->next != nullptr) {
      ptr = ptr->next;
    }

    T deletedValue = ptr->next->data;
    delete(ptr->next);
    ptr->next = nullptr;
    list_size--;

    return deletedValue;
  }

  /**
   * Empties the `LinkedList`, releasing all allocated memory, and resetting
   * member variables appropriately.
   */
  void clear() {
    Node* ptr = list_front;
    while (ptr != nullptr) {
      Node* next = ptr->next;
      delete(ptr);
      ptr = next;
      list_size--;
    }
    list_front = nullptr;
    list_size = 0;
  }

  /**
   * Destructor. Clears all allocated memory.
   */
  ~LinkedList() {
    clear();
  }

  /**
   * Returns the element at the given index in the `LinkedList`.
   *
   * If the index is invalid, throws `out_of_range`.
   */
  T &at(size_t index) const {
    if (index >= list_size) {
      throw out_of_range("Index is invalid.");
    }
    Node* ptr = list_front;
    for (size_t i = 0; i < index; i++) {
      ptr = ptr->next;
    }
    return ptr->data;
  }

  /**
   * Copy constructor. Creates a deep copy of the given `LinkedList`.
   *
   * Must run in O(N) time.
   */
  LinkedList(const LinkedList &other) {
    list_front = nullptr;
    list_size = 0;
    Node* original = other.list_front;
    if (original == nullptr) {
      return;
    }
    
    list_front = new Node(original->data);
    Node* llcopy = list_front;
    original = original->next;

    while (original != nullptr) {
      llcopy->next = new Node(original->data);
      llcopy = llcopy->next;
      original = original->next;
    }
    list_size = other.list_size;
  }

  /**
   * Assignment operator. Sets the current `LinkedList` to a deep copy of the
   * given `LinkedList`.
   *
   * Must run in O(N) time.
   */
  LinkedList &operator=(const LinkedList &other) {
    if (this == &other) {
      return *this;
    }

    clear();

    Node* original = other.list_front;
    if (original == nullptr) {
      list_front = nullptr;
      list_size = 0;
      return *this;
    }

    list_front = new Node(original->data);
    Node* llcopy = list_front;

    original = original->next;

    while (original != nullptr) {
      llcopy->next = new Node(original->data);
      llcopy = llcopy->next;
      original = original->next;
    }
    list_size = other.list_size;

    return *this;
  }

  /**
   * Converts the `LinkedList` to a string. Formatted like `[0, 1, 2, 3, 4]`
   * (without the backticks -- hover the function name to see). Runs in O(N)
   * time.
   */
  string to_string() const {
    stringstream ss;
    Node* ptr = list_front;
    ss << "[";
    while (ptr != nullptr) {
      ss << ptr->data;
      if (ptr->next != nullptr) {
        ss << ", ";
      }
      ptr = ptr->next;
    }
    ss << "]";
    return ss.str();
  }

  /**
   * Searches the `LinkedList` for the first matching element, and returns its
   * index. If no match is found, returns "-1".
   */
  size_t find(const T &data) {
    if (list_front == nullptr) {
      return -1;
    }
    Node* ptr = list_front;
    size_t index = 0;
    while (ptr->data != data && ptr->next != nullptr) {
      ptr = ptr->next;
      index++;
    }
    if (ptr->data != data) {
      return -1;
    }
    return index;
  }

  /**
   * Remove the element at the specified index in this list.
   *
   * If the index is invalid, throws `out_of_range`.
   */
  void remove_at(size_t index) {
    if (index == 0) {
      Node* target = list_front;
      list_front = list_front->next;
      delete target;
      list_size--;
      return;
    }

    if (index >= list_size || index < 0) {
      throw out_of_range("Index not in the range");
    }
    Node* ptr = list_front;
    for (size_t i = 0; i + 1 < index; i++) {
      ptr = ptr->next;
    }
    Node* target = ptr->next;
    ptr->next = target->next;
    delete target;
    list_size--;
  }

  /**
   * Inserts the given `T` as a new element in the `LinkedList` after
   * the given index. If the index is invalid, throws `out_of_range`.
   */
  void insert_after(size_t index, T data) {
    if (index >= list_size || index < 0) {
      throw out_of_range("Index not in the range");
    }

    Node* ptr = list_front;
    for (size_t i = 0; i < index; i++) {
      ptr = ptr->next;
    }
    Node* temp = ptr->next;
    ptr->next = new Node(data);
    ptr->next->next = temp;
    list_size++;
  }

  /**
   * Remove every element that is currently in an
   * even-numbered position on the list.
   *
   * Must run in O(N).
   *
   * For example, if a list was `[3, 9, 7, 6, 8]`, remove_evens
   * would change the list to `[9, 6]`, since we remove the
   * values in positions 0, 2, and 4 (the even-numbered indices)
   * from the list.
   */
  void remove_evens() {
    int count = 0;
    Node *ptr = list_front;
    Node *previous = nullptr;

    while (ptr != nullptr) {
      Node* next = ptr->next;

      if ((count % 2) == 0) {
        if (previous == nullptr) {
          list_front = next;
        }
        else {
          previous->next = next;
        }
        delete ptr;
        list_size--;
      }
      else {
        previous = ptr;
      }
      ptr = next;
      count++;
    }
  }

  /**
   * Returns a pointer to the node at the front of the `LinkedList`. For
   * autograder testing purposes only.
   */
  void *front() const {
    return this->list_front;
  }
};