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

    /**
     * 文件的加解密
     */
    public  native void encodeFile(String src, String des);
    public  native void decodeFile(String src, String des);

    /**
     * 文件的分割和合并
     */
    public  native void spliceFile(String src, String desStartName, int count);
    public  native void mergeFile(String srcStartName, int count, String des);
}
