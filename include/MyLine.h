//
// Created by jds on 3/5/24.
//

#ifndef MYGEOMETRY_MYLINE_H
#define MYGEOMETRY_MYLINE_H

#include "MyPoint.h"
#include "MyAngle.h"
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
    MyLine(const MyPoint& p, Eigen::Vector2d n);
//    MyPoint Pedal(const MyPoint& p) const;
    friend MyPoint operator |(const MyPoint& p, const MyLine& l);
    friend MyPoint operator |(const MyLine& l, const MyPoint& p);
    friend double operator %(const MyPoint& p, const MyLine& l);
    friend double operator %(const MyLine& l, const MyPoint& p);
    std::optional<double> operator %(const MyLine& l) const;
    std::optional<MyPoint> operator &(const MyLine& l) const;
    bool operator ==(const MyLine& l) const;
    bool operator ||(const MyLine& l) const;
    MyLine Offset(const Eigen::Vector2d& v) const ;
    void Move(const Eigen::Vector2d& v);
    std::tuple<double, double, double> Coefficients() const;
    MyAngle Angle() const;
    Eigen::Matrix2d M() const;
    Eigen::Vector2d N() const;
    Eigen::Vector2d E() const;
    TYPE Type() const;
private:
    double m_A, m_B, m_C;
    double m_A2B2, m_A2B2_sqrt;
//    double m_theta;
    MyAngle m_angle;
    Eigen::Matrix2d m_m;
    Eigen::Vector2d m_n;
    Eigen::Vector2d m_e;
    TYPE m_type;
};


#endif //MYGEOMETRY_MYLINE_H
