#ifndef _PIXEL_WIDGET_
#define _PIXEL_WIDGET_

#include <QtGui>
#include <QApplication>
#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QLabel>
#include <QVector2D>
#include <QDesktopWidget>
#include <iostream>
#include <vector>
#include "RGBVal.hpp"


class PixelWidget : public QWidget {
public:

  
  // set the number of pixels that the widget is meant to display
  PixelWidget
  (
   unsigned int n_horizontal, // the first integer determines the number of horizontal pixels 
   unsigned int n_vertical    // the second integer determines the number of vertical pixels
   );

  // sets a pixel at the specified RGBVal value; ignores non-existing pixels without warning
  void SetPixel
  ( 
   unsigned int  i_x, // horizontal pixel coordinate
   unsigned int  i_y, // vertical pixel coordinate
   const RGBVal& c    // RBGVal object for RGB values
    );

  // Use the body of this function to experiment with rendering algorithms
  void DefinePixelValues();
  bool isBaryCentric(QVector2D &p, QVector2D &pA, QVector2D &pB, QVector2D &pC, float &alpha, float &beta, float &gamma);
  void DrawLine(double p1x, double p1y, const RGBVal & p1Rgb, double p2x, double p2y, const RGBVal & p2Rgb, double step);
  void DrawInterpolatedLine(double p1x, double p1y, const RGBVal & p1Rgb, double p2x, double p2y, const RGBVal & p2Rgb, double step);
  void DrawBaryCentricTriangle(float p1x, float p1y, const RGBVal & p1Rgb, float p2x, float p2y, const RGBVal & p2Rgb, float p3x, float p3y, const RGBVal & p3Rgb);

protected:

  virtual void paintEvent(QPaintEvent*);


private:

  unsigned int _n_vertical;
  unsigned int _n_horizontal;

  std::vector<std::vector<RGBVal> > _vec_rects;
};

#endif

