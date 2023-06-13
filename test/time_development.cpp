#ifdef LibraryTest
#include <iostream>
#include <fstream>
#include <random>
#include <functional>

#include <transform2d/transform2d.hpp>
#include "polynominal_frame.hpp"

using std::cout;
using std::endl;

#include "util.hpp"

int main()
{
    Polynomial<double, 2> x(10., 100.);
    Polynomial<double, 2> y(1000., 10000.);
    Polynomial<double, 2> th(100000., 1000000.);
    
    auto get = [&](double t){ return calcPolynomialFrame(x, y, th, t); };
    auto init_frame = get(0);
    print(init_frame);
    double t = 1.0;
    auto developted_frame = init_frame.timeDevelopment(t);
    print(developted_frame);
    auto t_frame = get(t);
    print(t_frame);
}
#endif
