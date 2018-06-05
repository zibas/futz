#ifndef DEMO_H_
#define DEMO_H_
#include "GameBase.h"

#include "Futz.h"
#include "math/Vector3.h"
#include "math/Matrix4.h"
#include "math/Quaternion.h"
#include "core/components/DrawAxis.h"

#include "Fish.h"

class TestGame : public GameBase {
private:
    Fish* fish1;
	float fishYrot;
	float deltaZ;
	Vector3 fishPos;
	Model* model;
	Node* fish;

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
