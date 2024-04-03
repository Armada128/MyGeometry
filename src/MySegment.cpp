//
// Created by jds on 3/6/24.
//

#include "../include/MySegment.h"
#include "../include/MyAngle.h"

MySegment::MySegment(const MyPoint &a, const MyPoint &b) : m_begin(a), m_end(b), m_l(m_begin, m_end) {
    auto v = m_end - m_begin;
    m_angle = std::make_unique<MyAngle>(atan2(v.y(), v.x()));
}

std::optional<MyPoint> MySegment::operator&(const MySegment &s) const {
    auto p_i = m_l & s.Line();
    if (!p_i.has_value()) return std::nullopt;
    return (Envelope(p_i.value()) && s.Envelope(p_i.value())) ? p_i : std::nullopt;
}

std::optional<MyPoint> operator &(const MySegment& s, const MyLine& l) {
    auto p_i = l & s.Line();
    if (!p_i.has_value()) return std::nullopt;
    return s.Envelope(p_i.value()) ? p_i : std::nullopt;
}

std::optional<MyPoint> operator &(const MyLine& l, const MySegment& s) {
    return s & l;
}

std::optional<MyPoint>operator |(const MyPoint& p, const MySegment& s) {
    auto pedal = p | s.Line();
    if (s.Envelope(pedal)) return pedal;
    else return std::nullopt;
}

std::optional<MyPoint> operator |(const MySegment& s, const MyPoint& p) {
    return p | s;
}

//等分
std::vector<MyPoint> MySegment::operator /(int n) const {
    if (n <= 0) throw std::invalid_argument("Nonpositive n for MySegment division!");
    std::vector<MyPoint> res;
    res.reserve(n + 1);
    MyPoint step = End() - Begin();
    step *= (double) 1 / n;
    for (int i = 0; i <= n; ++i) res.emplace_back(Begin() + step * i);
    return res;
}

MyAngle MySegment::Angle() const { return MyAngle{**m_angle}; }

bool MySegment::Envelope(const MyPoint &p) const {
    double x_l = fmin(m_begin.x(), m_end.x());
    double x_h = fmax(m_begin.x(), m_end.x());
    double y_l = fmin(m_begin.y(), m_end.y());
    double y_h = fmax(m_begin.y(), m_end.y());
    return p.x() <= x_h && p.x() >= x_l && p.y() <= y_h && p.y() >= y_l;
}

const MyPoint& MySegment::Begin() const {
    return m_begin;
}

const MyPoint& MySegment::End() const {
    return m_end;
}

const MyLine& MySegment::Line() const {
    return m_l;
}