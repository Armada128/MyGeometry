//
// Created by jds on 3/5/24.
//

#ifndef MYGEOMETRY_MYPOINT_H
#define MYGEOMETRY_MYPOINT_H

#include "Eigen/Core"

class MyPoint {
public:
    MyPoint(double x, double y);
    MyPoint(const Eigen::Vector2d& v);
    MyPoint operator -(const MyPoint& p) const;
    MyPoint operator +(const MyPoint& p) const;
    double operator *(const MyPoint& p) const;
    double operator ^(const MyPoint& p) const;
    bool operator ==(const MyPoint& p) const;
    bool operator !=(const MyPoint& p) const;
    bool operator <(const MyPoint& p) const;
    friend std::ostream& operator <<(std::ostream& out, const MyPoint& p);
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
private:
    double m_x, m_y;
};


#endif //MYGEOMETRY_MYPOINT_H
