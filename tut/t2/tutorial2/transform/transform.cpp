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
  int hour = 3;
  int minute = 55;
  virtual void paintEvent(QPaintEvent*);
};

static const QPoint hourHand[3] = 
{
  QPoint(3,0),
  QPoint(-3,0),
  QPoint(0,-10)
};

static const QPoint minuteHand[3] = 
{
  QPoint(3,0),
  QPoint(-3,0),
  QPoint(0,-20)
};

QColor hourColour(127,0,127);
QColor minColour(0,127,127,191);


void MyWidget::paintEvent( QPaintEvent * )
{
  // you might be tempted to make QPainter a class variable,
  // but the documentation warns explicitly against that

  QPainter p( this );


  // --------------Uncomment the next line--------------
   p.setWindow(QRect(-50, -50, 100, 100)); // this now creates a logical space  from (-50, -50) to (50, 50)
                                          // in these coordinates from bottom-left to top-right
                                          // if the aspect ratio changes, the figure becomes deformed
                                          // unless a viewport is defined

  // ---------------Uncomment the next two lines----------------- 
  int side = qMin(width(), height());  
  p.setViewport(0, 0, side, side);

  p.setPen( Qt::darkGray );
  p.drawRect( -25,-25, 50, 50 );

  p.setPen(QPen(Qt::white, 0.2));
  QLineF minLine(0,0,0,-20);
  for(int i = 1; i<=60; i++)
  {
    p.rotate(6);
    p.drawLine(minLine);
  }

  p.setPen(QPen(Qt::cyan, 0.5));
  QLineF hourLine(0,0,0,-20);
  p.drawLine(hourLine);
  for(int i = 1; i<=12; i++)
  {
    p.rotate(30);
    p.drawLine(hourLine);
  }

  // p.scale(0.5,0.5);
  QTransform transform;
  p.setPen(QPen(hourColour,0.3));
  transform.rotate(hour*(30));
  p.setTransform(transform);
  p.drawPolygon(hourHand,3);

  p.setPen(QPen(minColour,0.3));
  transform.reset();
  transform.rotate(minute * 6);
  p.setTransform(transform);
  p.drawPolygon(minuteHand,3);
  // http://doc.qt.io/archives/qt-4.8/qtransform.html
  // Look at this for transformation matrix for tomorrow... Bed now.

  


  

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
