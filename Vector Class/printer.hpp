#pragma once

#include "array.hpp"
#include "vector.hpp"

// Adding headers to console output
void line(const char *s) {
  std::cout << "\n************ " << s << " ************\n";
}

// Print vector of integers
void show_vector(const Vector<int> &vec) {
  const size_t SIZE{vec.size()};
  std::cout << "------------------------\n";
  std::cout << "SIZE: " << SIZE << "  CAPACITY: " << vec.capacity()
            << "\nDATA: ";
  if (SIZE == 0) {
    std::cout << "NO ELEMENTS\n";
  } else {
    std::cout << "\n[";
    for (size_t i{0}; i < SIZE; ++i) {
      std::cout << vec[i] << " ";
    }
    std::cout << "]\n";
  }
  std::cout << "------------------------\n";
}

// Print vector of Arrays
void show_vector(const Vector<Array> &vec) {
  const size_t SIZE{vec.size()};
  std::cout << "------------------------\n";
  std::cout << "SIZE: " << SIZE << "  CAPACITY: " << vec.capacity()
            << "\nDATA: ";
  if (SIZE == 0) {
    std::cout << "NO ELEMENTS\n";
  } else {
    std::cout << "\n";
    for (size_t i{0}; i < SIZE; ++i) {
      vec[i].print(" ");
    }
  }
  std::cout << "------------------------\n";
}
