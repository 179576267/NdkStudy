package com.wzf.ndkstudy.jni;

import com.wzf.ndkstudy.model.Child;
import com.wzf.ndkstudy.model.Parent;

import java.util.Date;

public class HelloJNI {
    //通过c修改
    public String key = "i am in java";
    static {
        System.loadLibrary("HelloJNI");
        initIds();
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

    public void testGlobalRef(){
        createGlobalRef();
        System.out.println(getGlobalRef());
        deleteGlobalRef();
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
    //中文乱码
    public native String  chineseChars(String str);
    //传入数组给C 排序
    public native String[]  giveSortArray(int [] array);
    //局部引用优化
    public native void localRef();
    //全局引用优化
    public native void createGlobalRef();
    public native String getGlobalRef();
    public native void deleteGlobalRef();
    //异常处理
    public native void exception();
    //缓存策略
    public native void jniCache();
    public static native void initIds();//初始化全局变量，一般在loadLibrary后调用
}
