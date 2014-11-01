/**

  @author F. Aubert
  **/


#include "GLView.h"
#include <iostream>
#include <QPushButton>
#include "Nurbs.h"

using namespace std;
using namespace prog3d;


/// ctor
GLView::GLView(QWidget *parent) : QGLWidget(parent) {

    setFocusPolicy(Qt::StrongFocus); // this widget can now catch the keyboard events

    _choice=1;
}


/// dtor
GLView::~GLView() {
}

/**
 initialize GL context (with glew ou without glew) + common set up
 **/
void GLView::initializeGL() {

#ifdef WITH_GLEW
    // initialization of all available OpenGL functionalities
    if (glewInit()!=GLEW_OK) {
        throw ErrorD("cant initialize glew");
    }
#endif

    cout << "GL version :" << glGetString(GL_VERSION) << endl;
    cout << "Shading Language  : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;

    // common OpenGL set up
    glEnable(GL_DEPTH_TEST);  // hidden parts removal with depth buffer algorithm
    glClearColor(1,1,1,1); // color value when glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) is done
    glClearDepth(1.0);       // depth value when glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) is done

    glDisable(GL_STENCIL_TEST);
    glClearStencil(0);

    // polygon drawings set up
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    glPixelStorei(GL_PACK_ALIGNMENT,4);
    glPixelStorei(GL_UNPACK_ALIGNMENT,4);

    ugl::initUtilGL(this);

    initData();

}


/** ***************************************************************************
resize
  **/


/// when the graphics window is sized/resized (including the first time the window is shown)
void GLView::resizeGL(int width, int height) {
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1,1,-1,1,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



/** **********************************************************************
  Events
  **/
void GLView::mousePressEvent(QMouseEvent *event) {
    if (event->button()==Qt::LeftButton) {
        cout << "left mouse : " << event->x() << "," << event->y() << endl;
    }
    if (event->button()==Qt::RightButton) {
        cout << "right mouse : " << event->x() << "," << event->y() << endl;
    }
}

void GLView::mouseMoveEvent(QMouseEvent *event) {
    cout << "motion : " << event->x() << "," << event->y() << endl;
}

void GLView::mouseReleaseEvent(QMouseEvent *event) {
    switch(event->button()){
    case Qt::LeftButton:
        cout << "left mouse released" << endl;
        break;
    case Qt::RightButton:
        break;
    default:break;
    }
}

void GLView::wheelEvent(QWheelEvent *event) {
    cout << "mouse wheel :" << event->delta() << endl;
}


void GLView::keyPressEvent(QKeyEvent *event) {
    if (event->isAutoRepeat())
        QGLWidget::keyPressEvent(event);
    else
        switch(event->key()){
        case Qt::Key_Z:
            cout << "Z pressed" << endl;
            break;
        case Qt::Key_S:
            cout << "S pressed" << endl;
            break;
        case Qt::Key_Space:
            cout << "space pressed" << endl;
            break;
        default:
            QGLWidget::keyPressEvent(event); // dispatch the event to the parent
        }
}
//std::cout<<"_knot.at(degre) = "<<_knot.at(degre) << " _knot.at(_controle.size) = " <<_knot.at(_controle.size()) <<  std::endl;
void GLView::keyReleaseEvent(QKeyEvent *event) {
    if (event->isAutoRepeat())
        QGLWidget::keyReleaseEvent(event);
    else
        switch(event->key()){
        case Qt::Key_Space:
            cout << "space released" << endl;
        case Qt::Key_Z:
            break;
        case Qt::Key_S:
            break;
        default:
            QGLWidget::keyReleaseEvent(event); // dispatch the event to the parent
        }
}



/** ***************************************************************************
  init/update data
  **/
void GLView::initData() {
    n.initialize(7,2);
    n.addControlPoint(Vector2(1,0));
    n.addControlPoint(Vector2(1.1,2));
    n.addControlPoint(Vector2(3,2.2));
    n.addControlPoint(Vector2(5,1.6));
    n.addControlPoint(Vector2(4,1));
}

void GLView::updateData() {
    // update data :


    // update view :
    updateGL();
}


/** ******************************************************************* **/
/**
  Drawings
**/


void GLView::drawChoice0() {
    /// drawing example

    //glColor3f(0,0.5,1);
    //ugl::drawText("drawChoice0: "+_choiceText,0,0);
    /*glLineWidth(2);
    glPointSize(4);

    glPushMatrix();
    glOrtho(-5,18,-2,2,-1,1);
    n.drawNurbs(2);
    glPopMatrix();*/


}

void GLView::drawChoice1() {
    glColor3f(0,0.2,1);
    ugl::drawText("drawChoice1 :"+_choiceText,0,0);

    glLineWidth(1);
    glPointSize(4);

    glPushMatrix();
    glOrtho(0,22,-2,2,-1,1);
    n.drawNurbs(2);
    glPopMatrix();

    glPushMatrix();
    glOrtho(-15,10,-5,5,-1,1);
    n.drawBSpline();
    glPopMatrix();
}


void GLView::drawChoice2() {
    glColor3f(0,0.2,1);
    ugl::drawText("drawChoice2 :"+_choiceText,0,0);


    glPushMatrix();
    glPointSize(8);
    glOrtho(-15,10,-5,5,-1,1);
    n.drawBSplineAnimation();
    glPopMatrix();
}
void GLView::paintGL() {
    /// clears the window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    /// choice example
    switch(_choice) {
    case 0:
        /// call the drawing method for the clicked button 0 ...
        drawChoice0();
        break;
    case 1:
        /// call the drawing method for the clicked button 1 ...
        drawChoice1();
        break;
    case 2 :
        drawChoice2();
        break;
    }

}

/** ********************************************************************** **/

void GLView::choice(int i,const string &s) {
    // i = button number, s = button text
    cout << "choice " << i << " " << s << endl;
    _choice=i;
    _choiceText=s;
}
