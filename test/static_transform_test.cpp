#ifdef LibraryTest
#include <iostream>
#include <transform2d/static_transform.hpp>

using std::cout;
using std::endl;
#include "util.hpp"

void check(double x0, double y0, double theta0, double x1, double y1, double theta1) {
    cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    Transform::StaticTransform<double> base(x0, y0, theta0);
    Transform::StaticTransform<double> add(x1, y1, theta1);
    print(base);
    print(add);
    print(base+add);
    print(-base+add);

}

int main()
{
  check(1, 10, M_PI / 2.0, 100, 1000, M_PI / 2.0);

  check(1, 4, M_PI, 5, 2, -M_PI / 2.0);
}
#endif
