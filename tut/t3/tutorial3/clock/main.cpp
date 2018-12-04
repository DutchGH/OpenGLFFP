#include "mainwindow.hpp"
#include <QApplication>
 
int main(int argc, char *argv[]) 
{
  QApplication app(argc, argv);
  MyMainWindow mainWindow;
  mainWindow.setCentralWidget(&mainWindow.mine);
  mainWindow.showMaximized();
  return app.exec();
}
