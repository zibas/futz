#include "GameBase.h"
#include "Futz.h"
#include "math/Vector3.h"
#ifdef _WIN32
#include <memory>
#else
#include <trl/memory>
#endif

class Fish {
private:
	Vector3 drag;
	float mass;

	Vector3 position;
	Vector3 thrust;
	Vector3 lastThrust;
	Vector3 velocity;
	Vector3 acceleration;

	float speed;

public:
	Node* node;
	Model* model;
	int id = 1;

	enum MOODS { NORMAL, HAPPY, SAD };
	MOODS mood = NORMAL;
	bool color = false;

	typedef std::shared_ptr<Fish> FishHandle;

	static FishHandle Create(int id);

	void Load();
	void UpdateTexture();
	void ThrustOn(double x, double y);
	void Update();
	void PhysicsUpdate();
	void ApplyDrag();

	~Fish();

	std::string Status() {
		std::string status = "Fish status " + std::to_string(position.x);
		return status;
	}
};
