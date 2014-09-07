#if FUTZ_PLATFORM_ANDROID
#include <GLES/gl.h>
#include <GLES/glext.h>
#include <jni.h>
#include <sstream>
#include <sys/types.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>  

#include "../Futz.h"
#include "FutzAndroid.h"
#include "../3rdParty/stb_image.h"

#include "GameBase.h"
//#include "demo/Demo.h"

void FutzAndroid::Initialize(int argc, char** argv){
	Futz::Log("Initializing Android abstraction layer");
	//Futz::Instance()->InitWindow(10,10);
	Futz::Instance()->camera->SetViewport(futz->platform->width, futz->platform->height);

	this->InitOpenGL(10,10);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
	Futz::Instance()->gameObject->Start();
}

void FutzAndroid::Resize(int width, int height){
	//Futz::Instance()->InitWindow(width,height);
	this->InitOpenGL(width,height);
	if (height==0)
		height=1;
	glViewport(0, 0, width, height);

        float ratio = (float) width / height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
        glFrustumf(-ratio, ratio, -1, 1, 1, 400);      
	//glMatrixMode(GL_MODELVIEW);
}

unsigned char* FutzAndroid::LoadImage(string filename, int *x, int *y){
    int n;
  //  unsigned char* data = stbi_load(filename.c_str(), x, y, &n, 4);
    off_t len;
    unsigned char* buffer = ReadfileRaw(filename, &len); 
    unsigned char* data = stbi_load_from_memory(buffer, len, x, y, &n, 4);
	
    if(data == NULL){
	Futz::Log("Error loading: "+filename + " - null");
    }

    stringstream ss;
    ss << "Image loaded: "+filename +
	    "\n\tXxY: " << *x << "x" << *y << "\nComponents: "<<n<< "\nLength: "<< len << endl;
    Futz::Log(ss.str());

    return data;
	
//    stbi_image_free(data)
}

unsigned char* FutzAndroid::ReadfileRaw(string filename, off_t *length){
	if(Futz::Instance()->platform->assetManager == NULL){
		Futz::Log("AssetManager is null");
	}
	AAsset* asset = AAssetManager_open(Futz::Instance()->platform->assetManager,filename.c_str(), AASSET_MODE_UNKNOWN);  
	if(asset == NULL){
		Futz::Log("Asset not found " + filename);
	} else {
		Futz::Log("Asset not null");
		off_t start;
		int fd = AAsset_openFileDescriptor(asset, &start, length);
		if(fd <= 0){
			Futz::Log("Asset not directly accessible");
		}

		stringstream ss;
		ss << "fd: "<<fd<<" start: "<<start<<" length: "<<*length;
		Futz::Log(ss.str());

		off_t bufferSize = AAsset_getLength(asset);
		
		stringstream ss2;
		ss2 << "Buffer size: " << bufferSize;
		Futz::Log(ss2.str());
		
		unsigned char* buffer = new unsigned char[bufferSize]; 
		int numBytesRead = AAsset_read(asset, buffer, bufferSize);
		int numBytesRemaining = AAsset_getRemainingLength(asset); 

		AAsset_close(asset);
		return buffer;
	}
	return NULL;
}

string FutzAndroid::Readfile(string filename){
	off_t len;
	return (char*)ReadfileRaw(filename, &len); 
}

extern "C" {
JNIEXPORT void JNICALL Java_com_popcannibal_futz_Futz_Initialize(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_popcannibal_futz_Futz_Start(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_popcannibal_futz_Futz_Update(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_popcannibal_futz_Futz_Render(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_popcannibal_futz_Futz_Resize(JNIEnv * env, jobject obj, int width, int height);
//JNIEXPORT void JNICALL Java_com_popcannibal_futz_Futz_SetAssetManager(JNIEnv * env, jclass clazz, jobject obj);
JNIEXPORT void JNICALL Java_com_popcannibal_futz_Futz_PushMouse(JNIEnv * env, jobject obj, int x, int y);
JNIEXPORT void JNICALL Java_com_popcannibal_futz_Futz_PushKey(JNIEnv * env, jobject obj, char c);
};

JNIEXPORT void JNICALL Java_com_popcannibal_futz_Futz_Initialize(JNIEnv * env, jobject obj){
	Futz::Log("Initizlizing");
};


JNIEXPORT void JNICALL Java_com_popcannibal_futz_Futz_Start(JNIEnv * env, jobject obj){
	char** tmp;
	Futz::Instance()->Start(100,tmp);
};

JNIEXPORT void JNICALL Java_com_popcannibal_futz_Futz_Update(JNIEnv * env, jobject obj){
	Futz::Instance()->Update();
};

JNIEXPORT void JNICALL Java_com_popcannibal_futz_Futz_Render(JNIEnv * env, jobject obj){
	Futz::Instance()->Render();
};

JNIEXPORT void JNICALL Java_com_popcannibal_futz_Futz_Resize(JNIEnv * env, jobject obj, int width, int height){
	Futz::Instance()->platform->Resize(width, height);
};

JNIEXPORT void JNICALL Java_com_popcannibal_futz_Futz_PushMouse(JNIEnv * env, jobject obj, int x, int y){
	Futz::Instance()->inputEventQueue.PushMouse(x, y);
};

JNIEXPORT void JNICALL Java_com_popcannibal_futz_Futz_PushKey(JNIEnv * env, jobject obj, char c){
	Futz::Instance()->inputEventQueue.Push(c);
};

/*
JNIEXPORT void JNICALL Java_com_popcannibal_futz_Futz_SetAssetManager(JNIEnv * env, jclass clazz, jobject obj){
	Futz::Log("Set AssetManager");
	Futz::Instance()->platform->assetManager =  AAssetManager_fromJava(env, obj);
	if(Futz::Instance()->platform->assetManager == NULL){
		Futz::Log("Assetmanager == NULL");
	} else {
		Futz::Log("Assetmanager set");
		Futz* futz = Futz::Instance();
		Demo* game = new Demo();
		futz->gameObject = game;
	}
};
*/
#endif
