//
// Created by jds on 3/9/24.
//

#include "../include/Douglas_Peucker.h"

std::vector<MyPoint> Douglas_Peucker::Solve(const std::vector<MyPoint>& points, double threshold) {
    if (threshold <= 0) throw std::invalid_argument("Nonpositive threshold for Douglas Peucker!");
    if (points.size() < 3) return std::vector<MyPoint>{points};
    MyLine line{*points.begin(), *points.end()};
    double dist_max = -1;
    int index_max = -1;
    int i = 0;
    std::for_each(points.begin(), points.end(), [&](MyPoint p) mutable {
        auto pendulum = p % line;
        if (pendulum >= dist_max) {
            dist_max = pendulum;
            index_max = i;
        }
        ++i;
    });
    if (index_max >= 0) {
        std::vector<MyPoint> sub_left{points.begin(), points.begin() + index_max + 1};
        std::vector<MyPoint> sub_right{points.begin() + index_max, points.end()};
        std::vector<MyPoint> rarified_left = Solve(sub_left, threshold);
        std::vector<MyPoint> rarified_right = Solve(sub_right, threshold);
        rarified_left.insert(rarified_left.end(), rarified_right.begin() + 1, rarified_right.end());
        return rarified_left;
    } else std::vector<MyPoint> res{*points.begin(), *points.end()};
}