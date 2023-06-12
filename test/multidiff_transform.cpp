#include <iostream>
#include <transform2d/transform.hpp>

using std::cout;
using std::endl;

#include "util.hpp"

int main()
{
  Transform::StaticTransform<double> pos(1, 0, M_PI / 2.0);
  Transform::DynamicTransform<double> vel(0, 1, 0);
  Transform::DynamicTransform<double> acc(-1, 0, 0);

  Transform::MultidiffTransform<double, 2> frame(pos, vel, acc);

  print(frame);

  auto [vx, vy] = vel.getPos();
  print(vx);
  print(vy);

  print(-pos+frame);
}
