#include "other.hpp"
#include "unique_ptr.hpp"

// DEMO
int main() {
  // *******************************************
  header("Default destuctor");
  int *val1 = new int{1};
  {
    unique_ptr<int> ptr1(val1);
    print("val1", ptr1.get());
  }
  print("val1", val1);
  // *******************************************
  header("User-defined destuctor");
  int *val2 = new int{2};
  {
    unique_ptr<int, decltype(&my_dtor)> ptr2(val2, my_dtor);
    print("val2", ptr2.get());
  }
  print("val2", val2);
  // *******************************************
  header("Move constructor");
  {
    unique_ptr<int, decltype(&my_dtor)> ptr3(new int{3}, my_dtor);
    print("ptr3", ptr3.get());
    unique_ptr<int, decltype(&my_dtor)> ptr4(std::move(ptr3));
    print("ptr3", ptr3.get());
    print("ptr4", ptr4.get());
  }
  // *******************************************
  header("Move assignment");
  {
    unique_ptr<int, decltype(&my_dtor_2)> ptr5(new int{5}, my_dtor_2);
    unique_ptr<int, decltype(&my_dtor)> ptr6(new int{6}, my_dtor);
    print("ptr5", ptr5.get());
    print("ptr6", ptr6.get());
    ptr5 = std::move(ptr6);
    print("ptr5", ptr5.get());
    print("ptr6", ptr6.get());
  }
  // *******************************************
  header("Reset");
  {
    unique_ptr<int, decltype(&my_dtor)> ptr7(new int{7}, my_dtor);
    print("ptr7", ptr7.get());
    ptr7.reset();
    print("ptr7", ptr7.get());
    ptr7.reset(new int{17});
    print("ptr7", ptr7.get());
  }
  // *******************************************
  header("Release");
  {
    unique_ptr<int, decltype(&my_dtor)> ptr8(new int{8}, my_dtor);
    print("ptr8", ptr8.get());
    int *raw = ptr8.release();
    print("raw", raw);
    print("ptr8", ptr8.get());
    delete raw;
  }
  // *******************************************
  header("Array specification - default destructor");
  MyKlass *raw_ptr_1 = new MyKlass[5];
  { unique_ptr<MyKlass[], std::default_delete<MyKlass[]>> uptr_1(raw_ptr_1); }
  // *******************************************
  header("Array specification - user destructor");
  MyKlass *raw_ptr_2 = new MyKlass[3];
  { unique_ptr<MyKlass[], decltype(&my_dtor_3)> uptr_2(raw_ptr_2, my_dtor_3); }
  // *******************************************
  return 0;
}
