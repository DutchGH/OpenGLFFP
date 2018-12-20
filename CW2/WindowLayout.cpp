#include "WindowLayout.h"

// constructor / destructor
WindowLayout::WindowLayout(QWidget *parent)
	: QWidget(parent)
	{ // constructor

	// create menu bar
	menuBar = new QMenuBar(this);
	
	// create file menu
	fileMenu = menuBar->addMenu("&File");

	// create the action
	actionQuit = new QAction("&Quit", this);

	// leave signals & slots to the controller
	
	// add the item to the menu
	fileMenu->addAction(actionQuit);
	
	// create the window layout
	windowLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);

	// create main widget
	glWidget = new GLMain(this);
	windowLayout->addWidget(glWidget);

	// create slider
	nVerticesSlider = new QSlider(Qt::Horizontal);
	windowLayout->addWidget(nVerticesSlider);
	sunBox = new QSpinBox();
	starButton = new QPushButton("Change Star Colours");

	connect(sunBox, SIGNAL(valueChanged(int)), glWidget, SLOT(setSolairePose(int)));
	connect(starButton, SIGNAL (released()), glWidget, SLOT(changeStarColours()));
	windowLayout->addWidget(sunBox);
	windowLayout->addWidget(starButton);

	

	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), glWidget, SLOT(setCubeAngle()));
	timer->start(1);



		// connect(nVerticesSlider, SIGNAL(valueChanged(int)), cubeWidget, SLOT(setCubeAngle(int)));

	} // constructor

WindowLayout::~WindowLayout()
	{ // destructor
	// delete praiseButton;
	delete starButton;
	delete nVerticesSlider;
	delete glWidget;
	delete windowLayout;
	delete actionQuit;
	delete fileMenu;
	delete menuBar;
	} // destructor

// resets all the interface elements
void WindowLayout::ResetInterface()
	{ // ResetInterface()
	nVerticesSlider->setMinimum(0);
	nVerticesSlider->setMaximum(360);

	//don't use the slider for now

	//	nVerticesSlider->setValue(thePolygon->nVertices);
	
	// now force refresh
	glWidget->update();
	update();
	} // ResetInterface()
