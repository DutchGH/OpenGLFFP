#include <QtGui>
#include <QApplication>
#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QLabel>
#include <QDesktopWidget>
#include <cmath>
#include <iostream>
#include <fstream>
#include "pixelwidget.hpp"


void PixelWidget::DefinePixelValues(){ //add pixels here; write methods like this for the assignments
  SetPixel(10,30,RGBVal(255,0,0));
}


void PixelWidget::DrawLine(double p1x, double p1y, const RGBVal & p1Rgb, double p2x, double p2y, const RGBVal & p2Rgb, double step){ //add pixels here; write methods like this for the assignments
  SetPixel(p1x,p1y,p1Rgb);
  SetPixel(p2x,p2y,p2Rgb);
  //Calculate Direction Vector in terms of X and Y for Parametic
  double dirX = p2x-p1x;
  double dirY = p2y-p1y;
  qDebug() << dirX << "," << dirY;

  for (double i = step; i < 1; i += step)
  {
    qDebug() << i;

    double x = abs(p1x + (dirX * i));
    qDebug() << x;

    double y = abs(p1y +(dirY * i));
    qDebug() << y;

    SetPixel(x,y,RGBVal(255,0,0));
  }
}


// -----------------Most code below can remain untouched -------------------------
// ------but look at where DefinePixelValues is called in paintEvent--------------

PixelWidget::PixelWidget(unsigned int n_vertical, unsigned int n_horizontal):
  _n_vertical   (n_vertical),
  _n_horizontal (n_horizontal),
  _vec_rects(0)
{
  // all pixels are initialized to black
     for (unsigned int i_col = 0; i_col < n_vertical; i_col++)
       _vec_rects.push_back(std::vector<RGBVal>(n_horizontal));
}



void PixelWidget::SetPixel(unsigned int i_column, unsigned int i_row, const RGBVal& rgb)
{

  // if the pixel exists, set it
  if (i_column < _n_vertical && i_row < _n_horizontal)
    _vec_rects[i_column][i_row] = rgb;
}


void PixelWidget::paintEvent( QPaintEvent * )
{

  QPainter p( this );
  // no antialiasing, want thin lines between the cell
  p.setRenderHint( QPainter::Antialiasing, false );

  // set window/viewport so that the size fits the screen, within reason
  p.setWindow(QRect(-1.,-1.,_n_vertical+2,_n_horizontal+2));
  int side = qMin(width(), height());  
  p.setViewport(0, 0, side, side);

  // black thin boundary around the cells
  QPen pen( Qt::black );
  pen.setWidth(0.);

  // here the pixel values defined by the user are set in the pixel array
  DrawLine(10,30,RGBVal(255,0,0),50,10,RGBVal(255,0,0), 0.02);

  for (unsigned int i_column = 0 ; i_column < _n_vertical; i_column++)
    for(unsigned int i_row = 0; i_row < _n_horizontal; i_row++){
      QRect rect(i_column,i_row,1,1);
      QColor c = QColor(_vec_rects[i_column][i_row]._red, _vec_rects[i_column][i_row]._green, _vec_rects[i_column][i_row]._blue);
    
      // fill with color for the pixel
      p.fillRect(rect, QBrush(c));
      p.setPen(pen);
      p.drawRect(rect);
    }
}
