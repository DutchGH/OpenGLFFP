 #ifndef MAINWINDOW_H
 #define MAINWINDOW_H
 
#include <QMainWindow>
#include <QPushButton>
#include "clockWidget.hpp"
 
namespace Ui {
  class MyMainWindow;
}
 
class MyMainWindow : public QMainWindow
{
    Q_OBJECT
    public:
  explicit MyMainWindow(QWidget *parent = 0);

public:
  clockWidget mine;
};
 
#endif // MAINWINDOW_H
