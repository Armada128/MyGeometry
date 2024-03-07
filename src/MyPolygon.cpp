//
// Created by jds on 3/6/24.
//

#include "../include/MyPolygon.h"

MyPolygon::MyPolygon(const std::vector<MyPoint> &points) {
    if (points.size() < 3) throw std::invalid_argument("Too few vertices for polygon construction!");
    m_vertices.reserve(points.size());
    std::unordered_set<MyPoint, MyPoint::Hash> points_uset;
    for (const auto& p : points) if (points_uset.emplace(p).second) m_vertices.emplace_back(p);
    for (auto it = m_vertices.begin(); it < m_vertices.end(); ) {
        MyPoint a = (it == m_vertices.end() - 1) ? *m_vertices.begin() - *it : *(it + 1) - *it;
        MyPoint b = (it == m_vertices.begin()) ? *(m_vertices.end() - 1) - *it : *(it - 1) - *it;
        if ((a ^ b) == 0) it = m_vertices.erase(it);
        else it++;
    }
    m_edges.reserve(m_vertices.size());
    for (auto it = m_vertices.begin(); it < m_vertices.end(); ++it) {
        if (it < m_vertices.end() - 1) m_edges.emplace_back(*it, *(it + 1));
        else m_edges.emplace_back(*it, *m_vertices.begin());
    }
    if (SelfIntersect()) m_type = TYPE::SELF_INTERSECT;
    else if (Convex()) m_type = TYPE::CONVEX;
    else m_type = TYPE::CONCAVE;
}

bool MyPolygon::SelfIntersect() const {
    for (int i = 2; i < m_edges.size() - 1; ++i) if (m_edges.at(0) & m_edges.at(i)) return true;
    for (int i = 1; i < m_edges.size() - 2; ++i) for (int j = i + 2; j < m_edges.size(); ++j) if (m_edges.at(i) & m_edges.at(j)) return true;
    return false;
}

bool MyPolygon::Convex() const {
    if (m_edges.size() == 3) return true;
    for (const auto& edge : m_edges) {
        std::unique_ptr<bool> flag{nullptr};
        for (const auto& vertex : m_vertices) {
            if (vertex != edge.Begin() && vertex != edge.End()) {
                MyPoint a = edge.Begin() - vertex;
                MyPoint b = edge.End() - vertex;
                bool flag_temp = (a ^ b) >= 0;
                if (flag == nullptr) flag = std::make_unique<bool>(flag_temp);
                else if (*flag != flag_temp) return false;
            }
        }
    }
    return true;
}

std::set<MyPoint> MyPolygon::Intersect(const MyLine& l) const {
    std::set<MyPoint> res;
    for (const auto& edge : m_edges) {
        auto p_i = edge & l;
        if (p_i.has_value()) res.emplace(p_i.value());
    }
    return res;
}

std::set<MyPoint> MyPolygon::Intersect(const MySegment& s) const {
    std::set<MyPoint> res;
    for (const auto& edge : m_edges) {
        auto p_i = edge & s;
        if (p_i.has_value()) res.emplace(p_i.value());
    }
    return res;
}

const std::vector<MyPoint>& MyPolygon::Vertices() const {
    return m_vertices;
}

const std::vector<MySegment>& MyPolygon::Edges() const {
    return m_edges;
}

MyPolygon::TYPE MyPolygon::Type() const {
    return m_type;
}