//
// Created by jds on 3/5/24.
//

#include <iostream>
#include "../include/MyPoint.h"
#include "../include/MyLine.h"
#include "../include/MySegment.h"
#include "../include/MyPolygon.h"

int main(int argc, char** argv) {
    /*
    MyPoint p1{1, 2};
    MyPoint p2{3, 4};
    auto cross = p1 ^ p2;
    auto dot = p1 * p2;

    std::cout << "cross: " << cross << std::endl;
    std::cout << "dot: " << dot << std::endl;
     */

    std::vector<MyPoint> v{{0, 0}, {1, 0}, {0, 1}, {1, 1}};
//    std::vector<MyPoint> v{{0, 0}, {1, 0}, {2, 1}, {2, 2}, {1, 3}, {0, 3}, {-1, 2}, {-1, 1}};
    MyPolygon poly{v};

    MyPoint a{0.8, 0};
    MyPoint b{0.8, 2};
    MyLine l{a, b};
    auto p_i = poly.Intersect(l);
    if (!p_i.empty())
        for (const auto& p : p_i) {
            std::cout << p << std::endl;
        }

    return 0;
}