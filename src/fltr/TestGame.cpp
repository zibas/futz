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
		fish[i] = new Fish();
		fish[i]->id = i + 1;
		fish[i]->Load();
	}


	glClearColor(1.0, 1.0, 1.0, 0.0);

	futz->camera.center.z = 0;

}

void TestGame::UpdateLoop() {
	Futz* futz = Futz::Instance();
	this->HandleInput();
	for (int i = 0; i < MAXFISH; i++) {
		fish[i]->Update();
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

	for (int i = 0; i < MAXFISH; i++) {

		if (futz->input.IsDown(FUTZ_UP, FUTZ_PLAYER_ONE)) {
			fish[i]->ThrustOn(0, 1);
		}
		if (futz->input.IsDown(FUTZ_DOWN, FUTZ_PLAYER_TWO)) {
			fish[i]->ThrustOn(0, -1);
		}
		if (futz->input.IsDown(FUTZ_LEFT)) {
			fish[i]->ThrustOn(-1, 0);
		}
		if (futz->input.IsDown(FUTZ_RIGHT)) {
			fish[i]->ThrustOn(1, 0);
		}
	}

	if (futz->input.OnUp('f')) {
		futz->platform->ToggleFullscreen();
	}
	if (futz->input.OnUp('c')) {
		futz->camera.Print();
		futz->camera.center.z = 0;


		for (int i = 0; i < MAXFISH; i++) {

			//cout << fish[i]->Status();
			fish[i]->color = !fish[i]->color;
			fish[i]->UpdateTexture();
			switch (fish[i]->mood) {
			case Fish::NORMAL:
				fish[i]->mood = Fish::HAPPY;
				break;
			case Fish::HAPPY:
				fish[i]->mood = Fish::SAD;
				break;
			case Fish::SAD:
				fish[i]->mood = Fish::NORMAL;
				break;
			}

		}

	}

	if (futz->input.IsDown(FUTZ_BACK)) {
		exit(0);
	}


}

TestGame::~TestGame() {}
