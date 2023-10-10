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
#include "point.h"

void Point::setX(int x)
{
    _x = x;
}

void Point::setY(int y)
{
    _y = y;
}

int Point::X()
{
    return _x;
}

int Point::Y()
{
    return _y;
}
