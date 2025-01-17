//
// Created by jds on 3/5/24.
//

#ifndef MYGEOMETRY_MYPOINT_H
#define MYGEOMETRY_MYPOINT_H

#include "Eigen/Core"
#include "MyAngle.h"

class MySegment;
class MyLine;
class MyArc;
class MyCircle;

class MyPoint {
public:
    MyPoint(double x, double y);
    MyPoint(const Eigen::Vector2d& v);
    MyPoint operator -(const MyPoint& p) const;
    MyPoint operator +(const MyPoint& p) const;
    double operator *(const MyPoint& p) const;
    friend MyPoint operator *(double scale, const MyPoint& p);
    friend MyPoint operator *(const MyPoint& p, double scale);
    MyPoint operator /(double scale) const;
    MyPoint& operator +=(const MyPoint& p);
    MyPoint& operator -=(const MyPoint& p);
    MyPoint& operator *=(double scale);
    MyPoint& operator /=(double scale);
    double operator ^(const MyPoint& p) const;
    bool operator ==(const MyPoint& p) const;
    bool operator !=(const MyPoint& p) const;
    bool operator <(const MyPoint& p) const;
    double operator &(const MyPoint& p) const;
    friend std::ostream& operator <<(std::ostream& out, const MyPoint& p);
    double Norm() const;
    void Normalize();
//    MyPoint Rotate(double theta) const;
    void Transfer(MyAngle angle, double x, double y);
    MyPoint getTransfer(MyAngle angle, double x, double y) const;
    double x() const;
    double y() const;
    void setX(double x);
    void setY(double y);
    void Refresh(double x, double y);
    Eigen::Vector2d v() const;
    struct Hash
    {
        size_t operator()(const MyPoint& p) const
        {
            size_t xHash = std::hash<int>()(static_cast<int>(p.m_x * 100));
            size_t yHash = std::hash<int>()(static_cast<int>(p.m_y * 100)) << 1;
            return xHash ^ yHash;
        }
    };
    bool On(const MyLine& l) const;
    bool On(const MySegment& s) const;
    bool On(const MyCircle& c) const;
    bool On(const MyArc& a) const;

private:
    double m_x, m_y;
};


#endif //MYGEOMETRY_MYPOINT_H
