#ifndef MODEL_H_
#define MODEL_H_
#include <stdio.h>
#include <vector>
#include <map>
#ifdef _WIN32
#include <Windows.h>
#endif

#ifdef OSX
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#elif OPENGLES1
#ifdef IOS
#include <OpenGLES/ES1/gl.h>
#else
#include <GLES/gl.h>
#include <GLES/glext.h>
#endif
#else
#include <GL/gl.h>
#endif
#include "Triangle.h"
#include "Material.h"
#include "../math/Matrix4.h"

using namespace std;
class Model {
protected:


	int indexLength;

	#define MAX_TEXTURES 50

	string filename;
	string path;

	
	void ConvertTrianglesToBuffers();

	
public:
	vector<Triangle> triangles;
	vector<Vector3> vertices;
	vector<Vector3> normals;
	vector<Vector3> textureCoords;

	map<string, Material> materials;
	unsigned char* imageData;
	GLuint textureIDs[MAX_TEXTURES];

	unsigned short* indexArray;

	vector<pair<Material*, int> > vertexGroups;
	float* colorArray;
	float* vertexArray;
	float* normalArray;
	float* textureCoordsArray;

	Model(string);
	virtual void Load();
	virtual void Update(){};
	virtual void Statistics();
	virtual int PolyCount();
	virtual void LoadTexturesForMaterials();
	virtual void LoadImage(string filename, int textureIndex);
	virtual ~Model();
};

#endif /* MODEL_H_ */
