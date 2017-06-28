package com.wzf.ndkstudy;

import android.app.Activity;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.os.Environment;
import android.support.annotation.Nullable;
import android.view.View;
import android.widget.ImageView;
import android.widget.Toast;

import com.wzf.ndkstudy.jni.AndroidNdkUtils;

import java.io.File;
import java.io.IOException;

import butterknife.Bind;
import butterknife.ButterKnife;
import butterknife.OnClick;

/**
 * Created by wzf on 2017/6/28.
 */

public class FileSpliceActivity extends Activity {
    final String ROOT  = Environment.getExternalStorageDirectory().getAbsolutePath() + File.separator;
    final String createFileName = "image_create.jpg";
    final int splicePartCount = 3;
    final String spliceFileNameStart = "image_splice";
    final String megrgeFileName = "image_merge.jpg";
    @Bind(R.id.im)
    ImageView im;

    AndroidNdkUtils ndkUtils;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_splice_file);
        ButterKnife.bind(this);
        ndkUtils = new AndroidNdkUtils();
    }

    @OnClick({R.id.btn_create, R.id.btn_splice, R.id.btn_merge})
    public void onViewClicked(View view) {
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
            case R.id.btn_splice:
                ndkUtils.spliceFile(ROOT + createFileName, ROOT + spliceFileNameStart, splicePartCount);
                break;
            case R.id.btn_merge:
                ndkUtils.mergeFile(ROOT + spliceFileNameStart, splicePartCount, ROOT + megrgeFileName);
                break;
        }
    }
}
