#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <stdio.h>

using namespace std;

class Material{
public:
	float rgba[4];
	string textureFilename;
	bool hasTexture;
	int textureIndex;
	Material();
};
#endif /* MATERIAL_H_ */
