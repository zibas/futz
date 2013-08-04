#ifndef AxisAlignedBoundingBox_H_
#define AxisAlignedBoundingBox_H_

#include "../Component.h"
#include "../../models/Model.h"

class AxisAlignedBoundingBox : public Component {
    private:
        float width;
        Model* model;
    public:
        int extremeIndices[6];
        Vector3 v1,v2,v3,v4,v5,v6,v7,v8;
        Vector3 lv1,lv2,lv3,lv4,lv5,lv6,lv7,lv8;


        AxisAlignedBoundingBox();
        void Start();
        void Update();
        void Draw();
        void DrawLocal(){};
        void SetLocalVerticesFromExtremes();

        void ReadModel(Model*);
};

#endif
