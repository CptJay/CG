//
// Created by yassir on 09.03.22.
//

#include <cmath>
#include "Point2D.h"

void Point2D::schaling(double schaalfactor) {
    x *= schaalfactor;
    y *= schaalfactor;
}

void Point2D::optelling(double dx, double dy) {
    x += dx;
    y += dy;
}

void Point2D::afronden() {
    x = std::lround(x);
    y = std::lround(y);
}
