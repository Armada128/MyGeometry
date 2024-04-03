//
// Created by jds on 3/5/24.
//

#include "../include/MyPoint.h"
#include "../include/MyLine.h"
#include "../include/MySegment.h"
#include "../include/MyCircle.h"
#include "../include/MyArc.h"

MyPoint::MyPoint(double x, double y) : m_x(x), m_y(y) {}

MyPoint::MyPoint(const Eigen::Vector2d &v) : MyPoint(v[0], v[1]) {}

//向量加
MyPoint MyPoint::operator+(const MyPoint &p) const { return {p.m_x + m_x, p.m_y + m_y}; }

//向量减
MyPoint MyPoint::operator-(const MyPoint &p) const { return {-p.m_x + m_x, -p.m_y + m_y}; }

//点乘
double MyPoint::operator*(const MyPoint &p) const { return m_x * p.m_x + m_y * p.m_y; }

//缩放
MyPoint operator *(double scale, const MyPoint& p) { return MyPoint{scale * p.m_x, scale * p.m_y}; }

MyPoint operator *(const MyPoint& p, double scale) { return scale * p; }

MyPoint MyPoint::operator /(double scale) const {
    if (scale == 0) throw std::invalid_argument("Zero denominator for MyPoint division!");
    return MyPoint{m_x / scale, m_y / scale};
}

MyPoint& MyPoint::operator +=(const MyPoint& p) {
    m_x = m_x + p.m_x;
    m_y = m_y + p.m_y;
    return *this;
}

MyPoint& MyPoint::operator -=(const MyPoint& p) {
    m_x = m_x - p.m_x;
    m_y = m_y - p.m_y;
    return *this;
}

MyPoint& MyPoint::operator *=(double scale) {
    m_x *= scale;
    m_y *= scale;
    return *this;
}

MyPoint& MyPoint::operator /=(double scale) {
    if (scale == 0) throw std::invalid_argument("Zero denominator for MyPoint division!");
    m_x /= scale;
    m_y /= scale;
    return *this;
}

//叉乘
double MyPoint::operator^(const MyPoint &p) const { return m_x * p.m_y - m_y * p.m_x; }

bool MyPoint::operator==(const MyPoint &p) const { return m_x == p.m_x && m_y == p.m_y; }

bool MyPoint::operator!=(const MyPoint &p) const { return m_x != p.m_x || m_y != p.m_y; }

bool MyPoint::operator<(const MyPoint &p) const {
    if (m_x < p.m_x) return true;
    else if (m_x == p.m_x) return m_y < p.m_y;
    else return false;
}

//点距
double MyPoint::operator &(const MyPoint& p) const {
    return sqrt(pow(m_x - p.m_x, 2) + pow(m_y - p.m_y, 2));
}

std::ostream& operator <<(std::ostream& out, const MyPoint& p) {
    out << "(" << p.x() << "," << p.y() << ")";
    return out;
}

//范数
double MyPoint::Norm() const {
    return sqrt(pow(m_x, 2) + pow(m_y, 2));
}

void MyPoint::Normalize() {
    auto l = Norm();
    if (l != 0) {
        m_x /= l;
        m_y /= l;
    }
}
/*
MyPoint MyPoint::Rotate(double theta) const {
    double cos_theta = cos(theta);
    double sin_theta = sin(theta);
    return MyPoint{m_x * cos_theta - m_y * sin_theta, m_x * sin_theta + m_y * cos_theta};
}
*/
void MyPoint::Transfer(MyAngle angle, double x, double y) {
    double cos_theta = cos(*angle);
    double sin_theta = sin(*angle);
    m_x = m_x * cos_theta - m_y * sin_theta + x;
    m_y = m_x * sin_theta + m_y * cos_theta + y;
}

MyPoint MyPoint::getTransfer(MyAngle angle, double x, double y) const {
    double cos_theta = cos(*angle);
    double sin_theta = sin(*angle);
    return {m_x * cos_theta - m_y * sin_theta + x, m_x * sin_theta + m_y * cos_theta + y};
}

double MyPoint::x() const { return m_x; }

double MyPoint::y() const { return m_y; }

void MyPoint::setX(double x) { m_x = x; }

void MyPoint::setY(double y) { m_y = y; }

void MyPoint::Refresh(double x, double y) {
    m_x = x;
    m_y = y;
}

//向量化
Eigen::Vector2d MyPoint::v() const { return Eigen::Vector2d{m_x, m_y}; }

//是否在对象线条上
bool MyPoint::On(const MyLine& l) const {
    auto [A, B, C] = l.Coefficients();
    return A * m_x + B * m_y + C == 0;
}

bool MyPoint::On(const MySegment& s) const {
    auto p_begin = s.Begin() - *this;
    auto p_end = s.End() - *this;
    return p_begin * p_end == -p_begin.Norm() * p_end.Norm();
}

bool MyPoint::On(const MyCircle& c) const {
    return (*this & c.Center()) == c.R();
}

bool MyPoint::On(const MyArc& a) const {
    if (this->On(a.Circle())) {
        MySegment s{a.Circle().Center(), *this};
        return s.Angle() & a;
    }
    return false;
}