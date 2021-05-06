#pragma once

#ifndef POINT2D_H_
#define POINT2D_H_

struct point2d {
    friend std::ostream& operator<<(std::ostream& os, const point2d& p);

   public:
    point2d(double x = 0.0, double y = 0.0);

    bool operator<(const point2d& other) const;
    point2d operator+(const point2d& other) const;
    point2d operator-(const point2d& other) const;
    double operator^(const point2d& other) const;
    double length2() const;

   private:
    double x_, y_;
};

// Implementation

inline std::ostream& operator<<(std::ostream& os, const point2d& p) {
    return os << p.x_ << ' ' << p.y_;
}

inline point2d::point2d(double x, double y) : x_{x}, y_{y} {}

inline bool point2d::operator<(const point2d& other) const {
    return x_ == other.x_ ? y_ < other.y_ : x_ < other.x_;
}

inline point2d point2d::operator+(const point2d& other) const {
    return point2d{x_ + other.x_, y_ + other.y_};
}

inline point2d point2d::operator-(const point2d& other) const {
    return point2d{x_ - other.x_, y_ - other.y_};
}

inline double point2d::operator^(const point2d& other) const {
    return x_ * other.y_ - y_ * other.x_;
}

inline double point2d::length2() const { return x_ * x_ * y_ * y_; }

#endif  // POINT2D_H_
