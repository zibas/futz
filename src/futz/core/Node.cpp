#include "../Futz.h"
#include "components/AxisAlignedBoundingBox.h"
#include "components/BoxCollider.h"
#include "components/BoundingBox.h"
#include "components/DrawModel.h"
#include "components/BoundingSphere.h"
#include "Node.h"
#include <stdio.h>

Node::Node(){
	parent = NULL;
	enabled = true;
	useLighting = true;
	transparent = false;
	transform.node = this;
   // BoxCollider* boxCollider = new BoxCollider();
    //AddComponent((Component*) boxCollider);

    //AxisAlignedBoundingBox* axisBox = new AxisAlignedBoundingBox();
    //AddComponent((Component*) axisBox);

    BoundingBox* boundingBox = new BoundingBox();
    AddComponent((Component*) boundingBox);

    BoundingSphere* boundingSphere = new BoundingSphere();
    AddComponent((Component*) boundingSphere);
}

void Node::AddComponent(Component * component){
    component->node = this;
    component->Start();
    components.push_back(component);
    componentMap.insert(pair<int, string>(components.size() - 1, component->name));
}

Component* Node::GetComponent(string name){
	for(componentMapIterator = componentMap.begin(); componentMapIterator != componentMap.end(); ++componentMapIterator) {
		if((*componentMapIterator).second == name){
            return components[(*componentMapIterator).first];
        }
	}
    return NULL;
}

void Node::Print(){
	printf("===========\nNode:\n");
	transform.Print();
	printf("===========\n");
}

void Node::AddModel(Model* m){
    DrawModel* drawModel = new DrawModel();
    drawModel->model = m;
    AddComponent((Component*) drawModel);

   // ((AxisAlignedBoundingBox*)GetComponent("AxisAlignedBoundingBox"))->SetModel(m);
    ((BoundingBox*)GetComponent("BoundingBox"))->ReadModel(m);
   // ((BoundingSphere*)GetComponent("BoundingSphere"))->ReadModel(m);
}

void Node::Update(){
	// Todo: Update recalculates the matrix, but the only case that isn't done
	// on a change is if a parent is updated, the child isn't.
	// We can do better than updating everything everytime
	if(parent != NULL){
		transform.RecalculateMatrix();
	}

	for(componentsIterator = components.begin(); componentsIterator != components.end(); ++componentsIterator) {
		(*componentsIterator)->Update();
	}
}

float Node::DistanceFromCamera(){
	Vector3 cameraPosition;
	cameraPosition.x =  Futz::Instance()->camera.transform.values[12];
	cameraPosition.y =  Futz::Instance()->camera.transform.values[13];
	cameraPosition.z =  Futz::Instance()->camera.transform.values[14];
	return (cameraPosition - transform.position).Length();
}

void Node::Draw(){
    Futz::Instance()->renderer->StartTransform(transform.matrix.values);
	for(std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it) {
		(*it)->DrawLocal();
	}
    Futz::Instance()->renderer->EndTransform();
	for(std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it) {
		(*it)->Draw();
	}
}

Node::~Node(){
    // TODO: Destroy components!
}
