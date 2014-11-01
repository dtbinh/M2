#ifndef NURBS_H
#define NURBS_H

#include <vector>
#include "Vector2.h"

/**
 * @brief The Nurbs class Classe permettant de dessiner des courbes Nurbs et bSplines
 */
class Nurbs{
    /**
     * @brief degre Degré de la courbe
     */
    int degre;

    /**
     * @brief nbPoints Nombre de points de contrôle
     */
    int nbPoints;

    /**
     * @brief _knot Vecteur nodal
     */
    std::vector<double> _knot;

    /**
     * @brief _controle Vecteur contenant les points de contrôle
     */
    std::vector<Vector2> _controle;

    unsigned int currentPositionSpline;
    Vector2 currentPoint;
    bool calculFait;
    bool calculNurbsFait;
    std::vector<Vector2> bSplinePoints;
    std::vector<Vector2> nurbsPoints;

public:

    Nurbs();
    virtual ~Nurbs();
    void initialize(int _nbPoints , int _degre);
    double evalue(int k, int p, double t);
    Vector2 evalBSpline(double t);
    void drawN(int k, int p);
    void drawNurbs(int p);
    void drawBSpline();
    void drawBSplineAnimation();
    void addControlPoint(Vector2 p);
};

#endif // NURBS_H
