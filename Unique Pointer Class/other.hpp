#pragma once
#include <iostream>
#include <string>

// Test Class
class MyKlass {
public:
  MyKlass() = default;
  ~MyKlass() { std::cout << "MyKlass Destructor got called\n"; }
};

// Custom destructors
void my_dtor(int *a) {
  std::cout << "My destructor got called\n";
  delete a;
}

void my_dtor_2(int *a) {
  std::cout << "My destructor got called\n";
  delete a;
}

void my_dtor_3(MyKlass *a) {
  std::cout << "My destructor 2 got called\n";
  delete[] a;
}

// print content of a pointer
void print(const std::string &pointer_name, int *ptr) {
  std::cout << pointer_name << " : ";
  if (ptr == nullptr) {
    std::cout << "empty\n";
  } else {
    std::cout << *ptr << std::endl;
  }
}

void print_array(int *ptr, const size_t SIZE) {
  std::cout << "Data :";
  if (ptr == nullptr) {
    std::cout << "empty\n";
  } else {
    for (size_t i{0}; i < SIZE; ++i) {
      std::cout << ptr[i] << " ";
    }
    std::cout << std::endl;
  }
}

// add header to console
void header(const std::string &header) {
  std::cout << "\n-------- " << header << " --------\n";
}