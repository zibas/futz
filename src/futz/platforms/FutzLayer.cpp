/*
 * FutzLayer.cpp
 *
 *  Created on: Nov 3, 2010
 *      Author: ziba
 */

#include "../Futz.h"
#include "FutzLayer.h"
#include <stdio.h>

FutzLayer::FutzLayer() {
	// TODO Auto-generated constructor stub
}

void FutzLayer::Initialize(int argc, char** argv){
	Futz* futz = Futz::Instance();
	Futz::Log("FutzLayer not implemented\n");
	Futz::Instance()->renderer->Initialize(futz->platform->width,futz->platform->height);
	futz->gameObject->Start();
	while(1){
		futz->Update();
		futz->Render();
		futz->gameObject->RenderLoop();
	}
}

FutzLayer::~FutzLayer() {
	// TODO Auto-generated destructor stub
}
