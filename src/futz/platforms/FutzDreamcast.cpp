#if FUTZ_PLATFORM_DREAMCAST

#include "../Futz.h"
#include "FutzDreamcast.h"
/* You can safely remove this line if you don't use a ROMDISK */
extern uint8 romdisk[];

KOS_INIT_FLAGS(INIT_DEFAULT | INIT_MALLOCSTATS);

/* And specify a romdisk, if you want one (or leave it out) */
KOS_INIT_ROMDISK(romdisk);
pvr_init_params_t params = {
        /* Enable opaque and translucent polygons with size 16 */
        { PVR_BINSIZE_16, PVR_BINSIZE_0, PVR_BINSIZE_16, PVR_BINSIZE_0, PVR_BINSIZE_0 },

        /* Vertex buffer size 512K */
        512*1024
};

void FutzDreamcast::Initialize(int argc, char** argv){
	Futz* futz = Futz::Instance();
	Futz::Log("Platform Dreamcast\n");
	maple_device_t *cont;
	cont_state_t *state;
	static int dpad = 0;
	pvr_init(&params);
	Futz::Instance()->camera->SetViewport(futz->platform->width, futz->platform->height);

	Futz::Instance()->renderer->Initialize(futz->platform->width,futz->platform->height);
	futz->gameObject->Start();


	joyactive = 0;
	max[0] = 0; max[1] = 0;
	min[0] = 255.0;
	min[1] = 255.0;

	while(1) {
		cont = maple_enum_type(0, MAPLE_FUNC_CONTROLLER);

		/* Check key status */
		state = (cont_state_t *)maple_dev_status(cont);
		if (!state) {
			printf("Error reading controller\n");
			break;
		}
		if (state->buttons & CONT_START)
			break;

	if (state->buttons & CONT_DPAD_UP) {
		Futz::Instance()->inputEventQueue.Push('w');
	}

	if (state->buttons & CONT_DPAD_DOWN) {
		Futz::Instance()->inputEventQueue.Push('s');
	}

	if (state->buttons & CONT_DPAD_LEFT) {
		Futz::Instance()->inputEventQueue.Push('a');
	}

	if (state->buttons & CONT_DPAD_RIGHT) {
		Futz::Instance()->inputEventQueue.Push('d');
	}

	Joystick(state);

		futz->Update();
		futz->Render();
		futz->gameObject->RenderLoop();
		
	}
	printf("Exiting\n");
}

// from kos/examples/dreamcast/kgl/demos/tunnel/tunnel.cpp
typedef struct JOYINFO {
	float wXpos;
	float wYpos;
};

#define FABS(n) ((((n) < 0.0) ? (-1.0*(n)) : (n)))
void FutzDreamcast::Joystick(cont_state_t *cond) {
	
	JOYINFO joy;

	joy.wXpos = (float)cond->joyx;
	joy.wYpos = (float)cond->joyy;

	Futz* futz = Futz::Instance();
	
	static float lastX = 0;
	static float fakeMouseX = 0;
	static float lastY = 0;
	static float fakeMouseY = 0;

	float speed = 0.3f;
	if(joy.wXpos != 0){
		fakeMouseX += joy.wXpos * speed * futz->time.delta;
	}

	if(joy.wYpos != 0){
		fakeMouseY += joy.wYpos * speed * futz->time.delta;
	}

	if(fakeMouseX != lastX || fakeMouseY != lastY){
   		Futz::Instance()->inputEventQueue.PushMouse(fakeMouseX, fakeMouseY);
	}
	lastX = fakeMouseX;
	lastY = fakeMouseY;
/*
	if (joy.wXpos - lastX > threshold){
	printf("x,y: %f,%f\n",joy.wXpos,joy.wYpos);
		Futz::Instance()->inputEventQueue.PushMouse(speed * futz->time.delta, 0);
	}
*/
	lastX = joy.wXpos;
/*
	if (joy.wXpos < -threshold){
		Futz::Instance()->inputEventQueue.PushMouse(-speed * futz->time.delta, 0);
	}
	if (joy.wYpos > threshold){
		Futz::Instance()->inputEventQueue.PushMouse(0,speed);
	}
	if (joy.wYpos < threshold){
		Futz::Instance()->inputEventQueue.PushMouse(0, -speed);
	}
*/		
	
/*
	if ((cond->rtrig > 128) && (velocity < 100))
		velocity += 1;
	if ((cond->ltrig > 128) && (velocity > -100))
		velocity -= 1;
	if ((cond->ltrig > 128) && (cond->rtrig > 128))
		velocity = 0;
*/
}

unsigned char* FutzDreamcast::LoadImage(string filename, int *x, int *y){
    filename = ResolveFilename(filename);
    unsigned char* data;

    return data;
}

#endif