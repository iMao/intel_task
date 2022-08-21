#include <iostream>

#include "shared_ptr.h"

class X {
 public:
  void Print() { std::cout << "class X for test only\n"; }
};

int main() {
  std::cout << "Task from Intel" << std::endl;

  try {
    tsk::shared_ptr<int> number_shptr;
    tsk::shared_ptr<int> second_number_shptr(new int(10));
    tsk::shared_ptr<int> third_number_shptr(second_number_shptr);
    tsk::shared_ptr<int> fourth_number_shptr = second_number_shptr;

    std::cout << "Demonstration of shared_ptr<>\n";

    std::cout << "usage constructor with pointer: " << *second_number_shptr
              << " ref_counter: " << second_number_shptr.use_count()
              << std::endl;

    std::cout << "usage copy constractor:         " << *third_number_shptr
              << " ref_counter: " << third_number_shptr.use_count()
              << std::endl;

    std::cout << "copy asignment operator:        " << *fourth_number_shptr
              << " ref_counter: " << fourth_number_shptr.use_count()
              << std::endl;

    int* raw_ptr = new int(100);
    second_number_shptr.reset(raw_ptr);

    std::cout << "usage reset(T*ptr):             " << *second_number_shptr
              << " ref_counter: " << second_number_shptr.use_count()
              << std::endl;

    std::cout << "One shared_ptr<int> was reseted at raw pointer\n";
    std::cout << "How many references now:        " << *third_number_shptr
              << " ref_counter: " << third_number_shptr.use_count()
              << std::endl;

    std::cout << "Get raw pointer:                "
              << *(second_number_shptr.get()) << std::endl;

    tsk::shared_ptr<X> x_ptr(new X);
    std::cout << "Test operator ->                ";
    x_ptr->Print();

  } catch (const std::exception& e) {
    std::cout << "exception: " << e.what() << std::endl;
  }

  return 0;
}
