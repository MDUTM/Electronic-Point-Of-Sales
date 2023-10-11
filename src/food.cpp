#include "food.h"

Food::Food(std::string name, double price)
{
    _name = name;
    _price = price;
    _count = 0;
}

std::string Food::Name()
{
    return _name;
}

double Food::Price()
{
    return _price;
}

int Food::Count()
{
    return _count;
}

void Food::addCount()
{
    ++_count;
}

void Food::subCount()
{
    _count = --_count < 0 ? 0 : _count;
}
