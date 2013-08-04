#ifndef WAVEFRONTMODEL_H_ 
#define WAVEFRONTMODEL_H_ 
#include <fstream>
#include <string>
#include "../Model.h"
using namespace std;
class WavefrontModel: public Model {

public:
	WavefrontModel(string filename):Model(filename){};
	void Load();
	void LoadMaterials(string filename);
	bool ParseFile(istream &modelFile);
	bool ParseMaterialsFile(istream &materialsFile);
	Vector3 LineToVector(string line);
};
#endif
