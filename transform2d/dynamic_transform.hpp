#pragma once
#include <iostream>
#include <utility>

#ifdef LibraryTest
#include <linear_algebra/Mat2.hpp>
#else
#include "../linear_algebra/Mat2.hpp"
#endif

namespace Transform
{
template <class T>
struct DynamicTransform
{
    DynamicTransform(T dx, T dy, T rot)
        : pos(linear::Vec2<T>{dx,dy}), rot(rot)
    {
    }

    DynamicTransform(linear::Vec2<T> pos, T rot)
        : pos(pos),  rot(rot)
    {
    }

    DynamicTransform()
        : pos(linear::Vec2<T>()),  rot(0)
    {
    }

    std::pair<T, T> getPos() const
    {
        return std::make_pair<T, T>(T(pos.x), T(pos.y));
    }

    linear::Vec2<T> pos;
    T rot;
};

template <class T>
inline std::ostream& operator<<(std::ostream& os, DynamicTransform<T> frame)
{
    os << "{{" << frame.pos.x << ", " << frame.pos.y << "}, {" << frame.rot << "}";
    return os;
}

}
