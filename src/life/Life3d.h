#ifndef DEMO_H_
#define DEMO_H_
#include "GameBase.h"

#include "Futz.h"
#include "liblife.h"

class Life3d : public GameBase {
private:
	Model* model;
	Node* cellNodes[50 * 50 * 50];
	int width;
	int height;
	int depth;

	life_grid* grid;
	double cellPeriod;
	double cellClock;
	double speed;
	double turnSpeed;

	void Randomize();

public:
	Life3d();
	void Init(int argc, char** argv);
	void ArrangeCells();
	void UpdateLoop();
	void RenderLoop();
	void HandleInput();
	virtual ~Life3d();
};

#endif /* DEMO_H_ */
