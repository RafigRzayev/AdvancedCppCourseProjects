#pragma once
#include <memory>

// General template
template <typename T, typename D = std::default_delete<T>> class unique_ptr {
public:
  unique_ptr() = default;
  unique_ptr(T *ptr, D dtor = std::default_delete<T>()) noexcept
      : ptr_{ptr}, dtor_{dtor} {}
  unique_ptr(unique_ptr &&rhs) noexcept : ptr_{rhs.ptr_}, dtor_{rhs.dtor_} {
    rhs.ptr_ = nullptr;
  }
  unique_ptr &operator=(unique_ptr &&rhs) noexcept {
    destroy();
    ptr_ = rhs.ptr_;
    dtor_ = rhs.dtor_;
    rhs.ptr_ = nullptr;
    return *this;
  }
  ~unique_ptr() noexcept { destroy(); }

  T *get() noexcept { return ptr_; }

  void reset(T *ptr = nullptr) noexcept {
    destroy();
    ptr_ = ptr;
  }

  T *release() noexcept {
    T *tmp{ptr_};
    ptr_ = nullptr;
    return tmp;
  }

  explicit operator bool() const noexcept { return ptr_ != nullptr; }
  T *operator->() { return ptr_; }
  T &operator*() { return *ptr_; }

  unique_ptr(const unique_ptr &) = delete;
  unique_ptr &operator=(const unique_ptr &) = delete;

private:
  void destroy() {
    if (ptr_ != nullptr) {
      dtor_(ptr_);
    }
  }

  T *ptr_{nullptr};
  D dtor_{std::default_delete<T>()};
};

// Array specification
template <typename T, typename D> class unique_ptr<T[], D> {
public:
  unique_ptr() = default;
  unique_ptr(T *ptr, D dtor = std::default_delete<T[]>()) noexcept : ptr_{ptr}, dtor_{dtor} {}
  unique_ptr(unique_ptr &&rhs) noexcept : ptr_{rhs.ptr_}, dtor_{rhs.dtor_} {
    rhs.ptr_ = nullptr;
  }
  unique_ptr &operator=(unique_ptr &&rhs) noexcept {
    destroy();
    ptr_ = rhs.ptr_;
    dtor_ = rhs.dtor_;
    rhs.ptr_ = nullptr;
    return *this;
  }
  ~unique_ptr() noexcept { destroy(); }

  T *get() noexcept { return ptr_; }

  void reset(T *ptr = nullptr) noexcept {
    destroy();
    ptr_ = ptr;
  }

  T *release() noexcept {
    T *tmp{ptr_};
    ptr_ = nullptr;
    return tmp;
  }

  explicit operator bool() const noexcept { return ptr_ != nullptr; }
  T *operator->() { return ptr_; }
  T &operator*() { return *ptr_; }
  T &operator[](size_t i) { return *(ptr_ + i); }

  unique_ptr(const unique_ptr &) = delete;
  unique_ptr &operator=(const unique_ptr &) = delete;

private:
  void destroy() noexcept {
    if (ptr_ != nullptr) {
      dtor_(ptr_);
    }
  }

  T *ptr_{nullptr};
  D dtor_{std::default_delete<T[]>()};
};