#include <stdlib.h>
#include <iostream>
#include "Vector2.h"

Vector2::Vector2(){
    this->x=0.0;
    this->y=0.0;
}

Vector2::Vector2(double _x, double _y){
    this->x=_x;
    this->y=_y;
}

Vector2::~Vector2(){}


double Vector2::dot(Vector2 v){
    double res;
    res = this->x * v.x + this->y * v.y;
    return res;
}

Vector2 Vector2::operator +(const Vector2  & v) const{
    double _x,_y;
    _x = this->x + v.x;
    _y = this->y + v.y;
    Vector2 res(_x,_y);
    return res;
}

Vector2 Vector2::operator *(double k) const{
    double _x,_y;
    _x = this->x * k;
    _y = this->y * k;
    Vector2 res(_x,_y);
    return res;
}
