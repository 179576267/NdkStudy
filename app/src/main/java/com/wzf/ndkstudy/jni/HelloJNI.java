package com.wzf.ndkstudy.jni;

public class HelloJNI {
    //通过c修改
    public String key = "i am in java";
    static {
        System.loadLibrary("HelloJNI");
    }

    public static String callStaticByC(int num){
        System.out.println("callStaticByC: " + num);
        return "callStaticByC: " + num;
    }

    private String callByC(int num){
        System.out.println("callByC: " + num);
        return "callByC: " + num;
    }



    public native void sayHello();
    public native String sayHelloString();
    public native static String getStringFromC2(String str);
    //访问属性，返回修改之后的属性内容
    public native String changeKey();
    //访问方法
    public native void  runJavaMethod();
}
