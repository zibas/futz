#ifndef SCENEGRAPH_H_
#define SCENEGRAPH_H_

#include "../core/Node.h"
#include <map>
using namespace std;
class SceneGraph {
	private:
		int nodeIndex;
		int lastPolyCount;
		map<int, Node*> nodes;
		
		int RenderOpaqueNodes();
		int RenderTransparentNodes();

		vector<Node*> sortedTransparencies;
        void FrustumCulling();

	public:
		SceneGraph();
		void Print();
		void AddNode(Node* node);
		void Update();
		void Render();
		int NodeCount();
		int PolyCount();
		virtual ~SceneGraph();
		

};

#endif
