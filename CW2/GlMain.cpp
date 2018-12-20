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
  { 4.0, 4.0, 4.0, 4.0},
  { 4.0, 4.0, 4.0, 4.0},
  { 4.0, 4.0, 4.0, 4.0},
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
  solaire = new Solaire();
	glOrtho(-20.0, 20.0, -20.0, 20.0, -50.0, 50.0);

	} // resizeGL()


//-----------------HELPER FUNCTIONS/SLOTS------------------//
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

void GLMain::increaseZoom(int i){
  currentZoom = 1 + (static_cast<double>(i)/50);
  this->repaint();
}


void GLMain::setSolairePose(int i)
{
  if (this->solaire)
  {
    float newAngle = 180 * (i*0.01);
    this->solaire->updateArmAngle(newAngle);
    this->repaint();
  }
}

//we have 8 colours, so make sure we don't go out of bounds..
void GLMain::changeStarColours()
{
  currentColourEmission = (currentColourEmission + 1) % 8;
}

//return point to emission array
GLfloat * GLMain::getCurrentColour()
{
  return emission[currentColourEmission];
}

//Create multiple tringles via a single point (origin)
//vertices will occur at incremental points in the inner and outer circle
void GLMain::drawSingleStar(){
  const float GOLDEN_RATIO = 1.61803398875;
  const float STAR_MULTI_FACTOR = 1 + GOLDEN_RATIO;
	const float outerRadius = 1;
	const float innerRadius = 1/STAR_MULTI_FACTOR;

    materialStruct* p_front = &StarLight;
    glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
    glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);
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




//Use a "Random" function to plot some stars in the background.
void GLMain::drawStarCluster(GLint NUMBER_OF_STARS)
{
  srand (static_cast <unsigned> (time(0)));
  //We have a viewport of 20,-20. in both X and y I would like to clip some stars without being overly wasteful
  float MIN = -30.0;
  float MAX = 30.0;
  float DIFFERENCE = (MAX - MIN) + 1;
  for (int i = 0; i < NUMBER_OF_STARS; ++i)
  {
    float transX = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/DIFFERENCE)) + (MIN);
    float transY = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/DIFFERENCE)) + (MIN);
    glPushMatrix();
      glTranslatef(transX, transY, 0);
      drawSingleStar();
    glPopMatrix();
  }
}


// called every time the widget needs painting
void GLMain::paintGL()
{ // paintGL()
	// clear the widget
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// You must set the matrix mode to model view directly before enabling the depth test

	glEnable(GL_DEPTH_TEST); // comment out depth test to observe the result
 	glDisable(GL_LIGHTING); //Disabling lighting when rendering the sun as the light is at the origin, The object will be textured to create depth anyway
  
  //Increase the overall zoom level, so you can witness more "lovely" details
  glScaled(currentZoom, currentZoom, currentZoom);
  
  glPushMatrix();
    glRotatef(0,0.0,-1.0,0.0);
    gluQuadricOrientation(sun->mPlanetQuad, GLU_INSIDE);
    materialStruct * p_front = &StarLight;
    glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
    glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, this->getCurrentColour() );
    glPushMatrix();
      glRotatef(40,-1,0,0);
      //I'm sorry Marc... I truly am.
      sun->DrawPlanet();
    glPopMatrix();
  glPopMatrix();

  //Let's render the earth nicely
  glEnable(GL_LIGHTING);
	glPushMatrix();
	  glLoadIdentity();
    GLfloat light_pos[] = {0., 0., 0., 1.};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glPopMatrix();

  glPushMatrix();
    glTranslatef(0,0,-20);
      glPushMatrix();
        drawStarCluster(200);
      glPopMatrix();
  glPopMatrix();

  //Reset emission as the other materials don't use it
  GLfloat defaultEmission[] = {0,0,0,1};
  glMaterialfv(GL_FRONT, GL_EMISSION, defaultEmission );

  glPushMatrix();
    glRotatef((this->getCubeAngle()) ,0.0,-1.0,0.0);
    glPushMatrix();
      glTranslatef(-10.0,0.0,0.0);
      glRotatef((this->getCubeAngle()) ,0.0,-1.0,0.0);
      p_front = &superBright;
      glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
      glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
      glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
      glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);
      earth->DrawPlanet();

      glPushMatrix();
        glTranslatef(0,4,0);
        glScalef(0.5,0.5,0.5);
        solaire->displaySolaire();
      glPopMatrix();

      glPushMatrix();
        // GLfloat emission2[4] = {1.f, 0.0f, 0.0f, 1.0f};
        glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
        glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);
        glTranslatef(-3.0,0.0,0.0);
        glRotatef((this->getCubeAngle()) ,0.0,1.0,0.0);
        //lets add a moon for completeness
        moon->DrawPlanet();
      glPopMatrix();
    glPopMatrix();
  glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
  gluLookAt(0.,1.,1., 0.0,0.0,-1, 0.0,1.0,0.0);
       
	// flush to screen
	glFlush();	

	} // paintGL()
