//
// Created by jds on 3/5/24.
//

#include <iostream>
#include "../include/MyPoint.h"
#include "../include/MyLine.h"
#include "../include/MySegment.h"
#include "../include/MyPolygon.h"
#include "../include/MyArc.h"
#include "../include/MyCircle.h"

std::unique_ptr<MyLine> m_line{new MyLine{MyPoint{0, 0}, MyPoint{1, 1}}};

using namespace std;
int main(int argc, char** argv) {
    /*
    MyCircle c1{MyPoint{0.5, 1.5}, 1.5};

    std::vector<MyPoint> v{{0, 0}, {1, 0}, {2, 1}, {2, 2}, {1, 3}, {0, 3}, {-1, 2}, {-1, 1}};
    MyPolygon poly{v};

    auto intersection = poly & c1;
    for (const auto& p : intersection) {
        cout << p << endl;
    }
*/
    MyArc a1{{{0, 0}, 5}, M_PI * 0.5, 0, MyAngle::DIRECTION::CLOCKWISE};
    MyArc a2{{{10, 0}, 10}, M_PI * 1.5, M_PI * 0.5, MyAngle::DIRECTION::CLOCKWISE};
    MyLine l{MyPoint{0, 0}, MyPoint{1, 1}};

    auto res = a1 & l;
    for (const auto& p : res) {
        cout << p << endl;
    }

    return 0;
}