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

bool MyPolygon::operator &(const MyPoint& p) {
    if (m_type == TYPE::SELF_INTERSECT) return false;
    MyLine l{p, Eigen::Vector2d{0, 1}};
    std::set<MyPoint> point_set;
    for (const auto& edge : m_edges) {
        if ((p % edge.Line()) == 0) return true;
        auto p_i = edge & l;
        if (p_i.has_value() && std::find(m_vertices.begin(), m_vertices.end(), p_i.value()) == m_vertices.end()) point_set.insert(p_i.value());
    }
    if (!point_set.empty()) {
        point_set.insert(p);
        int count = 0;
        for (auto it = point_set.begin(); it != point_set.end(); ) {
            if (*it != p) ++count;
            else {
                if (count % 2 == 0) return false;
                else count = 0;
            }
            ++it;
        }
        return count % 2 != 0;
    } else return false;
}

std::set<MyPoint> operator &(const MyPolygon& poly, const MyLine& l) {
    std::set<MyPoint> res;
    for (const auto& edge : poly.Edges()) {
        auto p_i = edge & l;
        if (p_i.has_value()) res.emplace(p_i.value());
    }
    return res;
}

std::set<MyPoint> operator &(const MyLine& l, const MyPolygon& poly) {
    return poly & l;
}

std::set<MyPoint> operator &(const MyPolygon& poly, const MySegment& s) {
    std::set<MyPoint> res;
    for (const auto& edge : poly.Edges()) {
        auto p_i = edge & s;
        if (p_i.has_value()) res.emplace(p_i.value());
    }
    return res;
}

std::set<MyPoint> operator &(const MySegment& s, const MyPolygon& poly) {
    return poly & s;
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