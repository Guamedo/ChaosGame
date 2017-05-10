//
// Created by GPA on 10/05/2017.
//

#include "Point.h"

Point::Point() {
    posX=0;
    posY=0;
    col={0.0,0.0,0.0};
}

Point::Point(int x, int y, std::array<float, 3> c) {
    posX=x;
    posY=y;
    col=c;
}