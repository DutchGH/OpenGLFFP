#pragma once
#include <GL/glu.h>
#include <GL/glut.h>
#include "Image.h"

class Planet{
    public:
        Planet(GLdouble radius, GLint slices, GLint stacks, Image * image);
        void DrawPlanet();
        GLUquadricObj* mPlanetQuad = nullptr;
        GLuint loadTexture();
    private:

        GLdouble mRadius; 
        GLint mSlices;
        GLint mStacks;
        Image * mImage = nullptr;
        GLuint mTexID;
        bool isTexturePresent;
         
    protected:

};