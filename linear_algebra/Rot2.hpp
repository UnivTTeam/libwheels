#pragma once
#include <cmath>

#include "Mat2.hpp"

namespace linear {
template <class T>
struct Rot2 {
  Rot2() : theta(0), costheta(1), sintheta(0)
  { 
  }

  Rot2(T theta) : theta(theta), costheta(std::cos(theta)), sintheta(std::sin(theta))
  {
  }

  Rot2(T theta, T costheta, T sintheta) 
  : theta(theta), costheta(costheta), sintheta(sintheta)
  {
  }

  Rot2 operator+(const Rot2<T>& other) const {
    return Rot2(this->theta + other.getAngle());
  }

  Rot2 operator-(const Rot2<T>& other) const {
    return Rot2(this->theta - other.getAngle());
  }

  Vec2<T> operator*(const Vec2<T>& other) const {
    Mat2<T> R(costheta, -sintheta, sintheta, costheta);
    return R * other;
  }

  Rot2<T> inverse() const {
    return Rot2<T>(-theta, costheta, -sintheta);
  }

  T getAngle() const {
    return theta;
  }

private:
  T theta;
  T costheta;
  T sintheta;  
};

template <class T>
std::ostream& operator<<(std::ostream& os, const Rot2<T>& R) {
  os << "{" << R.getAngle() << "}" << std::endl;
  return os;
}

}  // namespace linear
