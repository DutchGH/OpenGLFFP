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
  SetPixel(static_cast<unsigned int>(p1x), static_cast<unsigned int>(p1y),p1Rgb);
  SetPixel(static_cast<unsigned int>(p2x), static_cast<unsigned int>(p2y),p2Rgb);
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

    SetPixel(static_cast<unsigned int>(x), static_cast<unsigned int>(y),RGBVal(255,0,0));
  }
}

void PixelWidget::DrawInterpolatedLine(double p1x, double p1y, const RGBVal & p1Rgb, double p2x, double p2y, const RGBVal & p2Rgb, double step){ //add pixels here; write methods like this for the assignments
  SetPixel( static_cast<unsigned int>(p1x), static_cast<unsigned int>(p1y),p1Rgb);
  SetPixel( static_cast<unsigned int>(p2x), static_cast<unsigned int>(p2y),p2Rgb);
  //Calculate Direction Vector in terms of X and Y for Parametic
  double dirX = p2x-p1x;
  double dirY = p2y-p1y;
  int rDiff = static_cast<int>(p2Rgb._red - p1Rgb._red);
  int gDiff = static_cast<int>(p2Rgb._green - p1Rgb._green);
  int bDiff = static_cast<int>(p2Rgb._blue - p1Rgb._blue);

  for (double i = step; i < 1; i += step)
  {
    double x = std::abs(p1x + (dirX * i));
    double y = std::abs(p1y +(dirY * i));
    unsigned int r = static_cast<unsigned int>(p1Rgb._red + rDiff * i);
    unsigned int g = static_cast<unsigned int>(p1Rgb._green + gDiff * i);
    unsigned int b = static_cast<unsigned int>(p1Rgb._blue + bDiff * i);

    SetPixel(static_cast<unsigned int>(x), static_cast<unsigned int>(y),RGBVal(r,g,b));
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
  DrawInterpolatedLine(10,30,RGBVal(255,0,0),50,10,RGBVal(120,100,255), 0.02);

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
