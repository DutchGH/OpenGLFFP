#ifndef __GL_POLYGON_WIDGET_H__
#define __GL_POLYGON_WIDGET_H__ 1

#include <QGLWidget>
#include <GL/glut.h>
#include "Image.h"

class SolidCubeWidget: public QGLWidget
	{ // 

	Q_OBJECT

	public:

	SolidCubeWidget(QWidget *parent);
	~SolidCubeWidget();

	public slots:
	void updateAngle(int);

	protected:
	// called when OpenGL context is set up
	void initializeGL();
	// called every time the widget is resized
	void resizeGL(int w, int h);
	// called every time the widget needs painting
	void paintGL();

	private:

	void sphere();

	Image _image;

	int angle;
	}; // class GLPolygonWidget
	
#endif
