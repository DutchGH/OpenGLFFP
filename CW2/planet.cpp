#include "planet.h"
#include "GLMain.h"


Planet::Planet( GLdouble radius, 
                GLint slices, 
                GLint stacks,
                Image * image
              )
{   
    mPlanetQuad = gluNewQuadric();
    mRadius = radius;
    mSlices = slices;
    mStacks = stacks;
    if (image)
    {
        mImage = image;
        mTexID = loadTexture();
    }
}

GLuint Planet::loadTexture()
{
    GLuint textureId;
    glGenTextures(1, &textureId); //Make room for our texture
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mImage->Width(), mImage->Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, mImage->imageField());
    isTexturePresent = true;
    return textureId;
}

void Planet::DrawPlanet()
{
    gluQuadricOrientation(mPlanetQuad, GLU_OUTSIDE);
    if (isTexturePresent)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, mTexID);
        // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        gluQuadricTexture(mPlanetQuad, 1);
    }
    glPushMatrix();
        glRotatef(10,0,-1,0);
        glRotatef(90,-1,0,0);
        gluSphere(mPlanetQuad, mRadius, mSlices, mStacks);
      glPopMatrix();
    

}


