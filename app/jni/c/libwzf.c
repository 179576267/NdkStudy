#include <jni.h>
#include<stdio.h>
#include<stdlib.h>
#include "../header/log.h"

char pwd[] = "wangzhenfei";

JNIEXPORT void JNICALL
Java_com_wzf_ndkstudy_jni_AndroidNdkUtils_encodeFile(JNIEnv *env, jobject instance, jstring src_,
                                                     jstring des_) {
    const char *src = (*env)->GetStringUTFChars(env, src_, 0);
    const char *des = (*env)->GetStringUTFChars(env, des_, 0);
    LOG_I("encodeFilePath: %s\n", src);

    // TODO

    FILE *src_fp = fopen(src, "rb");
    if(src_fp == NULL){
        printf("src error!\n");
        return;
    }
    FILE *des_fp = fopen(des, "wb");

    int ch;
    int i = 0;//循环使用密码中的字符进行异或
    int pwd_len = strlen(pwd);
    printf("++++++++++++++++++++++++++++++++++\n");
    while((ch = fgetc(src_fp)) != EOF){
        printf("%c", pwd[i % pwd_len]);
        fputc(ch ^ pwd[i % pwd_len], des_fp);
        i++;
    }

    fclose(src_fp);
    fclose(des_fp);

    (*env)->ReleaseStringUTFChars(env, src_, src);
    (*env)->ReleaseStringUTFChars(env, des_, des);
}

JNIEXPORT void JNICALL
Java_com_wzf_ndkstudy_jni_AndroidNdkUtils_decodeFile(JNIEnv *env, jobject instance, jstring src_,
                                                     jstring des_) {
    const char *src = (*env)->GetStringUTFChars(env, src_, 0);
    const char *des = (*env)->GetStringUTFChars(env, des_, 0);
    LOG_I("decodeFilePath: %s\n", src);
    // TODO
    FILE *src_fp = fopen(src, "rb");
    if(src_fp == NULL){
        printf("src error!\n");
        return;
    }
    FILE *des_fp = fopen(des, "wb");
    printf("++++++++++++++++++++++++++++++++++\n");
    int ch;
    int i = 0;//循环使用密码中的字符进行异或
    int pwd_len = strlen(pwd);
    while((ch = fgetc(src_fp)) != EOF){
        fputc(ch ^ pwd[i % pwd_len], des_fp);
        i++;
    }

    fclose(src_fp);
    fclose(des_fp);

    (*env)->ReleaseStringUTFChars(env, src_, src);
    (*env)->ReleaseStringUTFChars(env, des_, des);
}