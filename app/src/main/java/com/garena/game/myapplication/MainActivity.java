package com.garena.game.myapplication;


import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import com.garena.game.myapplication.databinding.ActivityMainBinding;

import java.util.Arrays;
import java.util.Random;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'myapplication' library on application startup.
    static {
        System.loadLibrary("hello_jni");
    }

    private ActivityMainBinding binding;
    private static final String TAG = "Hello_JNI";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.sampleText;
        tv.setText(getStringFromC("hello c"));

        tv.setOnClickListener(v -> {
            Random random = new Random(5);
            int[] a = new int[3];
            for (int i = 0; i < 3; i++) {
                a[i] = random.nextInt(9);
            }
            Log.d(TAG, Arrays.toString(a));
            testArray(a);
        });

    }


    /**
     * A native method that is implemented by the 'myapplication' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native String getStringFromC(String str);

    public native void testArray(int[] testArray);


}