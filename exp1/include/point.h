#pragma once

#ifndef POINT_H_
#define POINT_H_

struct point {
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
    point operator^(const point& other) const;

   private:
    double x_, y_;
};

// Implementation

point::point(double x, double y) : x_{x}, y_{y} {}

double point::x() const { return x_; }

double point::y() const { return y_; }

bool point::operator<(const point& other) const {
    return x() == other.x() ? y() < other.y() : x() < other.x();
}

bool point::operator==(const point& other) const {
    return x() == other.x() && y() == other.y();
}

point point::operator+(const point& other) const {
    return point{x() + other.x(), y() + other.y()};
}

point point::operator-(const point& other) const {
    return point{x_ - other.x_, y_ - other.y_};
}

point point::operator-() const {
    return point{-x_, -y_};
}

point point::operator*(double k) const {
    return point{x_ * k, y_ * k};
}

point point::operator/(double k) const {
    return point{x_ / k, y_ / k};
}

point& point::operator+=(const point& other) {
    this->x_ += other.x_;
    this->y_ += other.y_;
    return *this;
}

point& point::operator-=(const point& other) {
    this->x_ -= other.x_;
    this->y_ -= other.y_;
    return *this;
}

point& point::operator*=(double k) {
    this->x_ *= k;
    this->y_ *= k;
    return *this;
}

point& point::operator/=(double k) {
    this->x_ /= k;
    this->y_ /= k;
    return *this;
}

double point::operator*(const point& other) const {
    return x_ * other.x_ + y_ * other.y_;
}

point point::operator^(const point& other) const {
    return point{x_ * other.y_, y_ * other.x_};
}

#endif  // POINT_H_
