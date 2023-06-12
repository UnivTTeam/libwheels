#include <iostream>

#include <linear_algebra/Mat2.hpp>
#include <util/print.hpp>

using linear::Vec2d, linear::Mat2d;
using std::cout, std::cin, std::endl;

int main() {
  auto x = Vec2d(3, 4);
  auto A = Mat2d(1, 0, 1, 1);
  print(x);
  print(A);

  print(A * x);
  print(A * (A * x));
}
