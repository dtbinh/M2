#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2{


    public:
    double x,y;
    Vector2(double _x, double _y);
    virtual ~Vector2();
    Vector2 add(Vector2 v);
    double dot(Vector2 v);
};

#endif // VECTOR2_H
