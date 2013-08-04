
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include "../../Futz.h"
#include "../../math/Vector3.h"
#include "../Triangle.h"
#include "../Material.h"
#include "WavefrontModel.h"

#ifdef ANDROID
#include <sys/types.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>  
#include "platforms/FutzAndroid.h"
#endif

using namespace std;

void WavefrontModel::Load(){

	stringstream modelFile;
	if(Futz::Instance()->platform == NULL){
		Futz::Log("Abstraction platform is null");
	}
	modelFile << Futz::Instance()->platform->Readfile(filename);
	if(modelFile.good() && (modelFile.str()).length() > 0){
		Futz::Log("Loading wavefront geometry file: "+filename);
		ParseFile(modelFile);
		ConvertTrianglesToBuffers();
		LoadTexturesForMaterials();
		Statistics();
	} else {
		Futz::Log("Couldn't open file: " + Futz::Instance()->platform->ResolveFilename(filename));
	}
}

void WavefrontModel::LoadMaterials(string filenameString){
	size_t found;
	found = filename.find_last_of(".");

	string materialfilename = filename.substr(0,found+1) + "mtl";

	stringstream materialsFile;
	materialsFile << Futz::Instance()->platform->Readfile(materialfilename);
	if(materialsFile.good()){
		Futz::Log("Read "+materialfilename+" for materials");
		ParseMaterialsFile(materialsFile);
	} else {
		Futz::Log("Couldn't open materials file: "+materialfilename);
	}
}

Vector3 WavefrontModel::LineToVector(string line){
	char * pEnd;
	char* cstr = new char [line.size()+1];
	strcpy (cstr, line.c_str());
	pEnd = &cstr[2];
	Vector3 v;
	v.x = (float)strtod(pEnd, &pEnd);
	v.y = (float)strtod(pEnd, &pEnd);
	v.z = (float)strtod(pEnd, NULL);
	delete[] cstr;
	return v;
}

bool WavefrontModel::ParseMaterialsFile(istream &materialsFile){
	string line;
	string currentMaterial;
	bool materialToCommit = false; 

	Material m = Material();

	while ( materialsFile.good() )
	{

		getline (materialsFile,line);
		if(line.compare(0,6,"newmtl") == 0){
			if(materialToCommit){
				materials.insert(pair<string,Material>(currentMaterial,m));
				m = Material();
			}
			currentMaterial.assign(line,7,line.size()-7);
		}
		else if(line.compare(0,3,"Kd ") == 0){
			Vector3 v = LineToVector(line);
			m.rgba[0] = v.x;
			m.rgba[1] = v.y;
			m.rgba[2] = v.z;
			materialToCommit = true;
		}
		else if(line.compare(0,2,"d ") == 0){
			Vector3 v = LineToVector(line);
			m.rgba[3] = v.x;
		}
		else if(line.compare(0,7,"map_Kd ") == 0){
			m.hasTexture = true;
			m.textureFilename = path + line.substr(7);
			//textureFilenames.push_back(path + "/"+line.substr(7));
			materialToCommit = true;
		}
	}
	if(materialToCommit){
		materials.insert(pair<string,Material>(currentMaterial,m));
	}
	return true;
}

bool WavefrontModel::ParseFile(istream &modelFile){
	string line;
	string currentMaterial;
	string materialsFile;
	currentMaterial.clear();


//			materialLengthMap.insert(pair<int,int>(0,6));
//			materialLengthMap.insert(pair<int,int>(1,6));
	while ( modelFile.good() )
	{

		getline (modelFile,line);
		

		if(line.compare(0,6,"mtllib") == 0){
			materialsFile.assign(line,7, line.size()-7);
			LoadMaterials(path +"/"+materialsFile);
		}
		if(line.compare(0,6,"usemtl") == 0){
			currentMaterial.assign(line,7,line.size()-7);
		}
	
		if(line.empty()){
			break;
		}

		switch(line[0]){
			
			case 'v':
				if(line[1] == ' '){
					Vector3 v = LineToVector(line);
					vertices.push_back(v);
				}
				else if(line[1] == 'n'){
					Vector3 v = LineToVector(line);
					normals.push_back(v);
				}
				else if(line[1] == 't'){
					Vector3 v = LineToVector(line);
					v.y = 1 - v.y;
					textureCoords.push_back(v);
				}
				break;
			case 'f':
				Triangle t;
				char* p;
				char* cstr = new char [line.size()+1];
				int pos = 0;
				int prevPos = 2;

				char delim = '/';

				for(int i = 0; i < 3; i++){
					int vertex, texture, normal;
					delim = '/';
					if (string::npos != (pos = line.find_first_of(delim,prevPos)))
					{
						vertex = atoi(line.substr(prevPos, pos - prevPos).c_str());
						prevPos = pos+1;
					}
					if (string::npos != (pos = line.find_first_of(delim,prevPos)))
					{
						texture = atoi(line.substr(prevPos, pos - prevPos).c_str());
						prevPos = pos+1;
					}
					if(i<2){
						if (string::npos != (pos = line.find_first_of(' ',prevPos)))
						{
							normal = atoi(line.substr(prevPos, pos - prevPos).c_str());
							prevPos = pos+1;
						}
					} else {
						if (string::npos != (pos = line.find_last_of('/')))
						{
							normal = atoi(line.substr(pos+1).c_str());
						}
					}
					switch(i){
						case 0:
							t.v1 = vertex - 1;
							t.tex1 = texture - 1;
							t.n1 = normal - 1;
						break;
						case 1:
							t.v2 = vertex - 1;
							t.tex2 = texture - 1;
							t.n2 = normal - 1;
						break;
						case 2:
							t.v3 = vertex - 1;
							t.tex3 = texture - 1;
							t.n3 = normal - 1;
						break;
					}
					//cout << "Vertex: "<< vertex << "\tTexture: "<<texture<<"\tNormal: "<<normal<<endl;
				}

				t.materialName = currentMaterial;
				
				Material m = materials[currentMaterial];
				t.rgba[0] = m.rgba[0];
				t.rgba[1] = m.rgba[1];
				t.rgba[2] = m.rgba[2];
				t.rgba[3] = m.rgba[3];

				t.textureIndex = 0;
				triangles.push_back(t);

				delete[] cstr;
				break;
		}

	}
	return true;
}

