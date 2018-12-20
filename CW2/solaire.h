#include <QGLWidget>
#include <GL/glut.h>

class Solaire
{ // 

	~Solaire();


	public:
        void updateArmAngle(int i);
        Solaire();
        void displaySolaire();
	

	protected:
	private:

	void head();
	void torso();
	void shoulders();
	void upper_arm_left();
	void lower_arm_left();
    void upper_arm_right();
    void lower_arm_right();

	GLUquadricObj* mHead;
	GLUquadricObj* mTorso;
	GLUquadricObj* mShoulders;
	GLUquadricObj* mUpperLeft;
    GLUquadricObj* mUpperRight;
	GLUquadricObj* mLowerLeft;
    GLUquadricObj* mLowerRight;
	

	float armangle = 0;

};
	