#include <jni.h>


jstring
Java_com_wzf_ndkstudy_MainActivity_stringFromJNIFromC(JNIEnv* env,
                                                    jobject thiz ) {

    return (*env)->NewStringUTF(env, "Hello from JNI !  Compiled with ABI ");
}

JNIEXPORT jint JNICALL
Java_com_wzf_ndkstudy_MainActivity_add(JNIEnv *env, jobject instance, jint a, jint b) {

    // TODO

    return a + b;
}

JNIEXPORT jstring JNICALL
Java_com_wzf_ndkstudy_jni_NativeClass_getStringFromC(JNIEnv *env, jclass type) {


    return (*env)->NewStringUTF(env, "hahah");
}

JNIEXPORT void JNICALL
Java_com_wzf_ndkstudy_jni_HelloJNI_getStringFromC(JNIEnv *env, jobject instance) {

    // TODO

}