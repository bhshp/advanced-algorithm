#pragma once

#ifndef POINT2D_H_
#define POINT2D_H_

#include "util.h"

struct point2d {
    friend std::istream& operator>>(std::istream& is, point2d& p);
    friend std::ostream& operator<<(std::ostream& os, const point2d& p);

   public:
    point2d(double x = 0.0, double y = 0.0);

    double x() const;
    double y() const;

    bool operator<(const point2d& other) const;
    bool operator==(const point2d& other) const;

    point2d operator+(const point2d& other) const;
    point2d operator-(const point2d& other) const;
    point2d operator-() const;
    point2d operator*(double k) const;
    point2d operator/(double k) const;

    point2d& operator+=(const point2d& other);
    point2d& operator-=(const point2d& other);
    point2d& operator*=(double k);
    point2d& operator/=(double k);

    double operator*(const point2d& other) const;
    double operator^(const point2d& other) const;

    double length() const;
    double length2() const;

   private:
    double x_, y_;
};

// Implementation

inline std::istream& operator>>(std::istream& is, point2d& p) {
    return is >> p.x_ >> p.y_;
}

inline std::ostream& operator<<(std::ostream& os, const point2d& p) {
    return os << p.x_ << ' ' << p.y_;
}

inline point2d::point2d(double x, double y) : x_{x}, y_{y} {}

inline double point2d::x() const { return x_; }

inline double point2d::y() const { return y_; }

inline bool point2d::operator<(const point2d& other) const {
    return x() == other.x() ? y() < other.y() : x() < other.x();
}

inline bool point2d::operator==(const point2d& other) const {
    return x() == other.x() && y() == other.y();
}

inline point2d point2d::operator+(const point2d& other) const {
    return point2d{x() + other.x(), y() + other.y()};
}

inline point2d point2d::operator-(const point2d& other) const {
    return point2d{x_ - other.x_, y_ - other.y_};
}

inline point2d point2d::operator-() const {
    return point2d{-x_, -y_};
}

inline point2d point2d::operator*(double k) const {
    return point2d{x_ * k, y_ * k};
}

inline point2d point2d::operator/(double k) const {
    return point2d{x_ / k, y_ / k};
}

inline point2d& point2d::operator+=(const point2d& other) {
    this->x_ += other.x_;
    this->y_ += other.y_;
    return *this;
}

inline point2d& point2d::operator-=(const point2d& other) {
    this->x_ -= other.x_;
    this->y_ -= other.y_;
    return *this;
}

inline point2d& point2d::operator*=(double k) {
    this->x_ *= k;
    this->y_ *= k;
    return *this;
}

inline point2d& point2d::operator/=(double k) {
    this->x_ /= k;
    this->y_ /= k;
    return *this;
}

inline double point2d::operator*(const point2d& other) const {
    return x_ * other.x_ + y_ * other.y_;
}

inline double point2d::operator^(const point2d& other) const {
    return x_ * other.y_ - y_ * other.x_;
}

inline double point2d::length() const {
    return std::sqrt(length2());
}

inline double point2d::length2() const {
    return sqr(x_) * sqr(y_);
}

#endif  // POINT2D_H_
