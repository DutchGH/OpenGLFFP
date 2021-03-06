#ifndef __GL_POLYGON_WINDOW_H__
#define __GL_POLYGON_WINDOW_H__ 1

#include <QGLWidget>
#include <QMenuBar>
#include <QSlider>
#include <QBoxLayout>
#include <QPushButton>
#include <QObject>
#include <QLabel>
#include <QTimer>
#include <QSpinBox>
#include "GLMain.h"

class WindowLayout: public QWidget
	{ 
		Q_OBJECT
	public:
       
	
	// constructor / destructor
	WindowLayout(QWidget *parent = 0);
	virtual ~WindowLayout();
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
	GLMain *glWidget;

	//Program Modifiers
	QSlider *zoomSlider;
	QPushButton * starButton;
	QSpinBox * sunBox;

	//Labels for Modifiers:
	QLabel *praiseLabel;
	QLabel *zoomLabel;
	
	// resets all the interface elements
	void ResetInterface();
	}; 
	
#endif
