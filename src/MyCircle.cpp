//
// Created by jds on 3/7/24.
//

#include "../include/MyCircle.h"

MyCircle::MyCircle(const MyPoint &center, double radius) : m_center(center) {
    if (radius <= 0) throw std::invalid_argument("Negative radius!");
    m_radius = radius;
    m_radius2 = m_radius * m_radius;
    m_area = M_PI * m_radius2;
}

bool MyCircle::operator ==(const MyCircle& c) const {
    return Concentric(c) && (m_radius == c.m_radius);
}

bool MyCircle::operator &(const MyPoint& p) const {
    return ((m_center & p) <= m_radius);
}

std::set<MyPoint> MyCircle::operator &(const MyCircle& c) const {
    std::set<MyPoint> res;
    if (!Concentric(c)) {
        auto center_dist = m_center & c.m_center;
        auto radius_sum = m_radius + c.m_radius;
        if (center_dist <= radius_sum) {
            MyPoint e = c.m_center - m_center;
            e.Normalize();
            MyPoint n = e.getTransfer(M_PI * 0.5, 0, 0);
            double cos_theta = (-c.m_radius2 + m_radius2 + pow(center_dist, 2)) / (2 * m_radius * center_dist);
            double sin_theta = sqrt(1 - pow(cos_theta, 2));
            double scale_n = m_radius * sin_theta;
            auto a = m_radius * cos_theta * e + scale_n * n;
            res.emplace(m_center + MyPoint{a});
            if (sin_theta != 0) {
                auto b = a - 2 * scale_n * n;
                res.emplace(m_center + b);
            }
        }
    }
    return res;
}

std::set<MyPoint> operator &(const MyCircle& c, const MyLine& l) {
    std::set<MyPoint> res;
    auto pedal = c.m_center | l;
    auto pendulum = c.m_center & pedal;
    if (pendulum <= c.m_radius) {
        MyPoint half_chord_v{l.E()};
        double half_chord = sqrt(c.m_radius2 - pow(pendulum, 2));
        half_chord_v *= half_chord;
        res.emplace(pedal + half_chord_v);
        if (half_chord != 0) res.emplace(pedal - half_chord_v);
    }
    return res;
}

std::set<MyPoint> operator &(const MyLine& l, const MyCircle& c) {
    return c & l;
}

std::set<MyPoint> operator &(const MyCircle& c, const MySegment& s) {
    std::set<MyPoint> res;
    auto candidates = c & s.Line();
    if (!candidates.empty()) for (const auto& p : candidates) if (p.On(s)) res.emplace(p);
    return res;
}

std::set<MyPoint> operator &(const MySegment& s, const MyCircle& c) {
    return c & s;
}

std::set<MyPoint> operator &(const MyCircle& c, const MyPolygon& poly) {
    std::set<MyPoint> res;
    for (const auto& edge : poly.Edges()) {
        auto candidates = c & edge;
        res.insert(candidates.begin(), candidates.end());
    }
    return res;
}

std::set<MyPoint> operator &(const MyPolygon& poly, const MyCircle& c) {
    return c & poly;
}

bool MyCircle::Concentric(const MyCircle& c) const {
    return m_center == c.m_center;
}

const MyPoint& MyCircle::Center() const { return m_center; }

double MyCircle::R() const { return m_radius; }

double MyCircle::Area() const { return m_area; }