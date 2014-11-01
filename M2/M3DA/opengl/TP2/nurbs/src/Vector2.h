#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2{


public:
    double x,y;
    Vector2();
    Vector2(double _x, double _y);
    virtual ~Vector2();
    double dot(Vector2 v);
    Vector2 operator +(const Vector2  & v) const;
    Vector2 operator *(double k) const;
};

#endif // VECTOR2_H
