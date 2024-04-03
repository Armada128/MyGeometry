//
// Created by jds on 3/12/24.
//

#include "../include/MyArc.h"

MyArc::MyArc(const MyCircle& c, MyAngle begin, MyAngle end, MyAngle::DIRECTION direction) : m_c(c), m_begin(begin), m_end(end), m_direction(direction) {}

bool MyArc::operator ==(const MyArc& a) {
    return (m_c == a.m_c) && (m_begin == a.m_begin) && (m_end == a.m_end) && (m_direction == a.m_direction);
}

std::set<MyPoint> MyArc::operator &(const MyArc& a) const {
    std::set<MyPoint> res;
    auto candidates = m_c & a.m_c;
    for (const auto& p : candidates) if (p.On(*this)) res.emplace(p);
    return res;
}

bool operator &(const MyArc& arc, const MyAngle& angle) {
    if (arc.m_direction == MyAngle::DIRECTION::CLOCKWISE) {
        if (arc.m_begin <= arc.m_end) return (angle <= arc.m_begin) || (angle >= arc.m_end);
        else return (angle >= arc.m_end) && (angle <= arc.m_begin);
    } else {
        if (arc.m_begin >= arc.m_end) return (angle >= arc.m_begin) || (angle <= arc.m_end);
        else return (angle >= arc.m_begin) && (angle <= arc.m_end);
    }
}

bool operator &(const MyAngle& angle, const MyArc& arc) {
    return arc & angle;
}

std::set<MyPoint> operator &(const MyArc& a, const MyLine& l) {
    std::set<MyPoint> res;
    auto candidates = a.m_c & l;
    for (const auto& p : candidates) if (p.On(a)) res.emplace(p);
    return res;
}

std::set<MyPoint> operator &(const MyLine& l, const MyArc& a) {
    return a & l;
}

std::set<MyPoint> operator &(const MyArc& a, const MySegment& s) {
    std::set<MyPoint> res;
    auto candidates = a.m_c & s;
    for (const auto& p : candidates) if (p.On(a)) res.emplace(p);
    return res;
}

std::set<MyPoint> operator &(const MySegment& s, const MyArc& a) {
    return a & s;
}

std::set<MyPoint> operator &(const MyArc& a, const MyPolygon& poly) {
    std::set<MyPoint> res;
    auto candidates = a.m_c & poly;
    for (const auto& p : candidates) if (p.On(a)) res.emplace(p);
    return res;
}

std::set<MyPoint> operator &(const MyPolygon& poly, const MyArc& a) {
    return a & poly;
}

std::vector<MyPoint> MyArc::operator /(int n) const {
    if (n <= 0) throw std::invalid_argument("Nonpositive n for MyArc division!");
    std::vector<MyPoint> res;
    res.reserve(n + 1);
    auto step = (m_end - m_begin) / n;
    double r = m_c.R();
    for (int i = 0; i <= n; ++i) {
        auto theta = m_begin + i * step;
        res.emplace_back(m_c.Center() + MyPoint{r * cos(*theta), r * sin(*theta)});
    }
    return res;
}

const MyCircle& MyArc::Circle() const {
    return m_c;
}

double MyArc::Begin() const {
    return *m_begin;
}

double MyArc::End() const {
    return *m_end;
}

MyAngle::DIRECTION MyArc::Direction() const {
    return m_direction;
}