#ifndef __GL_POLYGON_WIDGET_H__
#define __GL_POLYGON_WIDGET_H__ 1
#include <GL/glu.h>
#include <QGLWidget>
#include <QObject>
#include "Image.h"
#include "planet.h"



class GLMain: public QGLWidget
	{ // 
	Q_OBJECT
	public:
	GLMain(QWidget *parent = 0);
	int getCubeAngle(){return cubeAngle;}

	public slots:
		void setCubeAngle(int angle);
		void setCubeAngle();
	

	protected:
	// called when OpenGL context is set up
	void initializeGL();
	// called every time the widget is resized
	void resizeGL(int w, int h);
	// called every time the widget needs painting
	void paintGL();

	private:

	void cube();
	void polygon(int, int, int, int);
	Image *earthTex = new Image("./textures/earth.ppm");
	Image *sunTex = new Image("./textures/Moi.ppm");
	Image *moonTex = new Image("./textures/moon.ppm");

	Planet * earth = nullptr;
  	Planet * moon = nullptr;
  	Planet * sun = nullptr;

	int cubeAngle = 0;

	}; // class GLPolygonWidget
	
#endif
