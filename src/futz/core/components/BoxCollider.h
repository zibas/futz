#ifndef BOXCOLLIDER_H_
#define BOXCOLLIDER_H_

#include "../primatives/Box.h"
#include "../Component.h"
#include "../../models/Model.h"

class BoxCollider : public Component {
    private:
        bool draw;
    public:
        Box box; 

        Vector3 center;
        Vector3 dimensions;


        BoxCollider();
        void Start();
        void Update();
        void Draw();
        void DrawLocal(){};


        bool Intersects(BoxCollider*);
};

#endif
