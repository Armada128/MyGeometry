//
// Created by jds on 3/9/24.
//

#ifndef MYGEOMETRY_DOUGLAS_PEUCKER_H
#define MYGEOMETRY_DOUGLAS_PEUCKER_H

#include <vector>
#include <unordered_set>
#include "MyPoint.h"
#include "MyLine.h"

class Douglas_Peucker {
public:
    static std::vector<MyPoint> Solve(const std::vector<MyPoint>& points, double threshold);
};


#endif //MYGEOMETRY_DOUGLAS_PEUCKER_H
