#include <QtGui>
#include <QApplication>
#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QLabel>
#include <QVector2D>
#include <QDesktopWidget>
#include <cmath>
#include <iostream>
#include <fstream>
#include "pixelwidget.hpp"


void PixelWidget::DefinePixelValues(){ //add pixels here; write methods like this for the assignments
  SetPixel(10,30,RGBVal(255,0,0));
}


void PixelWidget::DrawLine(double p1x, double p1y, double p2x, double p2y, double step)
{
  SetPixel(static_cast<unsigned int>(p1x), static_cast<unsigned int>(p1y),RGBVal(255,0,0));
  SetPixel(static_cast<unsigned int>(p2x), static_cast<unsigned int>(p2y),RGBVal(255,0,0));
  //Calculate Direction Vector in terms of X and Y for Parametic
  double dirX = p2x-p1x;
  double dirY = p2y-p1y;
//  qDebug() << dirX << "," << dirY;

  for (double i = step; i < 1; i += step)
  {
//    qDebug() << i;

    double x = abs(p1x + (dirX * i));
//    qDebug() << x;

    double y = abs(p1y +(dirY * i));
//    qDebug() << y;

    SetPixel(static_cast<unsigned int>(x), static_cast<unsigned int>(y),RGBVal(255,0,0));
  }
}

