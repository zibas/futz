#include <iostream>
using namespace std;

#include <stdlib.h>
#include <stdio.h>
#include <jni.h>

#include <sys/types.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>  

#include "Futz.h"
#include "Demo.h"
#include "GameBase.h"

extern "C" {
JNIEXPORT void JNICALL Java_com_popcannibal_futz_demo_Demo_Initialize(JNIEnv * env, jclass clazz, jobject obj);
};

JNIEXPORT void JNICALL Java_com_popcannibal_futz_demo_Demo_Initialize(JNIEnv * env, jclass clazz, jobject obj){
	char** tmp;

	// This will both initialize and retrive the futz singleton
	Futz* futz = Futz::Instance();
	Futz::Log("Initializing Android.cpp");

	Demo* game = new Demo();
	Futz::Log("created game");
	futz->gameObject = game;
	Futz::Log("set game object");

	Futz::Log("Set AssetManager");
	Futz::Instance()->platform->assetManager =  AAssetManager_fromJava(env, obj);
	if(Futz::Instance()->platform->assetManager == NULL){
		Futz::Log("Assetmanager == NULL");
	}

	futz->Start(1, tmp);

};
