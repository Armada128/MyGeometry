//
// Created by jds on 3/5/24.
//

#include "../include/MyLine.h"

MyLine::MyLine(double A, double B, double C) : m_A(A), m_B(B), m_C(C), m_A2B2(m_A * m_A + m_B * m_B), m_A2B2_sqrt(sqrt(m_A2B2)), m_angle(atan2(-m_A, m_B)) {
    m_e << m_B / m_A2B2_sqrt, -m_A / m_A2B2_sqrt;
    m_n << m_A / m_A2B2_sqrt, m_B / m_A2B2_sqrt;
    m_m << m_A, m_B,
         -m_B, m_A;
    if (m_A == 0 && m_B != 0) m_type = TYPE::HORIZONTAL;
    else if (m_B == 0 && m_A != 0) m_type = TYPE::VERTICAL;
    else if (m_A != 0 && m_B != 0) m_type = TYPE::NORMAL;
    else throw std::invalid_argument("Wrong arguments for constucting line!");
}

MyLine::MyLine(const MyPoint &p1, const MyPoint &p2) : MyLine(p1.y() - p2.y(), p2.x() - p1.x(), p1.x() * p2.y() - p1.y() * p2.x()) {}

//点法式
MyLine::MyLine(const MyPoint& p, Eigen::Vector2d n) : MyLine(n[0], n[1], -n[0] * p.x() - n[1] * p.y()) {}

//点在直线投影
MyPoint operator |(const MyPoint& p, const MyLine& l) {
    auto [A, B, C] = l.Coefficients();
    Eigen::Vector2d b{-C, A * p.y() - B * p.x()};
    Eigen::Vector2d res = l.M().lu().solve(b);
    return {res[0], res[1]};
}

MyPoint operator |(const MyLine& l, const MyPoint& p) {
    return p | l;
}

//点到直线距离
double operator %(const MyPoint& p, const MyLine& l) {
    MyPoint pedal = l | p;
    return (pedal & p);
}

double operator %(const MyLine& l, const MyPoint& p) {
    return p % l;
}

//平移线
MyLine MyLine::Offset(const Eigen::Vector2d &v) const {
    return {m_A, m_B, m_C - m_A * v[0] - m_B * v[1]};
}

void MyLine::Move(const Eigen::Vector2d &v) {
    m_C -= m_A * v[0] + m_B * v[1];
}

//两直线交点
std::optional<MyPoint> MyLine::operator &(const MyLine &l) const {
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

//平行直线距离
std::optional<double> MyLine::operator %(const MyLine& l) const {
    if (!(*this || l)) return std::nullopt;
    return abs(m_C - l.m_C) / m_A2B2;
}

//判断平行
bool MyLine::operator ||(const MyLine& l) const {
    if (m_type != l.Type()) return false;
    return m_A * l.m_B == l.m_A * m_B;
}

std::tuple<double, double, double> MyLine::Coefficients() const {
    return {m_A, m_B, m_C};
}

MyAngle MyLine::Angle() const {
    return m_angle;
}

Eigen::Matrix2d MyLine::M() const {
    return m_m;
}

//法向量
Eigen::Vector2d MyLine::N() const {
    return m_n;
}

//方向向量
Eigen::Vector2d MyLine::E() const {
    return m_e;
}

MyLine::TYPE MyLine::Type() const {
    return m_type;
}