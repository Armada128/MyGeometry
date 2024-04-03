//
// Created by jds on 3/7/24.
//

#ifndef MYGEOMETRY_MYCIRCLE_H
#define MYGEOMETRY_MYCIRCLE_H

#include <set>
#include "MyPoint.h"
#include "MySegment.h"
#include "MyPolygon.h"

class MyCircle {
public:
    MyCircle(const MyPoint& center, double radius);
    bool operator ==(const MyCircle& c) const;
    bool operator &(const MyPoint& p) const;
    std::set<MyPoint> operator &(const MyCircle& c) const;
    friend std::set<MyPoint> operator &(const MyCircle& c, const MyLine& l);
    friend std::set<MyPoint> operator &(const MyLine& l, const MyCircle& c);
    friend std::set<MyPoint> operator &(const MyCircle& c, const MySegment& s);
    friend std::set<MyPoint> operator &(const MySegment& s, const MyCircle& c);
    friend std::set<MyPoint> operator &(const MyCircle& c, const MyPolygon& poly);
    friend std::set<MyPoint> operator &(const MyPolygon& poly, const MyCircle& c);
    bool Concentric(const MyCircle& c) const;
    const MyPoint& Center() const;
    double R() const;
    double Area() const;

private:
    MyPoint m_center;
    double m_radius;
    double m_radius2;
    double m_area;
};


#endif //MYGEOMETRY_MYCIRCLE_H
