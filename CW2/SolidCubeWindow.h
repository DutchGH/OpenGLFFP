#ifndef __GL_POLYGON_WINDOW_H__
#define __GL_POLYGON_WINDOW_H__ 1

#include <QGLWidget>
#include <QMenuBar>
#include <QPushButton>
#include <QSlider>
#include <QBoxLayout>
#include "SolidCubeWidget.h"

class SolidCubeWindow: public QWidget
	{ 
	public:
       
	
	// constructor / destructor
	SolidCubeWindow(QWidget *parent);
	~SolidCubeWindow();

	// visual hierarchy
	// menu bar
	QMenuBar *menuBar;
		// file menu
		QMenu *fileMenu;
			// quit action
			QAction *actionQuit;

	// window layout
	QBoxLayout *windowLayout;

	// beneath that, the main widget
	SolidCubeWidget *cubeWidget;
	
	//Slider for Speed of The Eart
	QSlider *nSlider;

	//Slider for "Praising the Sun"
	QPushButton *praiseButton;


	// resets all the interface elements
	void ResetInterface();
	}; 
	
#endif
