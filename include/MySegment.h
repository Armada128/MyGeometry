//
// Created by jds on 3/6/24.
//

#ifndef MYGEOMETRY_MYSEGMENT_H
#define MYGEOMETRY_MYSEGMENT_H

#include "MyLine.h"

class MySegment {
public:
    MySegment(const MyPoint& a, const MyPoint& b);
    std::optional<MyPoint> operator &(const MySegment& s) const;
    std::optional<MyPoint> operator &(const MyLine& s) const;
    bool Envelope(const MyPoint& p) const ;
    const MyPoint& Begin() const;
    const MyPoint& End() const;
    const MyLine& Line() const;
private:
    MyPoint m_a, m_b;
    MyLine m_l;
};


#endif //MYGEOMETRY_MYSEGMENT_H
