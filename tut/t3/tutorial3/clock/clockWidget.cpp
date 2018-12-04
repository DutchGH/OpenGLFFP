#include <fstream>

#include "clockWidget.hpp"


clockWidget::clockWidget(QWidget *parent): QWidget(parent)
{
//     QTimer *timer = new QTimer(this);
//     connect(timer, SIGNAL(timeout()), this, SLOT(update()));
//     timer->start(1000);
}

void clockWidget::updateTime()
{
  this->hour = QTime::currentTime().hour() % 12;
  this->minute = QTime::currentTime().minute();
  this->second = QTime::currentTime().second();

  this->repaint();
}

void clockWidget::paintEvent( QPaintEvent * )
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
  p.setPen(QPen(getHourColour(),0.3));
  transform.rotate(this->hour*(30));
  p.setTransform(transform);
  p.drawPolygon(hourHand,3);

  p.setPen(QPen(getMinuteColour(),0.3));
  transform.reset();
  transform.rotate(this->minute * 6);
  p.setTransform(transform);
  p.drawPolygon(minuteHand,3);

  p.setPen(QPen(Qt::red, 0.3));
  QLineF secLine(0,0,0,-20);
  transform.reset();
  transform.rotate(this->second * 6);
  p.setTransform(transform);
  p.drawLine(secLine);

  // http://doc.qt.io/archives/qt-4.8/qtransform.html
  // Look at this for transformation matrix for tomorrow... Bed now.
}