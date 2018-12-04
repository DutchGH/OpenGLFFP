 #include "mainwindow.hpp"
 
#include <QCoreApplication>
 
MyMainWindow::MyMainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  // Create the button, make "this" the parent
  // m_button = new QPushButton("My Button", this);
  // set size and location of the button
  resize(QDesktopWidget().availableGeometry(this).size() * 0.7);

  QTimer *timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), &mine, SLOT(updateTime()));
  timer->start(1000);

}
 
