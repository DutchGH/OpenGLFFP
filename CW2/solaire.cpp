#include <GL/glu.h>
#include <QGLWidget>
#include <QSlider>
#include <cmath>
#include <iostream>
#include "solaire.h"

double HEAD_HEIGHT    = 1.5;
double ARM_LENGTH     = 2.5;
double SHOULDER_WIDTH = 3.0;

// Setting up material properties
typedef struct materialStruct {
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
    GLfloat shininess;
} materialStruct;


static materialStruct shinyGold = {
    { 0.24725f, 0.1995f, 0.0745f, 1.0f },
    {0.75164f, 0.60648f, 0.22648f, 1.0f },
    {1.628281f, 1.555802f, 1.366065f, 1.0f },
    51.2f

};

static materialStruct whiteRubber = {
    { 0.0f,0.0f,0.0f,1.0f },
    { 0.55f,0.55f,0.55f,1.0f},
    {0.70f,0.70f,0.70f,1.0f },
    32.0f 
};

// constructor
Solaire::Solaire()
    { // constructor       
        mHead      = gluNewQuadric();
        mShoulders = gluNewQuadric();
        mTorso     = gluNewQuadric();
        mUpperLeft = gluNewQuadric();
        mUpperRight = gluNewQuadric();
        mLowerLeft = gluNewQuadric();
        mLowerRight = gluNewQuadric();
    } // constructor


Solaire::~Solaire()
{
    gluDeleteQuadric(mHead);
    gluDeleteQuadric(mShoulders);
    gluDeleteQuadric(mTorso);
    gluDeleteQuadric(mUpperLeft);
    gluDeleteQuadric(mLowerLeft);
    gluDeleteQuadric(mUpperRight);
    gluDeleteQuadric(mLowerRight);
}


void Solaire::updateArmAngle(int i){
    armangle = i;
}



void Solaire::head(){
    gluCylinder(mHead,0.75,0.75,1.5,20,20);
    gluQuadricOrientation(mHead,GLU_INSIDE);

}

void Solaire::torso(){
    gluCylinder(mTorso,1.0,1.0,5,20,20);
    gluQuadricOrientation(mTorso,GLU_INSIDE);

}


void Solaire::shoulders(){
    gluCylinder(mShoulders,0.5,0.5,3,8,8);
    // gluQuadricOrientation(mShoulders,GLU_INSIDE);

}	


void Solaire::upper_arm_left(){
    gluCylinder(mUpperLeft,0.5,0.5,2.5,8,8);
    gluQuadricOrientation(mUpperLeft,GLU_INSIDE);

}

void Solaire::upper_arm_right(){
    gluCylinder(mUpperRight,0.5,0.5,2.5,8,8);
    gluQuadricOrientation(mUpperRight,GLU_INSIDE);

}


void Solaire::lower_arm_left(){
    gluCylinder(mLowerLeft,0.5,0.5,2.5,8,8);
    gluQuadricOrientation(mLowerLeft,GLU_INSIDE);

}

void Solaire::lower_arm_right(){
    gluCylinder(mLowerRight,0.5,0.5,2.5,8,8);
    gluQuadricOrientation(mLowerRight,GLU_INSIDE);

}


// called every time the widget needs painting
void Solaire::displaySolaire()
    { 
    materialStruct* p_front = &whiteRubber;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
    glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);
    
    // creating the torso
    glPushMatrix(); // save the world
          glRotatef(90.,1.,0.,0.);
        this->torso();
    glPopMatrix(); // restore the world


    p_front = &shinyGold;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT,    p_front->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,    p_front->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,   p_front->specular);
    glMaterialf(GL_FRONT, GL_SHININESS,   p_front->shininess);

    // shoulders
    glPushMatrix();
        glTranslatef(0.,0.,-SHOULDER_WIDTH/2);
        this->shoulders();
    glPopMatrix();

    // placing the head
    glPushMatrix(); 
    glTranslatef(0., HEAD_HEIGHT, 0.);
    glRotatef(90.,1.,0.,0.);
    this->head();
    glPopMatrix();  

    // Left Arm
    glPushMatrix();
    glRotatef((double)armangle,0.,0.,1.);                                                                                                                                  
        glTranslatef(0.,0., SHOULDER_WIDTH/2.);
           glRotatef(75,1.,0.,0.);
        this->upper_arm_right();
        glTranslatef(0.,0.,ARM_LENGTH); 
        // glRotatef(armangle/2,0.,1.,0.);                                                                                                                                  
        this->lower_arm_right();
    glPopMatrix();
  

    //right Arm
    glPushMatrix();
    glRotatef((double)armangle,0.,0.,1.);                                                                                                                                  
        glTranslatef(0.,0., -SHOULDER_WIDTH/2.);
           glRotatef(105,1.,0.,0.);
        this->upper_arm_right();
        glTranslatef(0.,0.,ARM_LENGTH); 
        // glRotatef(armangle/2,0.,1.,0.);                                                                                                                                  
        this->lower_arm_right();
    glPopMatrix();

    } // paintGL()
