package com.wzf.ndkstudy;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tvC = (TextView) findViewById(R.id.sample_text_c);
        tvC.setText(add(10, 11) + "");
        TextView tvCpp = (TextView) findViewById(R.id.sample_text_cpp);
        tvCpp.setText(stringFromJNIFromCpp());
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNIFromCpp();
    public native String stringFromJNIFromC();
    public native int add(int a, int b);

}
