#ifndef _FOOD_H
#define _FOOD_H 1

#include <iostream>
#include <string>

class Food
{
    std::string _name;
    double _price;
    int _count;

public:
    Food(std::string name, double price);

    std::string Name();
    double Price();
    int Count();
    void addCount();
    void subCount();
};

#endif /* _FOOD_H */