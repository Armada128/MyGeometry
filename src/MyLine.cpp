//
// Created by jds on 3/5/24.
//

#include "../include/MyLine.h"

MyLine::MyLine(double A, double B, double C) : m_A(A), m_B(B), m_C(C), m_A2B2(m_A * m_A + m_B * m_B), m_A2B2_sqrt(sqrt(m_A2B2)), m_theta(atan2(-m_A, m_B)) {
    m_e << m_B / m_A2B2_sqrt, -m_A / m_A2B2_sqrt;
    m_n << m_A / m_A2B2_sqrt, m_B / m_A2B2_sqrt;
    m_a << m_A, m_B,
         -m_B, m_A;
    if (m_A == 0 && m_B != 0) m_type = TYPE::HORIZONTAL;
    else if (m_B == 0 && m_A != 0) m_type = TYPE::VERTICAL;
    else if (m_A != 0 && m_B != 0) m_type = TYPE::NORMAL;
}

MyLine::MyLine(const MyPoint &p1, const MyPoint &p2) : MyLine(p1.y() - p2.y(), p2.x() - p1.x(), p1.x() * p2.y() - p1.y() * p2.x()) {}

MyPoint MyLine::Pedal(const MyPoint &p) {
    Eigen::Vector2d b{-m_C, m_A * p.y() - m_B * p.x()};
    Eigen::Vector2d res = m_a.lu().solve(b);
    return {res[0], res[1]};
}

MyLine MyLine::Offset(const Eigen::Vector2d &v) const {
    return {m_A, m_B, m_C - m_A * v[0] - m_B * v[1]};
}

void MyLine::Move(const Eigen::Vector2d &v) {
    m_C -= m_A * v[0] + m_B * v[1];
}

std::optional<MyPoint> MyLine::Intersect(const MyLine& l) const {
    if (m_A * l.m_B == m_B * l.m_A) return std::nullopt;
    Eigen::Matrix2d A;
    A << m_A, m_B,
         l.m_A, l.m_B;
    Eigen::Vector2d b;
    b << -m_C, -l.m_C;
    Eigen::Vector2d v = A.lu().solve(b);
    return MyPoint{v[0], v[1]};
}

bool MyLine::operator==(const MyLine &l) const {
    if (l.m_type == TYPE::VERTICAL) return l.m_C == 0 || m_A / l.m_A == m_C / l.m_C;
    else if (l.m_type == TYPE::HORIZONTAL) return l.m_C == 0 || m_B / l.m_B == m_C / l.m_C;
    else if (m_A / l.m_A == m_B / l.m_B) return l.m_C == 0 || m_C / l.m_C == m_A / l.m_A;
    else return false;
}

std::tuple<double, double, double> MyLine::Coefficients() const {
    return {m_A, m_B, m_C};
}

double MyLine::Theta() const {
    return m_theta;
}

Eigen::Vector2d MyLine::N() const {
    return m_n;
}

Eigen::Vector2d MyLine::E() const {
    return m_e;
}

MyLine::TYPE MyLine::Type() const {
    return m_type;
}