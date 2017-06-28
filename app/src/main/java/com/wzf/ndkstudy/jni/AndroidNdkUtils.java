package com.wzf.ndkstudy.jni;

/**
 * @Description:
 * @author: wangzhenfei
 * @date: 2017-06-28 16:20
 */

public class AndroidNdkUtils {
    static {
        System.loadLibrary("wzf");
    }
    public  native void encodeFile(String src, String des);
    public  native void decodeFile(String src, String des);
}
