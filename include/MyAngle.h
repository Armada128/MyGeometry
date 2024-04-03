//
// Created by jds on 3/12/24.
//

#ifndef MYGEOMETRY_MYANGLE_H
#define MYGEOMETRY_MYANGLE_H

#include <cmath>
#include <stdexcept>

namespace MyGeometry {
    constexpr double R2D = 180 / M_PI;
    constexpr double D2R = M_PI / 180;
    constexpr double PI_2 = 2 * M_PI;
}

class MyAngle {
public:
    enum class TYPE {
        RAD,
        DEGREE
    };
    enum class DIRECTION {
        CLOCKWISE,
        ANTICLOCKWISE
    };
    MyAngle(double angle, TYPE type = TYPE::RAD);
    double operator *() const;
    MyAngle operator -(const MyAngle& angle) const;
    MyAngle operator +(const MyAngle& angle) const;
    friend MyAngle operator *(const MyAngle& angle, double scale);
    friend MyAngle operator *(double scale, const MyAngle& angle);
    MyAngle operator /(double scale) const;
    bool operator ==(const MyAngle& angle) const;
    bool operator <(const MyAngle& angle) const;
    bool operator <=(const MyAngle& angle) const;
    bool operator >(const MyAngle& angle) const;
    bool operator >=(const MyAngle& angle) const;

private:
    double m_angle;
};


#endif //MYGEOMETRY_MYANGLE_H
