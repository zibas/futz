/*
 * FutzAndroid.h
 *
 *  Created on: Apr 17, 2011
 *      Author: ziba
 */

#ifndef FUTZANDROID_H_
#define FUTZANDROID_H_

#define  LOG_TAG    "libfutz"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#include <android/log.h>
#include <string.h>
#include "SystemLayerBase.h"


class FutzAndroid: public SystemLayerBase {
public:
	

	void Initialize(int argc, char** argv);
	string Readfile(string filename);
	unsigned char* ReadfileRaw(string filename, off_t *length);
	void Resize(int, int);
	unsigned char* LoadImage(string filename, int *x, int *y);
//	virtual ~FutzAndroid();
};

#endif /* FUTZANDROID_H_ */
