package com.garena.game.myapplication;

import android.os.Bundle;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import com.garena.game.myapplication.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'myapplication' library on application startup.
    static {
        System.loadLibrary("myapplication");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.sampleText;
        tv.setText(getStringFromC("hello c"));


    }


    /**
     * A native method that is implemented by the 'myapplication' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native String getStringFromC(String str);


    public native void OnCameraStart(int cameraId, int previewWidth, int previewHeight, int cameraRotation);


}