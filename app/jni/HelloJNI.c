#include<jni.h>
#include <stdio.h>
#include "header/com_wzf_ndkstudy_jni_HelloJNI.h"
#include "header/log.h"
#include <string.h>

JNIEXPORT void JNICALL Java_com_wzf_ndkstudy_jni_HelloJNI_sayHello(JNIEnv *env, jobject thisObj) {
   LOG_I("%s  %d\n", "大小为：", 200);
   return;
}

JNIEXPORT jstring JNICALL Java_com_wzf_ndkstudy_jni_HelloJNI_sayHelloString(JNIEnv *env, jobject thisObj) {
   return (*env)->NewStringUTF(env, "Java_com_wzf_jni_HelloJNI_sayHelloString");
}

JNIEXPORT jstring JNICALL Java_com_wzf_ndkstudy_jni_HelloJNI_getStringFromC2(JNIEnv *env, jclass jcls, jstring str){
   return (*env)->NewStringUTF(env, "C STRING 2");
}

//修改非静态属性key
JNIEXPORT jstring JNICALL Java_com_wzf_ndkstudy_jni_HelloJNI_changeKey(JNIEnv *env, jobject thisObj){
   //jfieldID    (*GetFieldID)(JNIEnv*, jclass, const char*, const char*);
   //获取jclass
   jclass cls = (*env)->GetObjectClass(env, thisObj);
   //属性名称和属性签名   签名和属性类型有关,有配置表
   jfieldID fid = (*env)->GetFieldID(env, cls, "key", "Ljava/lang/String;");
   // i am in java ->> i am in java but  modify in c
   //获取key的值
   jstring  jstr = (*env)->GetObjectField(env, thisObj, fid);
   //jstring -->c字符串
   //第三个参数 isCopy
   //jstr 是java里的字符串， 当JNI_TRUE时候，c_str就是拷贝的字符串
                              //当为JNI_FALSE, c_str就是原来的字符串，地址相同
   jboolean boolean = JNI_TRUE;
   char *c_str = (*env)->GetStringUTFChars(env, jstr, &boolean);

   //c的字符串转成jstring
   char text[50];
   strcpy(text, c_str);
   strcat(text," but  modify in c");
   jstring  new_jstr = (*env)->NewStringUTF(env, text);
   //修改key
   (*env)->SetObjectField(env, thisObj, fid, new_jstr);
   return new_jstr;

}

//调用java方法
JNIEXPORT void JNICALL Java_com_wzf_ndkstudy_jni_HelloJNI_runJavaMethod(JNIEnv *env, jobject jObj){
   //获取jclass
   jclass cls = (*env)->GetObjectClass(env, jObj);
   //非静态方法调用
   jmethodID  methodId = (*env)->GetMethodID(env, cls, "callByC", "(I)Ljava/lang/String;");
   if(methodId == NULL){
      LOG_E("%s\n", "method not find");
      return;
   }
   //调用
   jint num = 10;
   jobject  str = (*env)->CallObjectMethod(env, jObj, methodId, num);
   char *retString = (*env)->GetStringUTFChars(env, str, NULL);
   LOG_I("return value is : %s\n", retString);

   //静态方法调用
   jmethodID  smethodId = (*env)->GetStaticMethodID(env, cls, "callStaticByC", "(I)Ljava/lang/String;");
   if(smethodId == NULL){
      LOG_E("%s\n", "smethodId not find");
      return;
   }
   //调用
   str = (*env)->CallStaticObjectMethod(env, cls, smethodId, num);
   retString = (*env)->GetStringUTFChars(env, str, NULL);
   LOG_I("static method return value is : %s\n", retString);

}

//访问构造方法 <init>
//使用java.util.Date产生一个当前的时间戳
JNIEXPORT jobject JNICALL Java_com_wzf_ndkstudy_jni_HelloJNI_callConstructor(JNIEnv *env, jobject jObj){
   jclass cls = (*env)->FindClass(env, "java/util/Date");
   jmethodID  mid = (*env)->GetMethodID(env, cls, "<init>", "()V");
   //实例化一个对象
   jobject  date_obj = (*env)->NewObject(env, cls, mid);
   //获取getTime方法id
   jmethodID  getTimeId = (*env)->GetMethodID(env, cls, "getTime", "()J");
   //调用getTime方法
   jlong  time = (*env)->CallLongMethod(env, date_obj, getTimeId);
   LOG_I("时间戳为：%lld\n", time);
   return date_obj;
}

//访问父类方法 java引用调用重写了的父类方法不行， 可以通过c来调用
JNIEXPORT jobject JNICALL Java_com_wzf_ndkstudy_jni_HelloJNI_callParentMethod(JNIEnv *env, jobject jObj){
   jclass cls = (*env)->GetObjectClass(env, jObj);
   //获取testClass 字段
   jfieldID  fid = (*env)->GetFieldID(env, cls, "testClass", "Lcom/wzf/ndkstudy/model/Parent;");
   //获取字段的对象
   jobject  fid_obj = (*env)->GetObjectField(env, jObj, fid);
   //获取相应的方法
   jmethodID mid = (*env)->GetMethodID(env,cls, "printFormParent", "(I)Ljava/lang/String");
   //执行方法
   jobject result = (*env)->CallObjectMethod(env, jObj, mid, 123);

   char * retString = (*env)->GetStringUTFChars(env, result, NULL);
   LOG_I("method result : %s\n", retString);
}
