#ifndef __GL_POLYGON_WIDGET_H__
#define __GL_POLYGON_WIDGET_H__ 1
#include <GL/glu.h>
#include <QGLWidget>
#include <QObject>
#include "Image.h"
#include "planet.h"
#include "solaire.h"



class GLMain: public QGLWidget
	{ 
	Q_OBJECT
	public:
		GLMain(QWidget *parent = 0);
		int getCubeAngle(){return cubeAngle;}
		GLfloat * getCurrentColour();

	public slots:
		void setCubeAngle(int angle);
		void setCubeAngle();
		void setSolairePose(int i);
		void changeStarColours();
		void increaseZoom(int i);

	

	protected:
		// called when OpenGL context is set up
		void initializeGL();
		// called every time the widget is resized
		void resizeGL(int w, int h);
		// called every time the widget needs painting
		void paintGL();

	private:

		void drawSingleStar();
		void drawStarCluster(GLint NUMBER_OF_STARS);
		void polygon(int, int, int, int);

		//Texture models for our planets
		Image *earthTex = new Image("./textures/earth.ppm");
		Image *sunTex = new Image("./textures/Moi.ppm");
		Image *moonTex = new Image("./textures/moon.ppm");

		//Our objects we want to display
		Planet * earth = nullptr;
		Planet * moon = nullptr;
		Planet * sun = nullptr;
		Solaire * solaire = nullptr;


		int currentColourEmission = 0;
		float currentZoom = 1;

		int cubeAngle = 0;

		GLfloat emission[8][4] = {
			{0,0,0,1},
			{1,0,0,1},
			{0,1,0,1},
			{0,1,1,1},
			{1,0,1,1},
			{1,1,0,1},
			{1,1,0,1},
			{0,0,0,1},
		};

	}; 
	
#endif
