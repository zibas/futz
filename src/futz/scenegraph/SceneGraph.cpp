#include "../Futz.h"
#include "../scenegraph/SceneGraph.h"
#include "../core/Node.h"
#include "../core/components/DrawModel.h"
#include <algorithm>
#include <stdio.h>
#include <map>


using namespace std;
SceneGraph::SceneGraph(){
	nodeIndex = 0;
	lastPolyCount = 0;
}

void SceneGraph::AddNode(Node* node){
	nodes.insert(pair<int,Node*>(nodeIndex,node));
	nodeIndex++;
	if(node->transparent){
		sortedTransparencies.push_back(node);
	}
}

void SceneGraph::Print(){
	printf("===========\nSceneGraph:\n");
	printf("Node count:\t%d\n", nodes.size());
	printf("===========\n");
}

bool futz_distance_sort_nodes(Node* a, Node* b){ return a->DistanceFromCamera() > b->DistanceFromCamera();}

void SceneGraph::Update(){
	map<int,Node*>::iterator node;
	node=nodes.begin();
	for ( node=nodes.begin() ; node != nodes.end(); node++ ){
		if((*node).second->enabled){
			(*node).second->Update();
		}
	}


	//Todo: alpha sorting on a separate thread
	sort(sortedTransparencies.begin(), sortedTransparencies.end(), futz_distance_sort_nodes);
}

void SceneGraph::FrustumCulling(){
	map<int,Node*>::iterator node;
	node=nodes.begin();
	for ( node=nodes.begin() ; node != nodes.end(); node++ ){
		if((*node).second->enabled){

		//	((BoundingBox*)(*node)->GetComponent("BoundingBox"))->model->PolyCount();
		}
	}

}

void SceneGraph::Render(){
    Futz* futz = Futz::Instance();
	lastPolyCount = 0;
    futz->profiler.Start("Render Opaque");
	lastPolyCount += RenderOpaqueNodes();
    futz->profiler.End();
    futz->profiler.Start("Render Transparent");
	lastPolyCount += RenderTransparentNodes();
    futz->profiler.End();

}

int SceneGraph::RenderTransparentNodes(){
	vector<Node*>::iterator node;
	int polyCount = 0;
	for ( node=sortedTransparencies.begin() ; node != sortedTransparencies.end(); node++ ){
		if((*node)->enabled){
			if(!(*node)->useLighting){
				Futz::Instance()->renderer->DisableLighting();
			}
			(*node)->Draw();
			if(!(*node)->useLighting){
				Futz::Instance()->renderer->EnableLighting();
			}
            //TODO: could be more efficient than using GetComponent
			polyCount += ((DrawModel*)(*node)->GetComponent("DrawModel"))->model->PolyCount();
		}
	}
	return polyCount;
}

int SceneGraph::RenderOpaqueNodes(){
	map<int,Node*>::iterator node;
	node=nodes.begin();
	int polyCount = 0;
    DrawModel* drawModel;
	for ( node=nodes.begin() ; node != nodes.end(); node++ ){
		if((*node).second->enabled && !(*node).second->transparent){
			if(!(*node).second->useLighting){
				Futz::Instance()->renderer->DisableLighting();
			}
			(*node).second->Draw();
			if(!(*node).second->useLighting){
				Futz::Instance()->renderer->EnableLighting();
			}
            //TODO: could be more efficient than using GetComponent
            drawModel = (DrawModel*)((*node).second)->GetComponent("DrawModel");

            if(drawModel != NULL){
			    polyCount += drawModel->model->PolyCount();
            }
		}
	}
	return polyCount;
}

int SceneGraph::NodeCount(){
	return nodeIndex;
}

int SceneGraph::PolyCount(){
	return lastPolyCount;
}

SceneGraph::~SceneGraph(){

}
