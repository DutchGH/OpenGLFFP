#include <GL/glu.h>
#include <QGLWidget>
#include "SolidCubeWidget.h"

// constructor
SolidCubeWidget::SolidCubeWidget(QWidget *parent)
	: QGLWidget(parent)
	{ // constructor
       

	} // constructor

// called when OpenGL context is set up
void SolidCubeWidget::initializeGL()
	{ // initializeGL()
	// set the widget background colour
	glClearColor(0.3, 0.3, 0.3, 0.0);
	
	glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-4.0, 4.0, -4.0, 4.0, -4.0, 4.0);


        // You must set the matrix mode to model view directly before enabling the depth test                                                                                        
        glMatrixMode(GL_MODELVIEW);
               glEnable(GL_DEPTH_TEST); // comment out depth test to observe the result                                                                                              
	} // initializeGL()

// called every time the widget is resized
void SolidCubeWidget::resizeGL(int w, int h)
	{ // resizeGL()
	// set the viewport to the entire widget
	glViewport(0, 0, w, h);
        
	} // resizeGL()


void SolidCubeWidget::cube(){

  glColor3f(1.0,1.0,0.0);
    glBegin(GL_POLYGON);
    glVertex3f( 1.0,  -1.0, -1.0);
    glVertex3f( 1.0,  -1.0,  1.0);
    glVertex3f(-1.0,  -1.0,  1.0);
    glVertex3f(-1.0,  -1.0,  -1.0);
    glEnd();

  glColor3f(0.0,1.0,0.0);
  glBegin(GL_POLYGON);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f( 1.0, -1.0, 1.0);
    glVertex3f( 1.0,  1.0, 1.0);
    glVertex3f(-1.0,  1.0, 1.0);
  glEnd();

  glColor3f(1.0,0.0,0.0);
  glBegin(GL_POLYGON);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f( 1.0, -1.0, -1.0);
    glVertex3f( 1.0,  1.0, -1.0);
    glVertex3f(-1.0,  1.0, -1.0);
  glEnd();

   glColor3f(0.0,0.0,1.0);
  glBegin(GL_POLYGON);
    glVertex3f( -1.0, -1.0,  1.0);
    glVertex3f( -1.0, -1.0, -1.0);
    glVertex3f( -1.0,  1.0, -1.0);
    glVertex3f( -1.0,  1.0,  1.0);
    glEnd();

  glColor3f(0.0,0.0,1.0);
  glBegin(GL_POLYGON);
    glVertex3f( 1.0, -1.0,  1.0);
    glVertex3f( 1.0, -1.0, -1.0);
    glVertex3f( 1.0,  1.0, -1.0);
    glVertex3f( 1.0,  1.0,  1.0);
    glEnd();

    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
    glVertex3f( 1.0,  1.0, -1.0);
    glVertex3f( 1.0,  1.0,  1.0);
    glVertex3f(-1.0,  1.0,  1.0);
    glVertex3f(-1.0,  1.0,  -1.0);
    glEnd();

    

  

}
	
// called every time the widget needs painting
void SolidCubeWidget::paintGL()
	{ // paintGL()
	// clear the widget
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	this->cube();

	glLoadIdentity();
       	gluLookAt(1.0,1.0,1.0, 0.0,0.0,0.0, 0.0,1.0,0.0);
	
	// flush to screen
	glFlush();	

	} // paintGL()
