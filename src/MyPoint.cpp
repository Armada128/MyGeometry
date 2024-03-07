//
// Created by jds on 3/5/24.
//

#include "../include/MyPoint.h"

MyPoint::MyPoint(double x, double y) : m_x(x), m_y(y) {}

MyPoint::MyPoint(const Eigen::Vector2d &v) : MyPoint(v[0], v[1]) {}

MyPoint MyPoint::operator+(const MyPoint &p) const { return {p.m_x + m_x, p.m_y + m_y}; }

MyPoint MyPoint::operator-(const MyPoint &p) const { return {-p.m_x + m_x, -p.m_y + m_y}; }

double MyPoint::operator*(const MyPoint &p) const { return m_x * p.m_x + m_y * p.m_y; }

double MyPoint::operator^(const MyPoint &p) const { return m_x * p.m_y - m_y * p.m_x; }

bool MyPoint::operator==(const MyPoint &p) const { return m_x == p.m_x && m_y == p.m_y; }

bool MyPoint::operator!=(const MyPoint &p) const { return m_x != p.m_x || m_y != p.m_y; }

bool MyPoint::operator<(const MyPoint &p) const {
    if (m_x < p.m_x) return true;
    else if (m_x == p.m_x) return m_y < p.m_y;
    else return false;
}

std::ostream& operator <<(std::ostream& out, const MyPoint& p) {
    out << "(" << p.x() << "," << p.y() << ")";
    return out;
}

double MyPoint::x() const { return m_x; }

double MyPoint::y() const { return m_y; }

void MyPoint::setX(double x) { m_x = x; }

void MyPoint::setY(double y) { m_y = y; }

void MyPoint::Refresh(double x, double y) {
    m_x = x;
    m_y = y;
}

Eigen::Vector2d MyPoint::v() const { return Eigen::Vector2d{m_x, m_y}; }