#ifndef BOUNDINGSPHERE_H_
#define BOUNDINGSPHERE_H_

#include "../Component.h"
#include "../../models/Model.h"

class BoundingSphere : public Component {
    private:
        float width;
        Model* model;
        float maxVertexDistanceFromCenter;
    public:
        bool draw;
        int extremeIndices[6];
        Vector3 center;
        float radius;


        BoundingSphere();
        void Start();
        void Update();
        void Draw();
        void DrawLocal(){};
        void SetLocalVerticesFromExtremes();

        void ReadModel(Model*);
};

#endif