void PixelWidget::DrawInterpolatedLine(double p1x, double p1y, const RGBVal & p1Rgb, double p2x, double p2y, const RGBVal & p2Rgb, double step)
{
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

bool PixelWidget::isBaryCentric(QVector2D &p, QVector2D &pA, QVector2D &pB, QVector2D &pC, float &alpha, float &beta, float &gamma)
{
    float D = ((pA.x() - pC.x()) * (pB.y() - pC.y())) - ((pB.x() - pC.x()) * (pA.y() - pC.y()));
    if(D == 0.f)
    {
        return false;
    }

    float invD = 1/D;

    //corresponding matrix values
    float yByC = (pB.y() - pC.y()) * invD;
    float xBxC = ((pB.x() - pC.x())* -1.f) * invD;
    float yAyC = ((pA.y() - pC.y())* -1.f) * invD;
    float xAxC = (pA.x() - pC.x()) * invD;

    float xPxC = p.x() - pC.x();
    float yPyC = p.y() - pC.y();

    alpha = (yByC * xPxC) + (xBxC * yPyC);
    beta = (yAyC * xPxC) + (xAxC * yPyC);

    if(alpha < 0 || beta < 0 || gamma < 0)
    {
        return false;
    }

    if(alpha+beta <= 1.f)
    {
        gamma = 1-alpha-beta;
        return true;
    }

    return false;


}
void PixelWidget::DrawBaryCentricTriangle(float p1x, float p1y, const RGBVal & p1Rgb, float p2x, float p2y, const RGBVal & p2Rgb, float p3x, float p3y, const RGBVal & p3Rgb)
{
    //Find the bounding triangle betweeen the values
    int maxX = static_cast<int>(std::max(p1x, std::max(p2x, p3x)));
    int minX = static_cast<int>(std::min(p1x, std::min(p2x, p3x)));
    int maxY = static_cast<int>(std::max(p1y, std::max(p2y, p3y)));
    int minY = static_cast<int>(std::min(p1y, std::min(p2y, p3y)));

    for (int y = minY; y <= maxY; y++)
    {
      for (int x = minX; x <= maxX; x++)
      {
        float alpha = 0.f;
        float beta = 0.f;
        float gamma = 0.f;
        bool inside = false;

        QVector2D p = QVector2D(x, y);
        QVector2D a = QVector2D(p1x, p1y);
        QVector2D b = QVector2D(p2x, p2y);
        QVector2D c = QVector2D(p3x, p3y);

//        bool inAB = halfPlaneTest(a.x(), a.y(), b.x(), b.y(), p.x(), p.y());
//        bool inBC = halfPlaneTest(b.x(), b.y(), c.x(), c.y(), p.x(), p.y());
//        bool inCA = halfPlaneTest(c.x(), c.y(), a.x(), a.y(), p.x(), p.y());

//        if(inAB && inBC && inCA)
//        {
//            qDebug() << "INSIDE!";
//            inside = true;
//        }



        if(isBaryCentric(p, a, b, c, alpha, beta, gamma) /*&& inside*/)
        {
            unsigned int newR = static_cast<unsigned int>((p1Rgb._red * alpha) + (p2Rgb._red * beta) + (p3Rgb._red * gamma));
            unsigned int newG = static_cast<unsigned int>((p1Rgb._green * alpha) + (p2Rgb._green * beta) + (p3Rgb._green * gamma));
            unsigned int newB = static_cast<unsigned int>((p1Rgb._blue * alpha) + (p2Rgb._blue * beta) + (p3Rgb._blue * gamma));
            SetPixel(static_cast<unsigned int>(x), static_cast<unsigned int>(y),RGBVal(newR,newG,newB));
        }

      }
    }
}

bool PixelWidget::halfPlaneTest(float p1x, float p1y, float p2x, float p2y, float px, float py)
{
    //find normal to P
    float nX = p2x - p1x;
    float nY = p2y - p1y;
    QVector2D n = QVector2D((nY*-1.f),nX);


    //Find F(P)
    float xPx = px - p1x;
    float xPy = py - p1y;
    QVector2D p = QVector2D(xPx,xPy);

    auto fP = QVector2D::dotProduct(p,n);

    if (fP >= 0)
    {
        return true;
    }
    return false;
}

void PixelWidget::isInside(float p1x, float p1y, float p2x, float p2y, float p3x, float p3y)
{
    std::ofstream myfile;
    myfile.open ("example.txt");

    for (int y = 0; y <= static_cast<int>(_n_vertical); y++)
    {
      for (int x = 0; x <= static_cast<int>(_n_horizontal); x++)
      {
        float alpha = 0.f;
        float beta = 0.f;
        float gamma = 0.f;
        bool inside = false;

        QVector2D p = QVector2D(x, y);
        QVector2D a = QVector2D(p1x, p1y);
        QVector2D b = QVector2D(p2x, p2y);
        QVector2D c = QVector2D(p3x, p3y);

        bool inAB = halfPlaneTest(a.x(), a.y(), b.x(), b.y(), p.x(), p.y());
        bool inBC = halfPlaneTest(b.x(), b.y(), c.x(), c.y(), p.x(), p.y());
        bool inCA = halfPlaneTest(c.x(), c.y(), a.x(), a.y(), p.x(), p.y());

        if(inAB && inBC && inCA)
        {
            inside = true;
        }


        isBaryCentric(p, a, b, c, alpha, beta, gamma);

        myfile << alpha << "," << beta << "," << gamma << "," << inside << "; ";
      }
      myfile << std::endl;
    }

    myfile.close();


}


void PixelWidget::generatePPM(float p1x, float p1y, const RGBVal & p1Rgb, float p2x, float p2y, const RGBVal & p2Rgb, float p3x, float p3y, const RGBVal & p3Rgb)
{
    std::ofstream myfile;
    myfile.open ("output.ppm");

    myfile << "P3\n" << _n_horizontal << "\n" << _n_vertical << "\n" << "255" << std::endl;
    for (int y = 0; y <= static_cast<int>(_n_vertical); y++)
    {
      for (int x = 0; x <= static_cast<int>(_n_horizontal); x++)
      {
        float alpha = 0.f;
        float beta = 0.f;
        float gamma = 0.f;

        QVector2D p = QVector2D(x, y);
        QVector2D a = QVector2D(p1x, p1y);
        QVector2D b = QVector2D(p2x, p2y);
        QVector2D c = QVector2D(p3x, p3y);


        if(isBaryCentric(p, a, b, c, alpha, beta, gamma))
        {
            unsigned int newR = static_cast<unsigned int>((p1Rgb._red * alpha) + (p2Rgb._red * beta) + (p3Rgb._red * gamma));
            unsigned int newG = static_cast<unsigned int>((p1Rgb._green * alpha) + (p2Rgb._green * beta) + (p3Rgb._green * gamma));
            unsigned int newB = static_cast<unsigned int>((p1Rgb._blue * alpha) + (p2Rgb._blue * beta) + (p3Rgb._blue * gamma));
            myfile << newR << " " << newG << " " << newB << "\t";
        }
        else
        {
            myfile << "0" << " " << "0" << " " << "0" << "\t";
        }

      }
      myfile << std::endl;
    }

    myfile.close();


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
  p.setWindow(QRect(-1.,-1.,static_cast<int>(_n_vertical+2),static_cast<int>(_n_horizontal+2)));
  int side = qMin(width(), height());  
  p.setViewport(0, 0, side, side);

  // black thin boundary around the cells
  QPen pen( Qt::black );
  pen.setWidth(0.);

//All Assignments Can Be Put Here:
  //  ASSIGNMENT 1
  //  DrawLine(10,30,50,10,0.02);

  //  ASSIGNMENT 2
  //  DrawInterpolatedLine(10,30,RGBVal(255,0,0),50,10,RGBVal(0,255,0),0.02);

  //  ASSIGNMENT 3
//    DrawBaryCentricTriangle(10,30,RGBVal(255,0,0),50,10,RGBVal(0,255,0),30,30,RGBVal(0,0,255));

  //  ASSIGNMENT 4
    isInside(10,30, 50,10,30,30);

  //  ASSIGNMENT 5
  //  generatePPM(10,30,RGBVal(255,0,0),50,10,RGBVal(0,255,0),30,30,RGBVal(0,0,255));


  for (int i_column = 0 ; i_column < static_cast<int>(_n_vertical); i_column++)
    for(int i_row = 0; i_row < static_cast<int>(_n_horizontal); i_row++){
      QRect rect(i_column,i_row,1,1);
      QColor c = QColor(_vec_rects[i_column][i_row]._red,
                        _vec_rects[i_column][i_row]._green,
                        _vec_rects[i_column][i_row]._blue);
    
      // fill with color for the pixel
      p.fillRect(rect, QBrush(c));
      p.setPen(pen);
      p.drawRect(rect);
    }
}
