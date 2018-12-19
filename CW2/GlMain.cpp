#include <GL/glu.h>
#include <QGLWidget>
#include <QTimer>
#include <math.h>
#include <QDebug>
#include "GLMain.h"
#include "planet.h"
typedef struct materialStruct {
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat shininess;
} materialStruct;


materialStruct brassMaterials = {
  { 0.33, 0.22, 0.03, 1.0},
  { 0.78, 0.57, 0.11, 1.0},
  { 0.99, 0.91, 0.81, 1.0},
  27.8 
};

materialStruct whiteShinyMaterials = {
  { 1.0, 1.0, 1.0, 1.0},
  { 1.0, 1.0, 1.0, 1.0},
  { 1.0, 1.0, 1.0, 1.0},
  100.0 
};

materialStruct superBright = {
  { 1.5, 1.5, 1.5, 1.5},
  { 1.5, 1.5, 1.5, 1.5},
  { 1.5, 1.5, 1.5, 1.5},
  100.0 
};

materialStruct StarLight = {
  { 5.0, 5.0, 5.0, 5.0},
  { 5.0, 5.0, 5.0, 5.0},
  { 5.0, 5.0, 5.0, 5.0},
  100.0 
};

// constructor
GLMain::GLMain(QWidget *parent)
	: QGLWidget(parent)
	{ // constructor

       

	} // constructor

// called when OpenGL context is set up
void GLMain::initializeGL()
	{ // initializeGL()
	// set the widget background colour
	glClearColor(0.0, 0.0, 0.0, 0.0);

	} // initializeGL()

  
// called every time the widget is resized
void GLMain::resizeGL(int w, int h)
	{ // resizeGL()
	// set the viewport to the entire widget
	glViewport(0, 0, w, h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
  glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat light_pos[] = {0., 0., 0., 1.};	
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
        // glLightf (GL_LIGHT0, GL_SPOT_CUTOFF,15.);
                                                                                                                                        
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
  earth = new Planet(2.0f, 30,30, earthTex);
  moon = new Planet(0.5f, 30,30, moonTex);
  sun = new Planet(5.0f, 30,30, sunTex);
	glOrtho(-20.0, 20.0, -20.0, 20.0, -50.0, 50.0);

	} // resizeGL()


void GLMain::setCubeAngle(int angle) 
{
  cubeAngle = angle* 3.6;
  // qDebug() << cubeAngle;
  this->updateGL();
}

void GLMain::setCubeAngle() 
{
  cubeAngle = (cubeAngle + 1) % 360;
  // qDebug() << cubeAngle;
  this->updateGL();
}

void GLMain::cube(){

  // // Here are the normals, correctly calculated for the cube faces below  
  // GLfloat normals[][3] = { {1., 0. ,0.}, 
  //                          {-1., 0., 0.}, 
  //                          {0., 0., 1.}, 
  //                          {0., 0., -1.} };

  // Here we give every face the same normal
  // GLfloat normals[][3] = { {0.333, 0.333, 0.333 }, {0.333, 0.333, 0.333}, {0.333, 0.333, 0.333}, {0.3333, 0.3333, 0.333}};

  // Here we have permuted the first normal array
  // GLfloat normals[][3] = {  {-1., 0., 0.}, {0., 0., 1.}, {1., 0. ,0.}, {0., 0., -1.} };

	// Draw ten triangles
  const float GOLDEN_RATIO = 1.61803398875;
  const float STAR_MULTI_FACTOR = 1 + GOLDEN_RATIO;
	const float outerRadius = 1;
	const float innerRadius = 1/STAR_MULTI_FACTOR;
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0, 0, 0.0);
		for (int i = 0; i < 10; ++i) {
			float fAngleStart	= M_PI/2.0 + (i*2.0*M_PI)/10.0;
			float fAngleEnd		= fAngleStart + M_PI/5.0;
			if (i % 2 == 0) {
				glVertex3f(outerRadius*cos(fAngleStart)/1.9, outerRadius*sin(fAngleStart), 0.0);
				glVertex3f(innerRadius*cos(fAngleEnd)/1.9, innerRadius*sin(fAngleEnd), 0.0);
			} else {
				glVertex3f(innerRadius*cos(fAngleStart)/1.9,innerRadius*sin(fAngleStart), 0.0);
				glVertex3f(outerRadius*cos(fAngleEnd)/1.9, outerRadius*sin(fAngleEnd), 0.0);
			}
		}
	glEnd();
  
}


// called every time the widget needs painting
void GLMain::paintGL()
	{ // paintGL()
	// clear the widget
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// You must set the matrix mode to model view directly before enabling the depth test

	glEnable(GL_DEPTH_TEST); // comment out depth test to observe the result
  GLfloat emission[4] = {0.f, 0.0f, 1.0f, 1.0f};
 	glDisable(GL_LIGHTING);
    glPushMatrix();
      glRotatef(0,0.0,-1.0,0.0);

      // glRotatef(this->cubeAngle ,0.0,0.0,1.0);
      gluQuadricOrientation(sun->mPlanetQuad, GLU_INSIDE);
      materialStruct* p_front = &brassMaterials;
      glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
      glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
      glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
      glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);
      // glMaterialfv(GL_FRONT, GL_EMISSION, emission );
      glPushMatrix();
      glRotatef(40,-1,0,0);
      sun->DrawPlanet();
      glPopMatrix();
      // this->cube();
  glPopMatrix();
 	glEnable(GL_LIGHTING);




	glPushMatrix();
	glLoadIdentity();
        GLfloat light_pos[] = {0., 0., 0., 1.};
        // glRotatef(this->getCubeAngle(),0.0, 1.0, 0.0);
        glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
        // glLightf (GL_LIGHT0, GL_SPOT_CUTOFF,15.);
	glPopMatrix();

  glPushMatrix();
          glTranslatef(0,10,0);
          cube();
      glPopMatrix();



  // this->cube();
  // this->cube();
  p_front = &superBright;
  glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
  glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);
  glPushMatrix();
      glRotatef((this->getCubeAngle()) ,0.0,-1.0,0.0);
    glPushMatrix();
        glTranslatef(-10.0,0.0,0.0);
        glRotatef((this->getCubeAngle()) ,0.0,-1.0,0.0);

        // glRotatef(this->cubeAngle ,0.0,0.0,1.0);
        // materialStruct* p_front = &whiteShinyMaterials;
        // glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
        // glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
        // glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
        // glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);
        earth->DrawPlanet();
        glPushMatrix();
          // GLfloat emission2[4] = {1.f, 0.0f, 0.0f, 1.0f};
          // glMaterialfv(GL_FRONT, GL_EMISSION, emission2 ); 
          glTranslatef(-3.0,0.0,0.0);
          glRotatef((this->getCubeAngle()) ,0.0,1.0,0.0);
          moon->DrawPlanet();
        glPopMatrix();
        // this->cube();
    glPopMatrix();
  glPopMatrix();
  // glPushMatrix();
    // glTranslatef(3.0,0.0,0.0);
    //  glRotatef(30.0,0.0,4.0,0.0);
    // glTranslatef(-3.0,0.0,0.0);
  // glPopMatrix();


  


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

       	gluLookAt(0.,1.,1., 0.0,0.0,-1, 0.0,1.0,0.0);
  // glRotatef(45, 0.0, 1.0, 0.0);
       
	
	// flush to screen
	glFlush();	

	} // paintGL()
