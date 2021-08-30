#include <memory>
#include <iostream>

struct base_t { virtual ~base_t() { } };
struct derived1_t : base_t { };
struct derived2_t : base_t { };

template<typename T, typename T2, typename Deleter>
requires(requires { dynamic_cast<T>(std::declval<T2*>()); } )
bool operator is(const std::unique_ptr<T2, Deleter>& p) noexcept {
  return nullptr != dynamic_cast<T>(p.get());
}

template<typename T, typename T2, typename Deleter>
requires(requires { dynamic_cast<T>(std::declval<T2*>()); } )
T operator as(const std::unique_ptr<T2, Deleter>& p) noexcept {
  return dynamic_cast<T>(p.get());
}

template<typename T, typename T2, typename Deleter>
requires(requires { dynamic_cast<T>(std::declval<T2*>()); } )
T operator as(std::unique_ptr<T2, Deleter>& p) noexcept {
  return dynamic_cast<T>(p.get());
}

int main() {
  std::unique_ptr<base_t> p1(new derived1_t());
  std::unique_ptr<base_t> p2(new derived2_t());
  
  std::cout<< p1 is (derived2_t*)<< "\n";     // false
  std::cout<< p2 is (derived2_t*)<< "\n";     // true

  std::cout<< p1 as derived2_t*<< "\n";       // nullptr
  std::cout<< p2 as derived2_t*<< "\n";       // p2
}