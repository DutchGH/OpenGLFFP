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

	//Zoom into the Sun
	zoomSlider = new QSlider(Qt::Horizontal);
	connect(zoomSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(increaseZoom(int)));
	zoomSlider->setMinimum(0);
	zoomSlider->setMaximum(45);
	zoomSlider->setValue(0);
	zoomLabel = new QLabel();
	zoomLabel->setText("Zoom Level:");
	zoomLabel->setAlignment(Qt::AlignBottom | Qt::AlignLeft);
	zoomLabel->setWordWrap(true);
	zoomLabel->setMaximumHeight(20);
	windowLayout->addWidget(zoomLabel);
	windowLayout->addWidget(zoomSlider);

	//Spin box for raising the arms of solaire (Points if you get the reference)
	sunBox = new QSpinBox();
	connect(sunBox, SIGNAL(valueChanged(int)), glWidget, SLOT(setSolairePose(int)));
	sunBox->setSuffix("%");
	sunBox->setMinimum(0);
	sunBox->setMaximum(100);
	sunBox->setValue(0);
	praiseLabel = new QLabel();
	praiseLabel->setText("How much do you wish to praise the sun?:");
	praiseLabel->setAlignment(Qt::AlignBottom | Qt::AlignLeft);
	praiseLabel->setWordWrap(true);
	praiseLabel->setMaximumHeight(20);
	windowLayout->addWidget(praiseLabel);
	windowLayout->addWidget(sunBox);

	//Change the star colours from a set array
	starButton = new QPushButton("Change Star Colours!");
	connect(starButton, SIGNAL (released()), glWidget, SLOT(changeStarColours()));
	windowLayout->addWidget(starButton);

	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), glWidget, SLOT(setCubeAngle()));
	timer->start(1);

	} // constructor

WindowLayout::~WindowLayout()
	{ // destructor
	// delete praiseButton;
	delete starButton;
	delete sunBox;
	delete zoomSlider;
	delete glWidget;
	delete windowLayout;
	delete actionQuit;
	delete fileMenu;
	delete menuBar;
	} // destructor

// resets all the interface elements
void WindowLayout::ResetInterface()
	{ // ResetInterface()
	zoomSlider->setMinimum(0);
	zoomSlider->setMaximum(45);
	zoomSlider->setValue(0);

	sunBox->setMinimum(0);
	sunBox->setMaximum(100);
	sunBox->setValue(0);

	//don't use the slider for now

	//	nVerticesSlider->setValue(thePolygon->nVertices);
	
	// now force refresh
	glWidget->update();
	update();
	} // ResetInterface()
