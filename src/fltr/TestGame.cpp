#include "TestGame.h"
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "Futz.h"
#include "input/InputEventQueue.h"

TestGame::TestGame() {
	speed = 0.5;
	turnSpeed = 100;
	srand(time(NULL));
	Futz::Log("Game Constructor done");
}

void TestGame::Start() {
	Futz* futz = Futz::Instance();

	for (int i = 0; i < MAXFISH; i++) {
		Fish::FishHandle f = Fish::Create(i+1);
		f->Load();
		fishes.push_back(f);
	}
	
	glClearColor(1.0, 1.0, 1.0, 0.0);
	futz->camera.center.z = 0;
}

void TestGame::UpdateLoop() {
	Futz* futz = Futz::Instance();
	this->HandleInput();

	for(auto fish : fishes){
		fish->Update();
	}

	deltaZ = 0;
}


void TestGame::RenderLoop()
{
	Futz* futz = Futz::Instance();
	futz->renderer->DefaultLighting();
}


void TestGame::HandleInput() {

	Futz* futz = Futz::Instance();

	double deltaX = 0;
	double deltaY = 0;

	for(auto fish : fishes){
		if (futz->input.IsDown(FUTZ_UP)) {
			fish->ThrustOn(0, 1);
		}
		if (futz->input.IsDown(FUTZ_DOWN)) {
			fish->ThrustOn(0, -1);
		}
		if (futz->input.IsDown(FUTZ_LEFT)) {
			fish->ThrustOn(-1, 0);
		}
		if (futz->input.IsDown(FUTZ_RIGHT)) {
			fish->ThrustOn(1, 0);
		}
	}

	if (futz->input.OnUp('f')) {
		futz->platform->ToggleFullscreen();
	}
	if (futz->input.OnUp('c')) {
		futz->camera.Print();
		futz->camera.center.z = 0;

		for(auto fish : fishes){
			fish->color = !fish->color;
			fish->UpdateTexture();
			switch (fish->mood) {
			case Fish::NORMAL:
				fish->mood = Fish::HAPPY;
				break;
			case Fish::HAPPY:
				fish->mood = Fish::SAD;
				break;
			case Fish::SAD:
				fish->mood = Fish::NORMAL;
				break;
			}

		}

	}

	if (futz->input.IsDown(FUTZ_BACK)) {
		fishes.clear();
		exit(0);
	}


}

TestGame::~TestGame() {}
