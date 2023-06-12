#pragma once
#include <iostream>

#include <linear_algebra/Mat2.hpp>
#include <linear_algebra/Rot2.hpp>

namespace Transform
{
template <class T>
struct StaticTransform
{
    StaticTransform(T x, T y, T theta)
        : pos(linear::Vec2<T>{x,y}), rot(linear::Rot2<T>(theta))
    {
    }

    StaticTransform(linear::Vec2<T> pos, T theta)
        : pos(pos), rot(linear::Rot2<T>{theta})
    {
    }

    StaticTransform(linear::Vec2<T> pos, linear::Rot2<T> rot)
        : pos(pos), rot(rot)
    {
    }
    
    StaticTransform()
    {
    }

    StaticTransform operator -() const
    {
        linear::Rot2<T> Rot = rot.inverse();
	    linear::Vec2<T> Pos = Rot * (-pos);
	    return StaticTransform{Pos, Rot};
    }

    StaticTransform operator +(const StaticTransform& frame) const
    {
        return StaticTransform(pos + rot * frame.pos, rot + frame.rot);
    }

    linear::Vec2<T> pos;
    linear::Rot2<T> rot;
};

template <class T>
inline std::ostream& operator<<(std::ostream& os, StaticTransform<T> frame)
{
    os << "{{" << frame.pos.x << ", " << frame.pos.y << "}, {" << frame.rot.getAngle() << "}}";
    return os;
}

}
