#include <iostream>
#include <transform2d/transform2d.hpp>

using std::cout;
using std::endl;

#include "util.hpp"

int main()
{
  Transform::StaticTransform<double> pos(2.0, 3.0, M_PI / 3.0);
  Transform::DynamicTransform<double> vel(5.0, 20., 1.0);

  Transform::MultidiffTransform<double, 1> frame(pos, vel);

  Transform::StaticTransform<double> sub_pos(20.0, -40.0, -M_PI / 2.0);
  auto sub_frame = frame + sub_pos;
  
  print(sub_frame);

  auto recalc_frame = sub_frame + (-sub_pos);
  print(recalc_frame);

  print(frame);
}
