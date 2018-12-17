#include <GL/glu.h>
#include <QGLWidget>
#include <cmath>
#include "SolidCubeWidget.h"


// Setting up material properties
typedef struct materialStruct {
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat shininess;
} materialStruct;


static materialStruct brassMaterials = {
  { 0.33, 0.22, 0.03, 1.0},
  { 0.78, 0.57, 0.11, 1.0},
  { 0.99, 0.91, 0.81, 1.0},
  27.8 
};

static materialStruct whiteShinyMaterials = {
  { 1.0, 1.0, 1.0, 1.0},
  { 1.0, 1.0, 1.0, 1.0},
  { 1.0, 1.0, 1.0, 1.0},
  100.0 
};

// constructor
SolidCubeWidget::SolidCubeWidget(QWidget *parent)
  : QGLWidget(parent),
    angle(0),
    _image("./earth.ppm")
	{ // constructor       
	} // constructor

// called when OpenGL context is set up
void SolidCubeWidget::initializeGL()
	{ // initializeGL()
	// set the widget background colour
	glClearColor(0.3, 0.3, 0.3, 0.0);
	glEnable(GL_TEXTURE_2D);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _image.Width(), _image.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, _image.imageField());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

 	} // initializeGL()

const int NR_PHI   = 20;
const int NR_THETA = 20;

void SolidCubeWidget::sphere(){
  for(int longitude = 0; longitude < NR_PHI; longitude++)
    for(int latitude = 0; latitude < NR_THETA; latitude++){
      float d_phi   = 2*M_PI/NR_PHI;
      float d_theta = M_PI/NR_THETA; 
      glBegin(GL_TRIANGLES);
      double x, y, z;
     
      x = cos(longitude*d_phi)*sin(latitude*d_theta);
      y = sin(longitude*d_phi)*sin(latitude*d_theta);
      z = cos(latitude*d_theta);
      glNormal3f(x, y, z);
      glTexCoord2f(static_cast<float>(longitude)/NR_PHI, static_cast<float>(latitude)/NR_THETA);
      glVertex3f(x, y, z);
      x = cos((longitude+1)*d_phi)*sin(latitude*d_theta);
      y = sin((longitude+1)*d_phi)*sin(latitude*d_theta);
      z = cos(latitude*d_theta);
      glNormal3f(x, y, z);
      glTexCoord2f(d_phi,0);
      glTexCoord2f(static_cast<float>(longitude+1)/NR_PHI, static_cast<float>(latitude)/NR_THETA);
      glVertex3f(x, y, z);
      x = cos((longitude+1)*d_phi)*sin((latitude+1)*d_theta);
      y = sin((longitude+1)*d_phi)*sin((latitude+1)*d_theta);
      z = cos((latitude+1)*d_theta);
      glNormal3f(x, y, z);
      glTexCoord2f(static_cast<float>(longitude+1)/NR_PHI, static_cast<float>(latitude+1)/NR_THETA);
      glVertex3f(x, y, z);      
                                       
      x = cos(longitude*d_phi)*sin(latitude*d_theta);
      y = sin(longitude*d_phi)*sin(latitude*d_theta);
      z = cos(latitude*d_theta); 
      glNormal3f(x, y, z);
      glTexCoord2f(static_cast<float>(longitude)/NR_PHI, static_cast<float>(latitude)/NR_THETA);
      glVertex3f(x, y, z);
      x = cos((longitude+1)*d_phi)*sin((latitude+1)*d_theta);
      y = sin((longitude+1)*d_phi)*sin((latitude+1)*d_theta);
      z = cos((latitude+1)*d_theta);
      glNormal3f(x, y, z);
      glTexCoord2f(static_cast<float>(longitude+1)/NR_PHI, static_cast<float>(latitude+1)/NR_THETA);
      glVertex3f(x, y, z);
      x = cos((longitude)*d_phi)*sin((latitude+1)*d_theta);
      y = sin((longitude)*d_phi)*sin((latitude+1)*d_theta);
      z = cos((latitude+1)*d_theta);
      glNormal3f(x, y, z);
      glTexCoord2f(static_cast<float>(longitude)/NR_PHI, static_cast<float>(latitude+1)/NR_THETA);
      glVertex3f(x, y, z);      
     
     
      glEnd();
      
  } 
}

SolidCubeWidget::~SolidCubeWidget()
{
}

void SolidCubeWidget::updateAngle(int i){
  angle = i;
  this->repaint();
}

// called every time the widget is resized
void SolidCubeWidget::resizeGL(int w, int h)
	{ // resizeGL()
	// set the viewport to the entire widget
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0, 0, w, h);

	materialStruct* p_front = &whiteShinyMaterials;
	
       	glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
	glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);
        
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-4.0, 4.0, -4.0, 4.0, -4.0, 4.0);

	} // resizeGL()

	
// called every time the widget needs painting
void SolidCubeWidget::paintGL()
	{ // paintGL()
	// clear the widget
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//	glEnable(GL_LIGHTING); // enable lighting in general
        //      glEnable(GL_LIGHT0);   // each light source must also be enabled

      	glShadeModel(GL_SMOOTH);
	glPushMatrix();
	// You must set the matrix mode to model view directly before enabling the depth test
      	glMatrixMode(GL_MODELVIEW);
        glEnable(GL_DEPTH_TEST); // comment out depth test to observe the result
	//       	glEnable(GL_CULL_FACE);
        //glCullFace(GL_BACK);

	glLoadIdentity();
	GLfloat light_pos[] = {2., 2., 2., 1.};
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
        glPopMatrix();



	glRotatef((double)angle,0.,0.,1.);
	glScalef(2.,2.,2.);
  // disk()
	sphere();

	glLoadIdentity();
       	gluLookAt(0.,0.,2.0, 0.0,0.0,0.0, 0.0,1.0,0.0);
	
	// flush to screen
	glFlush();	

	} // paintGL()
