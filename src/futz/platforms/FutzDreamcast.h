#if FUTZ_PLATFORM_DREAMCAST


#ifndef FUTZDREAMCAST_H_
#define FUTZDREAMCAST_H_
#include <kos.h>

#include "SystemLayerBase.h"
class FutzDreamcast: public SystemLayerBase {
	string ResolveFilename(string filename){return "/rd/"+filename;};
	void Initialize(int argc, char** argv);
	unsigned char* LoadImage(string filename, int *x, int *y);
	void Joystick(cont_state_t* );
 int joyactive;
 float max[2];
 float min[2];
 float center[2];
};
#endif
#endif