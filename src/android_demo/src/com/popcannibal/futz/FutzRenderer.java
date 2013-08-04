package com.popcannibal.futz;


import java.io.IOException;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import com.popcannibal.futz.demo.Demo;


import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.content.res.AssetFileDescriptor;
import android.content.res.AssetManager;
import android.opengl.GLSurfaceView;
import android.util.Log;


public class FutzRenderer implements GLSurfaceView.Renderer {

	
	public FutzActivity activity;
		
	static AssetManager assetManager;
	 
	private boolean hasStarted = false;
	
    public FutzRenderer(FutzActivity activity) {
    	this.activity = activity;
    	// Can't start Futz here because there's no gl context
    }

	public void onDrawFrame(GL10 gl) {
		
	
        Futz.Update();
        Futz.Render();
	}

	public void onSurfaceChanged(GL10 gl, int width, int height) {
		Futz.Resize(width, height);
	}

	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		if(!hasStarted){			     
           // Need to hold on to a reference so it doesn't
           // get garbage collected while in use by the ndk
           assetManager = activity.getAssets();
           Futz.Initialize();
           Demo.Initialize(assetManager);
           hasStarted = true;
		}  else {
			Futz.Resize(0,0);
		}
	}
   
}

