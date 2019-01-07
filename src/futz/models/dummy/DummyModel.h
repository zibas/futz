#ifndef DUMMYMODEL_H_ 
#define DUMMYMODEL_H_ 
#ifdef OSX
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#elif OPENGLES1
#ifdef IOS
#include <OpenGLES/ES1/gl.h>
#else
#include <GLES/gl.h>
#include <GLES/glext.h>
#endif
#else
#include <GL/gl.h>
#endif
#include <stdio.h>

class DummyModel: public Model {

public:
	GLfloat n[6][3];
	GLint faces[6][4];
	GLfloat v[8][3];

	DummyModel(char* filename):Model(filename){

		n[0][0] = -1;
		n[0][1] = 0;
		n[0][2] = 0;

		n[1][0] = 0;
		n[1][1] = 1;
		n[1][2] = 0;

		n[2][0] = 1;
		n[2][1] = 0;
		n[2][2] = 0;

		n[3][0] = 0;
		n[3][1] = -1;
		n[3][2] = 0;

		n[4][0] = 0;
		n[4][1] = 0;
		n[4][2] = 1;

		n[5][0] = 0;
		n[5][1] = 0;
		n[5][2] = -1;

		faces[0][0] = 0;
		faces[0][1] = 1;
		faces[0][2] = 2;
		faces[0][3] = 3;

		faces[1][0] = 3;
		faces[1][1] = 2;
		faces[1][2] = 6;
		faces[1][3] = 7;

		faces[2][0] = 7;
		faces[2][1] = 6;
		faces[2][2] = 5;
		faces[2][3] = 4;

		faces[3][0] = 4;
		faces[3][1] = 5;
		faces[3][2] = 1;
		faces[3][3] = 0;

		faces[4][0] = 5;
		faces[4][1] = 6;
		faces[4][2] = 2;
		faces[4][3] = 1;

		faces[5][0] = 7;
		faces[5][1] = 4;
		faces[5][2] = 0;
		faces[5][3] = 3;

		/* Setup cube vertex data. */
		v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1;
		v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1;
		v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1;
		v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1;
		v[0][2] = v[3][2] = v[4][2] = v[7][2] = 1;
		v[1][2] = v[2][2] = v[5][2] = v[6][2] = -1;
	};

	void Draw(double* matrixValues){
		int i;

#ifndef OPENGLES1
		glPushMatrix();
		glMultMatrixd(matrixValues);
		for (i = 0; i < 6; i++) {
			glBegin(GL_QUADS);
			glNormal3fv(&n[i][0]);
			glVertex3fv(&v[faces[i][0]][0]);
			glVertex3fv(&v[faces[i][1]][0]);
			glVertex3fv(&v[faces[i][2]][0]);
			glVertex3fv(&v[faces[i][3]][0]);
			glEnd();
		}
		glPopMatrix();
#endif
	}

};
#endif
