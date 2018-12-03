
#include <QtGui>
#include <QApplication>
#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QEvent>
#include <QDesktopWidget>
#include <iostream>

class MyWidget : public QWidget {
public:

  // mouse tracking must be enabled
  void EnableMouse();
  void EnableKeyboard();

protected:

  virtual void paintEvent(QPaintEvent*);
  // virtual void mouseMoveEvent(QMouseEvent*);
  virtual bool event(QEvent*);

private:
  bool messageDisplayed = false;

};

void MyWidget::EnableKeyboard()
{
  this->setFocusPolicy(Qt::StrongFocus);
}

void MyWidget::EnableMouse()
{
  // you must set mouse tracking, it's off by default
  this->setMouseTracking(true);
}

bool MyWidget::event(QEvent * event)
{
  if(event->type() == QEvent::KeyPress)
  {
    QMessageBox::information(this,"snowflake","OW GOD DAMMIT");
  }
  if (event->type() == QEvent::Enter && !messageDisplayed) 
  {
    QMessageBox::information(this,"snowflake","Please Don't Do That");
    messageDisplayed = true;
  }
  else if(event->type() == QEvent::Leave)
  {
    messageDisplayed = false;
  }

  return QWidget::event(event);



}
// void MyWidget::mouseMoveEvent(QMouseEvent *_event)
// {
//   if (this->rect().contains(_event->pos())) {
//     // Mouse over Widget
//   }
//   else {
//     // Mouse out of Widget
//   }
// }

void MyWidget::paintEvent( QPaintEvent * )
{
  QPainter p( this );
  p.setPen( Qt::darkGray );
  p.drawRect( 1,2, 5,4 );
  p.setPen( Qt::lightGray );
  p.drawLine( 9,2, 7,7 );
}


// I don't like the default way the main window pops up, I want it bigger
class MyMainWindow : public QMainWindow {

public: 
  
  MyMainWindow();

};

MyMainWindow::MyMainWindow(){
  // my window asks how big the desktop is; this is a widget for QT
  resize(QDesktopWidget().availableGeometry(this).size() * 0.7);
  // I've set my window to 70 % of the desktop
}

int main(int argc, char **argv) {
  QApplication app(argc, argv);
  MyMainWindow window;

  MyWidget w;
  w.EnableMouse(); // don't forget this
  w.EnableKeyboard();
  window.setCentralWidget(&w);
  window.show();

  return app.exec();
}
