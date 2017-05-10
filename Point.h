//
// Created by GPA on 10/05/2017.
//

#ifndef CHAOSGAME_POINT_H
#define CHAOSGAME_POINT_H


#include <array>

class Point {
public:
    Point();
    Point(int x, int y, std::array<float, 3> c);

    int posX;
    int posY;
    std::array<float, 3> col;
};


#endif //CHAOSGAME_POINT_H
