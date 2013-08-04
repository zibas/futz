#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "Node.h"
class Component {
    public:
        string name;
        bool enabled;
        virtual void Start(){};
        virtual void Update() = 0;
        virtual void Draw() = 0;
        virtual void DrawLocal() = 0;
        void* node;
};

#endif
