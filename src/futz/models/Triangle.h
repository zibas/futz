#ifndef TRIANGLE_H 
#define TRIANGLE_H 
#include <string>
#include "../math/Vector3.h"
using namespace std;
class Triangle {
	public:
		int v1, v2, v3;
		int n1, n2, n3;
		int tex1, tex2, tex3;

		int textureIndex;

		string materialName;
		float rgba[4];

		Triangle();
		void Print();
};
#endif
