#ifdef LibraryTest
#include <iostream>
#include <fstream>
#include <random>
#include <functional>

#include <transform2d/transform2d.hpp>

using std::cout;
using std::endl;

#include "util.hpp"
#include "polynominal_frame.hpp"

#define print_func(func) \
    std::cout << #func << ":" << func(-1.) << "," << func(0.) << "," << func(1.) << "," << func(2.) << std::endl;

template <class T>
Transform::MultidiffTransform<T, 3> calcDfdt(
    Transform::MultidiffTransform<T, 3> frame, Transform::MultidiffTransform<T, 3> dframe, T dt)
{
    Transform::MultidiffTransform<T, 3> dfdt;
    dfdt.static_frame = Transform::StaticTransform<double>();
    dfdt.dynamic_frame[0].pos = (dframe.static_frame.pos - frame.static_frame.pos) / dt;
    dfdt.dynamic_frame[0].rot = (dframe.static_frame.rot - frame.static_frame.rot).getAngle() / dt;

    dfdt.dynamic_frame[1].pos = (dframe.dynamic_frame[0].pos - frame.dynamic_frame[0].pos) / dt;
    dfdt.dynamic_frame[1].rot = (dframe.dynamic_frame[0].rot -  frame.dynamic_frame[0].rot) / dt;

    dfdt.dynamic_frame[2].pos = (dframe.dynamic_frame[1].pos - frame.dynamic_frame[1].pos) / dt;
    dfdt.dynamic_frame[2].rot = (dframe.dynamic_frame[1].rot -  frame.dynamic_frame[1].rot) / dt;

    return dfdt;
}

std::random_device seed_gen;
std::mt19937 engine(seed_gen());
std::uniform_real_distribution<> dist1(-1.0, 1.0);

Polynomial<double, 5> getRandomPolynomial() {
    return Polynomial<double, 5>(dist1(engine), dist1(engine), dist1(engine), dist1(engine), dist1(engine));
}

void write(std::ofstream& fs, const double& t, const Transform::MultidiffTransform<double, 3>& frame) {
    fs << t << " ";
    for(int i=0; i<3; i++){
        fs << frame.dynamic_frame[i].pos.x << " ";
        fs << frame.dynamic_frame[i].pos.y << " ";
        fs << frame.dynamic_frame[i].rot << " ";
    }
    fs << endl;
}

int main()
{
    // Step1. Polynomialのデバッグ
    {
        Polynomial<double, 3> f(1., -2, 1.);
        std::function<double(double)> fDiff0 = [&](double t){ return f.getDiff<0>(t); };
        print_func(fDiff0);
        std::function<double(double)> fDiff1 = [&](double t){ return f.getDiff<1>(t); };
        print_func(fDiff1);
        std::function<double(double)> fDiff2 = [&](double t){ return f.getDiff<2>(t); };
        print_func(fDiff2);
    }

    // Step2. MultidiffTransformのoperator+のデバッグ
    {
        std::ofstream fs1("theoretical2.log");
        std::ofstream fs2("numerical2.log");

        auto x = getRandomPolynomial();
        auto y = getRandomPolynomial();
        auto th = getRandomPolynomial();
        std::function<Transform::MultidiffTransform<double, 3>(double)> base = [&](double t){ return calcPolynomialFrame(x, y, th, t); };

        auto X = getRandomPolynomial();
        auto Y = getRandomPolynomial();
        auto Th = getRandomPolynomial();
        std::function<Transform::MultidiffTransform<double, 3>(double)> add = [&](double t){ return calcPolynomialFrame(X, Y, Th, t); };
        
        std::function<void(double)> callback = [&](double t){
            constexpr double dt = 0.001;
            auto frame = base(t) + add(t);
            auto dframe = base(t+dt) + add(t+dt);
            write(fs1, t, frame);

            Transform::MultidiffTransform<double, 3> dfdt = calcDfdt(frame, dframe, dt);

            write(fs2, t, dfdt);
        };

        for(double t=0.0; t<1.0; t+=0.01){
            callback(t);
        }
    }

    // Step3. MultidiffTransformのoperator-のデバッグ
    {
        std::ofstream fs1("theoretical3.log");
        std::ofstream fs2("numerical3.log");
                
        auto x = getRandomPolynomial();
        auto y = getRandomPolynomial();
        auto th = getRandomPolynomial();
        std::function<Transform::MultidiffTransform<double, 3>(double)> get = [&](double t){ return calcPolynomialFrame(x, y, th, t); };
        
        std::function<void(double)> callback = [&](double t){
            constexpr double dt = 0.001;
            auto frame = -get(t);
            auto dframe = -get(t+dt);
            write(fs1, t, frame);

            Transform::MultidiffTransform<double, 3> dfdt = calcDfdt(frame, dframe, dt);

            write(fs2, t, dfdt);
        };

        for(double t=0.0; t<1.0; t+=0.01){
            callback(t);
        }        
    }

    // step4 検証用のファイル
    {
        std::ofstream fs("check.py");
        fs << "import matplotlib.pyplot as plt" << endl;
        fs << "import numpy as np" << endl;
        fs << "" << endl;
        fs << "def read_file(x):" << endl;
        fs << "    print('read:', x)" << endl;
        fs << "    return np.array(list(map(" << endl;
        fs << "            lambda x:list(map(float, x.split()))," << endl;
        fs << "            open(x).readlines()" << endl;
        fs << "    ))).T" << endl;
        fs << "" << endl;
        fs << "def compare(a, b):" << endl;
        fs << "    A = read_file(a)" << endl;
        fs << "    B = read_file(b)" << endl;
        fs << "" << endl;
        fs << "    for i in range(1, len(A)):" << endl;
        fs << "        print(['vx', 'vy', 'omega', 'ax', 'ay', 'alpha', 'dax', 'day', 'dalpha'][i-1])" << endl;
        fs << "        plt.plot(A[0], A[i])" << endl;
        fs << "        plt.plot(B[0], B[i])" << endl;
        fs << "        plt.pause(1.0)" << endl;
        fs << "        plt.cla()" << endl;
        fs << "" << endl;
        fs << "compare('numerical2.log', 'theoretical2.log')" << endl;
        fs << "compare('numerical3.log', 'theoretical3.log')" << endl;
    }

    // step5 検証用ファイル保存用
    {
        std::ofstream fs("save_check_py.py");
        fs << "a = open(\"check.py\", \"r\").readlines()" << endl;
        fs << "for x in a:" << endl;
        fs << "    x = x.replace('\\\"', '\\'')" << endl;
        fs << "    print('        fs << \"', x.rstrip('\\n'), '\" << endl;', sep='')" << endl;
    }
}

#endif
