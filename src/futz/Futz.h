/*
 * Futz.h
 *
 *  Created on: Feb 25, 2010
 *      Author: ziba
 */

#ifndef FUTZ_H_
#define FUTZ_H_
#include <string.h>
#include "input/Input.h"
#include "input/InputEventQueue.h"

#include "GameBase.h"
#include "TimeKeeper.h"
#include "camera/Camera.h"
#include "models/Model.h"
#include "core/Node.h"
#include "core/Profiler.h"
#include "scenegraph/SceneGraph.h"

#include "platforms/SystemLayerBase.h"
#include "renderers/RendererBase.h"

class Futz {

public:
	static Futz* Instance();
	static void Log(string mesg);

	Camera camera;
	Input input;
	InputEventQueue inputEventQueue;
	TimeKeeper time;
	SceneGraph scene;
    Profiler profiler;

	// Dynamically set based on build options
	SystemLayerBase* platform;

	RendererBase* renderer;

	// Supplied by the game using Futz
	GameBase* gameObject;
	
	void Start(int argc, char** argv);
	void Update();
	void Render();
	Model* LoadModel(char* filename);

private:
	Futz();
	~Futz();

	static Futz* _instance;
};

#endif /* FUTZ_H_ */
