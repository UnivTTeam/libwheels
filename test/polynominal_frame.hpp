#ifdef LibraryTest
#pragma once
#include <iostream>

#include <transform2d/transform2d.hpp>

template <class T, long long N>
struct Polynomial
{
    explicit Polynomial(std::array<T, N> coeff)
    : coeff(coeff), dim(N-1)
    {
    }

    template <class... Args>
    explicit Polynomial(Args... coeff)
    : coeff(std::array<T, N>{coeff...}), dim(N-1)
    {
    }

    T getValue(T x) const
    {
        T ret = 0;
        T x_k = 1;
        for(int i = dim; i>=0; i--)
        {
            ret += coeff[i] * x_k;
            x_k *= x;
        }
        return ret;
    }

    T getDiff(const int& k, const T& x) const
    {
        T ret = 0;
        T x_k = 1;
        for(int i = dim; (i-k)>=0; i--)
        {
            int C = 1;
            for(int j=1;j<=k;j++){
                // x**(dim-i) <- (dim-i)+1〜(dim-i)+k
                C *= (dim-i)+j;
            }
            ret += C * coeff[i-k] * x_k;
            x_k *= x;
        }
        return ret;
    }

    template <long long k> 
    T getDiff(const T& x) const
    {
        return getDiff(k, x);
    }

private:
    int dim;
public:
    std::array<T, N> coeff;
};

template <class T, long long A, long long B, long long C>
Transform::MultidiffTransform<T, 3> calcPolynomialFrame(Polynomial<T, A> x, Polynomial<T, B> y, Polynomial<T, C> th, T t)
{
    Transform::StaticTransform<T> s(x.getValue(t), y.getValue(t), th.getValue(t));
    Transform::DynamicTransform<T> d1(x.getDiff(1, t), y.getDiff(1, t), th.getDiff(1, t));
    Transform::DynamicTransform<T> d2(x.getDiff(2, t), y.getDiff(2, t), th.getDiff(2, t));
    Transform::DynamicTransform<T> d3(x.getDiff(3, t), y.getDiff(3, t), th.getDiff(3, t));

    return Transform::MultidiffTransform<T, 3>(s, d1, d2, d3);
}
#endif
