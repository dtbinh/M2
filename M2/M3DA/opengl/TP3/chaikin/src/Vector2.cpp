#include <stdlib.h>
#include <iostream>
#include "Vector2.h"

Vector2::Vector2(double _x, double _y){
    this->x=_x;
    this->y=_y;
}

Vector2::~Vector2(){}

Vector2 Vector2::add(Vector2 v){
    double _x,_y;
    _x = this->x + v.x;
    _y = this->y + v.y;
    Vector2 res(_x,_y);
    return res;
}

double Vector2::dot(Vector2 v){
    double res;
    res = this->x * v.x + this->y * v.y;
    return res;
}
