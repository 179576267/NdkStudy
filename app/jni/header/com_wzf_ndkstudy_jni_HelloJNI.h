/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_wzf_ndkstudy_jni_HelloJNI */

#ifndef _Included_com_wzf_ndkstudy_jni_HelloJNI
#define _Included_com_wzf_ndkstudy_jni_HelloJNI
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_wzf_ndkstudy_jni_HelloJNI
 * Method:    sayHello
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_wzf_ndkstudy_jni_HelloJNI_sayHello
  (JNIEnv *, jobject);

/*
 * Class:     com_wzf_ndkstudy_jni_HelloJNI
 * Method:    sayHelloString
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_wzf_ndkstudy_jni_HelloJNI_sayHelloString
  (JNIEnv *, jobject);

/*
 * Class:     com_wzf_ndkstudy_jni_HelloJNI
 * Method:    getStringFromC2
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_wzf_ndkstudy_jni_HelloJNI_getStringFromC2
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_wzf_ndkstudy_jni_HelloJNI
 * Method:    changeKey
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_wzf_ndkstudy_jni_HelloJNI_changeKey
  (JNIEnv *, jobject);

/*
 * Class:     com_wzf_ndkstudy_jni_HelloJNI
 * Method:    runJavaMethod
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_wzf_ndkstudy_jni_HelloJNI_runJavaMethod
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
