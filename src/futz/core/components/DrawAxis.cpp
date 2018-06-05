#include "../../Futz.h"
#include "DrawAxis.h"

DrawAxis::DrawAxis(){
	name = "DrawAxis";
}

void DrawAxis::Draw(){
	float interval = 5;
	int emphasis = 2;
	Vector3 color;
	Vector3 v1, v2;
	Vector3 x;
	Vector3 y;
	Vector3 z;
	x.x = 1000;
	y.y = 1000;
	z.z = 1000;
	float width = 5;


	Futz* futz = Futz::Instance();
	futz->renderer->DisableLighting();

	color.x = 1; color.y = 0; color.z = 0;
	futz->renderer->DrawLine(x * -1, x, color);

	for (int i = -x.x; i < x.x; i += interval){
		v1.x = v2.x = i;
		v1.y = v2.y = 0;
		v1.z = -width/2; v2.z = width/2;
		color.x = 0.5; color.y = 0; color.z = 0;
		if (i % (int)(interval * emphasis) == 0)
		{
			color.x = 1;
			v1.z = -width; v2.z = width;
		}
		futz->renderer->DrawLine(v1, v2, color);
	}

	color.x = 0; color.y = 1; color.z = 0;
	futz->renderer->DrawLine(y * -1, y, color);

	for (int i = -y.y; i < y.y; i += interval){
		v1.y = v2.y = i;
		v1.x = v2.x = 0;
		v1.z = -width / 2; v2.z = width / 2;
		color.x = 0; color.y = 0.5; color.z = 0;
		if (i % (int)(interval * emphasis) == 0)
		{
			color.y = 1;
			v1.z = -width; v2.z = width;
		}
		futz->renderer->DrawLine(v1, v2, color);
	}


	color.x = 0.5; color.y = 0.5; color.z = 1;
	futz->renderer->DrawLine(z * -1, z, color);

	for (int i = -z.z; i < z.z; i += interval){
		v1.z = v2.z = i;
		v1.y = v2.y = 0;
		v1.x = -width / 2; v2.x = width / 2;
		color.x = 0.5; color.y = 0.5; color.z = 0.5;
		if (i % (int)(interval * emphasis) == 0)
		{
			color.z = 1;
			v1.x = -width; v2.x = width;
		}
		futz->renderer->DrawLine(v1, v2, color);
	}

}

void DrawAxis::Start(){
	Futz::Log("DrawAxis Start");
}


void DrawAxis::DrawLocal(){
}
