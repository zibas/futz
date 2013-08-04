/*
 * FutzGlut.h
 *
 *  Created on: Nov 3, 2010
 *      Author: ziba
 */

#ifndef FUTZGLUT_H_
#define FUTZGLUT_H_

#include "SystemLayerBase.h"

class FutzGlut: public SystemLayerBase {
public:
	static void Reshape(int, int);
	static void Timer(int);
	static void RenderScene(void);
	static void KeyPressFunc(unsigned char key, int x, int y);
	static void KeyUpFunc(unsigned char key, int x, int y);
	static void PassiveMotion(int x, int y);

	void Resize(int, int);
	void ToggleFullscreen();
	void Initialize(int argc, char** argv);
	virtual ~FutzGlut();
};

#endif /* FUTZGLUT_H_ */
