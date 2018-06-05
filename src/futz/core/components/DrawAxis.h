#ifndef DRAWAXIS_H_
#define DRAWAXIS_H_

#include "../Component.h"

class DrawAxis : public Component {
    public:
	DrawAxis();
        void Start();
        void Update(){};
        void Draw();
        void DrawLocal();
};

#endif
