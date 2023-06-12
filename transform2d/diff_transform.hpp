// Rot * Posの微分を計算する関数
#pragma once

#include <algorithm>

#include <linear_algebra/Mat2.hpp>

namespace Transform
{
template <class T>
inline linear::Vec2<T> rot_vec_diff1(const linear::Vec2<T>& r, const linear::Rot2<T> Rot,
    const linear::Vec2<T>& v, const T omega)
{
    const linear::Mat2<T> R(0, -1, 1, 0);
    return Rot * (omega * R * r + v);
}

template <class T>
inline linear::Vec2<T> rot_vec_diff2(const linear::Vec2<T>& r, const linear::Rot2<T> Rot,
    const linear::Vec2<T>& v, const T omega,
    const linear::Vec2<T>& a, const T alpha)
{
    const linear::Mat2<T> R(0, -1, 1, 0);
    const linear::Mat2<T> R2(-1, 0, 0, -1);
    return Rot *
       (std::pow(omega, 2) * R2 * r
           + alpha * R * r
           + 2 * omega * R * v
           + a);
}

template <class T>
inline linear::Vec2<T> rot_vec_diff3(const linear::Vec2<T>& r, const linear::Rot2<T> Rot,
    const linear::Vec2<T>& v, const T omega,
    const linear::Vec2<T>& a, const T alpha,
    const linear::Vec2<T>& da, const T dalpha)
{
    const linear::Mat2<T> R(0, -1, 1, 0);
    const linear::Mat2<T> R2(-1, 0, 0, -1);
    const linear::Mat2<T> R3(0, 1, -1, 0);

    return Rot * 
        (std::pow(omega, 3) * (R3 * r) + 3 * alpha * omega * (R2 * r) + dalpha * (R * r)
            + 3 * std::pow(omega, 2) * (R2 * v) + 3 * alpha * (R * v)
            + 3 * omega * (R * a)
            + da);
}

}
