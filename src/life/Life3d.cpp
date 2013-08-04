#include "Life3d.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "Futz.h"
#include "input/InputEventQueue.h"

Life3d::Life3d() {
	width = 100; 
	height = 100;
	depth = 1;

	cellClock = 0;
	cellPeriod = 0.3;
	speed = 0.5;
	turnSpeed = 20;

	srand (time(NULL));
	Futz* futz = Futz::Instance();
	
	char* file = (char*)"assets/cell.obj";
	model = futz->LoadModel(file);
	model->Load();

    	grid = life_init(width,height,depth);

	for(int i = 0; i < width*height*depth; i++){
		cellNodes[i] = new Node();	
		cellNodes[i]->AddModel(model);
		cellNodes[i]->transform.SetScale(0.5);
		//cellNodes[i]->enabled = false;
		futz->scene.AddNode(cellNodes[i]);
	}

	futz->camera.SetOrbit();
}

void Life3d::Init(int argc, char** argv){
    	//life_read_lif(grid, argv[1]);
}

void Life3d::UpdateLoop(){
	this->HandleInput();
	cellClock += Futz::Instance()->time.delta;
	if(cellClock >= cellPeriod){
		life_next_gen(grid);
		ArrangeCells();
		cellClock = 0;
	}
}

void Life3d::ArrangeCells(){
	int i, x, y, z;
	i = 0;
	for (y = 0; y < grid->y; y++ ){
		for(x = 0; x < grid->x; x++)
			for(z = 0; z < grid->z; z++)
			{
				if (life_is_alive(grid, x, y, z)){
					cellNodes[i]->transform.SetPosition((x - grid->x / 2),(y - grid->y / 2), (z - grid->z/2));
					cellNodes[i]->enabled = true;
				} else {
					cellNodes[i]->enabled = false;
				}
				i++;
			}
	}
}

void Life3d::Randomize(){
	int i, x, y, z;
	for (y = 0; y < grid->y; y++ ){
		for(x = 0; x < grid->x; x++){
			for(z = 0; z < grid->z; z++)
			{
				if(rand() % 2 == 1){
					life_set_alive(grid, x,y,z);
				} else {
					life_set_dead(grid, x,y,z);
				}
			}
		}
	}

}

void Life3d::RenderLoop()
{
	Futz::Instance()->renderer->DefaultLighting();
}


void Life3d::HandleInput(){

	Futz* futz = Futz::Instance();
	futzInputEvent* event = futz->inputEventQueue.Pop();

	double deltaX = 0;
	double deltaY = 0;

    if(futz->input.OnMouseMove()){
        deltaX = futz->input.mouseState.pixelX - futz->input.lastMouseState.pixelX;
        deltaY = futz->input.mouseState.pixelY - futz->input.lastMouseState.pixelY;
        futz->camera.RotY(-deltaX * futz->time.delta * turnSpeed);
        futz->camera.RotRightAxis(deltaY * futz->time.delta * turnSpeed);
    }

    if(futz->input.IsDown(FUTZ_LEFT)){
        futz->camera.MoveRight(-speed);
    }

    if(futz->input.IsDown(FUTZ_RIGHT)){
        futz->camera.MoveRight(speed);
    }

    if(futz->input.IsDown(FUTZ_UP)){
        futz->camera.MoveForward(-speed);
    }

    if(futz->input.IsDown(FUTZ_DOWN)){
        futz->camera.MoveForward(speed);
    }

    if(futz->input.OnDown('f')){
        futz->platform->ToggleFullscreen();
    }
    if(futz->input.OnDown('p')){
						life_print(grid);
    }
    if(futz->input.OnDown('r')){
						Randomize();
						ArrangeCells();
    }
    if(futz->input.OnDown('n')){
        					life_next_gen(grid);
						ArrangeCells();
    }
    if(futz->input.OnDown(FUTZ_ASCEND)){
				cellPeriod += 0.1;
    }
    if(futz->input.OnDown(FUTZ_DESCEND)){
				cellPeriod -= 0.1;
    }
    if(futz->input.OnDown(FUTZ_BACK)){
        exit(0);
    }
}

Life3d::~Life3d() {}
