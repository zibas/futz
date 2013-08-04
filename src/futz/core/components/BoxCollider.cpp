#include "../../Futz.h"
#include "BoxCollider.h"

BoxCollider::BoxCollider(){
    name = "BoxCollider";
    draw = true;
    dimensions.x = 2;
    dimensions.y = 2;
    dimensions.z = 2;

}

void BoxCollider::Start(){
	Futz::Log("BoxCollider Start");
}


void BoxCollider::Update(){
    //TODO: only update if the transform has changed
    box.Set(dimensions);
    box.Transform(((Node*)node)->transform.matrix);
}

void BoxCollider::Draw(){
    if(draw){
        Futz::Instance()->renderer->DrawLine(box.GetVector3(0), box.GetVector3(1));
        Futz::Instance()->renderer->DrawLine(box.GetVector3(1), box.GetVector3(3));
        Futz::Instance()->renderer->DrawLine(box.GetVector3(3), box.GetVector3(2));
        Futz::Instance()->renderer->DrawLine(box.GetVector3(2), box.GetVector3(0));

        Futz::Instance()->renderer->DrawLine(box.GetVector3(4), box.GetVector3(5));
        Futz::Instance()->renderer->DrawLine(box.GetVector3(5), box.GetVector3(7));
        Futz::Instance()->renderer->DrawLine(box.GetVector3(7), box.GetVector3(6));
        Futz::Instance()->renderer->DrawLine(box.GetVector3(6), box.GetVector3(4));

        Futz::Instance()->renderer->DrawLine(box.GetVector3(0), box.GetVector3(4));
        Futz::Instance()->renderer->DrawLine(box.GetVector3(1), box.GetVector3(5));
        Futz::Instance()->renderer->DrawLine(box.GetVector3(3), box.GetVector3(7));
        Futz::Instance()->renderer->DrawLine(box.GetVector3(2), box.GetVector3(6));
    }

}

    bool BoxCollider::Intersects(BoxCollider* b2){
        Futz::Instance()->profiler.Start("BoxCollider Intersection");
        for(int i = 0; i < 8; i++){
            if(box.PointIsInside(b2->box.GetVector3(i))){
                Futz::Instance()->profiler.End();
                return true;
            }
        }

        for(int i = 0; i < 8; i++){
            if(b2->box.PointIsInside(box.GetVector3(i))){
                Futz::Instance()->profiler.End();
                return true;
            }
        }

        Futz::Instance()->profiler.End();
        return false;

    }

