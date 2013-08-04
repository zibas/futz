#include <cstring>
#include <sstream>
#include <iostream>
#include <string>
#include "Model.h"
#include "../Futz.h"

Model::Model(string name) {
	filename = name;
	size_t found;
	found = filename.find_last_of("/\\");
	path = filename.substr(0,found+1);
}

void Model::Statistics(){
	stringstream ss;
	ss << "Model loaded: "+filename +
		"\n\tTriangles: " << triangles.size() <<
		"\n\tVertices: " << vertices.size() <<
		"\n\tNormals: " << normals.size() <<
		"\n\tTexture Coordinates: " << textureCoords.size() <<
		"\n\tMaterials: " << materials.size() <<
		"\n\tIndex Length: " << indexLength;
	Futz::Log(ss.str());


/*

	for(std::vector<Vector3>::iterator it = vertices.begin(); it != vertices.end(); ++it) {
		//(*it).Print();
	}

	for (int i = 0; i < vertices.size() * 3;  i += 3) {
		//printf("Vertex Array %d: %g, %g, %g\n",i,vertexArray[i],vertexArray[i+1],vertexArray[i+2]);
	}
*/	
}


void Model::ConvertTrianglesToBuffers(){
	vertexArray = new float[triangles.size() * 9];
	indexArray = new unsigned short[triangles.size() * 3];
	colorArray = new float[triangles.size() * 3 * 4];
	normalArray = new float[triangles.size() * 9];
	textureCoordsArray = new float[triangles.size() * 3 * 2];

	indexLength = 0;

	int submeshVertexCount = 0;
	string currentMaterialName = triangles[0].materialName;
	for (int i = 0; i < triangles.size(); i++) {
		Triangle t = triangles[i];

		if(currentMaterialName != t.materialName && 
	 	(materials[t.materialName].textureIndex != materials[currentMaterialName].textureIndex)  ){
			vertexGroups.push_back(pair<Material*, int>(&materials[t.materialName],submeshVertexCount));
			cout << "Pushing " << currentMaterialName << endl;
			submeshVertexCount = 0;
			currentMaterialName = t.materialName;
		}

		int j = i * 9;

		vertexArray[j] = vertices[t.v1].x; j++;
		vertexArray[j] = vertices[t.v1].y; j++;
		vertexArray[j] = vertices[t.v1].z; j++;
		vertexArray[j] = vertices[t.v2].x; j++;
		vertexArray[j] = vertices[t.v2].y; j++;
		vertexArray[j] = vertices[t.v2].z; j++;
		vertexArray[j] = vertices[t.v3].x; j++;
		vertexArray[j] = vertices[t.v3].y; j++;
		vertexArray[j] = vertices[t.v3].z; j++;

		submeshVertexCount += 3;
		

		j = i * 9;
		normalArray[j] = normals[t.n1].x; j++;
		normalArray[j] = normals[t.n1].y; j++;
		normalArray[j] = normals[t.n1].z; j++;
		normalArray[j] = normals[t.n2].x; j++;
		normalArray[j] = normals[t.n2].y; j++;
		normalArray[j] = normals[t.n2].z; j++;
		normalArray[j] = normals[t.n3].x; j++;
		normalArray[j] = normals[t.n3].y; j++;
		normalArray[j] = normals[t.n3].z; j++;

		j = i * 3;
		indexArray[j] = j; j++;
		indexArray[j] = j; j++;
		indexArray[j] = j; j++;
		indexLength += 3;

		
		j = i * 6;
		if(materials[currentMaterialName].hasTexture){
			textureCoordsArray[j] = textureCoords[t.tex1].x; j++;
			textureCoordsArray[j] = textureCoords[t.tex1].y; j++;
			textureCoordsArray[j] = textureCoords[t.tex2].x; j++;
			textureCoordsArray[j] = textureCoords[t.tex2].y; j++;
			textureCoordsArray[j] = textureCoords[t.tex3].x; j++;
			textureCoordsArray[j] = textureCoords[t.tex3].y; j++;
		} else {

			textureCoordsArray[j] = 0; j++;
			textureCoordsArray[j] = 0; j++;
			textureCoordsArray[j] = 0; j++;
			textureCoordsArray[j] = 0; j++;
			textureCoordsArray[j] = 0; j++;
			textureCoordsArray[j] = 0; j++;
		}

		j = i * 3 * 4;
		colorArray[j] = t.rgba[0]; j++;
		colorArray[j] = t.rgba[1]; j++;
		colorArray[j] = t.rgba[2]; j++;
		colorArray[j] = t.rgba[3]; j++;

		colorArray[j] = t.rgba[0]; j++;
		colorArray[j] = t.rgba[1]; j++;
		colorArray[j] = t.rgba[2]; j++;
		colorArray[j] = t.rgba[3]; j++;

		colorArray[j] = t.rgba[0]; j++;
		colorArray[j] = t.rgba[1]; j++;
		colorArray[j] = t.rgba[2]; j++;
		colorArray[j] = t.rgba[3]; j++;
	}

	if(submeshVertexCount > 0){
		vertexGroups.push_back(pair<Material*, int>(&materials[currentMaterialName],submeshVertexCount));
		submeshVertexCount = 0;
	} 
}


void Model::LoadTexturesForMaterials(){
	map<string,Material>::iterator pair;
	int i = 0;
	for ( pair=materials.begin() ; pair != materials.end(); pair++ ){
		if((*pair).second.hasTexture){
			LoadImage((*pair).second.textureFilename, i);
			materials[(*pair).first].textureIndex = i;
			i++;
		}
	}

}
void Model::LoadImage(string filename, int textureIndex){
	Futz::Instance()->renderer->LoadImage(this, filename, textureIndex);
}

int Model::PolyCount(){
	return triangles.size(); 
}

void Model::Load() {

}

Model::~Model() {
//	free(vertexArray);
}
