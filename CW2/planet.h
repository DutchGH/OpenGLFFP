#include <GL/glu.h>
#include <GL/glut.h>
#include "textures.h"

class Planet{
    public:
        Planet(GLdouble radius, GLint slices, GLint stacks);
        void DrawPlanet();
        GLUquadricObj* mPlanetQuad = nullptr;


    private:

        // materialStruct * mMaterial = nullptr;
        // Image * image, nullptr;
        GLdouble mRadius; 
        GLint mSlices;
        GLint mStacks;
         
    protected:

};