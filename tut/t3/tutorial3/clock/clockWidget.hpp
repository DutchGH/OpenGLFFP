#ifndef _MYCLASS
#define _MYCLASS
#include <QtGui>
#include <QApplication>
#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QLabel>
#include <QDesktopWidget>
#include <QObject>
#include <QTime>


class clockWidget: public QWidget  {

    Q_OBJECT

protected:
  virtual void paintEvent(QPaintEvent*) override;


public:
  clockWidget(QWidget *parent = 0);
  QColor getHourColour() {return QColor(127,0,127);}
  QColor getMinuteColour() {return QColor(0,127,127,191);}


public slots:
  void updateTime();

private:
  int hour = 0;
  int minute = 0;
  int second = 0;

  const QPoint hourHand[3]
  {
    QPoint(3,0),
    QPoint(-3,0),
    QPoint(0,-10)
  };

  const QPoint minuteHand[3] = 
  {
    QPoint(3,0),
    QPoint(-3,0),
    QPoint(0,-20)
  };

};

#endif // _MYCLASS
