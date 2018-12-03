#include <fstream>
#include <QDir>
#include "myclass.hpp"

MyClass::MyClass():
_working_directory(initializeWorkingDirectory())
{
  std::ofstream wd(_working_directory);
  wd << "Something in the way it moves" << std::endl;
}

std::string MyClass::initializeWorkingDirectory() const
{
  QDir dir;
  QString cp = dir.currentPath();
  std::string utf8_text = cp.toUtf8().constData() + std::string("/something.txt") ;
  return utf8_text;
}

void MyClass::handleButton(){
  std::ofstream wd;
  wd.open(_working_directory,std::ofstream::app);
  wd << "ouch" << std:: endl;
}
