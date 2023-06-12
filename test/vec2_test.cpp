#include <iostream>

#include <linear_algebra/Vec2.hpp>
#include <util/print.hpp>

using linear::Vec2d;
using std::cout, std::cin, std::endl;

int main() {
  auto v = Vec2d(3, 4);
  auto p = Vec2d(4, 3);
  print(v);
  print(p);

  print(v + p);
  print(v - p);
  print(v * p);
  print(v / 2);
  print(v.norm());
  print(d(v, p));
}
