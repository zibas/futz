#include "Futz.h"
#include "Asteroids.h"


void Asteroids::Start(){
	Futz* futz = Futz::Instance();
	//char* file = (char*)"assets/taxi_model.obj";
	//char* file = (char*)"assets/cell.obj";
	char* file = (char*)"assets/asteroid.obj";

	model = futz->LoadModel(file);
	model->Load();

	count = 0;

	srand (time(NULL));
	int randX;
	int randY;
	int randZ;
	float randScale;
	int randRange = 100;

	for(int i = 0; i < 100; i++){
		randX = (rand() % randRange) - (randRange / 2);
		randY = (rand() % randRange) - (randRange / 2);
		randZ = (rand() % randRange) - (randRange / 2);
		randScale = (rand() % 5) / 2;
		asteroids[count] = new Node();
		asteroids[count]->transform.SetScale(randScale);
		asteroids[count]->transform.SetPosition(randX, randY, randZ);
		asteroids[count]->transform.SetRotation(randX, randY, randZ);
		asteroids[count]->AddModel(model);
		futz->scene.AddNode(asteroids[count]);

		rotations[count] = new Vector3();
		rotations[count]->x = (rand()%20);
		rotations[count]->y = (rand()%20);
		rotations[count]->z = (rand()%20);
		count++;
	}
}

Asteroids::~Asteroids(){
	for(int i = 0; i < count; i++){
		delete asteroids[i];
		delete rotations[i];
	}
	delete model;
}

void Asteroids::Update(){
	Futz* futz = Futz::Instance();
	for(int i = 0; i < count; i++){
		asteroids[i]->transform.SetRotation(rotations[i]->x * futz->time.totalElapsedSeconds,
				rotations[i]->y * futz->time.totalElapsedSeconds,
				rotations[i]->z * futz->time.totalElapsedSeconds);
	}
}
