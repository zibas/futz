#include "Fish.h"
#include <iostream>

Fish::FishHandle Fish::Create(int id){
	FishHandle f(new Fish());
	f->id = id;
	return f;
}

void Fish::Load() {
	Futz* futz = Futz::Instance();

	drag = Vector3();
	position = Vector3();
	thrust = Vector3();
	lastThrust = Vector3();
	velocity = Vector3();
	acceleration = Vector3();

	drag.x = 2;
	drag.y = 3;
	drag.z = 0;

	speed = 5;

	//std::string file = "assets/Fish " + std::to_string(id) + "/normal.png";
	char* file = (char *)"assets/plane.obj";
	model = futz->LoadModel(file);
	model->Load();
	node = new Node();
	node->AddModel(model);
	node->transform.SetScale(1);
	position.x = (id * 3) - 10;
	node->transform.SetPosition(position.x, position.y, position.z);
	node->useLighting = false;
	futz->scene.AddNode(node);
	UpdateTexture();
}

void Fish::UpdateTexture() {
	std::string textureFile = "assets/Fish " + std::to_string(id) + "/";
	switch (mood) {
	case NORMAL:
		textureFile += "normal";
		break;
	case HAPPY:
		textureFile += "happy";
		break;
	case SAD:
		textureFile += "sad";
		break;
	}
	if (color) {
		textureFile += " color";
	}
	textureFile += ".png";

	model->LoadImage(textureFile, 0);

}
void Fish::PhysicsUpdate() {
		Futz* futz = Futz::Instance();
		float delta = futz->time.delta;
		acceleration = thrust;
		velocity = velocity + (acceleration * delta);

		position = position + (velocity * delta);
		lastThrust = thrust;

		ApplyDrag();
	}

	void Fish::ApplyDrag() {
		Futz* futz = Futz::Instance();
		float delta = futz->time.delta;

		if (velocity.x > 0)
		{
			velocity.x -= drag.x * delta;
			if (velocity.x < 0)
			{
				velocity.x = 0;
			}
		}
		else if (velocity.x < 0)
		{
			velocity.x += drag.x * delta;
			if (velocity.x > 0)
			{
				velocity.x = 0;
			}
		}

		if (velocity.y > 0)
		{
			velocity.y -= drag.y * delta;
			if (velocity.y < 0)
			{
				velocity.y = 0;
			}
		}
		else if (velocity.y < 0)
		{
			velocity.y += drag.y * delta;
			if (velocity.y > 0)
			{
				velocity.y = 0;
			}
		}
	}


	void Fish::ThrustOn(double x, double y) {
		x *= speed;
		y *= speed;
		if (x != 0) {
			thrust.x = x;
		}
		if (y != 0) {
			thrust.y = y;
		}
		thrust.z = 0;
	}

	void Fish::Update() {
		Futz* futz = Futz::Instance();
		//node->transform.AddRelativeTranslation(1*futz->time.delta,0,0);
		PhysicsUpdate();
		node->transform.SetPosition(position.x, position.y, position.z);
		thrust.x = 0;
		thrust.y = 0;
		thrust.z = 0;
	}



	Fish::~Fish(){
		cout << "[Fish " << id << "] destructing\n";
	}