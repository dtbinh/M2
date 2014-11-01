#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include "Nurbs.h"
#include "Vector2.h"
#include <GL/gl.h>

int cpt =0;

/**
 * @brief Nurbs::Nurbs Constructeur par défaut
 */
Nurbs::Nurbs(){}

/**
 * @brief Nurbs::~Nurbs Destructeur
 */
Nurbs::~Nurbs(){}

/**
 * @brief Nurbs::initialize initialisation du vecteur nodal
 * @param _nbPoints nombre de points de contrôle
 * @param _degre degré de la courbe
 */
void Nurbs::initialize(int _nbPoints , int _degre){
    this->degre = _degre;
    this->nbPoints = _nbPoints;

    this->calculFait = false;
    this->calculNurbsFait = false;

    this->bSplinePoints.clear();
    this->nurbsPoints.clear();
    this->_knot.clear();
    this->_controle.clear();

    for(unsigned int i=0;i<=_nbPoints+_degre+1;i++){
        this->_knot.push_back(i+1);
    }

    currentPositionSpline = 0;
}

/**
 * @brief Nurbs::evalue Calcul de l'image de l'abscisse t correspondant à la courbe au point k
 * @param k Début de la courbe
 * @param p Degré de la croube
 * @param t Abscisse pour laquelle on veut calculer l'image
 * @return
 */
double Nurbs::evalue(int k, int p, double t){
    if(p==0){
        if(t >= _knot.at(k) && t<_knot.at(k+1))
            return 1;
        else
            return 0;
    }
    else{
        return ((t-_knot.at(k))/(_knot.at(k+p)-_knot.at(k)))*(evalue(k,p-1,t))+(((_knot.at(p+k+1)-t)/(_knot.at(p+k+1)-_knot.at(k+1)))*evalue(k+1,p-1,t));
    }
}

/**
 * @brief Nurbs::evalBSpline Calcul de l'image de l'abscisse t définie par la fonction bspline
 * @param t Abscisse pour laquelle on veut calculer l'image
 * @return
 */
Vector2 Nurbs::evalBSpline(double t){
    Vector2 res;
    double n;
    for(unsigned int i=0;i<_controle.size();i++){
        n = evalue(i,degre,t);
        res = res + (_controle.at(i)*n);
    }
    return res;
}

/**
 * @brief Nurbs::drawN Dessin de la courbe correspondant au point k
 * @param k Indice du point ou la courbe commence
 * @param p Degré de la courbe
 */
void Nurbs::drawN(int k, int p){
    double n,t;

    glBegin(GL_LINE_STRIP);
    glColor3f(0,1,0);

    for(unsigned int i=k;i<k+p+1;i++){
        for(double j=0.0;j<1.0;j=j+0.1){
            t = _knot.at(i)+j;
            n =  evalue(k,p,t);
            glVertex2f(t,n);
            nurbsPoints.push_back(Vector2(t,n));
        }
    }

    glEnd();

    glColor3f(1,0,0);

    glBegin(GL_POINTS);
    for (unsigned int i = 0; i < _knot.size(); ++i)
        glVertex2f(_knot.at(i) ,0);
    glEnd();

}

/**
 * @brief Nurbs::drawNurbs Dessine les courbes de tous les points du vecteur nodal
 * @param p Degré de la courbe
 */
void Nurbs::drawNurbs(int p){
    if(!calculNurbsFait){
        nurbsPoints.clear();
        for(unsigned int i=0;i<_knot.size()-p-1;i++){
            drawN(i,p);
        }
        //calculNurbsFait = true;
    }

    else{
        glColor3f(0,1,0);
        glBegin(GL_LINE_STRIP);
        for(unsigned int i=0;i<nurbsPoints.size();i++){
            glVertex2f(nurbsPoints.at(i).x,nurbsPoints.at(i).y);
        }
        glEnd();

        glColor3f(1,0,0);

        glBegin(GL_POINTS);
        for (unsigned int i = 0; i < _knot.size(); ++i)
            glVertex2f(_knot.at(i) ,0);
        glEnd();
    }
}

/**
 * @brief Nurbs::drawBSpline Dessin de la courbe bSpline associée aux points de contrôle
 */
void Nurbs::drawBSpline(){
    Vector2 v;

    // Dessin des segments reliant les points de contrôle
    glColor3f(1,0,0);
    glBegin(GL_LINE_STRIP);
    for(int i=0;i<_controle.size();i++){
        glVertex2f(_controle.at(i).x,_controle.at(i).y);
    }
    glEnd();

    // Dessin de la courbe bSpline
    glColor3f(0,0,1);
    glBegin(GL_LINE_STRIP);
    if(!calculFait){
        for(double t=_knot.at(degre);t<_knot.at(_controle.size());t=t+0.1){
            v = evalBSpline(t);
            this->bSplinePoints.push_back(v);
            glVertex2f(v.x,v.y);
        }
        calculFait = true;
    }

    else{
        for(unsigned int i=0;i<bSplinePoints.size();i++){
            glVertex2f(bSplinePoints.at(i).x,bSplinePoints.at(i).y);
        }
    }

    glEnd();

    // Dessin des points de contrôle
    glColor3f(0,0,0);
    glBegin(GL_POINTS);

    for(int i=0;i<_controle.size();i++){
        glVertex2f(_controle.at(i).x,_controle.at(i).y);
    }

    glEnd();
}

void Nurbs::drawBSplineAnimation(){
    Vector2 v;

    // Dessin des segments reliant les points de contrôle
    glColor3f(1,0,0);
    glBegin(GL_LINE_STRIP);
    for(int i=0;i<_controle.size();i++){
        glVertex2f(_controle.at(i).x,_controle.at(i).y);
    }
    glEnd();

    // Dessin de la courbe bSpline
    glColor3f(0,0,1);
    glBegin(GL_LINE_STRIP);
    if(!calculFait){
        for(double t=_knot.at(degre);t<_knot.at(_controle.size());t=t+0.1){
            v = evalBSpline(t);
            this->bSplinePoints.push_back(v);
            glVertex2f(v.x,v.y);
        }
        calculFait = true;
    }

    else{
        for(unsigned int i=0;i<bSplinePoints.size();i++){
            glVertex2f(bSplinePoints.at(i).x,bSplinePoints.at(i).y);
        }
    }

    glEnd();

    glColor3f(0,1,0);
    glBegin(GL_POINTS);

    glVertex2f(bSplinePoints.at(currentPositionSpline).x,bSplinePoints.at(currentPositionSpline).y);

    glEnd();

    if(currentPositionSpline>=bSplinePoints.size()-1)
        currentPositionSpline = 0;
    else
        currentPositionSpline++;
}

/**
 * @brief Nurbs::addControlPoint Ajout d'un point de contrôle
 * @param p Point de contrôle à ajouter
 */
void Nurbs::addControlPoint(Vector2 p){
    _controle.push_back(p);
}


