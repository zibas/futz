#ifndef DEMO_H_
#define DEMO_H_
#include "GameBase.h"

#include "Asteroids.h"
#include "Ships.h"

class Demo : public GameBase {
private:
	double speed;
	double turnSpeed;
	float idleClock;
	float idleDelay;

public:
	Asteroids asteroids;
	Ships ships;

	Demo();
	void Start();
	void UpdateLoop();
	void RenderLoop();
	void HandleInput();
	void DrawBox();
	virtual ~Demo();
};

#endif /* DEMO_H_ */
