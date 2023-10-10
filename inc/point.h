/**
 * @file    point.h
 * @version 1.0
 * @brief   点类 (x, y)
 * 
 * @author  MDUTM  MDUTM@outlook.com
 * @date    2023-09-29
 * 
 * @copyright Copyright (c) 2023 
 */
#ifndef _POINT_H
#define _POINT_H 1

class Point {
public:
    Point(int x = 0, int y = 0) :_x(x), _y(y) { }
    void setX(int x);
    void setY(int y);
    int X();
    int Y();

private:
    int _x;
    int _y;
};

#endif /* _POINT_H */