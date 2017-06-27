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
