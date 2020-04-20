#pragma once

#include <cstring>
#include <initializer_list>
#include <iterator>
#include <type_traits>
#include <utility>

template <typename T> class Vector {
public:
  // Default Constructor
  Vector() = default;

  // User-Defined Constructor 1
  Vector(const size_t SIZE) {
    if (SIZE > 0) {
      T *tmp = new T[SIZE]{};
      update_parameters(tmp, SIZE, SIZE);
    }
  }

  // User-Defined Constructor 2
  Vector(std::initializer_list<T> list) {
    alloc(list.begin(), list.end(), list.size());
  }

  // User-Defined Constructor 3
  Vector(const T *begin, const T *const end) {
    alloc(begin, end, std::distance(begin, end));
  }

  // Copy Constructor
  Vector(const Vector &rhs) {
    alloc(rhs.data_, rhs.data_ + rhs.size_, rhs.capacity_);
  }

  // Move Constructor
  Vector(Vector &&rhs) noexcept
      : data_{rhs.data_}, size_{rhs.size_}, capacity_{rhs.capacity_} {
    rhs.update_parameters(nullptr, 0, 0);
  }

  // Copy Assignment
  Vector &operator=(const Vector &rhs) {
    if (this == &rhs) {
      return *this;
    }
    if (rhs.empty()) {
      clear();
      return *this;
    }
    realloc(rhs.data_, rhs.data_ + rhs.size_, rhs.capacity_);
    return *this;
  }

  // Move Assignment
  Vector &operator=(Vector &&rhs) noexcept {
    delete[] data_;
    update_parameters(rhs.data_, rhs.size_, rhs.capacity_);
    rhs.update_parameters(nullptr, 0, 0);
    return *this;
  }

  // Destructor
  ~Vector() noexcept { delete[] data_; }

  template <typename T1> void push_front(T1 &&value) {
    shift(0);
    *data_ = std::forward<T1>(value);
  }

  template <typename T2> void push_back(T2 &&value) {
    increase_capacity_if_full();
    *(data_ + size_++) = std::forward<T2>(value);
  }

  template <typename... Args> void emplace_back(Args &&... args) {
    increase_capacity_if_full();
    new (data_ + size_++) T{std::forward<Args...>(args...)};
  }

  template <typename T3> T *insert(T3 &&value, size_t pos) {
    if (pos > size_) {
      return nullptr;
    }
    shift(pos);
    *(data_ + pos) = std::forward<T3>(value);
    return data_ + pos;
  }

  T *erase(T *pos) { return erase(pos, pos + 1); }

  T *erase(size_t pos) { return erase(data_ + pos, data_ + pos + 1); }

  T *erase(T *begin, T *end) {
    if (begin < data_ || begin >= data_ + size_) {
      return nullptr;
    }
    if (end <= begin || end > data_ + size_) {
      return nullptr;
    }
    const auto ERASE_COUNT{std::distance(begin, end)};
    const auto ERASE_START_INDEX{std::distance(data_, begin)};
    custom_copy(begin, end, ERASE_START_INDEX, size_ - ERASE_COUNT, capacity_);
    return data_ + ERASE_START_INDEX;
  }

  void reserve(size_t new_cap) {
    if (new_cap > capacity_) {
      realloc(data_, data_ + size_, new_cap);
    }
  }

  void resize(size_t new_size) {
    if (new_size == size_) {
      return;
    }
    if (new_size > size_) {
      size_t new_capacity = (new_size > capacity_ ? new_size : capacity_);
      T *tmp = new T[new_capacity];
      copy(tmp, data_, data_ + size_);
      initialize(tmp + size_, tmp + new_size);
      delete[] data_;
      update_parameters(tmp, new_size, new_capacity);
    } else {
      release(data_ + new_size, data_ + size_);
      size_ = new_size;
    }
  }

  void clear() noexcept {
    delete[] data_;
    update_parameters(nullptr, 0, 0);
  }

  T *begin() noexcept { return data_; }
  T *const end() noexcept { return data_ + size_; }
  T front() const { return *data_; }
  T back() const { return *(data_ + size_ - 1); }
  T &operator[](size_t pos) { return *(data_ + pos); }
  const T &operator[](size_t pos) const { return *(data_ + pos); }
  size_t size() const noexcept { return size_; }
  size_t capacity() const noexcept { return capacity_; }
  size_t empty() const noexcept { return data_ == nullptr; }

private:
  // Copy values from source sequence into destination
  void copy(T *dst, const T *src_begin, const T *const src_end) {
    const auto LENGTH{std::distance(src_begin, src_end)};
    // Exceptions
    if (dst == nullptr || src_begin == nullptr || LENGTH <= 0) {
      return;
    }
    // Option 1: Copy with memcpy for POD types
    if constexpr (std::is_trivially_copyable<T>::value) {
      memcpy(dst, src_begin, sizeof(T) * LENGTH);
    }
    // Option 2: Copy with assignment operator for classes
    else {
      while (src_begin != src_end) {
        *dst++ = *src_begin++;
      }
    }
  }

  // Updates DATA_, SIZE_, and CAPACITY_ to new values
  void update_parameters(T *new_data, size_t new_size,
                         size_t new_capacity) noexcept {
    data_ = new_data;
    size_ = new_size;
    capacity_ = new_capacity;
  }

  // To be used when vector is full
  void increase_capacity_if_full() {
    if (size_ == capacity_) {
      if (capacity_ == 0) {
        reserve(1);
      } else {
        reserve(capacity_ * 2);
      }
    }
  }

  // Initialize already allocated memory
  void initialize(T *begin, T *end) {
    // Option 1: Initialize with memset for POD types
    if constexpr (std::is_trivial<T>::value) {
      memset(begin, 0, sizeof(T) * std::distance(begin, end));
    }
    // Option 2: Initialize with default constructor
    else {
      while (begin != end) {
        new (begin++) T{};
      }
    }
  }

  // Destroy vector elements
  void release(T *begin, T *end) {
    // Option 1: Reset values with memset for POD types
    if constexpr (std::is_trivially_destructible<T>::value) {
      memset(begin, 0, sizeof(T) * std::distance(begin, end));
    }
    // Option 2: Call destructors if vector elements are objects
    else {
      while (begin != end) {
        begin->~T();
        ++begin;
      }
    }
  }

  // Create vector from input data
  void alloc(const T *begin, const T *const end, const size_t CAPACITY) {
    const auto LENGTH{std::distance(begin, end)};
    if (begin != nullptr && LENGTH > 0) {
      T *tmp = new T[CAPACITY];
      copy(tmp, begin, end);
      update_parameters(tmp, LENGTH, CAPACITY);
    }
  }

  // Update vector with new data
  void realloc(T *begin, T *end, size_t CAPACITY) {
    T *tmp = new T[CAPACITY];
    copy(tmp, begin, end);
    delete[] data_;
    update_parameters(tmp, std::distance(begin, end), CAPACITY);
  }

  // Shift values after index to right
  void shift(size_t index) {
    size_t new_capacity{capacity_};
    if (size_ == capacity_) {
      new_capacity = (capacity_ == 0 ? 1 : capacity_ * 2);
    }
    custom_copy(data_ + index, data_ + index, index + 1, size_ + 1,
                new_capacity);
  }

  // Copy part of vector
  void custom_copy(T *SKIP_START, T *SKIP_STOP, size_t CONTINUE_INDEX,
                   size_t NEW_SIZE, size_t NEW_CAPACITY) {
    T *tmp = new T[NEW_CAPACITY];
    copy(tmp, data_, SKIP_START);
    copy(tmp + CONTINUE_INDEX, SKIP_STOP, data_ + size_);
    delete[] data_;
    update_parameters(tmp, NEW_SIZE, NEW_CAPACITY);
  }

  T *data_{nullptr};
  size_t size_{0};
  size_t capacity_{0};
};