#include "Fish.h"

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