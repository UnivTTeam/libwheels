#pragma once
#include <cmath>
#include <ostream>

namespace linear {
template <class T>
struct Vec2 {
  T x;
  T y;

  Vec2() : x(0), y(0) {}
  Vec2(T x, T y) : x(x), y(y) {}

  T norm() { return std::sqrt(x * x + y * y); }

  Vec2 operator+(const Vec2<T>& other) const {
    return Vec2{.x = this->x + other.x, .y = this->y + other.y};
  }

  Vec2 operator-(const Vec2<T>& other) const {
    return Vec2{.x = this->x - other.x, .y = this->y - other.y};
  }

  T operator*(const Vec2<T>& other) const {
    return this->x * other.x + this->y * other.y;
  }

  Vec2 operator*(const T& ratio) const {
    return Vec2{.x = this->x * ratio, .y = this->y * ratio};
  }

  Vec2 operator/(const T& ratio) const {
    return Vec2{.x = this->x / ratio, .y = this->y / ratio};
  }

  Vec2 operator-() const {
    return Vec2{.x = -this->x, .y = -this->y};
  }
};

template <class T>
Vec2<T> operator*(const double k, const Vec2<T>& v) {
  return v * k;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const Vec2<T>& v) {
  os << v.x << "," << v.y;
  return os;
}

template <class T>
T d(const Vec2<T>& v1, const Vec2<T>& v2) {
  return (v1 - v2).norm();
}

typedef Vec2<double> Vec2d;
typedef Vec2<float> Vec2f;
typedef Vec2<int> Vec2i;
}  // namespace linear
