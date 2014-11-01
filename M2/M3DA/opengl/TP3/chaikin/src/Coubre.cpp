#include <stdlib.h>
#include <iostream>
#include "Courbe.h"
#include <GL/gl.h>

Courbe::Courbe(){
    points.clear();
}

Courbe::~Courbe(){}


void Courbe::addPoint(Vector2 p){
    points.push_back(p);
}

void Courbe::clear(){
    points.clear();
}

void Courbe::dessiner(){
    if(points.size()>1){
        glColor3f(1,0,0);
        glLineWidth(3);
        glColor3f(0,1,0);
        glPushMatrix();
        Vector2 oldP = points.at(0);
        for(int i=1;i<points.size();i++){
            Vector2  p = points.at(i);
            glBegin(GL_LINES);
                glVertex2f(oldP.x,oldP.y);
                glVertex2f(p.x,p.y);
            glEnd();
            oldP = p;
        }
        glPopMatrix();
    }
}
