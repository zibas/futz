/*
 * GameBase.h
 *
 *  Created on: Nov 3, 2010
 *      Author: ziba
 */

#ifndef GAMEBASE_H_
#define GAMEBASE_H_
#include <stdio.h>
class GameBase {
public:
	GameBase();
	virtual void UpdateLoop(){};
	virtual void RenderLoop(){};
	virtual void Start(){ printf("default start\n");};
	virtual ~GameBase();
};

#endif /* GAMEBASE_H_ */
