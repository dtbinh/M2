#ifndef COURBE_H
#define COURBE_H
#include <vector>
#include <Vector2.h>

class Courbe{

    std::vector<Vector2> points;
    public:
    Courbe();
    virtual ~Courbe();
    void clear();
    void addPoint(Vector2 p);
    void dessiner();

};
#endif // COURBE_H
