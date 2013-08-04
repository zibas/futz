#ifndef DRAWMODEL_H_
#define DRAWMODEL_H_

#include "../Component.h"

class DrawModel : public Component {
    public:
        bool transparent;

		Model* model;

        DrawModel();
        void Start();
        void Update(){};
        void Draw(){};
        void DrawLocal();
};

#endif
