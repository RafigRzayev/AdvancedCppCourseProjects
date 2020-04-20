#include "array.hpp"
#include "vector.hpp"
#include "printer.hpp"
#include <iostream>

int main() {
  // PART 1: SHOW TEST CLASS
  line("--------- DEMONSTRATE ARRAY CLASS WHICH WILL BE USED TO TEST VECTOR ---------");
  line("CREATE OBJECTS");
  // Default Constructor
  Array a1;
  // User Constructor
  Array a2(4), a3(8);
  a1.print("a1");
  a2.print("a2");
  a3.print("a3");

  line("COPY CONSTRUCTOR");
  a2.print("a2");
  Array a4(a2);
  a2.print("a2");
  a4.print("a4");

  line("MOVE CONSTRUCTOR");
  a3.print("a3");
  Array a5(std::move(a3));
  a3.print("a3");
  a5.print("a5");

  line("COPY ASSIGNMENT");
  a1.print("a1");
  a2.print("a2");
  a1 = a2;
  a1.print("a1");
  a2.print("a2");

  line("MOVE ASSIGNMENT");
  a3.print("a3");
  a4.print("a4");
  a3 = std::move(a4);
  a3.print("a3");
  a4.print("a4");

  line("DESTRUCTOR");
  { Array a6; }

  // PART 2: SHOW VECTOR
  line("--------- DEMONSTRATE VECTOR CLASS ---------");

  line("DEFAULT CTOR");
  Vector<Array> v0;
  show_vector(v0);

  line("CTOR 1 - SIZE");
  Vector<Array> v1(3);
  show_vector(v1);

  line("CTOR 2 - INITIALIZER LIST");
  Vector<Array> v2({Array(1), Array(2)});
  show_vector(v2);

  line("CTOR 3 - BEGIN, END");
  const size_t SIZE{5};
  Array a[SIZE]{Array(1), Array(2), Array(4), Array(6), Array(8)};
  Vector<Array> v3(a, a + 3);
  show_vector(v3);

  line("COPY CTOR");
  Vector<Array> v4(3);
  Vector<Array> v5(v4);
  show_vector(v5);

  line("COPY ASSIGNMENT");
  Vector<Array> v6(1);
  Vector<Array> v7(2);
  v6 = v7;
  show_vector(v7);

  line("MOVE CTOR");
  Vector<Array> v8(2);
  Vector<Array> v9(std::move(v8));
  show_vector(v8);
  show_vector(v9);

  line("MOVE ASSIGNMENT");
  Vector<Array> v10(1);
  Vector<Array> v11(2);
  v11 = std::move(v10);
  show_vector(v10);
  show_vector(v11);

  line("PUSH FRONT LVAL");
  Array b(3);
  Vector<Array> v12(2);
  v12.push_front(b);
  show_vector(v12);

  line("PUSH FRONT RVAL");
  Vector<Array> v13(3);
  v13.push_front(Array(15));
  show_vector(v13);

  line("PUSH BACK LVAL");
  Array b1(3);
  Vector<Array> v14;
  v14.reserve(3);
  v14.push_back(b1);
  show_vector(v14);

  line("PUSH BACK RVAL");
  Array b2(3);
  Vector<Array> v15(2);
  v15.push_back(std::move(b2));
  show_vector(v15);

  line("EMPLACE BACK LVAL");
  Array b3(12);
  Vector<Array> v16;
  v16.reserve(3);
  v16.emplace_back(b3);
  show_vector(v16);

  line("EMPLACE BACK RVAL");
  Array b4(3);
  Vector<Array> v17;
  v17.reserve(3);
  v17.emplace_back(std::move(b4));
  show_vector(v17);

  line("EMPLACE BACK - PROVIDE CTOR ARGS");
  Vector<Array> v18;
  v18.reserve(3);
  const size_t SIZE_{5};
  v18.emplace_back(SIZE_);
  show_vector(v18);

  line("INSERT - LVAL");
  Array b5(10);
  Vector<Array> v19(4);
  v19.insert(b5, 1);
  show_vector(v19);

  line("INSERT - RVAL");
  Array b6(10);
  Vector<Array> v20(3);
  v20.insert(std::move(b5), 3);
  show_vector(v20);

  line("ERASE");
  Vector<Array> v21({Array(1), Array(2), Array(3), Array(4), Array(5)});
  show_vector(v21);
  v21.erase(v21.begin(), v21.begin() + 3);
  show_vector(v21);
  v21.erase(1);
  show_vector(v21);
  v21.erase(v21.end() - 1);
  show_vector(v21);

  line("RESERVE");
  Vector<Array> v22(2);
  std::cout << "*****\n";
  v22.reserve(2);
  std::cout << "*****\n";
  v22.reserve(3);
  std::cout << "*****\n";
  v22.reserve(1);

  line("RESIZE - DECREASE SIZE");
  Vector<Array> v23;
  v23.reserve(3);
  const size_t _SIZE_{3};
  v23.emplace_back(_SIZE_);
  v23.emplace_back(_SIZE_);
  v23.emplace_back(_SIZE_);
  show_vector(v23);
  v23.resize(1);
  show_vector(v23);

  line("RESIZE - INCREASE SIZE");
  Vector<Array> v24(1);
  show_vector(v24);
  v24.resize(3);
  show_vector(v24);

  line("RESIZE - SAME SIZE");
  Vector<Array> v25(3);
  v25.resize(3);

  line("GENERAL DEMONSTRATION WITH Vector<int>");
  Vector<int> z;
  z.reserve(10);
  z.push_back(4);
  z.push_front(2);
  z.push_front(1);
  z.insert(3, 2);
  z.emplace_back(5);
  show_vector(z);

  z = Vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  z.resize(5);
  z.resize(10);
  show_vector(z);

  line("END");


  return 0;
}