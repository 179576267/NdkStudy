package com.wzf.ndkstudy.jni;

import com.wzf.ndkstudy.model.Child;
import com.wzf.ndkstudy.model.Parent;

import java.util.Date;

public class HelloJNI {
    //通过c修改
    public String key = "i am in java";
    static {
        System.loadLibrary("HelloJNI");
    }
    public Parent testClass = new Child();
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
    //c访问java方法
    public native void  runJavaMethod();
    //c访问java构造方法
    public native Date  callConstructor();
    //c访问java父类方法
    public native void  callParentMethod();
}
