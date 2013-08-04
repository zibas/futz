/*
 * abstractionBase.h
 *
 *  Created on: Nov 3, 2010
 *      Author: ziba
 */

#ifndef SYSTEMLAYERBASE_H_
#define SYSTEMLAYERBASE_H_
#include <string>



#ifdef ANDROID
#include <sys/types.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>  
#endif 

using namespace std;

class SystemLayerBase {
public:
	#ifdef ANDROID
	AAssetManager* assetManager;
	#endif

	int width;
	int height;
	bool isFullscreen;

	SystemLayerBase();
	virtual void Initialize(int argc, char** argv){};
	virtual void Resize(int, int);
	virtual void ToggleFullscreen(){};
	virtual ~SystemLayerBase(){};
	virtual string Readfile(string filename);

	virtual unsigned char* LoadImage(string filename, int *x, int *y);
	virtual string ResolveFilename(string filename){return filename;};
};

#endif /* ABSTRACTIONBASE_H_ */
