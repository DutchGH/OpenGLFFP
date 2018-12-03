#include <QtGui>
#include <QApplication>
#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QLabel>
#include <QDesktopWidget>
#include <iostream>



class MyWidget : public QWidget {
protected:

  virtual void paintEvent(QPaintEvent*);
};

void MyWidget::paintEvent( QPaintEvent * )
{
  // you might be tempted to make QPainter a class variable,
  // but the documentation warns explicitly against that

  QPainter p( this );


  // --------------Uncomment the next line--------------
  //  p.setWindow(QRect(-50, -50, 100, 100)); // this now creates a logical space  from (-50, -50) to (50, 50)
                                          // in these coordinates from bottom-left to top-right
                                          // if the aspect ratio changes, the figure becomes deformed
                                          // unless a viewport is defined

  // ---------------Uncomment the next two lines----------------- 
  // int side = qMin(width(), height());  
  // p.setViewport(0, 0, side, side);

  p.setPen( Qt::darkGray );
  p.drawRect( -25,-25, 50, 50 );

}

// I don't like the default way the main window pops up, I want it bigger
class MyMainWindow : public QMainWindow {

public: 
  
  MyMainWindow();

private:

};

MyMainWindow::MyMainWindow()
{
  // my window asks how big the desktop is; this is a widget for QT
  resize(QDesktopWidget().availableGeometry(this).size() * 0.7);
  // I've set my window to 70 % of the desktop  
}



int main(int argc, char **argv) {
  QApplication app(argc, argv);
  MyMainWindow window;

  // this is the canonical way of doing things: place widgets and draw on them
  // do not try to mess with MyMainWindow's 
  MyWidget w;
  window.setCentralWidget(&w);
  window.show();

  return app.exec();
}
