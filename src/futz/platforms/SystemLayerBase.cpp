/*
 * abstractionBase.cpp
 *
 *  Created on: Nov 3, 2010
 *      Author: ziba
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#ifdef _WIN32
#include <Windows.h>
#endif
#ifdef OSX
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
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
#include <GL/glu.h>
#endif
#include "../Futz.h"
#ifndef DREAMCAST
#include "../3rdParty/stb_image.h"
#endif
#include "SystemLayerBase.h"

SystemLayerBase::SystemLayerBase(){
	isFullscreen = false;
	width = 800;
	height = 600;
}

void SystemLayerBase::Resize(int width, int height){
}

string SystemLayerBase::Readfile(string filename){
	
	filename = ResolveFilename(filename);
	
	string outString = "";
	ifstream is;
	char c;
	
	is.open(filename.c_str(), ios::in);

	
	while (is.good())
	{
		c = is.get();
		if (is.good()){
			outString += c;
		}
	}
	is.close();
	return outString;
}



unsigned char* SystemLayerBase::LoadImage(string filename, int *x, int *y){
	filename = ResolveFilename(filename);
    int n;
#ifndef DREAMCAST
    unsigned char* data = stbi_load(filename.c_str(), x, y, &n, 4);
	
    if(data == NULL){
	Futz::Log("Error loading: "+filename + " - null");
    }

    stringstream ss;
    ss << "Image loaded: "+filename +
	    "\n\tXxY: " << *x << "x" << *y << "\nComponents: "<<n<<endl;
    Futz::Log(ss.str());

    return data;
#else
	return NULL;
#endif
	
//    stbi_image_free(data)
}
