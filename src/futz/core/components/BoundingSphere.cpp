#include "../../Futz.h"
#include "BoundingSphere.h"
#include <stdlib.h>
#include <math.h>

BoundingSphere::BoundingSphere(){
    name = "BoundingSphere";
    draw = true;
}

void BoundingSphere::Start(){
	Futz::Log("BoundingSphere Start");
    center.x = 0;
    center.y = 0;
    center.z = 0;
    maxVertexDistanceFromCenter = 0;
    radius = 0;
}

void BoundingSphere::ReadModel(Model* m){
    model = m;

    int c = 0;
    maxVertexDistanceFromCenter = 0;
    //Bug: the max distance isn't the distance of any one dimension of a triplet, it's the whole vertex's distance from the center
    for(std::vector<Vector3>::iterator it = m->vertices.begin(); it != m->vertices.end(); ++it) {
		if((*it).Length() > maxVertexDistanceFromCenter){
                            printf("* %d %f > %f\n",c,(*it).Length(),maxVertexDistanceFromCenter);

                maxVertexDistanceFromCenter = (*it).Length();

		} else {
            printf("%d %f < %f\n",c,(*it).Length(),maxVertexDistanceFromCenter);
        }
	}

}

void BoundingSphere::Update(){
    center = ((Node*)node)->transform.position;
    radius = ((Node*)node)->transform.scale * maxVertexDistanceFromCenter;
    //radius = maxVertexDistanceFromCenter;
}

void BoundingSphere::Draw(){
    if(draw){
            Futz::Instance()->renderer->DrawSphere(center, radius);
    }

}
