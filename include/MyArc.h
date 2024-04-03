//
// Created by jds on 3/12/24.
//

#ifndef MYGEOMETRY_MYARC_H
#define MYGEOMETRY_MYARC_H

#include "MyCircle.h"
#include "MyAngle.h"

class MyArc {
public:
    MyArc(const MyCircle& c, MyAngle begin, MyAngle end, MyAngle::DIRECTION direction);
    bool operator ==(const MyArc& a);
    std::set<MyPoint> operator &(const MyArc& a) const;
    friend bool operator &(const MyArc& arc, const MyAngle& angle);
    friend bool operator &(const MyAngle& angle, const MyArc& arc);
    friend std::set<MyPoint> operator &(const MyArc& a, const MyLine& l);
    friend std::set<MyPoint> operator &(const MyLine& l, const MyArc& a);
    friend std::set<MyPoint> operator &(const MyArc& a, const MySegment& s);
    friend std::set<MyPoint> operator &(const MySegment& s, const MyArc& a);
    friend std::set<MyPoint> operator &(const MyArc& a, const MyPolygon& poly);
    friend std::set<MyPoint> operator &(const MyPolygon& poly, const MyArc& a);
    std::vector<MyPoint> operator /(int n) const;
    const MyCircle& Circle() const;
    double Begin() const;
    double End() const;
    MyAngle::DIRECTION Direction() const;

private:
    const MyCircle m_c;
    MyAngle m_begin, m_end;
    MyAngle::DIRECTION m_direction;
};


#endif //MYGEOMETRY_MYARC_H
