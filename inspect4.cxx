#include <iostream>
#include <concepts>
#include <variant>
#include <any>
#include <tuple>

// std::variant operator-is support.
template<typename T, typename... Ts>
constexpr size_t operator is(const std::variant<Ts...>& x) {
  return x.index(); 
}

template<size_t I, typename... Ts> requires(I < sizeof...(Ts))
constexpr Ts...[I]& as(std::variant<Ts...>& x) { 
  return std::get<I>(x);
}

template<size_t I, typename... Ts> requires(I < sizeof...(Ts))
constexpr const Ts...[I]& operator as(const std::variant<Ts...>& x) { 
  return std::get<I>(x);
}

// std::any operator-is support.
constexpr const std::type_info& operator is(const std::any& x) { 
  return x.type(); 
}

template<typename T> requires (!T.is_reference)
constexpr T operator as(const std::any& x) {
  return std::any_cast<T>(x);
}

template<typename T> requires (T.is_reference)
constexpr T& operator as(std::any& x) {
  if(auto p = std::any_cast<T.remove_reference*>(&x))
    return *p;
  throw std::bad_any_cast();
}

// Any even test. You must use a constraint so that errors show up as
// substitution failures.
constexpr bool even(std::integral auto x) {
  return 0 == (x % 2);
}

void f(const auto& x) {
  inspect(x) {
    i is int as int     => std::cout<< "int "<< i<< "\n";
    i is std::integral {
      is even => std::cout<< "even non-int integral "<< i<< "\n";
      is _    => std::cout<< "odd non-int integral "<< i<< "\n";
    }
    [a,b] is [int, int] => std::cout<< "2-int tuple "<< a<< " "<< b<< "\n";
    [_,y] is [0, even ] => std::cout<< "point on y-axis and even y "<< y<< "\n";
    s as std::string    => std::cout<< "string \"" + s + "\"\n";
    is _                => std::cout<< "((no matching value))\n";
  }
}

int main() {
  std::variant<float, char, int, long, std::string> var;
  var = 5;
  f(var);

  var = 5l;
  f(var);

  std::any any = std::string("Hello any");
  f(any);

  any = 100;
  f(any);

  f(std::make_tuple(1, 2));
  f(std::make_tuple(0ll, 6ll));
}
