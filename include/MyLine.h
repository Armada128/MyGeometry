//
// Created by jds on 3/5/24.
//

#ifndef MYGEOMETRY_MYLINE_H
#define MYGEOMETRY_MYLINE_H

#include "MyPoint.h"
#include "Eigen/LU"

class MyLine {
public:
    enum class TYPE {
        NORMAL,
        VERTICAL,
        HORIZONTAL
    };
    MyLine(const MyPoint& p1, const MyPoint& p2);
    MyLine(double A, double B, double C);
    MyPoint Pedal(const MyPoint& p);
    MyLine Offset(const Eigen::Vector2d& v) const ;
    void Move(const Eigen::Vector2d& v);
    std::optional<MyPoint> Intersect(const MyLine& l) const;
    bool operator ==(const MyLine& l) const;
    std::tuple<double, double, double> Coefficients() const;
    double Theta() const;
    Eigen::Vector2d N() const;
    Eigen::Vector2d E() const;
    TYPE Type() const;
private:
    double m_A, m_B, m_C;
    double m_A2B2, m_A2B2_sqrt;
    double m_theta;
    Eigen::Matrix2d m_a;
    Eigen::Vector2d m_n;
    Eigen::Vector2d m_e;
    TYPE m_type;
};


#endif //MYGEOMETRY_MYLINE_H
