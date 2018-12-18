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
	cubeWidget = new GLMain(this);
	windowLayout->addWidget(cubeWidget);

	// create slider
	nVerticesSlider = new QSlider(Qt::Horizontal);
	windowLayout->addWidget(nVerticesSlider);

	praiseButton = new QPushButton("PRAISE THE SUN!");
	starButton = new QPushButton("Change Star Colours");

	windowLayout->addWidget(praiseButton);
	windowLayout->addWidget(starButton);



	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), cubeWidget, SLOT(setCubeAngle()));
	timer->start(1);



		// connect(nVerticesSlider, SIGNAL(valueChanged(int)), cubeWidget, SLOT(setCubeAngle(int)));

	} // constructor

WindowLayout::~WindowLayout()
	{ // destructor
	delete praiseButton;
	delete starButton;
	delete nVerticesSlider;
	delete cubeWidget;
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
	cubeWidget->update();
	update();
	} // ResetInterface()
