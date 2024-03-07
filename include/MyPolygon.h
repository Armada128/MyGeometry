//
// Created by jds on 3/6/24.
//

#ifndef MYGEOMETRY_MYPOLYGON_H
#define MYGEOMETRY_MYPOLYGON_H

#include <unordered_set>
#include <set>
#include <vector>
#include <memory>
#include "MySegment.h"

class MyPolygon {
public:
    enum class TYPE {
        CONVEX,
        CONCAVE,
        SELF_INTERSECT
    };

    MyPolygon(const std::vector<MyPoint>& points);
    bool SelfIntersect() const;
    bool Convex() const;
    std::set<MyPoint> Intersect(const MyLine& l) const;
    std::set<MyPoint> Intersect(const MySegment& s) const;
    const std::vector<MyPoint>& Vertices() const;
    const std::vector<MySegment>& Edges() const;
    TYPE Type() const;

private:
    std::vector<MyPoint> m_vertices;
    std::vector<MySegment> m_edges;
    TYPE m_type;
};


#endif //MYGEOMETRY_MYPOLYGON_H
