package com.wzf.ndkstudy.jni;

import java.util.Date;

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
//        System.out.println("key修改前：" + jni.key);
//        System.out.println( jni.changeKey());
//        System.out.println("key修改后: " + jni.key);

        /**
         * 调用非静态方法
         */
//        jni.runJavaMethod();

        /**
         * 在c中实例化java对象
         */
//        Date date = jni.callConstructor();
//        System.out.println(date.toString());
        /**
         * 访问父类构造方法
         */
//        jni.testClass.printFormParent(20);
//        jni.callParentMethod();
        /**
         * 中文乱码问题
         */
//        System.out.println(jni.chineseChars("我是来自java"));
        /**
         * 传入数组，排序 ,返回数组
         */
//        int arr [] = new int[]{65, 3, 6, 43,2, 67, 1};
//        String sArray[] = jni.giveSortArray(arr);
//        for(Integer integer : arr){
//            System.out.println(integer);
//        }
//
//        for(String s : sArray){
//            System.out.println(s);
//        }
        /**
         * 本地引用和全局引用的回收
         */
//        jni.localRef();
//        jni.testGlobalRef();
        /**
         * c异常处理
//         */
        try {
            jni.exception();
        } catch (Exception e) {
            System.out.println("调用jni 发生异常 ： " + e.toString());
        }catch (Throwable e){
            System.out.println("发生jni原生异常 ： " + e.toString());
        }
//        System.out.println("+++++++++++++++异常之后+++++++++++++++++");
        /**
         * 缓存策略，不断的调用一个native 方法
         */
//        for(int i = 0; i < 100; i++){
//            jni.jniCache();
//        }

    }
}
