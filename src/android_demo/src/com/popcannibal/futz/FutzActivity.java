package com.popcannibal.futz;

//import android.R;
import android.app.Activity;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.MotionEvent;

import com.popcannibal.futz.demo.*;

public class FutzActivity extends Activity {

	private GLSurfaceView mView;

    @Override protected void onCreate(Bundle icicle) {
        super.onCreate(icicle);
        this.setContentView(R.layout.futz);
        mView = (GLSurfaceView) findViewById(R.id.glsurfaceview);
        mView.setRenderer(new FutzRenderer(this));
    }

    @Override protected void onPause() {
        super.onPause();
        mView.onPause();
    }

    @Override protected void onResume() {
        super.onResume();
        mView.onResume();
    }
    
    @Override public boolean onTrackballEvent(MotionEvent event) {    	
        if(event.getX() > 0f){
    		Futz.PushKey('w');
        }
        else if(event.getX() < 0f){
    		Futz.PushKey('s');
        }
    	return true;             
    }
    
    @Override public boolean onTouchEvent(MotionEvent event) {
		Futz.PushMouse((int)event.getX(), (int)event.getY());
    	return true;             
    }
}
