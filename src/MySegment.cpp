//
// Created by jds on 3/6/24.
//

#include "../include/MySegment.h"

MySegment::MySegment(const MyPoint &a, const MyPoint &b) : m_a(a), m_b(b), m_l(m_a, m_b) {

}

std::optional<MyPoint> MySegment::operator&(const MySegment &s) const {
    auto p_i = m_l.Intersect(s.m_l);
    if (!p_i.has_value()) return std::nullopt;
    return (Envelope(p_i.value()) && s.Envelope(p_i.value())) ? p_i : std::nullopt;
}

std::optional<MyPoint> MySegment::operator&(const MyLine &l) const {
    auto p_i = m_l.Intersect(l);
    if (!p_i.has_value()) return std::nullopt;
    return Envelope(p_i.value()) ? p_i : std::nullopt;
}

bool MySegment::Envelope(const MyPoint &p) const {
    double x_l = fmin(m_a.x(), m_b.x());
    double x_h = fmax(m_a.x(), m_b.x());
    double y_l = fmin(m_a.y(), m_b.y());
    double y_h = fmax(m_a.y(), m_b.y());
    return p.x() <= x_h && p.x() >= x_l && p.y() <= y_h && p.y() >= y_l;
}

const MyPoint& MySegment::Begin() const {
    return m_a;
}

const MyPoint& MySegment::End() const {
    return m_b;
}

const MyLine& MySegment::Line() const {
    return m_l;
}