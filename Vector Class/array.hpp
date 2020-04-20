#pragma once

#include <iostream>

// DUMMY CLASS FOR TESTING VECTOR
class Array {
public:
  // Default CTOR
  constexpr Array() noexcept { std::cout << "Array Default Constructor\n"; }
  // User CTOR
  Array(size_t size) : size_{size} {
    data_ = new int[size_]{};
    std::cout << "Array User Constructor\n";
  }
  // Copy CTOR
  Array(const Array &rhs) : size_{rhs.size_} {
    if (size_ == 0) {
      return;
    }
    data_ = new int[size_]{};
    std::cout << "Array Copy Constructor\n";
  }
  // Copy Assignment
  Array &operator=(const Array &rhs) {
    std::cout << "Array Copy Assignment\n";
    if (this == &rhs) {
      return *this;
    }
    delete data_;
    size_ = rhs.size_;
    data_ = new int[size_]{};
    return *this;
  }
  // Move CTOR
  Array(Array &&rhs) : data_{rhs.data_}, size_{rhs.size_} {
    std::cout << "Array Move Constructor\n";
    rhs.size_ = 0;
    rhs.data_ = nullptr;
  }
  // Move Assignment
  Array &operator=(Array &&rhs) noexcept {
    std::cout << "Array Move Assignment\n";
    delete data_;
    data_ = rhs.data_;
    size_ = rhs.size_;
    rhs.size_ = 0;
    rhs.data_ = nullptr;
    return *this;
  }
  // DTOR
  ~Array() {
    delete[] data_;
    std::cout << "Array Destructor\n";
  }
  // Print the object to console
  void print(const char *c) const {
    std::cout << c << " -> ";
    if (size_ == 0) {
      std::cout << "Empty\n";
      return;
    }
    std::cout << "[";
    for (size_t i{0}; i < size_; ++i) {
      std::cout << data_[i] << " ";
    }
    std::cout << "]" << std::endl;
  }

private:
  int *data_{nullptr};
  size_t size_{0};
};