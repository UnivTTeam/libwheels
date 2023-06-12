#pragma once
#include <array>

#include "Vec2.hpp"

namespace linear {
template <class T>
struct Mat2 {
  // 横ベクトルを2個持つ
  Vec2<T> x;
  Vec2<T> y;

  Mat2() : x(), y() {}
  Mat2(const Vec2<T>& x, const Vec2<T>& y) : x(x), y(y) {}
  Mat2(T a11, T a12, T a21, T a22) : x(a11, a12), y(a21, a22) {}

  Mat2<T> transpose() const {
    return Mat2<T>(Vec2<T>(this->x.x, this->y.x),
                Vec2<T>(this->x.y, this->y.y));
  }

  T norm() { return std::sqrt(x * x + y * y); }

  Mat2<T> operator+(const Mat2<T>& other) const {
    return Mat2<T>(this->x + other.x, this->y + other.y);
  }

  Mat2<T> operator-(const Mat2<T>& other) const {
    return Mat2<T>(this->x - other.x, this->y - other.y);
  }

  Vec2<T> operator*(const Vec2<T>& other) const {
    return Vec2<T>(this->x * other, this->y * other);
  }

  Mat2<T> operator*(const Mat2<T>& other) const {
    Mat2<T> other_T = other.transpose();
    Mat2<T> ans_T = ((*this) * other_T.x, (*this) * other_T.y);
    return ans_T.transpose();
  }

  Mat2<T> operator*(T ratio) const {
    return Mat2<T>(this->x * ratio, this->y * ratio);
  }

  Mat2<T> operator/(T ratio) const {
    return Mat2<T>(this->x / ratio, this->y / ratio);
  }

  std::array<T, 4> write_down() const {
    return std::array<T, 4>{this->x.x, this->x.y, this->y.x, this->y.y};
  }

  Mat2<T> inverse() const {
    const auto [a, b, c, d] = this->write_down();
    T det = a * d - b * c;
    return Mat2<T>(d, -b, -c, a) / det;
  }
};

template <class T>
Mat2<T> operator*(const double k, const Mat2<T>& v) {
  return v * k;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const Mat2<T>& v) {
  os << v.x << std::endl << v.y;
  return os;
}

typedef Mat2<double> Mat2d;
typedef Mat2<float> Mat2f;
typedef Mat2<int> Mat2i;
}  // namespace linear
