package com.wzf.ndkstudy.model;

/**
 * @Description:
 * @author: wangzhenfei
 * @date: 2017-06-27 18:01
 */

public class Child extends Parent{
    @Override
    public String printFormParent(int age) {
        this.age = age;
        System.out.println("print age from child: " + age);
        return "print age from child: " + age;
    }
}
