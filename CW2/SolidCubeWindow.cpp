#include "SolidCubeWindow.h"

// constructor / destructor
SolidCubeWindow::SolidCubeWindow(QWidget *parent)
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
	cubeWidget = new SolidCubeWidget(this);
	windowLayout->addWidget(cubeWidget);

	// create slider
	nSlider = new QSlider(Qt::Horizontal);
	connect(nSlider, SIGNAL(valueChanged(int)), cubeWidget, SLOT(updateAngle(int)));
	windowLayout->addWidget(nSlider);

	praiseButton = new QPushButton("PRAISE THE SUN");
	windowLayout->addWidget(praiseButton);
	} // constructor

	

SolidCubeWindow::~SolidCubeWindow()
	{ // destructor
	delete nSlider;
	delete cubeWidget;
	delete windowLayout;
	delete actionQuit;
	delete fileMenu;
	delete menuBar;
	} // destructor

// resets all the interface elements
void SolidCubeWindow::ResetInterface()
	{ // ResetInterface()
	nSlider->setMinimum(0);
	nSlider->setMaximum(360);
	nSlider->setValue(0);
	
	// now force refresh
	cubeWidget->update();
	update();
	} // ResetInterface()
