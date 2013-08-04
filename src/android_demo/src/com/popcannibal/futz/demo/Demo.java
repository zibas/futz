package com.popcannibal.futz.demo;

import android.content.res.AssetManager;

public class Demo {
	  static {
	         System.loadLibrary("futzdemo");
	     }

	     public static native void Initialize(AssetManager mgr);
}
