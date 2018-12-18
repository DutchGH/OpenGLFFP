#pragma once
#include "planet.h"
#include "GLMain.h"


Planet::Planet( GLdouble radius, 
                GLint slices, 
                GLint stacks 
              )
{   
    mPlanetQuad = gluNewQuadric();
    mRadius = radius;
    mSlices = slices;
    mStacks = stacks;
}

void Planet::DrawPlanet()
{
    gluQuadricTexture(mPlanetQuad, false);
    gluQuadricOrientation(mPlanetQuad, GLU_OUTSIDE);
    gluSphere(mPlanetQuad, mRadius, mSlices, mStacks);
}


