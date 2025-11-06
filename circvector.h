#pragma once

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

template <typename T>
class CircVector {
 private:
  T *data;
  size_t vec_size;
  size_t capacity;
  size_t front_idx;

  // TODO_STUDENT: add private helper functions, such as resize
  // You may also find a "wrapping" function helpful.
  void resize() {
    size_t new_capacity = capacity * 2;
    T* new_data = new T[new_capacity];

    for (size_t i = 0; i < vec_size; i++) {
      new_data[i] = data[(front_idx + i) % capacity];
    }
    delete[] data;
    data = new_data;
    capacity = new_capacity;
    front_idx = 0;
  }

 public:
  /**
   * Default constructor. Creates an empty `CircVector` with capacity 10.
   */
  CircVector() {
    vec_size = 0;
    capacity = 10;
    front_idx = 0;
    data = new T[capacity];
  }

  /**
   * Creates an empty `CircVector` with given capacity. Capacity must exceed 0.
   */
  CircVector(size_t capacity) {
    if (capacity > 0) {
      this->capacity = capacity;
    }
    else {
      cout << "Capacity must be > 0" << endl;
    }
    vec_size = 0;
    front_idx = 0;
    data = new T[capacity];
  }

  /**
   * Returns whether the `CircVector` is empty (i.e. whether its
   * size is 0).
   */
  bool empty() const {
    return vec_size == 0;
  }

  /**
   * Returns the number of elements in the `CircVector`.
   */
  size_t size() const {
    return vec_size;
  }

  /**
   * Adds the given `T` to the front of the `CircVector`.
   */
  void push_front(T elem) {
    if (capacity == vec_size) {
      resize();
    }
    front_idx = (front_idx + capacity - 1) % capacity;
    
    data[front_idx] = elem;

    vec_size++;
  }

  /**
   * Adds the given `T` to the back of the `CircVector`.
   */
  void push_back(T elem) {
    if (capacity == vec_size) {
      resize();
    }
    data[(front_idx + vec_size) % capacity] = elem;
    vec_size++;
  }

  /**
   * Removes the element at the front of the `CircVector`.
   *
   * If the `CircVector` is empty, throws a `runtime_error`.
   */
  T pop_front() {
    if (vec_size == 0) {
      throw runtime_error("Vector is empty");
    }
    T value = data[front_idx];
    front_idx = (front_idx + 1) % capacity;
    vec_size--;
    return value;
  }

  /**
   * Removes the element at the back of the `CircVector`.
   *
   * If the `CircVector` is empty, throws a `runtime_error`.
   */
  T pop_back() {
    if (vec_size == 0) {
      throw runtime_error("Vector is empty");
    }
    size_t back_idx = (front_idx + vec_size - 1) % capacity;
    T value = data[back_idx];
    vec_size--;
    return value;
  }

  /**
   * Removes all elements from the `CircVector`.
   */
  void clear() {
    vec_size = 0;
    front_idx = 0;
  }

  /**
   * Destructor. Clears all allocated memory.
   */
  ~CircVector() {
    delete[] data;
    data = nullptr;
    capacity = 0;
    front_idx = 0;
    vec_size = 0;
  }

  /**
   * Returns the element at the given index in the `CircVector`.
   *
   * If the index is invalid, throws `out_of_range`.
   */
  T &at(size_t index) const {
    if (index < 0 || index >= vec_size) {
      throw out_of_range("Index is out of range");
    };
    return data[(front_idx + index) % capacity];
  }

  /**
   * Copy constructor. Creates a deep copy of the given `CircVector`.
   *
   * Must run in O(N) time.
   */
  CircVector(const CircVector &other) {
    vec_size = other.vec_size;
    front_idx = other.front_idx;
    capacity = other.capacity;

    data = new T[capacity];

    for (size_t i = 0; i < vec_size; i++) {
      data[(front_idx + i) % capacity] = other.data[(other.front_idx + i) % capacity];
    }
  }

  /**
   * Assignment operator. Sets the current `CircVector` to a deep copy of the
   * given `CircVector`.
   *
   * Must run in O(N) time.
   */
  CircVector &operator=(const CircVector &other) {
    if (this == &other) {
      return *this;
    }

    delete[] data;

    vec_size = other.vec_size;
    front_idx = other.front_idx;
    capacity = other.capacity;

    data = new T[capacity];

    for (size_t i = 0; i < vec_size; i++) {
      data[(front_idx + i) % capacity] = other.data[(other.front_idx + i) % capacity];
    }

    return *this;
  }

  /**
   * Converts the `CircVector` to a string. Formatted like `[0, 1, 2, 3, 4]`
   * (without the backticks -- hover the function name to see). Runs in O(N)
   * time.
   */
  string to_string() const {
    stringstream ss;
    ss << "[";
    for (size_t i = 0; i < vec_size; i++) {
      ss << data[(front_idx + i) % capacity];
      if (i + 1 < vec_size){
        ss << ", ";
      }
    }
    ss << "]";
    return ss.str();
  }

  /**
   * Searches the `CircVector` for the first matching element, and returns its
   * index in the `CircVector`. If no match is found, returns "-1".
   */
  size_t find(const T &target) {
    for (size_t i = 0; i < vec_size; i++) {
      if (data[(front_idx + i) % capacity] == target) {
        return i;
      }
    }
    return -1;
  }

  /**
   * Remove the element at the specified index in this list.
   *
   * If the index is invalid, throws `out_of_range`.
   */
  void remove_at(size_t index) {
    if (index < 0 || index >= vec_size) {
      throw out_of_range("Index is out of range");
    }
    for (size_t i = index; i + 1 < vec_size; i++) {
      data[(front_idx + i) % capacity] = data[(front_idx + i + 1) % capacity];
    }
    vec_size--;
  }

  /**
   * Inserts the given `T` as a new element in the `CircVector` after
   * the given index. If the index is invalid, throws `out_of_range`.
   */
  void insert_after(size_t index, T elem) {
    if (index < 0 || index >= vec_size) {
      throw out_of_range("Index is out of range");
    }

    if(vec_size == capacity) {
        resize();
      }

    for (size_t i = vec_size; i > index + 1; i--) {
      data[(i + front_idx) % capacity] = data[(i + front_idx + capacity - 1) % capacity];
    }
    data[(front_idx + index + 1) % capacity] = elem;
    vec_size++;
  }

  /**
   * Remove every element that is currently in an
   * even-numbered position on the `CircVector`
   * (not the data array).
   *
   * Must run in O(N). Mustn't reallocate the array.
   *
   * For example, if a list was `[3, 9, 7, 6, 8]`, remove_evens
   * would change the list to `[9, 6]`, since we remove the
   * values in positions 0, 2, and 4 (the even-numbered indices)
   * from the list.
   */
  void remove_evens() {
    size_t index = 0;
    for (size_t i = 0; i < vec_size; i++) {
      if (i % 2 != 0) {
        data[(front_idx + index) % capacity] = data[(front_idx + i) % capacity];
        index++;
      }
    }
    vec_size = index;
  }

  /**
   * Returns a pointer to the underlying memory managed by the `CircVec`.
   * For autograder testing purposes only. Do not change.
   */
  T *get_data() const {
    return this->data;
  }

  /**
   * Returns the capacity of the underlying memory managed by the `CircVec`. For
   * autograder testing purposes only. Do not change.
   */
  size_t get_capacity() const {
    return this->capacity;
  }
};