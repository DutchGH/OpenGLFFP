 #ifndef MAINWINDOW_H
 #define MAINWINDOW_H
 
#include <QMainWindow>
#include <QPushButton>
#include "myclass.hpp"
 
namespace Ui {
  class MainWindow;
}
 
class MainWindow : public QMainWindow
{
    Q_OBJECT
    public:
  explicit MainWindow(QWidget *parent = 0);
private slots:
  void handleButton();
private:
  QPushButton *m_button;
  MyClass mine;
};
 
#endif // MAINWINDOW_H
