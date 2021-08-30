#include <array>
#include <vector>
#include <list>
#include <iostream>

int main() {
  // Compare types with types.
  static_assert(int is not double); // P2392R1
  static_assert(int is int);

  static_assert(int != double); // Circle Imperative Arguments
  static_assert(int == int);

  // Compare templates with templates.
  static_assert(std::list is not std::array); // P2392R1
  static_assert(std::array is std::array);
  
  static_assert(std::list != std::array); // CIA
  static_assert(std::array == std::array);

  // Compare class specializations with templates.
  static_assert(std::list<int> is not std::array); // P2392R1
  static_assert(std::array<int, 10> is std::array);

  static_assert(std::list<int>.template != std::array); // CIA
  static_assert(std::array<int, 10>.template == std::array);

  // Check concepts and trait-like variable templates.
  static_assert(int is std::integral); // P2392R1
  static_assert(int is std::is_integral_v); 

  static_assert(int.is_integral); // CIA
}