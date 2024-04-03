//
// Created by jds on 3/12/24.
//

#include "../include/MyAngle.h"

using namespace MyGeometry;

MyAngle::MyAngle(double angle, MyAngle::TYPE type) {
    double real = (type == TYPE::RAD) ? angle : angle * D2R;
    if (real < 0) real += ceil(-real / PI_2) * PI_2;
    else real -= floor(real / PI_2) * PI_2;
    m_angle = real;
}

double MyAngle::operator*() const { return m_angle; }

MyAngle MyAngle::operator -(const MyAngle& angle) const { return {m_angle - angle.m_angle}; }

MyAngle MyAngle::operator +(const MyAngle& angle) const { return {m_angle + angle.m_angle}; }

MyAngle operator *(const MyAngle& angle, double scale) { return {(*angle) * scale}; }

MyAngle operator *(double scale, const MyAngle& angle) { return angle * scale; }

MyAngle MyAngle::operator /(double scale) const {
    if (scale == 0) throw std::invalid_argument("Zero denominator for MyAngle division!");
    return {m_angle / scale};
}

bool MyAngle::operator ==(const MyAngle& angle) const { return m_angle == *angle; }

bool MyAngle::operator <(const MyAngle& angle) const { return m_angle < *angle; }

bool MyAngle::operator <=(const MyAngle& angle) const { return m_angle <= *angle; }

bool MyAngle::operator >(const MyAngle& angle) const { return m_angle > *angle; }

bool MyAngle::operator >=(const MyAngle& angle) const { return m_angle >= *angle; }