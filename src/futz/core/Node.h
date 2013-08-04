#ifndef NODE_H_
#define NODE_H_

#include <map>
#include <vector>
#include "../models/Model.h"
#include "Component.h"
#include "Transform.h"
class Node {
	public:
        map<int, string> componentMap;
        map<int, string>::iterator componentMapIterator;
        vector<Component*> components;
        vector<Component*>::iterator componentsIterator;
		Transform transform;
		Node();
		void Draw();
		void Update();
		virtual ~Node();
		void Print();
		void AddModel(Model*);
		bool enabled;
		bool useLighting;
		bool transparent;
		Node* parent;
		float DistanceFromCamera();

        void AddComponent(Component*);
        Component* GetComponent(string);
};

#endif
