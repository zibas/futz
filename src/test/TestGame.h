#ifndef DEMO_H_
#define DEMO_H_
#include "GameBase.h"

#include "Futz.h"
#include "math/Vector3.h"
#include "math/Matrix4.h"
#include "math/Quaternion.h"

class TestGame : public GameBase {
private:
	float barnYrot;
	float deltaZ;
	Vector3 barnPos;
	Model* model;
	Node* barn;

	Model* modelShip;
	Node* ship;

	Model* model2;
	Node* terrain;

	double speed;
	double turnSpeed;

public:
	TestGame();
	void Start();
	void UpdateLoop();
	void RenderLoop();
	void HandleInput();
	virtual ~TestGame();
};

#endif /* DEMO_H_ */
