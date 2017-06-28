package com.wzf.ndkstudy;

import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.ImageView;
import android.widget.Toast;

import com.wzf.ndkstudy.jni.AndroidNdkUtils;

import java.io.File;
import java.io.IOException;

import butterknife.Bind;
import butterknife.ButterKnife;
import butterknife.OnClick;

public class MainActivity extends AppCompatActivity {
    final String ROOT  = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separator;
    final String createFileName = "image_create.jpg";
    final String encodeFileName = "image_encode.jpg";
    final String decodeFileName = "image_decode.jpg";
    @Bind(R.id.im)
    ImageView im;

    AndroidNdkUtils ndkUtils;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ButterKnife.bind(this);
        ndkUtils = new AndroidNdkUtils();
    }

    @OnClick({R.id.btn_create, R.id.btn_encode, R.id.btn_decode})
    public void onClick(View view) {
        switch (view.getId()) {
            case R.id.btn_create:
                try {
                    Utils.saveToSD(Utils.myShot(this), ROOT, createFileName);
                    im.setImageBitmap(BitmapFactory.decodeFile(ROOT + createFileName));
                } catch (IOException e) {
                    e.printStackTrace();
                    Toast.makeText(this, "保存文件失败", Toast.LENGTH_SHORT).show();
                }
                break;
            case R.id.btn_encode:
                ndkUtils.encodeFile(ROOT + createFileName, ROOT + encodeFileName);
                im.setImageBitmap(BitmapFactory.decodeFile(ROOT + encodeFileName));
                break;
            case R.id.btn_decode:
                ndkUtils.decodeFile(ROOT + encodeFileName, ROOT + decodeFileName);
                im.setImageBitmap(BitmapFactory.decodeFile(ROOT + decodeFileName));
                break;
        }
    }
}
