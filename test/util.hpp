#pragma once
#include <iostream>

namespace util {
template <class X, class Y>
inline void print_impl(X x, Y y) {
  std::cout << x << " = " << y << std::endl;
}
#define print(a) ::util::print_impl(#a, a)
}  // namespace util
