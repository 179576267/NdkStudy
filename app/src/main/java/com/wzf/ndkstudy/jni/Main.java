package com.wzf.ndkstudy.jni;

/**
 * @Description:
 * @author: wangzhenfei
 * @date: 2017-06-26 18:05
 */

public class Main {
    public static void main(String[] args) {
        HelloJNI jni = new HelloJNI();
        /**
         * 调用c方法
         */
//        jni.sayHello();  // invoke the native method
//        System.out.println(jni.sayHelloString());  // invoke the native method
//        System.out.println(jni.getStringFromC2("wo shi java lai de "));  // invoke the native method
        /**
         * 修改非静态字段
         */
        System.out.println("key修改前：" + jni.key);
        System.out.println( jni.changeKey());
        System.out.println("key修改后: " + jni.key);
    }
}
