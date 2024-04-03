//
// Created by jds on 3/6/24.
//

#ifndef MYGEOMETRY_MYSEGMENT_H
#define MYGEOMETRY_MYSEGMENT_H

#include <memory>
#include "MyLine.h"

class MySegment {
public:
    MySegment(const MyPoint& a, const MyPoint& b);
    std::optional<MyPoint> operator &(const MySegment& s) const;
    friend std::optional<MyPoint> operator &(const MySegment& s, const MyLine& l);
    friend std::optional<MyPoint> operator &(const MyLine& l, const MySegment& s);
    friend std::optional<MyPoint> operator |(const MyPoint& p, const MySegment& s);
    friend std::optional<MyPoint> operator |(const MySegment& s, const MyPoint& p);
    std::vector<MyPoint> operator /(int n) const;
    MyAngle Angle() const;
    bool Envelope(const MyPoint& p) const ;
    const MyPoint& Begin() const;
    const MyPoint& End() const;
    const MyLine& Line() const;
private:
    MyPoint m_begin, m_end;
    MyLine m_l;
//    double m_theta;
    std::unique_ptr<MyAngle> m_angle{nullptr};
};


#endif //MYGEOMETRY_MYSEGMENT_H
