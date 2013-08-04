#include "Futz.h"
#include "Ships.h"


void Ships::Start(){
	Futz* futz = Futz::Instance();
	char* file = (char*)"assets/taxi_model.obj";

	model = futz->LoadModel(file);
	model->Load();
	
	count = 0;

	srand (time(NULL));
	int randX;
	int randY;
	int randZ;
	int randScale;
	int randRange = 50;

	for(int i = 0; i < 15; i++){
			randX = (rand() % randRange) - (randRange / 2);
			randY = (rand() % randRange) - (randRange / 2);
			randZ = (rand() % randRange) - (randRange / 2);
			randScale = (rand() % 5) / 2;
			ships[count] = new Node();
			ships[count]->transform.SetPosition(randX, randY, randZ);
			ships[count]->transform.SetRotation(randX, randY, randZ);
			ships[count]->AddModel(model);
			futz->scene.AddNode(ships[count]);

			rotations[count] = (rand()%20) + 10;
			radii[count] = (rand()%50) + 5;
			centers[count].x = randX;
			centers[count].y = randY;
			centers[count].z = randZ;

			count++;
	}
}

Ships::~Ships(){
	for(int i = 0; i < count; i++){
		delete ships[i];
	}
	delete model;
}

void Ships::Update(){
	Futz* futz = Futz::Instance();
	double radius;
	Quaternion rot;

	for(int i = 0; i < count; i++){
		rot.SetAxis(rotations[i] * futz->time.totalElapsedSeconds, 0, 1,0),
		//ships[i]->transform.SetOrbit(offset, radii[i],rot); 
		ships[i]->transform.SetOrbit(centers[i],radii[i],rot); 

	}
}
