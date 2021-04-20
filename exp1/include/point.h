#pragma once

#ifndef POINT_H_
#define POINT_H_

struct point {
    friend std::istream& operator>>(std::istream& is, point& p);
    friend std::ostream& operator<<(std::ostream& os, const point& p);

   public:
    point(double x = 0.0, double y = 0.0);

    double x() const;
    double y() const;

    bool operator<(const point& other) const;
    bool operator==(const point& other) const;

    point operator+(const point& other) const;
    point operator-(const point& other) const;
    point operator-() const;
    point operator*(double k) const;
    point operator/(double k) const;

    point& operator+=(const point& other);
    point& operator-=(const point& other);
    point& operator*=(double k);
    point& operator/=(double k);

    double operator*(const point& other) const;
    double operator^(const point& other) const;

   private:
    double x_, y_;
};

// Implementation

inline std::istream& operator>>(std::istream& is, point& p) {
    return is >> p.x_ >> p.y_;
}

inline std::ostream& operator<<(std::ostream& os, const point& p) {
    return os << p.x_ << ' ' << p.y_;
}

inline point::point(double x, double y) : x_{x}, y_{y} {}

inline double point::x() const { return x_; }

inline double point::y() const { return y_; }

inline bool point::operator<(const point& other) const {
    return x() == other.x() ? y() < other.y() : x() < other.x();
}

inline bool point::operator==(const point& other) const {
    return x() == other.x() && y() == other.y();
}

inline point point::operator+(const point& other) const {
    return point{x() + other.x(), y() + other.y()};
}

inline point point::operator-(const point& other) const {
    return point{x_ - other.x_, y_ - other.y_};
}

inline point point::operator-() const {
    return point{-x_, -y_};
}

inline point point::operator*(double k) const {
    return point{x_ * k, y_ * k};
}

inline point point::operator/(double k) const {
    return point{x_ / k, y_ / k};
}

inline point& point::operator+=(const point& other) {
    this->x_ += other.x_;
    this->y_ += other.y_;
    return *this;
}

inline point& point::operator-=(const point& other) {
    this->x_ -= other.x_;
    this->y_ -= other.y_;
    return *this;
}

inline point& point::operator*=(double k) {
    this->x_ *= k;
    this->y_ *= k;
    return *this;
}

inline point& point::operator/=(double k) {
    this->x_ /= k;
    this->y_ /= k;
    return *this;
}

inline double point::operator*(const point& other) const {
    return x_ * other.x_ + y_ * other.y_;
}

inline double point::operator^(const point& other) const {
    return x_ * other.y_ - y_ * other.x_;
}

#endif  // POINT_H_
