
#include "FutzIOS.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stdio.h>
#include "../Futz.h"

#import <UIKit/UIKit.h>
#include "../3rdParty/stb_image.h"

void FutzIOS::Initialize(int argc, char** argv){
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	
	stbi_convert_iphone_png_to_rgb(1);
	Futz::Log("Initializing IOS Layer");
	
	int retVal = UIApplicationMain(argc, argv, nil, nil);
    [pool release];
    //return retVal;
}

void FutzIOS::PostUIInit(){
	Futz::Log("Post UI Init");
	//this->InitOpenGL(100,100);
    Futz::Instance()->renderer->Initialize(100, 100);
	Futz::Instance()->gameObject->Start();
	glMatrixMode(GL_PROJECTION);                                                                                                                         
	glLoadIdentity();              
	float ratio = 320.0f/480.0f;
	glFrustumf(-ratio, ratio, -1, 1, 1, 500);
	
	GLenum error=glGetError ();
	while (error!=GL_NO_ERROR)
		error=glGetError ();
}

FutzIOS::FutzIOS() {

}

string FutzIOS::ResolveFilename(string filename){
	size_t found;
	found = filename.find_last_of("/\\");
	string fileOnly = filename.substr(found+1, filename.length() - 5 - found);
	found = filename.find_last_of(".");
	string extension = filename.substr(found+1, 3);

	CFStringRef fileString = (CFStringRef)[[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String: fileOnly.c_str()] ofType:[NSString stringWithUTF8String: extension.c_str()]];
    
    CFStringEncoding encodingMethod;
    encodingMethod = CFStringGetSystemEncoding();

    
    NSString* fileNSString = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String: fileOnly.c_str()] ofType:[NSString stringWithUTF8String: extension.c_str()]];
    
    const char* temp = [fileNSString cStringUsingEncoding:NSASCIIStringEncoding];
    filename = temp;
    
   //const char* temp = CFStringGetCStringPtr(fileString, encodingMethod);
   // filename = (char*)CFStringGetCStringPtr(fileString, encodingMethod);
    //if( filename == NULL )
   // {
   //     encodingMethod = kCFStringEncodingUTF8;
   //     filename = (char*)CFStringGetCStringPtr(fileString, encodingMethod);
   // }

	//filename = CFStringGetCStringPtr(fileString, kCFStringEncodingMacRoman);
	Futz::Log("Converted filename to: "+filename);
	
    
    
	return filename;
}