package com.garena.game.myapplication;

import android.util.Log;

public class CallJava {
    static {
        System.loadLibrary("hello_jni");
    }
    private static final String TAG = "CallJava";

    public native void callVoidMethod();

    public void hello() {
        Log.i(TAG, "Java的hello方法");
    }
}
