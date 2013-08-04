package com.popcannibal.futz;

import android.content.res.AssetManager;

//Wrapper for native library
public class Futz {

     static {
         System.loadLibrary("futz");
     }

     public static native void Initialize();

     public static native void Start();
     public static native void Resize(int width, int height);
     public static native void Update();
     public static native void Render();
    // public static native void SetAssetManager(AssetManager mgr);
     public static native void PushMouse(int x, int y);
     public static native void PushKey(char c);

}
